#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <iomanip>

using namespace std;

class Point
{
    public:
        Point(double, double);

        virtual ~Point();

        double distanceTo(Point*);

        friend ostream& operator<< (ostream&, Point&);

    protected:
    private:

        double x;
        double y;
};

#endif // POINT_H
