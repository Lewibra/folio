#include <vector>
#include <iostream>
#include <iterator>
#include "graph.h"
#include "disjointset.h"

using namespace std;


/** \brief
 *Constructor sets the number of vertices in
 *this Graph. Initialises the two dimensional
 *array of weights by setting all values to
 *INFINITY, in my case 1000000000, but all diagonal
 *weights to 0 (from top left to bottom right)
 * \param vertices - the number of vertices in this matrix
 *
 */
Graph::Graph(unsigned int verticies)
{
    this->numVertices = verticies;

    ///set up the first part of the matrix
    weights = new double*[numVertices];

    ///set up the full matrix
    ///set everything to infinity, and all diagonals
    ///from top left to bottom right to 0
    for (int j = 0; j < numVertices; j++)
    {
        weights[j] = new double[numVertices];
        for (int i = 0; i < numVertices; i++)
        {
            weights[j][i] = infinity;

        }
        weights[j][j] = 0;
    }
}

Graph::~Graph()
{
    delete weights;
}


/** \brief
 *  adds a vertex to the vector of vertices
 * \param vertex- vertex to be added
 */
void Graph::addVertex(Vertex* vertex)
{
    vertices.push_back(vertex);
}


/** \brief
 *  getter for the vertex, based on it's index
 * \param index- index of the vertice you want to return
 *
 */
Vertex* Graph::getVertex(int index)
{
    return vertices[index];
}


/** \brief
 *  adds an edge to the weights matrix,
 *  based on that edge's source and destination id
 *  Also adds the edge to the edge queue.
 * \param Edge- edge to add.
 */
void Graph::addEdge(Edge* edge)
{
    ///add the weight from edge to the weights matrix, top and bottom
    weights[edge->getSource()->getId()][edge->getDestination()->getId()] = edge->getWeight();
    weights[edge->getDestination()->getId()][edge->getSource()->getId()] = edge->getWeight();
    ///push the edge onto the edge queue
    edges.push(edge);
}


/** \brief
 *  This uses Kruskal's algorithm to return
 * a minimum spanning tree for this graph.
 * Stores the edges of this MST in the adjacency
 * set from the Vertex class.
 * \return
 */
double Graph::minimumSpanningTreeCost()
{
    ///Set up important variables
    minCost = 0;
    edgeCount = 0;
    unsigned int N = numVertices;
    disjoint = new DisjointSet(N);

    ///Begin our while loop
    Edge *e;
    while (!edges.empty() && edgeCount < (N - 1))
    {
        ///Retrieve the top of the queue, then pop it
        e = edges.top();
        edges.pop();
        ///if the sourceid isn't the same component as the destination
        if (!disjoint->sameComponent(e->getSource()->getId(), e->getDestination()->getId()))
        {
            ///Join these two
            disjoint->join(e->getSource()->getId(), e->getDestination()->getId());

            ///add thes source and destination to the adjacency set
            e->getDestination()->addAdjacency(e->getSource()->getId());
            e->getSource()->addAdjacency(e->getDestination()->getId());
            ///add the weight of e to the mincost
            minCost += e->getWeight();
            edgeCount++;
        }
    }
    return minCost;
}


/** \brief
 *Determines the shortest path from the source
 *vertex to all other vertices. Prints the length
 *of the path and the vertex identifiers in the
 *path
 * \param sourceId - the source id of the source to get to
 */
void Graph::dijkstra(unsigned int sourceId)
{
    ///Set up the vertieces before we do anything
    priority_queue<Vertex*,vector<Vertex*>, Vertex> verticesQueue;
    for(int i=0; i<numVertices; i++)
    {

        vertices[i]->setDiscovered(false);
        vertices[i]->setPredecessorId(sourceId);
        vertices[i]->setMinDistance(weights[sourceId][vertices[i]->getId()]);
        ///Push these vertices onto the queue
        verticesQueue.push(vertices[i]);
    }

    while (!verticesQueue.empty())
    {
        ///retrieve queue top, pop it, and set it to discovered
        Vertex* u = verticesQueue.top();
        verticesQueue.pop();
        u->setDiscovered(true);

        ///For all vertieces, get that verticy and find it's weight
        for (unsigned int i = 0; i < numVertices; i++)
        {
            Vertex* v = getVertex(i);
            double weight = weights[u->getId()][i];
            ///id the weight isn't 0 or infinity
            if (weight != 0 && weight != infinity)
            {
                if (!v->isDiscovered())
                {
                    ///find the new distance with u's min distance and the weight from u to v
                    double newDistance = u->getMinDistance() + weights[u->getId()][v->getId()];
                    if (newDistance <= v->getMinDistance())
                    {
                        ///if it is smaller than v's current min distance, set v's
                        ///new min distance to newDistance, and set the predecessors
                        ///id to u's
                        v->setMinDistance(newDistance);
                        v->setPredecessorId(u->getId());
                        verticesQueue.push(v);
                    }

                }
            }
        }
    }


    ///Outputting the minDisrances and their paths

    ///for each verticy that isn't the source id
    ///output it's pathing and distance to the destination
    for(unsigned int i = 0; i < numVertices; i++)
    {
        if (i != sourceId)
        {
            ///If the min distance is infinity, there is no path
            if(vertices[i]->getMinDistance() == infinity)
            {
                cout << sourceId << " to " << vertices[i]->getId() <<" has no path" << endl;
            }
            else
            {
                ///Set up an id variable for the pathing output
                int id = i;
                ///output the distance from the source to each vertex
                cout.precision(2);
                cout << std::fixed;
                cout << "Distance from " << sourceId << " to " << vertices[id]->getId()<< " is " << vertices[id]->getMinDistance() << "; pathing: \t0";

                ///backtrack to the source from id(destination)
                vector<int> way;
                ///while id does not equal the source
                while(id != sourceId){
                    ///add the id of all previous vertieces to a vector
                    way.push_back(id);
                    id = vertices[id]->getPredecessorId();
                }

                ///output from the back of the vector to get
                ///the path from the source to the destination
                while(!way.empty()){
                    cout << "  " << way.back();
                    way.pop_back();
                }
                cout << endl;

            }

        }
    }

}


/** \brief
 *Determines the shortest path from the source
 *vertex to all other vertices using only the
 *adjacencies in the minimum spanning tree.
 *Prints the length of the path and the vertex
 *identifiers in the path.
 *
 * \param sourceId - id of the source to get to
 *
 */

void Graph::bfs(unsigned int sourceId)
{
    ///Set all vertices to undiscovered, create a queue
    ///, set tje source vector to discovered, push the
    ///source onto the queue
    for(int i=0; i<numVertices; i++)
    {
        vertices[i]->setDiscovered(false);
    }
    priority_queue<Vertex*,vector<Vertex*>, Vertex> verticesQueueBfs;
    vertices[sourceId]->setDiscovered(true);
    verticesQueueBfs.push(vertices[sourceId]);


    ///start of main bfs algorithm
    ///for every verticy in the queue, get it's adjacencies set
    while(!verticesQueueBfs.empty())
    {
        Vertex* u = verticesQueueBfs.top();
        verticesQueueBfs.pop();

        ///iterate through each adjacency and if it isn't discovered
        ///set the prececessor id u's id and push it into the queue
        for (set<unsigned int>::iterator i = u->getAdjacencies()->begin(); i != u->getAdjacencies()->end(); i++ )
        {
            unsigned int tempId = *i;
            Vertex* v = getVertex(tempId);
            if (!v->isDiscovered())
            {
                v->setPredecessorId(u->getId());
                v->setDiscovered(true);
                verticesQueueBfs.push(v);
            }
        }


    }


    ///Outputting the distances
    vector<Vertex*> way;
    for(unsigned int i = 0; i < numVertices; i++)
    {
        if (i != sourceId)
        {

            if (vertices[i]->getMinDistance() == infinity)
            {
                cout << sourceId << " to " << vertices[i]->getId() <<" has no path" << endl;
            }
            else
            {
                ///set up the distance, and an
                ///id variable for the pathing
                double distance = 0;
                int cId = i;

                ///while the current id isn't the sources, get the
                ///weights of the edges between the destination and source
                while (cId != sourceId)
                {
                    Vertex* u = vertices[cId];
                    Vertex* v = vertices[u->getPredecessorId()];

                    distance+= weights[cId][v->getId()];
                    cId = v->getId();
                }
                cout.precision(2);
                cout << std::fixed;
                cout << "Distance from " <<  sourceId << " to " << vertices[i]->getId()<< " is " << distance << "; pathing: \t0";


                ///same as thhe dij method, backtrack to find the path
                vector<int> way;
                int id = i;
                while(id != sourceId){
                    way.push_back(id);
                    id = vertices[id]->getPredecessorId();
                }

                while(!way.empty()){
                    cout << "  " << way.back();
                    way.pop_back();
                }
                cout << endl;

            }


        }



    }



}


/** \brief
 * Output the matrix onto the stream
 */
ostream& operator<<(ostream& out, Graph& graph)
{
    for (int i = 0; i < graph.numVertices; i++)
    {
        for (int j = 0; j < graph.numVertices; j++)
        {
            double outPut = graph.weights[i][j];
            if (outPut == graph.infinity)
            {
                out << "---" << "\t";
            }
            else
            {
                cout.precision(2);
                cout << std::fixed;
                out << outPut << "\t";
            }

        }
        out << endl;
    }

    return out;
}
