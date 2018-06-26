/*	Hanna Salings
	Floyd Warshall and Dijkstra Algorithms: Shortest Path Problem
	CS2500 Section 1B
*/
#include <iostream>
#define MAX 100		//used in order to create function outside of main and allow the user to input vertice #
#define INF 999		//user inputs 999 for infinity value
using namespace std;

void dijkstra(int matrix[MAX][MAX], int verticeNum, int source);
void floydW(int matrix[MAX][MAX], int verticeNum);

int main()
{
    int verticeNum;
	int source;
	char algorithm;
	char choice;
	bool repeat = true;
	int matrix[MAX][MAX];
	
	while (repeat == true)
	{
		cout<< "Floyd Warshall or Dijkstra? ('F' or 'D'): ";
		cin >> algorithm;
	
		cout << "Enter the amount of vertices: ";
		cin >> verticeNum;
		while (verticeNum <= 0)
		{
			cout << "Must have a postive value! Re-enter vertice amount: ";
			cin >> verticeNum;
		}
	
		cout << "Values of matrix: " << endl;
		for (int i=0; i < verticeNum; i++)
		{
			for(int j=0; j < verticeNum; j++)
			{
				cout << "Enter weights for row " << i << " and column "<< j <<": ";
				cin >> matrix[i][j];
				while (matrix[i][j] < 0 && algorithm == 'D')
				{
					cout << "Djikstra algorithm cannot run negative weights! Please re-enter weight value: " << endl;
					cin >> matrix[i][j];
				}
				cout << "["<< i << "][" <<j <<"] = " << matrix[i][j] << " " << endl;
			}
		}
	
		if (algorithm == 'D')
		{
			cout << "Enter the source vertex: ";
			cin >> source;
			while (source >= verticeNum)
			{
				cout << "Source value too large, please re-enter: ";
				cin >> source;
			}
  
  	 	 	dijkstra(matrix, verticeNum, source);
		}
		
		else if (algorithm == 'F')
		{
			floydW(matrix, verticeNum);
		}
		
		cout << "Enter another matrix? (Y/N): ";
		cin >> choice;
		if (choice == 'N' || choice == 'n')
		{
			repeat = false;
		}
		else if (choice == 'Y' || choice == 'y')
		{
			repeat = true;
		}
	}
	
    return 0;
}

void dijkstra(int matrix[MAX][MAX], int verticeNum, int source)
{
    int distance[verticeNum];		// Distance matrix: distance from source -> i
  	int path[verticeNum];
    bool shortPath[verticeNum]; 	// If vertex is in the shortest path, set to true
  	
  	// Initializations: 
    for (int i = 0; i < verticeNum; i++)
    {
		shortPath[i] = false;		// Set to false until vertix is in shortest path
		distance[i] = INF;
		path[i] = -1;
	}
    distance[source] = 0;			// Distance from source -> source
  
	// Find shortest path
   for (int k = 0; k < verticeNum-1; k++)	//minimum distance between nearby vertices is calculated
	{
    	int minDistance = INF;
		int nextPath;
    	for (int v = 0; v < verticeNum; v++)
    	{
     		if ((!shortPath[v]) && distance[v] <= minDistance)	//if vertex not already on shortest path and less than the minimum distance
     		{
         		minDistance = distance[v];
				nextPath = v;
         	}
         	//else it keeps same value and moves onto next vertex
    	}
    	
       shortPath[nextPath] = true;		//vertex is added onto the shortest path
       
       // check for next vertex
       for (int i = 0; i < verticeNum; i++)
       {
  			if ((!shortPath[i]) && matrix[nextPath][i] && distance[nextPath] != MAX)
            {
				if (distance[i] > distance[nextPath] + matrix[nextPath][i])
            	{
					distance[i] = distance[nextPath] + matrix[nextPath][i];
					path[i] = nextPath;
				}
			}
		} 
     } //end first for-loop
    
	// Output
	for(int i=0; i < verticeNum; i++)
	{
    	cout << "	Vertex   Distance from Source   Path (Target <- Source)" << endl;
        cout << " 	  " << i << "		" << distance[i] << "		";
        int j = i;
        cout << i;					//outputs target value
        while (j != source)
        {
            j = path[j];
            cout << " <- " << j;	//target <- source
        }
        cout << " " << endl;
	}
}

void floydW(int matrix[MAX][MAX], int verticeNum)
{
	int distance[verticeNum][verticeNum];	//distance matrix
 	
 	// Set new matrix equal to the user input matrix
    for (int i = 0; i < verticeNum; i++)
    {
        for (int j = 0; j < verticeNum; j++)
        {
    		distance[i][j] = matrix[i][j];
    	}
    }
 
	// Goes through all vertice one at a time
    for (int v = 0; v < verticeNum; v++)
    {
        for (int i = 0; i < verticeNum; i++)
        {
            for (int j = 0; j < verticeNum; j++)
            {
                // Check if v is an intermediate vertex on the shortest-path
                if (distance[i][v] + distance[v][j] < distance[i][j])
                {
                    distance[i][j] = distance[i][v] + distance[v][j];	//distance is updated if v is on the shortest path
            	}
            	// if v is not on the shortest path, there is no change in the array
            }
        }
    }
 
	// Output
    cout << "Shortest distances: " << endl;
    for (int i = 0; i < verticeNum; i++)
    {
        for (int j = 0; j < verticeNum; j++)
        {
            if (distance[i][j] == INF)
            {
            	cout << "	INF";
        	}
            else
            {
                cout << "	" << distance[i][j];
        	}
        }
        cout << " " << endl;
    }	
}
