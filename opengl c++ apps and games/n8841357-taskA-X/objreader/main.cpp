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

GLdouble x, y, z;
GLdouble tempx, tempy, tempz;
GLdouble xRate = 0.02;
GLdouble xRate2 = 0.05;
GLdouble yRate = 0.05;
GLdouble yRate2 = 0.05;

GLfloat move_x = 3.0;
GLfloat move_x2 = -3.0;
GLfloat move_y = 3.0;
GLfloat move_y2 = -3.0;

GLfloat currentX, currentY;

GLfloat mouse_x = -3.0, mouse_y= 3.0;
GLfloat mouse_x2 = 3.0, mouse_y2= 3.0;
GLfloat mouse_x3 = 3.0, mouse_y3= -3.0;
GLfloat mouse_x4 = -3.0, mouse_y4= -3.0;
GLfloat mouseXCoord = 0.0, mouseYCoord= 0.0;

GLuint topLeft = 1, topRight = 2, bottomLeft = 3, bottomRight = 4;

GLfloat worldRotate = 0;

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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicieSize * sizeof(GLint) * 3, faces , GL_DYNAMIC_DRAW);
}


void Draw(void)
{

    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat posLight0[] = {-2.0f, 2.0f, -3.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, posLight0);
//    loadBuffers();
    glOrtho(-8, 8, -5, 8, -8, 8);
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
    glRotatef(worldRotate, 0.0, 1.0, 0.0);

    glPushMatrix();
    glTranslatef(move_x, move_y, 0);
    glColor3f(r, g, b);
    glRotated( rotate_x, 1.0, 0.0, 0.0 );
    glRotated( rotate_y, 0.0, 1.0, 0.0 );

    //glDrawElements(GL_TRIANGLES, amountOfFaces, GL_UNSIGNED_INT, (void*)0);

    glDrawElements(GL_QUADS, amountOfFaces, GL_UNSIGNED_INT, (void*)0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(move_x2, move_y2, 0);
    glRotated( rotate_x2, 1.0, 0.0, 0.0 );
    glRotated( rotate_y2, 0.0, 1.0, 0.0 );

    //glDrawElements(GL_TRIANGLES, amountOfFaces, GL_UNSIGNED_INT, (void*)0);

    //Call this method for "allcube.obj" or anything that uses quads
    glDrawElements(GL_QUADS, amountOfFaces, GL_UNSIGNED_INT, (void*)0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(mouse_x, mouse_y, 0);
    glRotated( rotate_x2, rotate_y2, 0.0, 0.0 );
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(mouse_x2, mouse_y2, 0);
    glRotated( rotate_x2, rotate_y2, 0.0, 0.0 );
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(mouse_x3, mouse_y3, 0);
    glRotated( rotate_x2, rotate_y2, 0.0, 0.0 );
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(mouse_x4, mouse_y4, 0);
    glRotated( rotate_x2, rotate_y2, 0.0, 0.0 );
    glutSolidCube(1);
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

bool moveUp;
bool moveLeft;
bool moveUp2;
bool moveLeft2;

GLfloat disFromXtoX2;
GLfloat disFromTopCubetoX2;
GLfloat disFromTopCubetoX;
GLfloat speed = 1.0;

void update(int value)
{
    rotate_y+=2.0f;
    rotate_x+=2.0f;

    rotate_y2+=7.0f;
    rotate_x2+=7.0f;
    if (!moveLeft){
        if ((move_x <= (GLfloat) mouse_x2))
        {

            move_x += xRate * speed;
        }else if((move_x >= (GLfloat) mouse_x2))
        {
            moveLeft = true;
        }

    }else{
        if ((move_x >= (GLfloat) mouse_x))
        {
            move_x -= xRate * speed;
        }else
        {
            moveLeft = false;
        }
    }


    if (!moveLeft2){

        if ((move_x2 <= (GLfloat) mouse_x3))
        {
            move_x2 += xRate2 * speed;

        }else if((move_x2 >= (GLfloat) mouse_x3))
        {
            moveLeft2 = true;
        }
    }else{
        if ((move_x2 >= (GLfloat) mouse_x4))
        {
            move_x2 -= xRate2 * speed;
        }else
        {
            moveLeft2 = false;
        }
    }


    if (moveLeft)
    {
        r += 0.02;
        g += 0.03;
        b += 0.005;
    }else {
        r -= 0.02;
        g -= 0.03;
        b -= 0.005;
    }



    if(rotate_y>360.f)
    {
        rotate_y-=360;
    }

    if(worldRotate>360.f)
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
        if(mouse_x < mouse_x2)
        {
      mouse_x += 0.1;
      mouse_x4 += 0.1;
      mouse_x2 -= 0.1;
      mouse_x3 -= 0.1;
        }

    }
    //  Left arrow - decrease rotation by 5 degree
    else if (key == GLUT_KEY_LEFT){
      mouse_x -= 0.1;
      mouse_x4 -= 0.1;
      mouse_x2 += 0.1;
      mouse_x3 += 0.1;

    }
    else if (key == GLUT_KEY_UP){
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }
    else if (key == GLUT_KEY_DOWN){
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }else if (key == GLUT_KEY_F1){
        worldRotate += 5;

    }



    //  Request display update
    glutPostRedisplay();
}


bool isPointInShape(GLdouble x, GLdouble y, GLdouble bottomLeftX, GLdouble topRightX
                               , GLdouble bottomLeftY, GLdouble topRightY) {
    bool inX = false;
    bool inY = false;
    if (x > bottomLeftX && x < topRightX)
        inX = true;

    if (y > bottomLeftY && y < topRightY)
        inY = true;

    return (inX && inY);
}

bool objectPicker(GLdouble objXCenter, GLdouble objYCenter)
{
    return (isPointInShape(x, y, objXCenter - 0.5, objXCenter + 0.5, objYCenter - 0.5, objYCenter + 0.5));

}

bool clickedTopLeft;
bool clickedTopRight;
bool clickedBottomLeft;
bool clickedBottomRight;
void drag(int x_cursor, int y_cursor)
{

    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX,winY;
    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    // obtain the Z position (not world coordinates but in range 0 - 1)
    GLfloat z_cursor;
    winX = (float)x_cursor;
     winY = (float)viewport[3]-(float)y_cursor;
    glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z_cursor);

    // obtain the world coordinates
    auto succes = gluUnProject(winX, winY, z_cursor, modelview, projection, viewport, &tempx, &tempy, &tempz);
    assert (succes == GL_TRUE);
    x = tempx;
    y = tempy;
    z = tempz;

    if (clickedTopLeft){
       mouse_x = x;
       mouse_y = y;
       mouse_y2 = y;
       move_y = y;
    }else if (clickedTopRight){
       mouse_x2 = x;
       mouse_y = y;
       mouse_y2 = y;
       move_y = y;
    }else if (clickedBottomRight){
       mouse_x3 = x;
       mouse_y3 = y;
       mouse_y4 = y;
       move_y2 = y;
    }else if (clickedBottomLeft){
       mouse_x4 = x;
       mouse_y3 = y;
       mouse_y4 = y;
       move_y2 = y;
    }




}

void mouseClick(int button, int state, int pixelx, int pixely)
{
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)){
        cout<<x<<" "<<"Printed out variable x"<<endl;
        cout<<y<<" "<<"Printed out variable y"<<endl;
        cout<<z<<" "<<"Printed out variable z"<<endl;

    if (objectPicker(mouse_x, mouse_y)){
            //top left
        r= 1.0;
        g= 0.0;
        b= 0.0;

        if (clickedTopLeft)
        {
            clickedTopLeft = false;
        }else{
            clickedTopLeft = true;
        }
    }else if (objectPicker(mouse_x2, mouse_y2)){
        //topright square
        r = 1.0;
        g = 1.0;
        b = 0.0;


        if (clickedTopRight)
        {
            clickedTopRight = false;
        }else{
            clickedTopRight = true;
        }


    }
    else if (objectPicker(mouse_x3, mouse_y3)){
        r = 1.0;
        g = 1.0;
        b = 1.0;

        if (clickedBottomRight)
        {
            clickedBottomRight = false;
        }else{
            clickedBottomRight = true;
        }

    }else if (objectPicker(mouse_x4, mouse_y4)){

        r = 1.0;
        g = 0.0;
        b = 1.0;



        if (clickedBottomLeft)
        {
            clickedBottomLeft = false;
        }else{
            clickedBottomLeft = true;
        }

    }else{
        r = 0.0;
        g = 0.0;
        b = 1.0;

        clickedBottomLeft = false;
        clickedBottomRight = false;
        clickedTopLeft = false;
        clickedTopRight = false;

        if (speed <= 16.0)
        {
            speed *= 2.0;
        }
    }
        //clickedTopLeft = false;

    }
    else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)){
        if (speed >= 0.1)
        {
            speed /=2;
        }

    }
}


void setUpArrays()
{
    loader->loadObject("win.obj");


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
    cout << "VERT: "<< endl ;
    for (unsigned int i = 1; i < temp.size()+1; i ++)
    {
        cout << temp[i-1] << " ";
        if (i % 3 == 0)
        {
            cout << endl;
        }
    }
    cout << "Norm: "<< endl ;
    for (unsigned int i = 1; i < tempNormal.size()+1; i ++)
    {
        cout << tempNormal[i-1] << " ";
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


    setUpArrays();

    glutDisplayFunc(Draw);
    glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(drag);
    glutSpecialFunc(specialKeys);

    glutReshapeFunc(reshape);

    loadBuffers();

    glUseProgram(shaderProgramID);

    glutTimerFunc(25,update,0);
    glutMainLoop();
        return 0;
}
