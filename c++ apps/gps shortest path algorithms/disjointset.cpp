#include "disjointset.h"

DisjointSet::DisjointSet(unsigned int elements)
{
    this->elements = elements;

    id = new unsigned int[elements];
    sizes = new unsigned int[elements];
    for (unsigned int i = 0; i < elements; i++)
    {
        id[i] = i;
        sizes[i] = 1;
    }
}

DisjointSet::~DisjointSet()
{
    //dtor
}

bool DisjointSet::sameComponent(unsigned int elm1, unsigned int elm2)
{
    return find(elm1) == find(elm2);
}

unsigned int DisjointSet::find(unsigned int i)
{
     while (i != id[i]) {
         id[i] = id[id[i]]; // make elements point to their grandparent
         i = id[i];
     }
     return i;
}

void DisjointSet::join(unsigned int p,unsigned int q)
{
    int i = find(p);
    int j = find(q);
    if (i==j) return;
    if(sizes[i] < sizes[j])
    {
        id[i] = j;
        sizes[j] += sizes[i];
    } else
    {
        id[j] = i;
        sizes[i] += sizes[j];
    }
}
