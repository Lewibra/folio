#include "Object.h"
#include <sstream>

Object::Object(char *fname):vertices(0),colours(0),cSize(0),vSize(0){
  vector<double> tmpVertices;
  vector<double> tmpColours;

  ifstream inStream(fname);
  if (inStream.is_open()){

    string line;

    while(!inStream.eof()) {
      getline(inStream, line);
      if (!line.empty())
	parseLine(&tmpVertices, &tmpColours, line);
    }
    inStream.close();
    
    vSize = tmpVertices.size();
    vertices = new GLfloat[vSize];
    for (unsigned int i=0; i<vSize; vertices[i]=(GLfloat) tmpVertices[i],i++);
    cSize = tmpColours.size();
    colours = new GLfloat[cSize];
    for (unsigned int i=0; i<cSize; colours[i]= (GLfloat) tmpColours[i],i++);
  }
}

Object::~Object(){
  if (vertices!=0) delete [] vertices;
  if (colours!=0) delete [] colours;
}


void Object::parseLine(vector<double> *v, vector<double> *c, string line){

  stringstream ss(line);
  double x,y,z,w,r,g,b,a;
  ss >> x >> y >> z >> w >> r >> g >> b >> a;
  v->push_back(x);
  v->push_back(y);
  v->push_back(z);
  v->push_back(w);
  c->push_back(r/255.0);
  c->push_back(g/255.0);
  c->push_back(b/255.0);
  c->push_back(a/255.0);

}
void Object::print(){

  for (unsigned int i = 0; i<vsize(); i++){
    if (i%4==0)
      cout << endl << "v ";
    cout << vertices[i] << " ";
  }

  for (unsigned int i = 0; i<csize(); i++){
    if (i%4==0)
      cout << endl << "c ";
    cout << colours[i] << " ";
  }
  cout << endl << "vSize: " << vsize() << "  vSize: " << csize() << endl;
}
