#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <vector>

/**
   Structure for storing vertex and colour information. Constructor
takes filename of text file that originally contains the data. Each
line of the file should contain position and colour information for a
vertex eg.

x1 y1 z1 w1 r1 g1 b1 a1
x2 y2 z2 w2 r2 g2 b2 a2
...

The position of the first vertex will be (x1,y1,z1,w1) and will have
colour (r1,g1,b1,a1). Positional information are assumed to be floats
and colour intensity information is expected to be unsigned integers
in the range 0-255.

Data is stored in 2 arrays of GLfloat, one corresponding to positions
and the other colours. Colour intensity information is converted from
0-255 to 0.0-1.0
 */
using namespace std;
class Object{

 private:

  GLfloat *vertices;
  GLfloat *colours;
  long unsigned int cSize, vSize;

  void parseLine(vector<double> *v, vector<double> *c, string line);
 
 public:

  Object(char *fname);
  ~Object();
  /** verts() returns address of vertices array */
  GLfloat *verts(){return vertices;};

  /** cols() returns an address for colours array */
  GLfloat *cols(){return colours;};

  /** number of bytes used for vertices*/
  long unsigned int vsize(){return vSize*sizeof(GLfloat);};

  /** number of bytes used for colours*/
  long unsigned int csize(){return cSize*sizeof(GLfloat);};

  /** number of vertices read*/
  long unsigned int numVertices(){return vSize/4;};

  void print();
};
