#define GLEW_STATIC
#include "coordinate.h"

Coordinate::Coordinate(GLfloat x, GLfloat y, GLfloat z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Coordinate::~Coordinate()
{
    //dtor
}
