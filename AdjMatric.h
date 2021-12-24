#include<iostream>

using namespace std;
const int n=5;
class Graph {
private:

    // Adjacency matrix
    int g[5][5];
    int w[5][5];
    int Tg[5][5];

public:
    // Constructor
    Graph()
    {

        // Initializing each element of the
        // adjacency matrix to zero
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                g[i][j] = 0;
                Tg[i][j] = 0;
            }
        }
    }
    int getTg(int i,int j){
    	return Tg[i][j];
	}
	int getg(int i,int j){
    	return g[i][j];
	}
	int getw(int i,int j){
    	return w[i][j];
	}
    // Function to display adjacency matrix
    void displayEdge()
    {
        // Displaying the 2D matrix
        for (int i = 0; i < n; i++) {
            cout << "\n";
            for (int j = 0; j < n; j++) {
                cout << " " << g[i][j];
            }
        }
    }
    void displayTEdge()
    {
        // Displaying the 2D matrix
        for (int i = 0; i < n; i++) {
            cout << "\n";
            for (int j = 0; j < n; j++) {
                cout << " " << Tg[i][j];
            }
        }
    }

    // Function to update adjacency
    // matrix for edge insertion
    void addEdge(int x, int y)
    {
        // Checks if the vertices
        // exist in the graph
        if ((x < 0) || (x >= n)) {
            cout << "Vertex" << x
                 << " does not exist!";
        }
        if ((y < 0) || (y >= n)) {
            cout << "Vertex" << y
                 << " does not exist!";
        }

        // Checks if it is a self edge
        if (x == y) {
            cout << "Same Vertex!";
        }

        else {
            // Insert edge
            g[x][y] = 1;
        }
    }

    // Function to update adjacency
    // matrix for edge removal
    void removeEdge(int x, int y)
    {
        // Checks if the vertices
        // exist in the graph
        if ((x < 0) || (x >= n)) {
            cout << "Vertex" << x
                 << " does not exist!";
        }
        if ((y < 0) || (y >= n)) {
            cout << "Vertex" << y
                 << " does not exist!";
        }

        // Checks if it is a self edge
        if (x == y) {
            cout << "Same Vertex!";
        }

        else {
            // Remove edge
            g[y][x] = 0;
            g[x][y] = 0;
        }
    }

    void transEdge(){
    	for(int i=0;i<n;i++){
    		for(int j=0;j<n;j++){
    			if(g[i][j]==1)
    				Tg[j][i]=1;
    			else if(g[i][j]==0)
    				Tg[j][i]=0;
			}
		}
	}

	void resetmatric(){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                g[i][j]=0;
                Tg[i][j]=0;
                w[i][j]=0;
            }
        }
	}

    int getww(int i,int j){
    for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if(g[i][j]==1)
                    return w[i][j];
            }
        }
    }
    void displayWeight();
    void addWeight(int x, int y,int weight);
    void removeWeight(int x, int y);
    void WeightEdge();
};


    void Graph :: displayWeight()
    {
        // Displaying the 2D matrix
        for (int i = 0; i < n; i++) {
            cout << "\n";
            for (int j = 0; j < n; j++) {
                if(g[i][j]==1)
                    cout << " " << w[i][j];
                else
                    cout<<" "<< "0";
            }
        }
    }

    void Graph :: addWeight(int x, int y,int weight)
    {
        w[x][y] = weight;
    }

    void Graph :: removeWeight(int x, int y)
    {
    	if(w[x][y]==0)
    		cout<<"Edge of vertex "<<x<<" -> "<<y<<" is not found!"<<endl;
    	else
        	w[x][y] = 0;
    }

    void Graph :: WeightEdge(){
    	cout<<"Weight : \n\n";
    	for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if(g[i][j]==1){
                	cout<<"Vertex "<<i<<" -> "<<j<<" : "<<w[i][j]<<endl;
				}
            }
        }
	}
