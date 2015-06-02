#ifndef EDGE_H
#define EDGE_H
#include <iostream>
#include <iomanip>
#include "vertex.h"

using namespace std;

class Edge
{
    public:
        Edge();
        Edge(Vertex*, Vertex*, double);
        virtual ~Edge();

        Vertex* getSource();

        Vertex* getDestination();

        double getWeight();

        bool operator()(Edge*, Edge*);

        friend ostream& operator<<(ostream&,Edge&);


    protected:
    private:
        Vertex* source;

        Vertex* destination;

        double weight;

};

#endif // EDGE_H
