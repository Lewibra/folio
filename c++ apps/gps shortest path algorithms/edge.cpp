#include <iostream>
#include <iomanip>
#include "vertex.h"
#include "edge.h"
#include <set>
using namespace std;

/** \brief
 *  Empty constructor
 */
Edge::Edge()
{
    //ctor
}

/** \brief
 *  Sets the source vertex, destination vertex
 *  and the weight for them
 * \param source -source vert
 * \param destination - destination vertex
 * \param weight - weight of these two
 */
Edge::Edge(Vertex* source, Vertex* destination, double weight)
{
    this->source = source;
    this->destination = destination;
    this->weight = weight;
}

Edge::~Edge()
{
    //dtor
}

/** \brief
 * Getter for the source vertex
 * \return source vertex
 *
 */
Vertex* Edge::getSource()
{
    return source;
}

/** \brief
 * Getter for the destination vertex
 * \return destination vertex
 *
 */
Vertex* Edge::getDestination()
{
    return destination;
}


/** \brief
 * Getter for the edge weight
 * \return edge weight
 *
 */
double Edge::getWeight()
{
    return weight;
}


/** \brief
 *Function operator provides an ordering for
 *edges
 *\return true if edge1's weight is greater than edge2's
 */
bool Edge::operator()(Edge* edge1, Edge* edge2)
{
    return edge1->weight > edge2->weight;
}


/** \brief
 * puts this edge onto the ostream as a string
 * showing the source, destination and weight.
 */
ostream& operator<<(ostream& out, Edge& edge)
{
    out << "Source: " << edge.getSource() << " Destination: " << edge.getDestination() << " Weight: " << edge.getWeight();
    return out;
}
