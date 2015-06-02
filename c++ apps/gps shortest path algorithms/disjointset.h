#ifndef DISJOINTSET_H
#define DISJOINTSET_H


class DisjointSet
{
    public:
        DisjointSet(unsigned int);
        virtual ~DisjointSet();

        bool sameComponent(unsigned int, unsigned int);

        unsigned int find(unsigned int);

        void join(unsigned int, unsigned int);
    protected:
    private:

        unsigned int elements;

        unsigned int* sizes;
        unsigned int* id;
};

#endif // DISJOINTSET_H
