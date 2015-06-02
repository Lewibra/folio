#include "point.h"
#include <stdio.h>
#include <math.h>
#include <string>

using namespace std;

/** \brief
 * Constructor that sets the x and y
 * co-ordinates for this point object
 * \param x - x co-ordinate
 * \param y - y co-ordinate
 *
 */
Point::Point(double x, double y)
{
    this->x = x;
    this->y = y;
}

/** \brief
 *  Destructor
 *
 */
Point::~Point()
{
    //dtor
}

/** \brief
 * Returns the distance between
 * this point object and another
 * \param point - the point you want the distance to
 * \return Distance
 */
double Point::distanceTo(Point* point)
{
    long double euclideanDistance = sqrt(pow(x - point->x, 2) + pow(y - point->y, 2));
    return euclideanDistance;
}


/** \brief
 *  Produces a string representation for this object
 * \param out - the ostream
 * \param point - the point to output
 * \return String representation
 *
 */
ostream& operator<<(ostream& out, Point& point)
{
    double x = point.x;
    double y = point.y;

    out << x << " " << y;
    return out;
}
