#define GLEW_STATIC
#ifndef FACE_H
#define FACE_H


class Face
{
    public:
        Face(int numFaces, int face1, int face2, int face3, int face4);
        Face(int numFaces, int face1, int face2, int face3);
        virtual ~Face();
        int getFaceNum();
        bool isQuad();
        void setToQuad();
        void notQuad();
        int faces[4];
    protected:
    private:
        int numFaces;
        bool four;


};

#endif // FACE_H
