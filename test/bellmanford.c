#include <stdio.h>
#include "debug.h"

int INT_MAX = 9999;

// edges (u,v,w)
int graph[8][3] =
 {{0, 1, -1}, {0, 2, 4}, {1, 2, 3},  
  {1, 3, 2}, {1, 4, 2}, {3, 2, 5}, 
  {3, 1, 1}, {4, 3, -3}};

void bellmanford(int V, int E, int src) {
    // Initialize distance of all vertices as 0. 
	int dis[V];
	for(int v = 0; v < V; v++)
	    dis[v] = INT_MAX;
  
    // initialize distance of source as 0 
    dis[src] = 0;
  
    /*Relax all edges |V| - 1 times. A simple 
      shortest path from src to any other 
      vertex can have at-most |V| - 1 edges*/
    for(int i = 0; i < (V-1); i++) {
        for(int j = 0; j < E; j++) {
            if(dis[graph[j][0]] + graph[j][2] < dis[graph[j][1]])
                dis[graph[j][1]] = dis[graph[j][0]] + graph[j][2];
		}
	}
  
    /* check for negative-weight cycles. 
       The above step guarantees shortest 
       distances if graph doesn't contain 
       negative weight cycle. If we get a 
       shorter path, then there is a cycle. */
    for(int i = 0; i < E; i++) {
        int x = graph[i][0];
        int y = graph[i][1];
        int weight = graph[i][2];
        if (dis[x] != INT_MAX && dis[x] + weight < dis[y])
            print(2, "Graph contains negative weight cycle\n");
	}
  
    print(2, "Vertex Distance from Source\n");
    for(int i = 0; i < V; i++) {
		print(0, &i);
		print(2, "\t");
		print(0, &dis[i]);
		print(2, "\n");
	}
}

int main() {
	init();
	bellmanford(5, 8, 0);
}


