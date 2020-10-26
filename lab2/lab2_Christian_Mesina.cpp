/*********************************************************************************************************************
 * Christian Mesina
 * lab2_Christian_Mesina.cpp
 * Created on 02/17/2020. Due by 03/04/2020
 * This program creates a game  game board is an N x N grid. Columns are named A, B, C, …. (from left to right), 
 * and rows are named 1, 2, 3, ... (from top to bottom). Each player takes turns as in chess or tic-tac-toe. 
 * That is, player X takes a move, then player O, then back to player X, and so forth. Each square 
 * has a fixed point value between 1 and 99. The objective of the game for each player is to score the most points. 
 * A player’s score is the sum of the point values of his or her occupied squares minus the sum of all point
 * values of the squares occupied by the other player. The game ends when all the squares are occupied by the players
 * since no more moves are left. Also, this program will be implementing the following two algorithms: 
 * standard Minimax algorithm and Alpha-Beta Pruning algorithm.
*********************************************************************************************************************/

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

void minimax_decision(vector<vector<char>> board, vector<vector<int>> game, char myPlayer, char myOpponent, int depth, int size, int GameScore, int best);
int minimax_min_value(vector<vector<char>> board, vector<vector<int>> game, char myPlayer, char myOpponent, int depth, int size, int GameScore, int row, int col);
int minimax_max_value(vector<vector<char>> board, vector<vector<int>> game, char myPlayer, char myOpponent, int depth, int size, int GameScore, int row, int col);

struct Move
{
    int score;
    int row;
    int col;
    bool raid = false;
};

// Gets the game score based on the current myPlayer map
int GetScore(vector<vector<char>> board, vector<vector<int>> game, char myPlayer, char myOpponent, int size)
{
    int score = 0;

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(board[i][j] == myPlayer)
            {
                score += game[i][j];
            }
            else if(board[i][j] == myOpponent)
            {
                score -= game[i][j];
            }
        }
    }
    return score;
}

// Checks to see if a position has any neighbors next to it to determine a raid
int checkNeighbors(vector<vector<char>> board, char check, int check2, int size, int row, int col)
{
    int n = 0;
    if(board[row][col] == check)
    {
        if(row == 0)
        {
            if(col > 0)
            {
                if(board[row][col-1] == check)
                {
                    n += 1;
                }
            }
            if(board[row+1][col] == check)
            {
                n += 1;
            }
            if(col < size-1)
            {
                if(board[row][col+1] == check)
                {
                    n += 1;
                }
            }
        }
        else if(row == size-1)
        {
            if(col > 0)
            {
                if(board[row][col-1] == check)
                {
                    n += 1;
                }
            }
            if(col < size -1)
            {
                if(board[row][col+1] == check)
                {
                    n += 1;
                }
            }
            if(board[row-1][col] == check)
            {
                n += 1;
            }
        }
        else
        {
            if(board[row][col-1] == check)
            {
                n += 1;
            }
            if(board[row+1][col] == check)
            {
                n += 1;
            }
            if(board[row][col+1] == check)
            {
                n += 1;
            }
            if(board[row-1][col] == check)
            {
                n += 1;
            }
        }
    }
    else if(board[row][col] == check)
    {
        if(row == 0)
        {
            if(col > 0)
            {
                if(board[row][col-1] == check2)
                {
                    n += 1;
                }
            }
            if(board[row+1][col] == check2)
            {
                n += 1;
            }
            if(col < size-1)
            {
                if(board[row][col+1] == check2)
                {
                    n += 1;
                }
            }
        }
        else if(row == size-1)
        {
            if(col > 0)
            {
                if(board[row][col-1] == check2)
                {
                    n += 1;
                }
            }
            if(col < size -1)
            {
                if(board[row][col+1] == check2)
                {
                    n += 1;
                }
            }
            if(board[row-1][col] == check2)
            {
                n += 1;
            }
        }
        else
        {
            if(board[row][col-1] == check2)
            {
                n += 1;
            }
            if(board[row+1][col] == check2)
            {
                n += 1;
            }
            if(board[row][col+1] == check2)
            {
                n += 1;
            }
            if(board[row-1][col] == check2)
            {
                n += 1;
            }
        }
    }
    return n;
}

// The beginning of the MiniMax Algorithm
int minimax(vector<vector<char>> board, vector<vector<int>> game, char myPlayer, char myOpponent, int depth, int size, int GameScore, int i, int j)
{
    int score;
    bool isMax;

    if(depth % 2 == 0)
    {
        isMax = false;
    }
    else
    {
        isMax = true;
    }

    if(depth > 0)
    {
        if(isMax == true)
        {
            minimax_max_value(board, game, myPlayer, myOpponent, depth, size, GameScore, i, j);
        }
        else if(isMax == false)
        {
            minimax_min_value(board, game, myPlayer, myOpponent, depth, size, GameScore, i, j);
        }
    }
    score = GetScore(board, game, myPlayer, myOpponent, size);
    return score;
}

// Finds the maximum game score for the myPlayer
int minimax_max_value(vector<vector<char>> board, vector<vector<int>> game, char myPlayer, char myOpponent, int depth, int size, int GameScore, int i, int j)
{
    int best = -1000;
    vector<vector<char>> temp1 = board;
    int neighbors;

    if(temp1[i][j] == '.')
    {
        temp1[i][j] == myPlayer;
        best = max(best, minimax(temp1, game, myPlayer, myOpponent, depth+1, size, GameScore, i, j));
        temp1[i][j] = '.';
    }

    return best;
}

// Finds the minimum game score for the myOpponent
int minimax_min_value(vector<vector<char>> board, vector<vector<int>> game, char myPlayer, char myOpponent, int depth, int size, int GameScore, int i, int j)
{
    int best = 1000;
    vector<vector<char>> temp1 = board;
    int neighbors;

    if(temp1[i][j] == '.')
    {
        temp1[i][j] == myOpponent;
        best = min(best, minimax(temp1, game, myPlayer, myOpponent, depth+1, size, GameScore, i, j));
        temp1[i][j] = '.';
    }

    return best;
}

// Finds the column that the best move is located at
int minimax_col(vector<vector<char>> board, vector<vector<int>> game, char myPlayer, char myOpponent, int depth, int size, int GameScore, int v, int s, Move p, int row, int col)
{
    bool isMax;
    int b;
    int Score;
    int np = 0;
    int no = 0;
    vector<vector<char>> temp = board;

    for(int x = depth; x > 0; x--)
    {
        if(x % 2 == 0)
        {
            isMax = false;
        }
        else
        {
            isMax = true;
        }

        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                if(i != row || j != col)
                {
                    if(temp[i][j] == '.')
                    {
                        if(isMax == true)
                        {
                            temp[i][j] = myPlayer;
                            np = checkNeighbors(temp, myPlayer, myOpponent, size, i, j);
                            if(np > 0)
                            {
                                no = checkNeighbors(temp, myOpponent, myPlayer, size, i, j);
                                if(no > 0)
                                {
                                    p.raid = true;
                                    vector<vector<char>> temp1 = temp;
                                        if(i == 0)
                                        {
                                            if(j > 0)
                                            {
                                                if(temp1[i][j-1] == myOpponent)
                                                {
                                                    temp1[i][j-1] = myPlayer;
                                                }
                                            }
                                            if(temp1[i+1][j] == myOpponent)
                                            {
                                                temp1[i+1][j] = myPlayer;
                                            }
                                            if(j < size-1)
                                            {
                                                if(temp1[i][j+1] == myOpponent)
                                                {
                                                    temp1[i][j+1] = myPlayer;
                                                }
                                            }
                                        }
                                        else if(i == size-1)
                                        {
                                            if(j > 0)
                                            {
                                                if(temp1[i][j-1] == myOpponent)
                                                {
                                                    temp1[i][j-1] = myPlayer;
                                                }
                                            }
                                            if(j < size -1)
                                            {
                                                if(temp1[i][j+1] == myOpponent)
                                                {
                                                    temp1[i][j+1] = myPlayer;
                                                }
                                            }
                                            if(temp1[i-1][j] == myOpponent)
                                            {
                                                temp1[i-1][j] = myPlayer;
                                            }
                                        }
                                        else
                                        {
                                            if(temp1[i][j-1] == myOpponent)
                                            {
                                                temp1[i][j-1] = myPlayer;
                                            }
                                            if(temp1[i+1][j] == myOpponent)
                                            {
                                                temp1[i+1][j] = myPlayer;
                                            }
                                            if(temp1[i][j+1] == myOpponent)
                                            {
                                                temp1[i][j+1] = myPlayer;
                                            }
                                            if(temp1[i-1][j] == myOpponent)
                                            {
                                                temp1[i-1][j] = myPlayer;
                                            }
                                        }
                                    Score = GetScore(temp1, game, myPlayer, myOpponent, size);
                                    b = minimax(temp1, game, myPlayer, myOpponent, x, size, Score, i, j);
                                }
                            }
                            else
                            {
                                Score = GetScore(temp, game, myPlayer, myOpponent, size);
                                b = minimax(temp, game, myPlayer, myOpponent, x, size, Score, i, j);
                            }
                            if(b > v)
                            {
                                v = b;
                                p.col = i;
                            }
                            temp[i][j] = '.';
                        }
                        else if(isMax == false)
                        {
                            v = v* -1;
                            temp[i][j] = myOpponent;
                            no = checkNeighbors(temp, myPlayer, myOpponent, size, i, j);
                            if(no > 0)
                            {
                            no = checkNeighbors(temp, myOpponent, myPlayer, size, i, j);
                                if(np > 0)
                                {
                                    vector<vector<char>> temp1 = temp;
                                    if(i == 0)
                                    {
                                        if(j > 0)
                                        {
                                            if(temp1[i][j-1] == myPlayer)
                                            {
                                                temp1[i][j-1] = myOpponent;
                                            }
                                        }
                                        if(temp1[i+1][j] == myPlayer)
                                        {
                                            temp1[i+1][j] = myOpponent;
                                        }
                                        if(j < size-1)
                                        {
                                            if(temp1[i][j+1] == myPlayer)
                                            {
                                                temp1[i][j+1] = myOpponent;
                                            }
                                        }
                                    }
                                    else if(i == size-1)
                                    {
                                        if(j > 0)
                                        {
                                            if(temp1[i][j-1] == myPlayer)
                                            {
                                                temp1[i][j-1] = myOpponent;
                                            }
                                        }
                                        if(j < size -1)
                                        {
                                            if(temp1[i][j+1] == myPlayer)
                                            {
                                                temp1[i][j+1] = myOpponent;
                                            }
                                        }
                                        if(temp1[i-1][j] == myPlayer)
                                        {
                                            temp1[i-1][j] = myOpponent;
                                        }
                                    }
                                    else
                                    {
                                        if(temp1[i][j-1] == myPlayer)
                                        {
                                            temp1[i][j-1] = myOpponent;
                                        }
                                        if(temp1[i+1][j] == myPlayer)
                                        {
                                            temp1[i+1][j] = myOpponent;
                                        }
                                        if(temp1[i][j+1] == myPlayer)
                                        {
                                            temp1[i][j+1] = myOpponent;
                                        }
                                        if(temp1[i-1][j] == myPlayer)
                                        {
                                            temp1[i-1][j] = myOpponent;
                                        }
                                    }
                                    Score = GetScore(temp1, game, myPlayer, myOpponent, size);
                                    b = minimax(temp1, game, myPlayer, myOpponent, x, size, Score, i, j);
                                }
                            }
                            else
                            {
                                Score = GetScore(temp, game, myPlayer, myOpponent, size);
                                b = minimax(temp, game, myPlayer, myOpponent, x, size, Score, i, j);
                            }
                            if(b < v)
                            {
                                v = b;
                            }
                            temp[i][j] = '.';
                        }
                    }
                }
            }
        }
    }
    return p.col;
}

// Finds the row that the best move is located at
int minimax_row(vector<vector<char>> board, vector<vector<int>> game, char myPlayer, char myOpponent, int depth, int size, int GameScore, int v, int s, Move p, int row, int col)
{
    bool isMax;
    int b;
    int Score;
    int np = 0;
    int no = 0;
    vector<vector<char>> temp = board;

    for(int x = depth; x > 0; x--)
    {
        if(x % 2 == 0)
        {
            isMax = false;
        }
        else
        {
            isMax = true;
        }

        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                if(i != row || j != col)
                {
                    if(temp[i][j] == '.')
                    {
                        if(isMax == true)
                        {
                            temp[i][j] = myPlayer;
                            np = checkNeighbors(temp, myPlayer, myOpponent, size, i, j);
                            if(np > 0)
                            {
                                no = checkNeighbors(temp, myOpponent, myPlayer, size, i, j);
                                if(no > 0)
                                {
                                    p.raid = true;
                                    vector<vector<char>> temp1 = temp;
                                        if(i == 0)
                                        {
                                            if(j > 0)
                                            {
                                                if(temp1[i][j-1] == myOpponent)
                                                {
                                                    temp1[i][j-1] = myPlayer;
                                                }
                                            }
                                            if(temp1[i+1][j] == myOpponent)
                                            {
                                                temp1[i+1][j] = myPlayer;
                                            }
                                            if(j < size-1)
                                            {
                                                if(temp1[i][j+1] == myOpponent)
                                                {
                                                    temp1[i][j+1] = myPlayer;
                                                }
                                            }
                                        }
                                        else if(i == size-1)
                                        {
                                            if(j > 0)
                                            {
                                                if(temp1[i][j-1] == myOpponent)
                                                {
                                                    temp1[i][j-1] = myPlayer;
                                                }
                                            }
                                            if(j < size -1)
                                            {
                                                if(temp1[i][j+1] == myOpponent)
                                                {
                                                    temp1[i][j+1] = myPlayer;
                                                }
                                            }
                                            if(temp1[i-1][j] == myOpponent)
                                            {
                                                temp1[i-1][j] = myPlayer;
                                            }
                                        }
                                        else
                                        {
                                            if(temp1[i][j-1] == myOpponent)
                                            {
                                                temp1[i][j-1] = myPlayer;
                                            }
                                            if(temp1[i+1][j] == myOpponent)
                                            {
                                                temp1[i+1][j] = myPlayer;
                                            }
                                            if(temp1[i][j+1] == myOpponent)
                                            {
                                                temp1[i][j+1] = myPlayer;
                                            }
                                            if(temp1[i-1][j] == myOpponent)
                                            {
                                                temp1[i-1][j] = myPlayer;
                                            }
                                        }
                                    Score = GetScore(temp1, game, myPlayer, myOpponent, size);
                                    b = minimax(temp1, game, myPlayer, myOpponent, x, size, Score, i, j);
                                }
                            }
                            else
                            {
                                Score = GetScore(temp, game, myPlayer, myOpponent, size);
                                b = minimax(temp, game, myPlayer, myOpponent, x, size, Score, i, j);
                            }
                            if(b > v)
                            {
                                v = b;
                                p.row = j;
                            }
                            temp[i][j] = '.';
                        }
                        else if(isMax == false)
                        {
                            v = v* -1;
                            temp[i][j] = myOpponent;
                            no = checkNeighbors(temp, myPlayer, myOpponent, size, i, j);
                            if(no > 0)
                            {
                            no = checkNeighbors(temp, myOpponent, myPlayer, size, i, j);
                                if(np > 0)
                                {
                                    vector<vector<char>> temp1 = temp;
                                    if(i == 0)
                                    {
                                        if(j > 0)
                                        {
                                            if(temp1[i][j-1] == myPlayer)
                                            {
                                                temp1[i][j-1] = myOpponent;
                                            }
                                        }
                                        if(temp1[i+1][j] == myPlayer)
                                        {
                                            temp1[i+1][j] = myOpponent;
                                        }
                                        if(j < size-1)
                                        {
                                            if(temp1[i][j+1] == myPlayer)
                                            {
                                                temp1[i][j+1] = myOpponent;
                                            }
                                        }
                                    }
                                    else if(i == size-1)
                                    {
                                        if(j > 0)
                                        {
                                            if(temp1[i][j-1] == myPlayer)
                                            {
                                                temp1[i][j-1] = myOpponent;
                                            }
                                        }
                                        if(j < size -1)
                                        {
                                            if(temp1[i][j+1] == myPlayer)
                                            {
                                                temp1[i][j+1] = myOpponent;
                                            }
                                        }
                                        if(temp1[i-1][j] == myPlayer)
                                        {
                                            temp1[i-1][j] = myOpponent;
                                        }
                                    }
                                    else
                                    {
                                        if(temp1[i][j-1] == myPlayer)
                                        {
                                            temp1[i][j-1] = myOpponent;
                                        }
                                        if(temp1[i+1][j] == myPlayer)
                                        {
                                            temp1[i+1][j] = myOpponent;
                                        }
                                        if(temp1[i][j+1] == myPlayer)
                                        {
                                            temp1[i][j+1] = myOpponent;
                                        }
                                        if(temp1[i-1][j] == myPlayer)
                                        {
                                            temp1[i-1][j] = myOpponent;
                                        }
                                    }
                                    Score = GetScore(temp1, game, myPlayer, myOpponent, size);
                                    b = minimax(temp1, game, myPlayer, myOpponent, x, size, Score, i, j);
                                }
                            }
                            else
                            {
                                Score = GetScore(temp, game, myPlayer, myOpponent, size);
                                b = minimax(temp, game, myPlayer, myOpponent, x, size, Score, i, j);
                            }
                            if(b < v)
                            {
                                v = b;
                            }
                            temp[i][j] = '.';
                        }
                    }
                }
            }
        }
    }
    return p.row;
}

// Finds the game score for every possible move
int minimax_player(vector<vector<char>> board, vector<vector<int>> game, char myPlayer, char myOpponent, int depth, int size, int GameScore, int v, int s, Move p, int row, int col)
{
    bool isMax;
    int b;
    int Score;
    int np = 0;
    int no = 0;
    vector<vector<char>> temp = board;

    for(int x = depth; x > 0; x--)
    {
        if(x % 2 == 0)
        {
            isMax = false;
        }
        else
        {
            isMax = true;
        }

        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                if(i != row || j != col)
                {
                    if(temp[i][j] == '.')
                    {
                        if(isMax == true)
                        {
                            temp[i][j] = myPlayer;
                            np = checkNeighbors(temp, myPlayer, myOpponent, size, i, j);
                            if(np > 0)
                            {
                                no = checkNeighbors(temp, myOpponent, myPlayer, size, i, j);
                                if(no > 0)
                                {
                                    p.raid = true;
                                    vector<vector<char>> temp1 = temp;
                                        if(i == 0)
                                        {
                                            if(j > 0)
                                            {
                                                if(temp1[i][j-1] == myOpponent)
                                                {
                                                    temp1[i][j-1] = myPlayer;
                                                }
                                            }
                                            if(temp1[i+1][j] == myOpponent)
                                            {
                                                temp1[i+1][j] = myPlayer;
                                            }
                                            if(j < size-1)
                                            {
                                                if(temp1[i][j+1] == myOpponent)
                                                {
                                                    temp1[i][j+1] = myPlayer;
                                                }
                                            }
                                        }
                                        else if(i == size-1)
                                        {
                                            if(j > 0)
                                            {
                                                if(temp1[i][j-1] == myOpponent)
                                                {
                                                    temp1[i][j-1] = myPlayer;
                                                }
                                            }
                                            if(j < size -1)
                                            {
                                                if(temp1[i][j+1] == myOpponent)
                                                {
                                                    temp1[i][j+1] = myPlayer;
                                                }
                                            }
                                            if(temp1[i-1][j] == myOpponent)
                                            {
                                                temp1[i-1][j] = myPlayer;
                                            }
                                        }
                                        else
                                        {
                                            if(temp1[i][j-1] == myOpponent)
                                            {
                                                temp1[i][j-1] = myPlayer;
                                            }
                                            if(temp1[i+1][j] == myOpponent)
                                            {
                                                temp1[i+1][j] = myPlayer;
                                            }
                                            if(temp1[i][j+1] == myOpponent)
                                            {
                                                temp1[i][j+1] = myPlayer;
                                            }
                                            if(temp1[i-1][j] == myOpponent)
                                            {
                                                temp1[i-1][j] = myPlayer;
                                            }
                                        }
                                    Score = GetScore(temp1, game, myPlayer, myOpponent, size);
                                    b = minimax(temp1, game, myPlayer, myOpponent, x, size, Score, i, j);
                                }
                            }
                            else
                            {
                                Score = GetScore(temp, game, myPlayer, myOpponent, size);
                                b = minimax(temp, game, myPlayer, myOpponent, x, size, Score, i, j);
                            }
                            if(b > v)
                            {
                                v = b;
                            }
                            temp[i][j] = '.';
                        }
                        else if(isMax == false)
                        {
                            v = v* -1;
                            temp[i][j] = myOpponent;
                            no = checkNeighbors(temp, myPlayer, myOpponent, size, i, j);
                            if(no > 0)
                            {
                                np = checkNeighbors(temp, myOpponent, myPlayer, size, i, j);
                                if(np > 0)
                                {
                                    vector<vector<char>> temp1 = temp;
                                    if(i == 0)
                                    {
                                        if(j > 0)
                                        {
                                            if(temp1[i][j-1] == myPlayer)
                                            {
                                                temp1[i][j-1] = myOpponent;
                                            }
                                        }
                                        if(temp1[i+1][j] == myPlayer)
                                        {
                                            temp1[i+1][j] = myOpponent;
                                        }
                                        if(j < size-1)
                                        {
                                            if(temp1[i][j+1] == myPlayer)
                                            {
                                                temp1[i][j+1] = myOpponent;
                                            }
                                        }
                                    }
                                    else if(i == size-1)
                                    {
                                        if(j > 0)
                                        {
                                            if(temp1[i][j-1] == myPlayer)
                                            {
                                                temp1[i][j-1] = myOpponent;
                                            }
                                        }
                                        if(j < size -1)
                                        {
                                            if(temp1[i][j+1] == myPlayer)
                                            {
                                                temp1[i][j+1] = myOpponent;
                                            }
                                        }
                                        if(temp1[i-1][j] == myPlayer)
                                        {
                                            temp1[i-1][j] = myOpponent;
                                        }
                                    }
                                    else
                                    {
                                        if(temp1[i][j-1] == myPlayer)
                                        {
                                            temp1[i][j-1] = myOpponent;
                                        }
                                        if(temp1[i+1][j] == myPlayer)
                                        {
                                            temp1[i+1][j] = myOpponent;
                                        }
                                        if(temp1[i][j+1] == myPlayer)
                                        {
                                            temp1[i][j+1] = myOpponent;
                                        }
                                        if(temp1[i-1][j] == myPlayer)
                                        {
                                            temp1[i-1][j] = myOpponent;
                                        }
                                    }
                                    Score = GetScore(temp1, game, myPlayer, myOpponent, size);
                                    b = minimax(temp1, game, myPlayer, myOpponent, x, size, Score, i, j);
                                }
                            }
                            else
                            {
                                Score = GetScore(temp, game, myPlayer, myOpponent, size);
                                b = minimax(temp, game, myPlayer, myOpponent, x, size, Score, i, j);
                            }
                            if(b < v)
                            {
                                v = b;
                            }
                            temp[i][j] = '.';
                        }
                    }
                }
            }
        }
    }
    return v;
}

// This function outputs the best move for the myPlayer to make, and outputs it to a text file
void minimax_decision(vector<vector<char>> board, vector<vector<int>> game, char myPlayer, char myOpponent, int depth, int size, int GameScore, int v, Move p, Move o)
{

    p.score = GameScore;
    int s;
    int row = 1000;
    int col = 1000;
    vector<vector<char>> temp = board;
    string ascii = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string stake;

    p.score = minimax_player(board, game, myPlayer, myOpponent, depth, size, GameScore, v, s, p, row, col);
    p.row = minimax_row(board, game, myPlayer, myOpponent, depth, size, GameScore, v, s, p, row, col);
    p.col = minimax_col(board, game, myPlayer, myOpponent, depth, size, GameScore, v, s, p, row, col);



    temp[p.col][p.row] = myPlayer;

    for(int x = depth; x > 1; x--)
    {
                temp[p.col][p.row] = '.';
                row = p.row;
                col = p.col;
                p.score = minimax_player(board, game, myPlayer, myOpponent, depth-1, size, GameScore, v, s, p, row, col);
                p.row = minimax_row(board, game, myPlayer, myOpponent, depth, size, GameScore, v, s, p, row, col);
                p.col = minimax_col(board, game, myPlayer, myOpponent, depth, size, GameScore, v, s, p, row, col);
                temp[p.col][p.row] = myPlayer;
    }

    if(p.raid == false)
    {
        stake = "Stake";
    }
    else
    {
        stake = "Raid";
    }

    ofstream out;
    out.open("output.txt");
    cout << ascii[p.row] << p.col + 1 << " " << stake << endl;
    out << ascii[p.row] << p.col + 1 << " " << stake << endl;

    if(stake == "Raid")
    {
        if(temp[p.row+1][p.col] == myOpponent)
        {
            temp[p.row+1][p.col] = myPlayer;
        }
        if(temp[p.row-1][p.col] == myOpponent)
        {
            temp[p.row-1][p.col] = myPlayer;
        }
        if(temp[p.row][p.col+1] == myOpponent)
        {
            temp[p.row][p.col+1] = myPlayer;
        }
        if(temp[p.row][p.col-1] == myOpponent)
        {
            temp[p.row][p.col-1] = myPlayer;
        }
    }

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            cout << temp[i][j] << " ";
        }
        cout << endl;
    }
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            out << temp[i][j] << " ";
        }
        out << endl;
    }
    out.close();
}

void alphabeta_search(vector<vector<char>> board, vector<vector<int>> game, char myPlayer, char myOpponent, int depth, int size, int GameScore, int best)
{
    bool isMax;
    if(depth % 2 == 0)
    {
        isMax == false;
    }
    else
    {
        isMax == true;
    }


    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            cout << game[i][j] << " ";
        }
        cout << endl;
    }

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void Algorithm(string Algorithm, vector<vector<char>> &board, vector<vector<int>> &game, char &myPlayer, char &myOpponent, int &depth, int &size, int &best)
{
    int v = -1000;
    int GameScore;
    Move p;
    Move o;
    GameScore = GetScore(board, game, myPlayer, myOpponent, size);

    if(Algorithm == "MINIMAX")
    {
        minimax_decision(board, game, myPlayer, myOpponent, depth, size, GameScore, v, p, o);
    }
    else if(Algorithm == "ALPHABETA")
    {
        alphabeta_search(board, game, myPlayer, myOpponent, depth, size, GameScore, best);
    }
}

// Reads all the information from the input file and stores it accordingly
int main()
{
    ifstream in;
    string input = "input.txt";
    in.open(input);
    ofstream Out;
    string out = "output.txt";

    if(!in.is_open())
    {
        cout << "Couldn't open file" << endl;
        exit(1);
    }

    string MapSize;
    int size;
    int depth;
    int best;
    string Algorithm;
    string p1;
    string p2;
    string depthth;

    getline(in, MapSize);
    size = stoi(MapSize);

    vector<vector<char>> board;
    vector<vector<int>> game;

    getline(in, Algorithm);
    getline(in, p1);
    getline(in, depthth);
    depth = stoi(depthth);

    if(p1 == "O")
    {
        p2 = "X";
    }
    else
    {
        p2 = "O";
    }

    char myPlayer = p1[0];
    char myOpponent = p2[0];

    for(int i = 0; i < size; i++)
    {
        vector<int> c;
        game.push_back(c);
        for(int j = 0; j < size; j++)
        {
            int v;
            in >> v;
            game[i].push_back(v);
        }
    }

    for(int i = 0; i < size; i++)
    {
        vector<char> c;
        board.push_back(c);
        for(int j = 0; j < size; j++)
        {
            char v;
            in >> v;
            board[i].push_back(v);
        }
    }

    Algorithm(Algorithm, board, game, myPlayer, myOpponent, depth, size, best);

    return 0;
}
