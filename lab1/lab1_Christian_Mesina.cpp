/*********************************************************************************************************************
 * Christian Mesina
 * lab1_Christian_Mesina.cpp
 * Created on 01/13/2020. Due by 02/09/2020
 * This program implements the following four search algorithms: Breadth First Search (BFS), Depth-First Search (DFS),
 * Uniform Cost Search (UCS), and A* Search. We are given a starting location and goal location (or destination), and 
 * must find a path to the goal location. In this problem, the optimal path is the one which has the shortest travel 
 * time. This program reads the user's input through an input file called input.txt and the program will choose 
 * what algortithm to use based on the input file's first line which is a string of the algortihm that will
 * be implemented.
*********************************************************************************************************************/ 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <iterator>

using namespace std;

// Creates a class called LiveRow for the Live Traffic data.
class LiveRow
{
public:
    string start;       // initializes the node
    string state;       // initializes the parent
    string end;         // initializes the child
    LiveRow* parent = nullptr;      // points to the parent node
    int step;       // initializes the path cost
    int heuristic;  // initializes the heuristic value
    LiveRow(){}     // LiveRow constructor
};

// Creates a Sunday struct for the Sunday Traffic
struct SundayRow
{
    string start;
    string state;       // parent node
    int cost;    // initializes the step cost
    int heuristic;  // initializes the heuristic value
    SundayRow* parent = nullptr;
    SundayRow(){}       // SundayRow constructor
};

// Creates the node structure for the algortihms
struct Node
{
    string state;           // parent node
    vector<string> path;    // creates a vector of string characters for the path cost
    vector<int> cost;       // creates a vector of integers for the cost value of algorithm
    Node(){};               // Node constructor
};


// Creates a copy function for the queue container so that the element can be pushed and 
// pop from the frontier
queue<string> copyQueue(queue<string> F)
{
    queue<string> f;
    for(int i = 0; i < F.size(); i++)
    {
        f.push(F.front());
        F.pop();
    }
    return f;
}

// Creates a BFS function that passes a vector, two strings, and the output file
void BFS(vector<LiveRow*> &v, string &StartState, string &GoalState, ofstream &out)
{
    // Creates a node and store it on a vector container
    Node* N = new Node;
    vector<Node*> n;
    // Creates a queue of string characters where frontier data will be contained
    queue<string> frontier;
    // Creates a vector of string character where explored data will be contained
    vector<string> explored;
    // Places the node node at the start state, places the step cost of the node and pushes the node at the frontier
    N->state = v[0]->start;
    N->path.push_back(v[0]->start);
    N->cost.push_back(0);
    n.push_back(N);
    frontier.push(v[0]->start);

    // If the frontier is empty print out a message and exit the program
    for(int i = 2; i < v.size(); i++)
    {
        if(frontier.empty())
        {
            cout << "The Frontier is empty" << endl;
            exit(1);
        }

        // Chooses the shallowest node in the frontier
        string temp = frontier.front();
        frontier.pop();
        // If the problem is the Goal State then return the solution (node)
        if(temp == GoalState)
        {
            for(int x = 0; x < n.size(); x++)
            {
                if(GoalState == n[x]->state)        // If the node is the goal state, print it out
                {
                    for(int y = 0; y < n[x]->path.size(); y++)
                    {
                        out << n[x]->path[y] << " " << n[x]->cost[y] << endl;       // outputs the results into an output file
                    }
                }
            }
            exit(1);
        }
        
        // Add the node state to explored
        explored.push_back(temp);
        // For each action in the problem node state, do the following arguments
        for(int j = 2; j < v.size(); j++)
        {
            string child = v[j]->state;
            string temp2 = (*(v[j]->parent)).state;

            if(temp2 == temp)
            {
                queue<string> tempQ = copyQueue(frontier);
                string check;
                for(int l = 0; l < explored.size(); l++)
                {
                    if(child == explored[l])
                    {
                        check = "Failure";
                    }
                }

                while(!tempQ.empty())
                {
                    if(child == tempQ.front())
                    {
                        check = "Failure";
                    }
                    tempQ.pop();
                }
               
                if(check == "Failure");
                // If child is not in explored or frontier then insert the child to the frontier
                else
                {
                    frontier.push(child);
                    Node* N = new Node;
                    N->state = child;
                    for(int x = 0; x < n.size(); x++)
                    {
                        if(temp == n[x]->state)
                        {
                            int cost = 0;
                            for(int y = 0; y < n[x]->path.size(); y++)
                            {
                                N->path.push_back(n[x]->path[y]);
                                cost = n[x]->cost[y];
                                N->cost.push_back(cost);
                            }
                            N->path.push_back(child);
                            cost += v[j]->step;
                            N->cost.push_back(cost);
                        }
                    }
                    n.push_back(N);
                }
            }
        }
    } 
}

// Creates a copy function just like the queue function from before but this one implements the stack
stack<string> copyStack(stack<string> F)
{
    stack<string> f;
    for(int i = 0; i < F.size(); i++)
    {
        f.push(F.top());
        F.top();
    }
    return f;
}

// Creates a DFS function that passes a vector, two strings, and the output file
void DFS(vector<LiveRow*> &v, string &StartState, string &GoalState, ofstream &out)
{
    Node* N = new Node;
    vector<Node*> n;
    stack<string> frontier;
    vector<string> explored;
    
    N->state = v[0]->start;
    N->path.push_back(v[0]->start);
    N->cost.push_back(0);
    n.push_back(N);
    frontier.push(v[0]->start);

    for(int i = 2; i < v.size(); i++)
    {
        if(frontier.empty())
        {
            cout << "The Frontier is empty" << endl;
            exit(1);
        }

        string temp = frontier.top();
        frontier.pop();
        if(temp == GoalState)
        {
            for(int x = 0; x < n.size(); x++)
            {
                if(GoalState == n[x]->state)
                {
                    for(int y = 0; y < n[x]->path.size(); y++)
                    {
                        out << n[x]->path[y] << " " << n[x]->cost[y] << endl;
                    }
                }
            }
            exit(1);
        }
        
        // This algorithm uses the exact code as BFS but now it will be implementing a stack rather than a queue data structure
        explored.push_back(temp);
        for(int j = 2; j < v.size(); j++)
        {
            string child = v[j]->state;
            string temp2 = (*(v[j]->parent)).state;

            if(temp2 == temp)
            {
                stack<string> tempQ = copyStack(frontier);
                string check;
                for(int l = 0; l < explored.size(); l++)
                {
                    if(child == explored[l])
                    {
                        check = "Failure";
                    }
                }

                while(!tempQ.empty())
                {
                    if(child == tempQ.top())
                    {
                        check = "Failure";
                    }
                    tempQ.pop();
                }

                if(check == "Failure");
                else
                {
                    frontier.push(child);
                    Node* N = new Node;
                    N->state = child;
                    for(int x = 0; x < n.size(); x++)
                    {
                        if(temp == n[x]->state)
                        {
                            int cost = 0;
                            for(int y = 0; y < n[x]->path.size(); y++)
                            {
                                N->path.push_back(n[x]->path[y]);
                                cost = n[x]->cost[y];
                                N->cost.push_back(cost);
                            }
                            N->path.push_back(child);
                            cost += v[j]->step;
                            N->cost.push_back(cost);
                        }
                    }
                    n.push_back(N);
                }
            }
        }
    }
}

// This SortFront function is like a basic selection sort in which iterators are used. It will pass two iterators and front as a reference. 
void SortFront(list<LiveRow*> &front)
{
    list<LiveRow*>::iterator it = front.begin();
    list<LiveRow*>::iterator it2 = ++front.begin();
    int temp;
    for(it; it != --front.end(); ++it)
    {
        for(it2; it2 != front.end(); ++it2)
        {
            if((*it)->step < (*it2)->step)
            {
                temp = (*it)->step;
                (*it)->step = (*it2)->step;
                (*it2)->step = temp;
                (*it)->state = (*it2)->state;
                (*it2)->state = temp; 
            }
        }
    }
}

// Creates a UCS function that passes a vector, two strings, and the output file
void UCS(vector<LiveRow*> &v, string &StartState, string &GoalState, ofstream &out)
{
    Node* N = new Node;
    LiveRow* Row = new LiveRow;

    // Instead of a queue and stack, this algorithm will be implementing a list data structure container
    list<LiveRow*> frontier;
    vector<string> explored;
    vector<Node*> n;

    N->state = v[0]->start;
    N->path.push_back(v[0]->start);
    N->cost.push_back(0);
    n.push_back(N);

    Row->state = v[0]->start;
    Row->step = v[0]->step;
    frontier.push_back(Row);

    for(int i = 2; i < v.size(); i++)
    {
        if(frontier.empty())
        {
            cout << "Frontier is empty!" << endl;
            exit(1);
        }

        // Pops the front of the frontier while placing the front to be a temp value
        string temp = frontier.front()->state;
        int path = frontier.front()->step;
        frontier.pop_front();
        
        if(temp == GoalState)
        {
            for(int x = 0; x < n.size(); x++)
            {
                if(GoalState == n[x]->state)
                {
                    for(int y = 0; y < n[x]->path.size(); y++)
                    {
                        out << n[x]->path[y] << " " << n[x]->cost[y] << endl;
                    }
                }
            }
            exit(1);
        }

        explored.push_back(temp);
        
        for(int j = 2; j < v.size(); j++)
        {
            string child = v[j]->state;
            string temp2 = (*(v[j]->parent)).state;
            if(temp2 == temp)
            {
                string check;
                for(int l = 0; l < explored.size(); l++)
                {
                    if(child == explored[l])
                    {
                        check = "failure";
                        cout << "in explored" << endl;
                    }
                }

                // Creates an iterator for the beginning and end of the frontier so that the value can be incremented
                for(list<LiveRow*>::iterator it = frontier.begin(); it != frontier.end(); ++it)
                {
                    if(child == (*it)->state)
                    {
                        check == "Frontier";
                    }
                }

                if(check == "failure");
                // If the current state child is in the frontier with higher path cost then replace that frontier node with the child
                else if(check == "Frontier")
                {
                    for(list<LiveRow*>::iterator it = frontier.begin(); it != frontier.end(); ++it)
                    {
                        if(child == (*it)->state)
                        {
                            int path2 = path;
                            path2 += v[j]->step;
                            if(path2 < (*it)->step)
                            {
                                path = path2;
                                (*it)->step = path;
                                SortFront(frontier);
                                Node* N = new Node;
                                N->state = child;
                                for(int x = 0; x < n.size(); x++)
                                {
                                    if(temp == n[x]->state)
                                    {
                                        int cost = 0;
                                        for(int y = 0; y < n[x]->path.size(); y++)
                                        {
                                            N->path.push_back(n[x]->path[y]);
                                            cost = n[x]->cost[y];
                                            N->cost.push_back(cost);
                                        }
                                        N->path.push_back(child);
                                        cost += v[j]->step;
                                        N->cost.push_back(cost);
                                    }
                                }
                                n.push_back(N);
                            }
                        }
                    }
                }
                else
                {
                    LiveRow* Row = new LiveRow;
                    Row->state = child;
                    path += v[j]->step;
                    Row->step = path;
                    frontier.push_back(Row);
                    SortFront(frontier);
                    Node* N = new Node;
                    N->state = child;
                    for(int x = 0; x < n.size(); x++)
                    {
                        if(temp == n[x]->state)
                        {
                            int cost = 0;
                            for(int y = 0; y < n[x]->path.size(); y++)
                            {
                                N->path.push_back(n[x]->path[y]);
                                cost = n[x]->cost[y];
                                N->cost.push_back(cost);
                            }
                            N->path.push_back(child);
                            cost += v[j]->step;
                            N->cost.push_back(cost);
                        }
                    }
                    n.push_back(N);
                }
            }
        }
    }
}

// Creates an A* function that passes a vector, two strings, and the output file
void A_Star(vector<LiveRow*> &v, string &StartState, string &GoalState, ofstream &out)
{
    Node* N = new Node;
    N->state = v[0]->start;
    N->path.push_back(v[0]->start);
    N->cost.push_back(0);

    LiveRow* Row = new LiveRow;
    Row->state = v[0]->start;
    Row->step = v[0]->step;

    // Instead of a queue or a stack, this algorithm will be implementing list data structure container
    list<LiveRow*> frontier;
    vector<string> explored;
    vector<Node*> n;
    n.push_back(N);
    frontier.push_back(Row);

    for(int i = 2; i < v.size(); i++)
    {
        if(frontier.empty())
        {
            cout << "Frontier is empty!" << endl;
            exit(1);
        }

        string temp = frontier.front()->state;
        int path = frontier.front()->step;
        frontier.pop_front();

        if(temp == GoalState)
        {
            for(int x = 0; x < n.size(); x++)
            {
                if(GoalState == n[x]->state)
                {
                    for(int y = 0; y < n[x]->path.size(); y++)
                    {
                        out << n[x]->path[y] << " " << n[x]->cost[y] << endl;
                    }
                }
            }
            exit(1);
        }

        explored.push_back(temp);
        for(int j = 2; j < v.size(); j++)
        {
            string child = v[j]->state;
            string temp2 = (*(v[j]->parent)).state;

            if(temp2 == temp)
            {
                string check;
                for(int l = 0; l < explored.size(); l++)
                {
                    if(child == explored[l])
                    {
                        check == "failure";
                    }
                }
                for(list<LiveRow*>::iterator it = frontier.begin(); it != frontier.end(); ++it)
                {
                    if(child == (*it)->state)
                    {
                        check == "Frontier";
                    }
                }

                if(check =="failure");

                // Same implementation as UCS but this algorithm adds the heuristic value to its step cost (instead of g, it is g + h)
                else if(check == "Frontier")
                {
                    for(list<LiveRow*>::iterator it = frontier.begin(); it != frontier.end(); ++it)
                    {
                        if(child == (*it)->state)
                        {
                            int path2 = path;
                            path2 += v[j]->step + v[j]->heuristic;
                            if(path2 < (*it)->step)
                            {
                                path = path2;
                                (*it)->step = path;
                                SortFront(frontier);
                                Node* N = new Node;
                                N->state = child;

                                for(int x = 0; x < n.size(); x++)
                                {
                                    if(temp == n[x]->state)
                                    {
                                        int cost = 0;
                                        for(int y = 0; y < n[x]->path.size(); y++)
                                        {
                                            N->path.push_back(n[x]->path[y]);
                                            cost = n[x]->cost[y];
                                            N->cost.push_back(cost);
                                        }
                                        N->path.push_back(child);
                                        cost += v[j]->step;
                                        N->cost.push_back(cost);
                                    }
                                }
                                n.push_back(N);
                            }
                        }
                    }
                }
                else
                {
                    LiveRow* Row = new LiveRow;
                    Row->state = child;
                    path += v[j]->step + v[j]->heuristic;
                    Row->step = path;
                    frontier.push_back(Row);
                    SortFront(frontier);
                    Node* N = new Node;
                    N->state = child;
                    for(int x = 0; x < n.size(); x++)
                    {
                        if(temp == n[x]->state)
                        {
                            int cost = 0;
                            for(int y = 0; y < n[x]->path.size(); y++)
                            {
                                N->path.push_back(n[x]->path[y]);
                                cost = n[x]->cost[y];
                                N->cost.push_back(cost);
                            }
                            N->path.push_back(child);
                            cost += v[j]->step;
                            N->cost.push_back(cost);
                        }
                    }
                    n.push_back(N);
                }
            }
        }
    }
}

// Creates a file check function in which if the file is not open, then it will print out
// an error message and exits the program
void file_check(ifstream &x, string &c)
{
    x.open(c.c_str());
    if(!x.is_open())
    {
        cout << "Couldn't open!" << endl;
        exit(1);
    }
}

// This Algorithm function checks what algorithm to use based on the file's first line of strings
void Algorithm(string &Algo, vector<LiveRow*> &v, string &StartState, string &GoalState, ofstream &out)
{
    if(Algo == "BFS")
    {
        BFS(v, StartState, GoalState, out);     // Do the BFS algorithm
    }

    else if(Algo == "DFS")
    {
        DFS(v, StartState, GoalState, out);     // Do the DFS algortihm
    }

    else if(Algo == "UCS")
    {
        UCS(v, StartState, GoalState, out);     // Do the UCS algorithm
    }

    else if(Algo == "A*")
    {
        A_Star(v, StartState, GoalState, out);  // Do the A* algorithm
    }
}

int main()
{
    string Algo;        // Creates the Algorithm string to read
    string StartState;  // Creates the Starting node string to read
    string GoalState;   // Creates the Goal node string to read
    string s, h;        
    string white_space;

    int length;         // Creates an integer length
    int h_length;

    // Creates and opens an output file where the outputs are going to be stored
    ofstream out;
    string output = "output.txt";
    out.open(output);

    // Creates and opens an input file where the user can input the test codes
    ifstream inputfile;
    string input = "input.txt";
    file_check(inputfile, input);

    // Creates a vector container for the class LiveRow
    vector<LiveRow*> v;
    LiveRow* Row = new LiveRow;
    // Creates a vector container for the struct SundayRow
    vector<SundayRow*> r;
    SundayRow* Sunday = new SundayRow;  
    

    // Reads the string of characters on the input file
    getline(inputfile, Algo);
    getline(inputfile, StartState);
    Row->start = StartState;
    Row->state = StartState;
    Row->step = 0;
    v.push_back(Row);
   
    // Creates a whole new row for the Live and Sunday traffic and then reads the goal state node of the file 
    Row = new LiveRow();
    Sunday = new SundayRow();
    getline(inputfile, GoalState);
    Row->start = GoalState;
    Row->state = GoalState;
    Row->step = 0;
    v.push_back(Row);

    // Reads the string for the number of traffic lines and conversts that string into an integer
    getline(inputfile, s);
    length = stoi(s);
    
    // For each row set a temp value for each string of characters: start, goal, and step cost
    for(int i = 0; i < length; i++)
    {
        string t, f;
        int c;
        inputfile >> t >> f >> c;
        Row = new LiveRow();
        Row->start = t;
        LiveRow* temp;
        for(int j = 0; j < v.size(); j++)
        {
            if(v[j]->state == Row->start)
            {
                temp = v[j];
                break;
            }
        }
        Row->parent = temp;
        Row->state = f;
        Row->step = c;
        v.push_back(Row);
    }

    // Uses the same implementation of the Live Traffic but instead replaces it with the Sunday Traffic values
    getline(inputfile, white_space);
    getline(inputfile, h);
    h_length = stoi(h);

    for(int i = 0; i < h_length; i++)
    {
        string t;
        int c;
        inputfile >> t >> c;
        Sunday = new SundayRow();
        Sunday->start = t; 
        SundayRow* temp;
        Sunday->parent = temp;
        Sunday->heuristic = c;
        r.push_back(Sunday);
    }

    // Passes all the data through this function which takes in the algorithm, vector of LiveRow, the States, and the output file
    Algorithm(Algo, v, StartState, GoalState, out);

    // Closes the output file
    out.close();
}
