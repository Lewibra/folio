#include <iostream>
#include <iomanip>
#include "vertex.h"
#include <set>
using namespace std;


/** \brief
 * No argument constructor
 */
Vertex::Vertex()
{
    //ctor
}

/** \brief
 *  Creates a vertex object with an id
 * \param identifier - the id of the vertex
 */
Vertex::Vertex(unsigned int identifier)
{
    this->identifier = identifier;
}

Vertex::~Vertex()
{
    //dtor
}

/** \brief
 *  Getter for the vertex's id
 * \return vertex id
 *
 */
unsigned int Vertex::getId()
{
    return identifier;
}

/** \brief
 *  Adds a vertex identifier (meant to be adjacent) to the set
 * of adjecencies, which is later used by
 * the Min spanning tree
 * \param identifier - id of the vertex to add
 */
void Vertex::addAdjacency(unsigned int  identifier)
{
    adjacencies.insert(identifier);
}


/** \brief
 *  Getter for the set of adjacencies
 * \return Set of adjacencies
 *
 */
set<unsigned int>* Vertex::getAdjacencies()
{
    return &adjacencies;
}


/** \brief
 *  Sets the vertex to discovered
 * or not discovered
 *\param true if discovered, false otherwise
 */
void Vertex::setDiscovered(bool boolean)
{
    discovered = boolean;
}


/** \brief
 * returns true if discovered
 *\return true if discovered, false otherwise
 */
bool Vertex::isDiscovered()
{
    return discovered;
}


/** \brief
 * Getter for the predecessor vertex's id
 * \return predecessor's id
 *
 */
unsigned int Vertex::getPredecessorId()
{
    return predecessorId;
}


/** \brief
 * Sets the minimum distance from this vertex
 * to the source vertex
 * \param distance - minimum distance
 *
 */
void Vertex::setMinDistance(double distance)
{
    minDistance = distance;
}


/** \brief
 * getter for the minimum distance from this
 * vertex and the source
 * \return minimum distance
 *
 */
double Vertex::getMinDistance()
{
    return minDistance;
}


/** \brief
 *Function operator implementation to
 *provide an ordering for two Vertex
 *instances. Used to order storage types
 * \return true if vertex1's min distance is greater than vertex2's
 *
 */
bool Vertex::operator()(Vertex* vertex1, Vertex* vertex2)
{
    return vertex1->getMinDistance() > vertex2->getMinDistance();
}


/** \brief
 *  sets the predecessor vertex's id
 * \param id - the id to set to
 *
 */
void Vertex::setPredecessorId(unsigned int id)
{
    predecessorId = id;
}


/** \brief
 *  Simple output of a string version of the vertex
 */
ostream& operator<<(ostream& out, Vertex& vert)
{
    out << vert.getId();
    return out;
}
