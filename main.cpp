#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "AdjMatric.h"
#include "stack.h"

using namespace std;

const int vertex=5;
const int m=10;

void strongConnected(Graph &, bool &);
void DFS(int ,bool ,bool [],stack<int[]> &,Graph &);
void printSolution1(int [][vertex]);
void transitiveClosure(int [][vertex]);
int minDistance(int [], bool []);
bool printPath(int [], int ,int,bool &);
bool printSolution(int [], int , int [],int ,int );
bool dijkstra(Graph &, int , int);
void displaycycle(int ,int [vertex][vertex]);
void findcycle(int ,int &,bool ,int [m][m],Graph );
bool cycledetect(Graph );
void randomedges(Graph &,int);
int getnewWeight(int , int );
void resetGraph(Graph &, int[vertex][vertex],int[vertex][vertex]);


// Driver Code
int main()
{
    int  V1,V2,W,choice;
 	int edge[vertex][vertex]={{0,1,0,0,1},{0,0,1,0,0},{0,0,0,1,0},{0,0,0,0,0},{0,0,0,1,0}};
	int weight[vertex][vertex]={{0,8603,0,0,8396},{0,0,4608,0,0},{0,0,0,10483,0},{0,0,0,0,0},{0,0,0,9615,0}};
    bool strong = false,path,cycle;
    Graph obj;

    for(int i=0;i<vertex;i++){
    	for (int j=0;j<vertex;j++){
    		if (edge[i][j]==1)
    			obj.addEdge(i, j);
    			obj.addWeight(i,j,weight[i][j]);
		}
	}

 	do{
			system("cls");
			cout<<char (218);
 			for(int i=1;i<40;i++)
				cout<<char (196);
			cout<<char (191);

			cout<<endl<<char (179)<<"Main Menu"<<"\t\t\t\t"<<char (179);
			cout<<endl<<char (179)<<"1. Display adjacency list"<<" \t\t"<<char (179);
			cout<<endl<<char (179)<<"2. Add Edge"<<"\t\t\t\t"<<char (179);
			cout<<endl<<char (179)<<"3. Remove Edge"<<"\t\t\t\t"<<char (179);
			cout<<endl<<char (179)<<"4. Display Weight for every Edge"<<"\t"<<char (179);
            cout<<endl<<char (179)<<"5. Finding Shortest Path"<<"\t\t"<<char (179);
            cout<<endl<<char (179)<<"6. Cycle Detection"<<"\t\t\t"<<char (179);
			cout<<endl<<char (179)<<"7. Strong Connection graph"<<"\t\t"<<char (179);
            cout<<endl<<char (179)<<"8. Reset graph"<<"\t\t\t\t"<<char (179)<<endl;
			cout<<char (192);
 			for(int i=1;i<40;i++)
				cout<<char (196);
 			cout<<char (217);

			cout<<"\nEnter your choice: ";
			cin>>choice;
			if(choice>8||choice<1){
				while(choice>8||choice<1){
					cout<<"\nChoice Not Listed!!\nEnter your choice: ";
					cin>>choice;
				}
			}
	        system("CLS");

	        switch(choice){
	            case 1:
	                    // print adjacency matric representation of a graph
						cout << "Adjacency Matric of Graph Edge :";
						obj.displayEdge();
						cout << "\n\nAdjacency Matric of Graph Weight :";
						obj.displayWeight();
						cout<<endl;
	        			system("pause");
	        			break;
	            case 2:
						cout << "Insert Vector 1 :";
						cin >> V1;
						cout << "Insert Vector 2 :";
						cin >> V2;
						W = getnewWeight(V1,V2);
	                    obj.addEdge(V1,V2);
	                    obj.addWeight(V1,V2,W);
						cout << "\nNew Adjacency Matric :";
						obj.displayEdge();
						cout<<endl;
	        			system("pause");
	        			break;

	            case 3:
						cout << "Insert Vector 1 :";
						cin >> V1;
						cout << "Insert Vector 2 :";
						cin >> V2;
	                    obj.removeEdge(V1,V2);
	                    obj.removeWeight(V1,V2);
						cout << "\nNew Adjacency Matric :";
						obj.displayEdge();
						cout<<endl;
	        			system("pause");
	        			break;
	        	case 4:
	        			obj.WeightEdge();
	        			system("pause");
	        			break;
	        	case 7:
	        			strongConnected(obj,strong);

	        			system("pause");
	        			while(strong!=true){
                            randomedges(obj,choice);
		        			strongConnected(obj,strong);
	        				system("pause");
						}
	        			break;

                case 5:
                        cout << "Vertex 1: " ;
                        cin >> V1;
                        cout << "\nVertex 2: ";
                        cin >> V2;
                        path = dijkstra(obj, V1,V2);
                        cout<<endl<<endl;
                        while (path!=true){
                        	cout<<endl<<"There is no path from vertex "<<V1<<" to "<<V2<<endl<<endl;
                        	system("pause");
                        	system("CLS");
                        	randomedges(obj,choice);
							cout<<endl<<endl;
                        	path = dijkstra(obj, V1,V2);
						}
						cout<<endl<<endl;
                        system("pause");
                        break;

                case 6:
						cout<<"Cycle path :"<<endl<<endl;
						path=cycledetect(obj);
						while (path!=true){
                        	system("pause");
                        	system("CLS");
                        	randomedges(obj,choice);
							cout<<endl;
                        	path = cycledetect(obj);
						}
						cout<<"\nThere are Cycle that has been detected in this graph."<<endl<<endl;
                		system("pause");
                        break;
                case 8:
                		resetGraph(obj,edge,weight);
                        break;

	    	}
	        if(choice==9)
	        	break;
		}while(choice<10||choice>0);

}

void DFS(int from,bool trans,bool visit[vertex],stack<int> &stack,Graph &obj){
	bool Checkedge;
	for (int i=0;i<vertex;i++){
		if(trans==true)
			Checkedge=obj.getTg(from,i);
		else
			Checkedge=obj.getg(from,i);

		if (Checkedge==true){
			if(visit[i]==false){
				visit[i]=true;
				DFS(i,trans,visit,stack,obj);
				stack.Push(from);
				stack.Push(i);
			}
		}
		Checkedge=false;
	}
}

void strongConnected(Graph &obj, bool &s)  {
	stack<int> stack, stack2;
	bool visit[vertex];
	bool strong[2]={true,true};
	int root=0;

	//set all visit point as false
	for(int i=0;i<vertex;i++)
		visit[i]=false;
	//DFS for graph
	for(int i = 0; i<vertex; i++){
      	if(visit[i]==false)
			DFS(i,false,visit,stack,obj);
	}

	//Displaying the path of DFS graph
	cout<<"Path based on DFS :\n";
	int a=stack.numStackNode();
	for(int i=0;i<a;i++){
		int To = stack.Top();
		stack.Pop();
		i++;
		int From = stack.Top();
		stack.Pop();
		cout<<" "<<From<<" -> "<<To<<endl;
	}

	for(int i=0;i<vertex;i++){
		//check for strong connection if strong false, it not strong
		if(visit[i]==false)
			strong[0]=false;

		//set all visit point as false
		visit[i]=false;
	}

	//create a transpose matrix
	obj.transEdge();

	//DFS for graph
	for(int j = 0; j<vertex; j++){
      	if(visit[j]==false)
			DFS(j,true,visit,stack2,obj);
	}
	//Displaying the path of transpose graph
	cout<<"Path based on DFS :\n";
	int a2=stack2.numStackNode();
	for(int i=0;i<a2;i++){
		int To = stack2.Top();
		stack2.Pop();
		i++;
		int From = stack2.Top();
		stack2.Pop();
		cout<<" "<<From<<" -> "<<To<<endl;
	}
	for(int i=0;i<vertex;i++){
		//check for strong connection if strong false, it not strong
		if(visit[i]==false)
			strong[2]=false;
	}
	if(strong[0]==true&&strong[1]==true){
		s=true;
		cout<<"\nThe graph is STRONGLY Connected."<<endl;
	}
	else{
		s=false;
		cout<<"\nThe graph is NOT STRONGLY Connected."<<endl;
	}
}

int minDistance(int dist[], bool sptSet[])
{

    // Initialize min value
    int min = INT_MAX, min_index;
    // set the minimum distance
    for (int v = 0; v < vertex; v++){
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
	}
    return min_index;
}

bool printPath(int parent[], int j,int V2,bool &path)
{
    // Base Case : If j is source
    if (parent[j] == - 1)
        return path;
	else{
        //Recursive case
	    printPath(parent, parent[j],V2,path);
	    printf("-> %d ", j);
		if(j==V2)
			path=true;
	    return path;
	}
}

bool printSolution(int dist[], int n, int parent[], int src, int V2)
{
	bool path=false;
    //this will print the vertex, its distance total and its path
	printf("\nVertex\t \tDistance\tPath\n");
	for (int i =src; i < V2+1; i++)
    {
    	if(dist[i]!=INT_MAX){
    		printf("\n%d -> %d \t\t %d\t\t %d ", src, i, dist[i], src);
        	path=printPath(parent, i,V2,path);
		}

    }
	return path;
}

bool dijkstra(Graph &obj, int src, int V2)
{

    // The output array. dist[vertex] will hold the shortest distance from src to vertex
    int dist[vertex];

    // sptSet[vertex] will true if vertex is included / in shortest
    // path tree or shortest distance from src to i is finalized
    bool sptSet[vertex];

    // Parent array to store shortest path tree
    int parent[vertex];

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < vertex; i++)
    {
        parent[i] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;
	int u;
    // Find shortest path for all vertices
    for (int count = 0; count < vertex - 1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not yet processed. u is always equal to src
        // in first iteration.
        u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < vertex; v++){

            // Update dist[v] only if is not in sptSet, there is an edge from u to v, and total weight of path from
            // src to v through u is smaller than current value of dist[v]
            if (!sptSet[v] && obj.getw(u,v) && dist[u] +obj.getw(u,v) < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + obj.getw(u,v);
            }
		}

    }

	bool path;
    // print the constructed
    // distance array
    path = printSolution(dist, vertex, parent,src,V2);
    return path;
}

void displaycycle(int cycle,int path[m][m]){
	for(int i=0;i<cycle;i++){
		int j=1;
		if(path[i][0]!=INT_MAX){
			cout<<path[i][0];
			while(path[i][j]!=INT_MAX){
				cout<<" -> "<<path[i][j];
				j++;
			}
		cout<<endl<<endl;
		}
	}

}
void findcycle(int i,int &cycles,bool reverse,int path[m][m],Graph obj){
	int from=i,ver=0,count=1,k;

	//use visiting point and initialize it first as false
	bool visit[vertex]={false,false,false,false,false};

	//set first vertex(root) on the path
	path[cycles][0]=i;

	//find circle and if circle not found, get out from looping
	while(ver==0){
		//serch path from root vertex until no more path found
		for(int j=0;j<vertex;j++){
			if(reverse==true)
				k=(vertex-1)-j;
			if(reverse==false)
				k=j;
			if(visit[k]==false){
				if(obj.getg(from,k)==1){
					visit[k]=true;
					path[cycles][count]=k;
					from=k;
					count++;
					if(visit[i]==true){
						cycles++;
						count--;
					}
					break;
				}
			}
			if(j==(vertex-1))
				ver=1;
		}
		if(visit[i]==true)
			break;
	}

	//checking if the cycle found, if not reset all path to 0
	if(ver==1){
		for(int j=0;j<m;j++)
			path[cycles][j]=INT_MAX;
	}
}

bool cycledetect(Graph obj){
	int cycles=0;
	int path[m][m];

	//initialize all path for cycles by infinite NULL value.
	for(int i=0;i<m;i++){
		for(int j=0;j<m;j++)
			path[i][j]=INT_MAX;
	}

	//finding circle with root starting from each vertex
	//the path will follow through increasing value of vertex.
	for(int i=0;i<vertex;i++){
		findcycle(i,cycles,false,path,obj);
	}

	//finding circle with root starting from each vertex
	//the path will follow through increasing value of vertex.
	for(int i=0;i<vertex;i++){
		findcycle(i,cycles,true,path,obj);
	}

	//deleting all the repeated or same circles made
	//by the findcycle() function
	int c=0;
	for(int i=cycles;i>0;i--){
		int j=1;
		while(path[i-1][j]!=INT_MAX){
			if(path[i][j-1]==path[i-1][j])
				c++;
			j++;
		}
		if(c>=2){
			for(int k=0;k<vertex;k++)
				path[i][k]=INT_MAX;
		}
	}

	//Displaying the path of cycles found
	if(cycles==0){
		cout<<" There is no cycle exist in the graph !!"<<endl<<endl;
		return false;
	}
	else{
		displaycycle(cycles,path);
		return true;
	}
}

void randomedges(Graph &obj,int cases){
    system("CLS");
    int V1,V2;
    int w;

    cout<<" Generating new edge to find....\n\n";
    do{
        V1=rand() % 5;
        V2=rand() % 5;
        if(cases!=7){
        	while(obj.getg(V1,V2)==1||obj.getg(V2,V1)==1){
	            V1=rand() % 5;
	            V2=rand() % 5;
	        }
		}
		else{
			while(obj.getg(V1,V2)==1){
	            V1=rand() % 5;
	            V2=rand() % 5;
	            if(V1==4&&V2==0){
	            	V1=rand() % 5;
	            	V2=rand() % 5;
				}
				if(V1+1==V2||V2+1==V1){
					V1=rand() % 5;
	            	V2=rand() % 5;
				}
	        }
		}
    }while(V1==V2);
    cout<<" New added edge : "<<V1<<" -> "<<V2<<endl<<endl;
    obj.addEdge(V1,V2);
    w=getnewWeight(V1,V2);
    obj.addWeight(V1,V2,w);
}

int getnewWeight(int i, int j){
		int weight[5][5];
        weight[0][2]=8918;
        weight[2][0]=weight[0][2];
        weight[0][3]=4437;
        weight[3][0]=weight[0][3];
        weight[1][4]=2887;
        weight[4][1]=weight[1][4];
        weight[1][3]=7282;
        weight[3][1]=weight[1][3];
        weight[2][4]=1767;
        weight[4][2]=weight[2][4];
		return weight[i][j];
}

void resetGraph(Graph &obj, int e[vertex][vertex], int w[vertex][vertex]){
    obj.resetmatric();

    int edge[vertex][vertex]={{0,1,0,0,1},{0,0,1,0,0},{0,0,0,1,0},{0,0,0,0,0},{0,0,0,1,0}};
	int weight[vertex][vertex]={{0,8603,0,0,8396},{0,0,4608,0,0},{0,0,0,10483,0},{0,0,0,0,0},{0,0,0,9615,0}};

    for(int i=0;i<vertex;i++){
    	for (int j=0;j<vertex;j++){
    		if (edge[i][j]==1)
    			obj.addEdge(i, j);
    			obj.addWeight(i,j,weight[i][j]);
		}
	}
    cout<<"Graph has been RESET to default";

}

