#include "face.h"

Face::Face(int numFaces, int face1, int face2, int face3, int face4)
{
    this->numFaces = numFaces;
    faces[0] = face1;
    faces[1] = face2;
    faces[2] = face3;
    faces[3] = face4;
    four = true;

}

Face::Face(int numFaces, int face1, int face2, int face3)
{
    this->numFaces = numFaces;
    faces[0] = face1;
    faces[1] = face2;
    faces[2] = face3;
    four = false;
}

Face::~Face()
{
    //dtor
}

int Face::getFaceNum()
{
    return numFaces;
}

bool Face::isQuad()
{
    return four;
}

void Face::setToQuad()
{
    four = true;
}

void Face::notQuad()
{
    four = false;
}
