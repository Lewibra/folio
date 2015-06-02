#ifndef LOADER_H
#define LOADER_H
#include "coordinate.h"
#include "face.h"
#include <vector>
using namespace std;
class Loader
{
    public:
        Loader();
        virtual ~Loader();
        void draw();
        void loadObject(const char* filename);
        void init();
        void display();
        vector<GLfloat> getNormals();
        vector<GLfloat> getVerticies();
        vector<GLint> getFaces();
        long getConnectedTriangles();

    protected:
    private:
        vector<GLint> setOfFaces;
        vector<GLfloat> vertex;
        vector<Face*> faces;
        vector<GLfloat> normals;
        long TotalConnectedTriangles;
};

#endif // LOADER_H
