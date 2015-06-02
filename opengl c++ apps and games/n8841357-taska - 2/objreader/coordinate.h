#ifndef COORDINATE_H
#define COORDINATE_H
#include<GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Coordinate
{
    public:
        Coordinate(GLfloat x, GLfloat y, GLfloat z);
        virtual ~Coordinate();
        GLfloat x,y,z;
    protected:
    private:

};

#endif // COORDINATE_H
