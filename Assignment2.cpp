#include <iostream>
#include <vector>
#include <stdint.h>
#include <stack>

using namespace std;

struct Edge{
    int destination;
    int weight;
}
struct Node{
    vector<Edge> connections;
    int32_t distance;
    bool visited;
    uint32_t parents;
    uint32_t path_count;
}

int main(){
    int vertices = -1, edges = -1;
    cin >> vertices >> edges;
    vector<Node> graph;
    graph.resize(vertices);
    
    for(int i = 0; i < edges; ++i){
       int start, end, w;
       cin >> start >> end >> w;
       start-=1; end-=1;
       //problem here maybe
       graph.at(start).connections.push_back(end,w);
    }

    // for(int i = 0; i < vertices; ++i){

    // }

    //initialize the graph
    for (Node& node : graph) {
        node.distance = INT_MAX;
        node.visited = false;
    }

    //Configure the starting node
    graph[0].distance = 0; 
    vector<int32_t> queue;
    queue.push_back(0);

    //starting the SPF algorithm (modified)
    while(!queue.empty()){
        int32_t n = queue.pop();
        if(graph[n].visited){
             continue;
        }
        if (graph[n].path_count == (vertices)){
            while(!graph[n].visited){
                graph[n].visited = true;
                n = graph[n].parent;
            }
            //DFS
            vector<int32_t> d;
            d.push_back(n);
            while(!d.empty()){
                int current = d.back();  // Getting the last element
                d.pop_back();  // Removing the last element

                for (Edge edge : graph[current].connections) {
                    if (!graph[edge.destination].visited) {
                        graph[edge.destination].visited = true;
                        d.push_back(edge.destination);  // Pushing to 'stack'
                    }
                } 
            }

        }else{
            for (Edge& edge : graph[n].connections) {
                if (graph[n].distance - edge.weight < graph[edge.destination].distance){
                    graph[edge.destination].distance = graph[n].distance - edge.weight;
                    queue.push_back(edge.destination);
                    edge.destination.parent = n;
                    graph[edge.destination].path_count = graph[n].path_count + 1;
                }
            }

        }


    }
    return 0;
}