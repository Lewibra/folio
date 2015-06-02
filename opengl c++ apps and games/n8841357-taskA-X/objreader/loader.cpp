#include "loader.h"
#include "coordinate.h"
#include "face.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <istream>
#include <iostream>
#define TOTAL_FLOATS_IN_TRIANGLE 9


using namespace std;


Loader::Loader()
{
    //ctor
}

Loader::~Loader()
{
    //dtor
}


vector<GLfloat> Loader::getNormals()
{
//    vector<GLfloat> tempNormals;
//    for (unsigned int i = 0; i < normals.size(); i++)
//    {
//        tempNormals.push_back(normals[i]->x);
//        tempNormals.push_back(normals[i]->y);
//        tempNormals.push_back(normals[i]->z);
//
//        cout << normals[i]->x << normals[i]->y << normals[i]->z << "  " << endl;
//    }
    return normals;
}

vector<GLfloat> Loader::getVerticies()
{
//    vector<GLfloat> tempVerticies;
//    for (unsigned int i = 0; i < vertex.size(); i++)
//    {
//        tempVerticies.push_back(vertex[i]->x);
//        tempVerticies.push_back(vertex[i]->y);
//        tempVerticies.push_back(vertex[i]->z);
//    }

    return vertex;
}

long Loader::getConnectedTriangles()
{
    return TotalConnectedTriangles;
}

void Loader::loadObject(const char* filename)
{
    vector<string*> coord;

    ifstream in(filename);

    if(!in.is_open())
    {
        cout << "Not opened" << endl;
    }

    char buf[1000];
    while(!in.eof())
    {
        in.getline(buf, 1000);
        coord.push_back(new string(buf));
    }


    for(int i=0; i<coord.size();i++)
    {
        if((*coord[i])[0] == '#')
        {
            continue;
        }else if ((*coord[i])[0] == 'v' && (*coord[i])[1]==' ')
        {
            GLfloat tempx,tempy, tempz;
            sscanf(coord[i]->c_str(),"v %f %f %f", &tempx, &tempy, &tempz);
            vertex.push_back(tempx);
            vertex.push_back(tempy);
            vertex.push_back(tempz);
        }else if ((*coord[i])[0] == 'v' && (*coord[i])[1]=='n')
        {
            GLfloat tempx,tempy, tempz;
            sscanf(coord[i]->c_str(),"vn %f %f %f", &tempx, &tempy, &tempz);

            normals.push_back(tempx);
            normals.push_back(tempy);
            normals.push_back(tempz);

        }else if ((*coord[i])[0] == 'f')
        {
            int a,b,c,d,e, neverUsed;
            if(count(coord[i]->begin(), coord[i]->end(), ' ') == 4)
            {
                sscanf(coord[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d",
                        &a,  &b, &c, &b, &d, &b, &e, &b);
                        faces.push_back(new Face(b,a,c,d,e));
            }else{
                sscanf(coord[i]->c_str(), "f %d//%d %d//%d %d//%d",
                        &a, &b, &c,  &b, &d,  &b);
                        faces.push_back(new Face(b,a,c,d));

            }



            TotalConnectedTriangles += TOTAL_FLOATS_IN_TRIANGLE;
        }
    }

    for (unsigned int i = 0; i < faces.size(); i++)
    {
        if(!faces[i]->isQuad()){
            setOfFaces.push_back((faces[i]->faces[0]) - 1);
            setOfFaces.push_back((faces[i]->faces[1]) - 1);
            setOfFaces.push_back((faces[i]->faces[2]) - 1);
        }else{
            setOfFaces.push_back((faces[i]->faces[0]) - 1);
            setOfFaces.push_back((faces[i]->faces[1]) - 1);
            setOfFaces.push_back((faces[i]->faces[2]) - 1);
            setOfFaces.push_back((faces[i]->faces[3]) - 1);
        }
    }


    in.close();
    //Avoiding memory leaking
    for(int i=0; i<coord.size();i++)
    {
        delete coord[i];
    }
    for(int i=0; i<faces.size();i++)
    {
        delete faces[i];
    }
//    for(int i=0; i<normals.size();i++)
//    {
//        delete normals[i];
//    }
//    for(int i=0; i<vertex.size();i++)
//    {
//        delete vertex[i];
//    }

}

vector<GLint> Loader::getFaces()
{
    return setOfFaces;
}

void Loader::draw()
{
    //    drawing ths obj
//    glBegin(GL_TRIANGLES);
//    for(int f = 0; f< faces.size(); f++)
//    {
//        glNormal3f(normals[faces[f]->getFaceNum() - 1]->x, normals[faces[f]->getFaceNum() - 1]->y, normals[faces[f]->getFaceNum() - 1]->z);
//        glVertex3f(vertex[faces[f]->faces[0] - 1]->x, vertex[faces[f]->faces[0] - 1]->y, vertex[faces[f]->faces[0] - 1]->z);
//
//        glVertex3f(vertex[faces[f]->faces[1] - 1]->x, vertex[faces[f]->faces[1] - 1]->y, vertex[faces[f]->faces[1] - 1]->z);
//
//        glVertex3f(vertex[faces[f]->faces[2] - 1]->x, vertex[faces[f]->faces[2] - 1]->y, vertex[faces[f]->faces[2] - 1]->z);
//    }
//    glEnd();
}
