#ifndef GRAPH_H
#define GRAPH_H
#include <queue>
#include <vector>
#include <iostream>
#include <iomanip>
#include "edge.h"
#include "disjointset.h"

using namespace std;

class Graph
{
    public:
        Graph(unsigned int);
        virtual ~Graph();

        void addVertex(Vertex*);

        Vertex* getVertex(int);

        void addEdge(Edge*);

        double minimumSpanningTreeCost();

        void dijkstra(unsigned int);

        void bfs(unsigned int);

        friend ostream& operator<<(ostream&, Graph&);
    protected:
    private:

        unsigned int numVertices;

        double** weights;

        priority_queue<Edge*, vector<Edge*>, Edge> edges;


        vector<Vertex*> vertices;

        double minCost;

        int edgeCount;

        DisjointSet *disjoint;

        int infinity = 1000000000;

};

#endif // GRAPH_H
