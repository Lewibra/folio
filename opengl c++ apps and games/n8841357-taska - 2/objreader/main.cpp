#define GLEW_STATIC
#include "loader.h"
#include "coordinate.h"
#include "face.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <windows.h>
#include <GL/glew.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <math.h>
# define M_PI           3.14159265358979323846
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))


using namespace std;

BYTE ** m_image;
GLdouble dr, dg, db;
GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0};

GLuint shaderProgramID;
GLfloat* vertices;
GLfloat* normals;
GLint* faces;
GLfloat* verticesBody;
GLfloat* normalsBody;
GLint* facesBody;
int amountOfFaces;
int vertSize;
int normalSize;
int indicieSize;
int amountOfFacesBody;
int vertSizeBody;
int normalSizeBody;
int indicieSizeBody;

GLdouble boundaries = 7.0;

double rotate_y=0;
double rotate_x=0;
double rotate_y2=0;
double rotate_x2=0;
Loader* loader = new Loader();

bool xPressed = false;

GLuint vertexbuffer;
GLuint normalbuffer;
GLuint elementbuffer;

GLdouble lols1 = 0.0;
GLdouble lols2 = 0.0;
GLdouble lols3 = 0.0;

GLuint vertexbufferBody;
GLuint normalbufferBody;
GLuint elementbufferBody;

int orthoDimension = 4;
bool falling;
bool zPressed = false;
GLfloat r = 1;
GLfloat g = 0.8;
GLfloat b = -0.1;
GLfloat wingAngle = 20.0f;
GLfloat rate = 2;
GLfloat fallingRate = 0.1;
GLdouble x, y, z;
GLdouble tempx, tempy, tempz;
GLdouble xRate = 0.02;
GLdouble xRate2 = 0.05;
GLdouble yRate = 0.05;
GLdouble yRate2 = 0.05;

GLfloat move_x = 0.0;
GLfloat move_z = 0.0;
GLfloat move_y = 0.0;
GLfloat speed = 1.0;
GLfloat worldRotate = 0;

GLfloat spinAround;

static char* readFile(const char* filename){
    FILE* fp = fopen(filename, "r");

    fseek(fp, 0, SEEK_END);
    long file_length = ftell(fp);

    fseek(fp, 0, SEEK_SET);

    char* contents = new char[file_length+1];

    for (int i = 0; i < file_length+1; i++){
        contents[i] = 0;
    }

    fread(contents, 1, file_length, fp);
    contents[file_length+1] = '\0';

    fclose(fp);

    return contents;
}



void loadBuffers()
{

     //Load Buffers
    //vertices
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(GLfloat), vertices, GL_DYNAMIC_DRAW);

    //normals
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normalSize * sizeof(GLfloat), normals, GL_DYNAMIC_DRAW);
    //indices
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicieSize * sizeof(GLint), faces , GL_DYNAMIC_DRAW);

    //vertices
    glGenBuffers(1, &vertexbufferBody);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbufferBody);
    glBufferData(GL_ARRAY_BUFFER, vertSizeBody * sizeof(GLfloat), verticesBody, GL_DYNAMIC_DRAW);
    //normals
    glGenBuffers(1, &normalbufferBody);
    glBindBuffer(GL_ARRAY_BUFFER, normalbufferBody);
    glBufferData(GL_ARRAY_BUFFER, normalSizeBody * sizeof(GLfloat), normalsBody, GL_DYNAMIC_DRAW);
    //indices
    glGenBuffers(1, &elementbufferBody);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbufferBody);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicieSizeBody * sizeof(GLint), facesBody , GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

bool drop(void)
{
    if (zPressed)
    {
        if (move_y <= -4.0)
        {
            return false;
        }
        return true;
    }
}

bool fallDown(void)
{

    if (xPressed)
    {
        cout << falling << endl;

        if (move_y <= -4.0)
        {
            speed *= 0.95;
            return false;
        }

        return true;
    }


}


GLfloat cameraspeed = -8.0;
GLfloat LR;
void Draw(void)
{

    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    GLfloat posLight0[] = {-2.0f, 2.0f, -3.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, posLight0);
    gluPerspective(90.0f, 500.0f/500.0f, 0.001f, 100);
//    loadBuffers();
    //glOrtho(-orthoDimension, orthoDimension, -orthoDimension, orthoDimension, -orthoDimension, orthoDimension);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);


    //vertices
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexPointer(3, GL_FLOAT,0, (void*)0);
    //Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    //Normals
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glNormalPointer(GL_FLOAT, 0, (void*)0);


    glRotatef(worldRotate, 0.0, 1.0, 0.0);

    glScalef(1.0, 1.0, 1.0);

    glTranslatef(0,0,cameraspeed);

    glPushMatrix();
            glTranslated(move_x, move_y, move_z);
        glPushMatrix();

            //glRotated(LR, 0.0, 1.0, 0.0);
            glRotated(spinAround, 0.0, 1.0, 0.0);



            glPushMatrix();
            //glTranslated(0.0, 0.0, 0.0);

            //glRotated(180.0f, 0.0, 1.0, 0.0);
                glPushMatrix();
                    glColor3f(r, g, b);
                    glTranslated(1.325, 0.5, -0.5);
                    glRotated( rotate_x, 0.0, 1.0, 1.0 );
                    //glRotated( rotate_y, 0.0, 1.0, 0.0 );
                    glDrawElements(GL_TRIANGLES, amountOfFaces, GL_UNSIGNED_INT, (void*)0);
                glPopMatrix();

                glPushMatrix();
                    glColor3f(r, g, b);
                    glScaled(-1, -1, -1);
                    glRotated(180.0, 1.0, 0.0, 0.0 );
                    glTranslated(-0.790, 0.5, -0.5);
                    glRotated( rotate_x, 0.0, 1.0, 1.0 );
                    //glRotated( rotate_y, 0.0, 1.0, 0.0 );
                    glDrawElements(GL_TRIANGLES, amountOfFaces, GL_UNSIGNED_INT, (void*)0);
                glPopMatrix();



    //body
            //vertices
                glBindBuffer(GL_ARRAY_BUFFER, vertexbufferBody);
                glVertexPointer(3, GL_FLOAT,0, (void*)0);
                //Indices
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbufferBody);
                //Normals
                glBindBuffer(GL_ARRAY_BUFFER, normalbufferBody);
                glNormalPointer(GL_FLOAT, 0, (void*)0);

                glTranslated(1.0, 0.0, 0.0);
                glPushMatrix();
                    glColor3f(r, g, b);
                    //glRotated( rotate_x, 1.0, 0.0, 0.0 );
                    //glRotated( rotate_y, 0.0, 1.0, 0.0 );
                    glDrawElements(GL_TRIANGLES, amountOfFacesBody, GL_UNSIGNED_INT, (void*)0);
                glPopMatrix();

            glPopMatrix();
        glPopMatrix();
   // glPopMatrix();


    glRotated(LR, 0.0, 1.0, 0.0);
    glPushMatrix();


        glPushMatrix();
        glTranslated(lols1*-1, 0.0, lols1*-1);
        glBegin(GL_LINES);
        for(int i=-10;i<=10;i++) {
            if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
            glVertex3f(i,-5,-10);
            glVertex3f(i,-5,10);
            if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
            glVertex3f(-10,-5,i);
            glVertex3f(10,-5,i);
        };
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslated(0.0, lols1, lols1);
        glBegin(GL_LINES);
        for(int i=-10;i<=10;i++) {
            if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
            glVertex3f(i,-5,-10);
            glVertex3f(i,15,-10);
            if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
            glVertex3f(-10,i+5,-10);
            glVertex3f(10,i+5,-10);
        };
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslated(lols1 *-1, 0.0, 0.0);
        glBegin(GL_LINES);
        for(int i=-5;i<=15;i++) {
            if (i==5) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
            glVertex3f(10,i,-10);
            glVertex3f(10,i,10);
            if (i==5) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
            glVertex3f(10,-5,i-5);
            glVertex3f(10,15,i-5);
        };
        glEnd();
        glPopMatrix();
    glPopMatrix();

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutSwapBuffers();
}

void reshape(int w, int h)
{

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-4.0, 4.0, -3.0 * (GLfloat) h / (GLfloat) w,
            5.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-4.0 * (GLfloat) w / (GLfloat) h,
            4.0 * (GLfloat) w / (GLfloat) h, -3.0, 5.0, -10.0, 10.0);
    //glMatrixMode(GL_MODELVIEW);
}


void update(int value)
{

    if (fallDown()){
        move_y -= fallingRate;
        spinAround += 30.0f;
        rate -= 0.05;

        move_z -= cos(spinAround * (M_PI/180))*rate;
        move_x -= sin(spinAround * (M_PI/180))*rate;
    }else if (drop()){
        move_y -= 0.05;
    }else{
        rate = 2;
        move_z -= (cos(spinAround * (M_PI/180))/5)*speed;
        move_x -= (sin(spinAround * (M_PI/180))/5)*speed;
    }
    if (move_x > boundaries)
    {
        move_x = boundaries;
    }else if (move_x < -boundaries)
    {
        move_x = -boundaries;
    }
    if (move_z > boundaries)
    {
        move_z = boundaries;
    }else if (move_z < -boundaries)
    {
        move_z = -boundaries;
    }




    rotate_x += wingAngle;
    rotate_y += 2.0f;


    if (rotate_x > 60.0f || rotate_x < 0.0f)
    {
        wingAngle *= -1;
    }

    if(rotate_y>360.f)
    {
        rotate_y-=360;
    }
    if(spinAround>360.f)
    {
        LR-=360;
    }

    glutPostRedisplay();
    glutTimerFunc(25,update,0);
}

void specialKeys(unsigned char key, int x, int y)
{
    if (key =='x' || fallDown())
    {
        xPressed = true;
    }else if(key =='z' || drop()) {
        zPressed = true;
    }else{
        switch (key)
        {
            //escape
            case 27:
                exit (0);
                break;
            case 'a':
                spinAround += 5.0f;
                break;
            case 'd':
                spinAround -= 5.0f;
                break;
            case 's':
                move_x -= (sin(spinAround * (M_PI/180))/5)*2;
                move_z -= (cos(spinAround * (M_PI/180))/5)*2;
                break;
            case 'r':
                move_x = 0.0;
                move_z = 0.0;
                move_y = 0.0;
                speed = 1;
                zPressed = false;
                xPressed = false;
                break;

            case 'l':
                lols1 -= 0.5;
                boundaries +=0.5;
                break;
            case 'o':
                lols1 += 0.5;
                boundaries -= 0.5;
                break;
            case 'g':
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, greenEmissiveMaterial);
                break;


        }
    }


    //  Request display update
    glutPostRedisplay();
}

void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            cameraspeed += 0.5;

            break;
        case GLUT_KEY_DOWN:
            cameraspeed -= 0.5;

            break;
        case GLUT_KEY_LEFT:
            worldRotate -= 5.0;
            break;
        case GLUT_KEY_RIGHT:
            worldRotate += 5.0;
            break;
    }
}


void setUpArrays()
{
    loader->loadObject("Wing.obj");


    vector<GLfloat> temp = loader->getVerticies();
    vertices = new GLfloat[temp.size()];
    memcpy(vertices, &temp.front(), sizeof(GLfloat) * temp.size());

    vector<GLfloat> tempNormal = loader->getNormals();
    normals = new GLfloat[tempNormal.size()];
    memcpy(normals, &tempNormal.front(), sizeof(GLfloat) * tempNormal.size());

    vector<GLint> tempIndices = loader->getFaces();
    faces = new GLint[tempIndices.size()];
    memcpy(faces, &tempIndices.front(), sizeof(GLint) * tempIndices.size());

    amountOfFaces = tempIndices.size();
    vertSize = temp.size();
    normalSize = tempNormal.size();
    indicieSize = tempIndices.size();



}

void setUpWings()
{
    Loader* bodyLoader = new Loader();
    bodyLoader->loadObject("Body.obj");


    vector<GLfloat> temp = bodyLoader->getVerticies();
    verticesBody = new GLfloat[temp.size()];
    memcpy(verticesBody, &temp.front(), sizeof(GLfloat) * temp.size());

    vector<GLfloat> tempNormal = bodyLoader->getNormals();
    normalsBody = new GLfloat[tempNormal.size()];
    memcpy(normalsBody, &tempNormal.front(), sizeof(GLfloat) * tempNormal.size());

    vector<GLint> tempIndices = bodyLoader->getFaces();
    facesBody = new GLint[tempIndices.size()];
    memcpy(facesBody, &tempIndices.front(), sizeof(GLint) * tempIndices.size());

    amountOfFacesBody = tempIndices.size();
    vertSizeBody = temp.size();
    normalSizeBody = tempNormal.size();
    indicieSizeBody = tempIndices.size();

}


GLuint makeVertexShader(const char* shaderSource){
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, (const GLchar**)&shaderSource, NULL);
    glCompileShader(vertexShaderID);
    return vertexShaderID;


}

GLuint makeFragShader(const char* shaderSource){
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, (const GLchar**)&shaderSource, NULL);
    glCompileShader(fragmentShaderID);
    return fragmentShaderID;


}

GLuint makeShaderProgram(GLuint vertex, GLuint frag){
    GLuint shaderID = glCreateProgram();
    glAttachShader(shaderID, vertex);
    glAttachShader(shaderID, frag);
    glLinkProgram(shaderID);
    return shaderID;


}



int main(int argc,char** argv)
{


    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Object Loader!");
    GLenum status = glewInit();
    assert(status ==0);

    char* vertexShaderSource = readFile("aVertexShader21.glsl");
    char* FRAGShaderSource = readFile("aFragShader21.glsl");

    GLuint vertShaderID = makeVertexShader(vertexShaderSource);
    GLuint fragShaderID = makeFragShader(FRAGShaderSource);
    shaderProgramID = makeShaderProgram(vertShaderID, fragShaderID);



    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);


    GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat amb[] = {0.1, 0.1, 0.1, 1.0};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);

    GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0};
    GLfloat mShininess[] = {128};



    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);



    setUpArrays();
    setUpWings();

    glutDisplayFunc(Draw);

    glutKeyboardFunc(specialKeys);
    glutSpecialFunc(SpecialInput);

    glutReshapeFunc(reshape);




    loadBuffers();

    glUseProgram(shaderProgramID);

    glutTimerFunc(25,update,0);
    glutMainLoop();
        return 0;
}
