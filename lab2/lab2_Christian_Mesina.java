/*
 * Christian Mesina
 * lab2_Christian_Mesina.java
 * Created on 02/17/2020. Due by 03/14/2020
 * This program creates a game  game board is an N x N grid. Columns are named A, B, C, …. (from left to right), 
 * and rows are named 1, 2, 3, ... (from top to bottom). Each player takes turns as in chess or tic-tac-toe. 
 * That is, player X takes a move, then player O, then back to player X, and so forth. Each square 
 * has a fixed point value between 1 and 99. The objective of the game for each player is to score the most points. 
 * A player’s score is the sum of the point values of his or her occupied squares minus the sum of all point
 * values of the squares occupied by the other player. The game ends when all the squares are occupied by the players
 * since no more moves are left. Also, this program will be implementing the following two algorithms: 
 * standard Minimax algorithm and Alpha-Beta Pruning algorithm.
*/

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class lab2_Christian_Mesina
{
    // Creates a Node class that creates an list of Arrays for the children, the board for the game that takes in rows, columns, score, alpha-beta algorithm, and the best move for the game.
    public static class Node 
    {
        List<Node> children = new ArrayList<>();
	    String[][] Board = new String[lab2_Christian_Mesina.size][lab2_Christian_Mesina.size];
	    
        int row = 0; 
        int col = 0;
        int score = 0; 
        int alpha = 0; 
        int beta = 0;
        String bestmove = "";
	
        // Returns the list of child nodes when the function is called
        public List<Node> getChildren()
	    {
		    return children;
	    }

        // This function sets the board to read the values of the rows and columnns using a two-dimensional array 
        public void setBoard(String board[][]) 
	    {
		    for (int i = 0; i < lab2_Christian_Mesina.size; i++)
		    {
			    for (int j = 0; j < lab2_Christian_Mesina.size; j++)
			    {
				    this.Board[i][j] = board[i][j];
			    }
		    }
	    }
    }

    // Initializes the strings and integers that will be used to be implemented in the game
	static String mode = "", myPlayer = "", myOpponent = "", s = "Stake", r = "Raid";
	static int size = 0, gamescore = 0, counter = 0;
	
    // Start of the main function that takes in an array of strings and arguments
    public static void main(String[] args)
	{
        // Creates an input .txt file and reads each line of that input file
		String file = "input.txt";
		try(BufferedReader in = new BufferedReader(new FileReader(file)))
		{
            // Creates a list of strings in an array where the inputs can be read
			String str = null;
			ArrayList<String> lines = new ArrayList<String>();
			// Creates a trim function that eliminates leading and trailing spaces
            while((str = in.readLine()) != null) 
			{
				lines.add(str.trim());
			}
            
            String[] linesArray = lines.toArray(new String[lines.size()]);
			// Converts the size, mode, player, opponent variables into a string to be read
            size = Integer.parseInt(linesArray[0]);
			mode = linesArray[1];
			myPlayer = linesArray[2];
			myOpponent = myPlayer.equals("X") ? "O" : "X";
            // Converts depth integer into a string and creates a two-dimensional array of the game and board
			int depth = Integer.parseInt(linesArray[3]);
			int game[][] = new int[size][size];
			String boardstate[][] = new String[size][size];

			for (int x = 4; x < size + 4; x++) 
			{
				String splitline[] = linesArray[x].split(" ");
				for (int temp = 0; temp < size; temp++) 
				{
					game[x - 4][temp] = Integer.parseInt(splitline[(temp)]);
				}
			}
			for (int y = (size + 4); y < linesArray.length; y++) 
			{
				char splitline1[] = linesArray[y].toCharArray();
				for (int temp = 0; temp < size; temp++) 
				{
					boardstate[(y - 4 - size)][temp] = splitline1[temp] + "";
				}
			}

         	linesArray=null;
			Node root = new Node();
			root.setBoard(boardstate);
			// This switch statement reads which algorithm to choose/run after reading the string from the input file
            switch(mode.trim())
			{
				case "MINIMAX":
				{
					Node goal = null;
					goal = Max_Value(game, 0, depth, root);
					Output(goal);
					break;
				}
				case "ALPHABETA": 
				{
					Node alpha = new Node();
					Node beta = new Node();
					alpha.score = Integer.MIN_VALUE;
					beta.score = Integer.MAX_VALUE;
					AlphaBeta(game, 0, depth, root, alpha, beta);
					break;
				}
			}
		}
        // This method prints a stack trace for this Throwable object on the standard error output stream
		catch (Exception e)
		{
			e.printStackTrace();
		}
		
	}

    // This function is the implementation of the Alpha-Beta Pruning Algorithm by calling the Prune function
	private static void AlphaBeta(int[][] game, int i, int depth, Node root, Node alpha, Node beta)
	{
		Node goal = Max_Value_Prune(game, 0, depth, root,alpha,beta);
		Output(goal);		
	}

    // This function gets the Max Value by pruning the other unneccesary nodes from the Alpha-Beta algorithm 
	private static Node Max_Value_Prune(int[][] game, int d, int depth, Node node, Node alpha, Node beta) 
	{
        // If the node is at the terminal state, return the node and call the GameScore function
		if(d == depth || terminalState(node))
		{
			 node.score = GameScore(game, node);
			 return node;
		}
		else
		{
			Node v = new Node();
			Node demo = null;
			v.score = Integer.MIN_VALUE;
			List<Node> MaxChildren = generateChild(node,d, game,"max");				
			for(Iterator<Node> iter = MaxChildren.iterator(); iter.hasNext();) 
			{
				counter++;
				demo = iter.next();
				iter.remove();
				Node temp = Min_Value_Prune(game, d + 1, depth, demo, alpha, beta);
				if(temp.score > v.score) 
				{
					v = demo;
					v.score = temp.score;
				}
				temp = null;
				if (v.score >= beta.score)
				{
					return v;
				}
				if (alpha.score < v.score)
				{
					alpha = v;
				}
			}
			return v;
		}
	}
	
    // This function gets the Min Value by pruning the other unneccesary nodes from the Alpha-Beta algorithm 
	private static Node Min_Value_Prune(int[][] game, int d, int depth, Node node, Node alpha, Node beta) 
	{
		if(d == depth || terminalState(node))
		{
			node.score = GameScore(game, node);
			return node;
		}
		else
		{
			Node demo = null;
			Node v = new Node();
          	v.score = Integer.MAX_VALUE;
			List<Node> MaxChildren = generateChild(node, d, game, "min");
			for(Iterator<Node> iter = MaxChildren.iterator(); iter.hasNext(); )
			{
				counter++;
				demo = iter.next();
				iter.remove();
				Node temp = Max_Value_Prune(game, d+1, depth, demo, alpha, beta);
				if (temp.score < v.score) 
				{
					v = demo;
					v.score = temp.score;
				}
				temp = null;
				if(v.score <= alpha.score)
				{
					return v;
				}
				if(beta.score > v.score)
                {
					beta = v;
                }
			}
			return v;
		}
	}

// This function implements the gamescore which computes the difference between the sum of the values of all squares occupied by your player and the sum of the values of all squares occupied by the other player.
	private static int GameScore(int[][] game, Node node)
	{
		int scoreX = 0, scoreO = 0;
		String opponent = myPlayer.equals("X") ? "O" : "X";
		for (int i = 0; i < size; i++) 
        {
		    for (int j = 0; j < size; j++) 
            {
              if(!node.Board[i][j].trim().equals("."))
              {
		    	if(node.Board[i][j].trim().equals(myPlayer))
		    	{
		    		scoreX += game[i][j];
		     	}
		    	else if(node.Board[i][j].trim().equals(opponent))
		    	{	
		    		scoreO += game[i][j];
		       	}
              }                
            }
		}
		return (scoreX - scoreO);
	}

    // This function writes the output of the data that was implemented in the game into a .txt file
	private static void Output(Node goal) 
    {
		try
		{
			String filepath = "output.txt";
			File file1 = new File(filepath);
			if(!file1.exists())
			{
				file1.delete();
			}
			PrintWriter writer = new PrintWriter(new FileOutputStream(filepath));
			String colr = ((char) ('A' + goal.col)) + "";
			writer.println(colr + "" + (goal.row + 1) + " " + goal.bestmove);
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					writer.print(goal.Board[i][j]);
				}
				writer.println();
			}
			writer.close();
		}
		catch (Exception e) 
		{
			System.out.println(counter);
			e.printStackTrace();
		}
	}

// This function implements the Raid function where from any square you occupy on the board, you can take the one next to it (up, down, left, right, but not diagonally) if it is unoccupied. 
    private static void Raid(int[][] game, String currplayer, int i, int j, Node node)
	{
		String opponent = (currplayer.equals("X") ? "O" : "X");
		node.Board[i][j] = currplayer;
		node.row = i;
		node.col = j;
		node.bestmove = r;
		
		if(i > 0)
		{
			if (node.Board[i - 1][j].trim().equals(opponent)) 
			{
				node.Board[i - 1][j] = currplayer;
			}
		}
		if(i < size - 1)
		{
			if (node.Board[i + 1][j].trim().equals(opponent)) 
			{
				node.Board[i + 1][j] = currplayer;
			}
		}
		if(j > 0)
		{
			if (node.Board[i][j - 1].trim().equals(opponent)) 
			{
				node.Board[i][j - 1] = currplayer;
			}
		}
		if(j < size - 1) 
		{
			if (node.Board[i][j + 1].trim().equals(opponent)) 
			{
				node.Board[i][j + 1] = currplayer;
			}
		}
    }

    // This function prints the board along with its current values stored inside it 
	public static void Print(String[][] boardstate) 
    {
        for(int i = 0; i < lab2_Christian_Mesina.size; i++)
		{
			for(int j = 0; j < lab2_Christian_Mesina.size; j++)
			{
				System.out.print(boardstate[i][j]);
			}
		System.out.println();
		}	
    }
	
    
    // This function gets the Max Value of the Minimax algorithm which follows the pseudocode 
	private static Node Max_Value(int[][] game, int d, int depth, Node node)
	{
		if(d == depth || terminalState(node))
		{
			 node.score = GameScore(game,node);
			 return node;
		}
		else
		{
			Node best = null;
			Node demo = null;
			int bestSoFar = Integer.MIN_VALUE;
			List<Node> MaxChildren = generateChild(node, d, game, "max");
			for(Iterator<Node> iter = MaxChildren.iterator(); iter.hasNext(); )
			{
				counter++;
				demo = iter.next();
				iter.remove();			
				Node temp = Min_Value(game, d+1, depth, demo);
				if(temp.score > bestSoFar)
				{
					bestSoFar = temp.score;
					best = demo;
					best.score = bestSoFar;			
				}
				temp = null;
			}
			return best;
		}
	}
		
    // This function gets the Min Value of the Minimax algorithm which follows the pseudocode 
	private static Node Min_Value(int[][] game, int d, int depth, Node node)
	{
		if(d == depth || terminalState(node))
		{
			node.score = GameScore(game, node );
			return node;
		}
		else
		{
			Node best = null;
			Node demo = null;
			int bestSoFar = Integer.MAX_VALUE;
			List<Node> MaxChildren = generateChild(node, d, game, "min");
			for(Iterator<Node> iter = MaxChildren.iterator(); iter.hasNext(); )
			{
				counter++;
				demo = iter.next();
				iter.remove();			
				Node temp = Max_Value(game, d+1, depth, demo);
				if (temp.score < bestSoFar)
				{
					bestSoFar = temp.score;
					best = demo;
					best.score = bestSoFar;
				}
				temp = null;
			}
			return best;
		}
}	
	// Boolean function that checks if the node is in the terminal state throughout the game
	public static boolean terminalState(Node node) 
	{
		for(int i = 0; i < lab2_Christian_Mesina.size; i++)
		{
			for(int j = 0; j < lab2_Christian_Mesina.size; j++)
			{
				if(node.Board[i][j].equals("."))
                {
					return false;
                }
			}
		}
		return true;
	}

    // This list function generates the child for each Node in the game
	private static List<Node> generateChild(Node parent, int d, int[][] game, String mode)
	{
        // This boolean checks if the neighboring Node is raidable in its current state 
		boolean RaidNeighbor = false, RaidOpponentNeighbor = false;
      	List<Node> RaidChildren = new ArrayList<>();

        // This for loop implements the check of the neighboring Nodes that can be raided and tells if it is the opponent or the player's move
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++) 
			{	
				if(parent.Board[i][j].trim().equals("."))
				{  					
					Node node = new Node();
					node.setBoard(parent.Board);
					node.row = i;
					node.col = j;
					node.bestmove = s;                 	
					
                    if(mode.equals("max"))
					{
						node.Board[i][j] = myPlayer;                      
						RaidNeighbor = CheckNeighbors(parent.Board, i, j, myPlayer);
						RaidOpponentNeighbor = CheckNeighbors(parent.Board, i, j, myOpponent);
						
                        if(RaidNeighbor && RaidOpponentNeighbor)
						{
							Node RaidNode = new Node();
							RaidNode.setBoard(parent.Board);
							Raid(game, myPlayer, i, j, RaidNode);
							RaidChildren.add(RaidNode);
						}
					}
					else
					{
						node.Board[i][j] = myOpponent;	
                     	RaidNeighbor = CheckNeighbors(parent.Board, i , j, myOpponent);
						RaidOpponentNeighbor = CheckNeighbors(parent.Board, i, j, myPlayer);
						
                        if(RaidNeighbor && RaidOpponentNeighbor)
						{
							Node RaidNode = new Node();
							RaidNode.setBoard(parent.Board);
							Raid(game, myOpponent, i, j, RaidNode);	
							RaidChildren.add(RaidNode);
						}
					}
					parent.getChildren().add(node);
				}
			}
		}
		if(!RaidChildren.isEmpty())
		{
			Node demo = null;
			for(Iterator<Node> iter = RaidChildren.iterator(); iter.hasNext(); ) 
			{
				demo = iter.next();
				iter.remove();
				parent.getChildren().add(demo);
				RaidChildren = null;
			}
		}
		return parent.getChildren();
}

    // This boolean function hecks to see if a position has any neighbors next to it to determine a raid
    private static boolean CheckNeighbors(String[][] boardstate, int i, int j, String opponent) 
	{
		if(i > 0)
		{ 
			if(boardstate[i-1][j].trim().equals(opponent))
			{
				return true;
			}
		}
		if(i < size - 1)
		{
			if(boardstate[i+1][j].trim().equals(opponent))
			{
				return true;
			}
		}
		if(j > 0)
		{
			if(boardstate[i][j-1].trim().equals(opponent))
			{
				return true;
			}
		}
		if(j < size - 1)
		{
			if(boardstate[i][j+1].trim().equals(opponent))
			{
				return true;
			}		
		}
		return false;	
	}
}
