#include "loader.h"
#include "coordinate.h"
#include "face.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <windows.h>
#define GLEW_STATIC
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
#include "InitShader.h"
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))
using namespace std;

GLuint shaderProgramID;
GLfloat* vertices;
GLfloat* normals;
GLint* faces;
int amountOfFaces;
double rotate_y=0;
double rotate_x=0;
double rotate_y2=0;
double rotate_x2=0;
Loader* loader = new Loader();
GLuint vertexbuffer;
GLuint normalbuffer;
GLuint elementbuffer;
GLfloat r = 1;
GLfloat g = 0.8;
GLfloat b = -0.1;

GLfloat xRate = 0.02;
GLfloat xRate2 = 0.05;
GLfloat yRate = 0.05;
GLfloat yRate2 = 0.05;

GLfloat move_x = 1.0;
GLfloat move_x2 = 1.0;
GLfloat move_y = 1.0;
GLfloat move_y2 = 1.0;

GLfloat mouse_x = -3.0, mouse_y= 3.0;
GLfloat mouse_x2 = 3.0, mouse_y2= 3.0;
GLfloat mouse_x3 = 3.0, mouse_y3= -3.0;
GLfloat mouse_x4 = -3.0, mouse_y4= -3.0;
GLfloat mouseXCoord = 0.0, mouseYCoord= 0.0;

GLuint topLeft = 1, topRight = 2, bottomLeft = 3, bottomRight = 4;

int vertSize;
int normalSize;
int indicieSize;

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
    glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(GLfloat) * 3, vertices, GL_DYNAMIC_DRAW);
    //normals
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normalSize * sizeof(GLfloat) * 3, normals, GL_DYNAMIC_DRAW);
    //indices
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicieSize * sizeof(GLfloat) * 3, faces , GL_DYNAMIC_DRAW);
}


void Draw(void)
{

    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();




    loadBuffers();
    glOrtho(-8, 8, -8, 8, -8, 8);
    glInitNames();
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glTranslatef(0,2,0);
    //vertices
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexPointer(3, GL_FLOAT,0, (void*)0);

    //Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

    //Normals
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glNormalPointer(GL_FLOAT, 0, (void*)0);

    glPushMatrix();
    glTranslatef(move_x, move_y, 0);
    glColor3f(r, g, b);
    glRotated( rotate_x, 1.0, 0.0, 0.0 );
    glRotated( rotate_y, 0.0, 1.0, 0.0 );




    glDrawElements(GL_TRIANGLES, amountOfFaces, GL_UNSIGNED_INT, (void*)0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2,0);
    glTranslatef(move_x2, move_y2, 0);
    glRotated( rotate_x2, 1.0, 0.0, 0.0 );

    glRotated( rotate_y2, 0.0, 1.0, 0.0 );

    glDrawElements(GL_TRIANGLES, amountOfFaces, GL_UNSIGNED_INT, (void*)0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(mouse_x, mouse_y, 0);
    glRotated( rotate_x2, 1.0, 0.0, 0.0 );
    glRotated( rotate_y2, 0.0, 1.0, 0.0 );
    glutSolidIcosahedron();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(mouse_x2, mouse_y2, 0);
    glRotated( rotate_x2, 1.0, 0.0, 0.0 );
    glRotated( rotate_y2, 0.0, 1.0, 0.0 );
    glutSolidIcosahedron();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(mouse_x3, mouse_y3, 0);
    glRotated( rotate_x2, 1.0, 0.0, 0.0 );
    glRotated( rotate_y2, 0.0, 1.0, 0.0 );
    glutSolidIcosahedron();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(mouse_x4, mouse_y4, 0);
    glRotated( rotate_x2, 1.0, 0.0, 0.0 );
    glRotated( rotate_y2, 0.0, 1.0, 0.0 );
    glutSolidIcosahedron();
    glPopMatrix();



    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glFlush();
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

bool moveUp;
bool moveLeft;
bool moveUp2;
bool moveLeft2;

//GLfloat mouse_x = -2.0, mouse_y= 2.0;
//GLfloat mouse_x2 = 2.0, mouse_y2= 2.0;
//GLfloat mouse_x3 = 2.0, mouse_y3= -2.0;
//GLfloat mouse_x4 = -2.0, mouse_y4= -2.0;

void update(int value)
{
    rotate_y+=2.0f;
    rotate_x+=2.0f;

    rotate_y2+=7.0f;
    rotate_x2+=7.0f;

    if (!moveLeft){
        if ((move_x <= (GLfloat) mouse_x2))
        {
            move_x += xRate;
            r += 0.002;
            g += 0.006;
            b += 0.002;
        }else if((move_x >= (GLfloat) mouse_x2))
        {
            moveLeft = true;
        }
    }else{
        if ((move_x >= (GLfloat) mouse_x))
        {
            r -= 0.002;
            g -= 0.006;
            b -= 0.002;
            move_x -= xRate;
        }else
        {
            moveLeft = false;
        }
    }

    if (!moveLeft2){
        if ((move_x2 <= (GLfloat) mouse_x3))
        {
            move_x2 += xRate2;

        }else if((move_x2 >= (GLfloat) mouse_x3))
        {
            moveLeft2 = true;
        }
    }else{
        if ((move_x2 >= (GLfloat) mouse_x4))
        {
            move_x2 -= xRate2;
        }else
        {
            moveLeft2 = false;
        }
    }


if (moveUp){
        if (move_y == mouse_y2)
        {

        }else
        if ((move_y <= (GLfloat) mouse_y2))
        {
            move_y += yRate;
        }else if((move_y >= (GLfloat) mouse_y2))
        {
            moveUp = false;
        }
    }else{
        if (move_y == mouse_y)
        {

        }else
        if ((move_y >= (GLfloat) mouse_y))
        {
            move_y -= yRate;
        }else
        {
            moveUp = true;
        }
    }




    if(rotate_y>360.f)
    {
        rotate_y-=360;
    }

    if(rotate_y2>360.f)
    {
        rotate_y2-=360;
    }
    glutPostRedisplay();
    glutTimerFunc(25,update,0);
}

void specialKeys(int key, int x, int y)
{
    //  Right arrow - increase rotation by 5 degree
    if (key == GLUT_KEY_RIGHT){
      //rotate_y += 5;
      //move_x += 0.01;
    }
    //  Left arrow - decrease rotation by 5 degree
    else if (key == GLUT_KEY_LEFT){
      //rotate_y -= 5;
      mouse_y2 -= 0.02;
      //move_x -= 0.01;
    }
    else if (key == GLUT_KEY_UP){
      //rotate_x += 5;
      mouse_y2 += 0.05;
    }
    else if (key == GLUT_KEY_DOWN){
      //rotate_x -= 5;
    }



    //  Request display update
    glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y)
{
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)){
      xRate *= 2;
      xRate2 *= 2;

      cout << x << ", " << y << endl;

    }
    else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)){
      xRate /= 2;
      xRate2 /= 2;
    }
}

void drag(int x, int y)
{

    //mouse_x = ((GLfloat)x *(2/500.0)) - 1.0f;
    //mouse_y = ((GLfloat)y *(2/500.0)) - 1.0f;
    //cout << mouse_x << ", " << mouse_y << endl;

}


void setUpArrays()
{
    loader->loadObject("cube.obj");


    vector<GLfloat> temp = loader->getVerticies();
    vertices = new GLfloat[temp.size()];
    memcpy(vertices, &temp.front(), sizeof(GLfloat) * temp.size());

    vector<GLfloat> tempNormal = loader->getNormals();
    normals = new GLfloat[tempNormal.size()];
    memcpy(normals, &tempNormal.front(), sizeof(GLfloat) * tempNormal.size());

    vector<GLint> tempIndices = loader->getFaces();
    faces = new GLint[tempIndices.size()];
    memcpy(faces, &tempIndices.front(), sizeof(GLint) * tempIndices.size());
    cout << "Indices: ";
    for (unsigned int i = 1; i < tempIndices.size()+1; i ++)
    {
        cout << faces[i-1] << " ";
        if (i % 3 == 0)
        {
            cout << endl;
        }
    }
    amountOfFaces = tempIndices.size();
    vertSize = temp.size();
    normalSize = tempNormal.size();
    indicieSize = tempIndices.size();
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

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Object Loader!");
    GLenum status = glewInit();
    assert(status ==0);

    char* vertexShaderSource = readFile("aVertexShader21.glsl");
    char* FRAGShaderSource = readFile("aFragShader21.glsl");

    cout << vertexShaderSource;

    //GLuint vertShaderID = makeVertexShader(vertexShaderSource);
    //GLuint fragShaderID = makeFragShader(FRAGShaderSource);
    //shaderProgramID = makeShaderProgram(vertShaderID, fragShaderID);



    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat posLight0[] = {0.0f, 0.0f, -1.0f, 0.0f};
    GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, posLight0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);

    setUpArrays();

    glutDisplayFunc(Draw);
    glutPassiveMotionFunc(drag);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouseClick);
    glutReshapeFunc(reshape);

    //loadBuffers();

    //glUseProgram(shaderProgramID);

    glutTimerFunc(25,update,0);
    glutMainLoop();
        return 0;
}
