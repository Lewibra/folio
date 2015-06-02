/// File:  roads.cpp
///
/// Driver program for Shortest Distances.
///
/// This program can use as input:
/// 1.  Randomly generated points from the Cartesian plane
/// 2.  Points from the Cartesian plane read from a file (file name given as a command line argument)
///
/// The points are required to compute the edge weights between the vertices.
///
/// NOTES: The given code uses pointers to objects in most places.
///

#include <iostream>
#include <fstream>
#include <iomanip>

#include "random.h"
#include "point.h"
#include "graph.h"

using namespace std;

const int MINIMUM_COORDINATE = 0;
const int MAXIMUM_COORDINATE = 100;
const int NUM_CITIES = 10;
const int SOURCE = 0;
const double EDGE_PROBABILITY = 0.45;

int main(int argc, char *argv[]) {

   bool readFromFile = (argc == 2);
   bool includeEdge;
   ifstream infile;
   int numCities = NUM_CITIES;
   Random* random = new Random();
   Point** cities;

   // allow for testing from file
   if (readFromFile) {
      // open the file and check it exists
      infile.open(argv[1]);
      if (infile.fail()) {
         cerr <<  "Error: Could not find file" << endl;
         return 1;
      }

      // read the number of cities and their co-ordinates
      int xCoordinate, yCoordinate;
      infile >> numCities;
      cities = new Point*[numCities];
      for (int city = 0; city < numCities; city++) {
         infile >> xCoordinate >> yCoordinate;
         cities[city] = new Point(xCoordinate, yCoordinate);
         cout << "City " << setw(2) << city << " co-ordinates : " << *cities[city] << endl;
      }

   } else {

      // randomly create and store numCities points
      cities = new Point*[numCities];
      for (int city = 0; city < numCities; city++) {
         cities[city] = new Point(random->randomInteger(MINIMUM_COORDINATE, MAXIMUM_COORDINATE),
                                  random->randomInteger(MINIMUM_COORDINATE, MAXIMUM_COORDINATE));
         cout << "City " << setw(2) << city << " co-ordinates : " << *cities[city] << endl;
      }
   }
   cout << endl;

   // create the graph and add vertices for all cities
   Graph* graph = new Graph(numCities);
   for (int i = 0; i < numCities; i++) {
      Vertex* v = new Vertex(i);
      graph->addVertex(v);
   }

   // add edges to graph
   for (int i = 0; i < numCities - 1; i++) {
      for (int j = i + 1; j < numCities; j++) {
         if (readFromFile) {
            infile >> includeEdge;
         } else {
            includeEdge = random->randomChance(EDGE_PROBABILITY);
         }
         if (includeEdge) {

            Edge* edge = new Edge(graph->getVertex(i), graph->getVertex(j), cities[i]->distanceTo(cities[j]));
            graph->addEdge(edge);
         }
      }
   }

   // if necessary close the input file
   if (readFromFile) {
      infile.close();
   }

   cout << "Edge Weights" << endl;
   cout << "============" << endl;
   cout << *graph << endl << endl;


   cout << "Shortest Paths" << endl;
   cout << "==============" << endl;
   graph->dijkstra(SOURCE);
   cout << endl;

   double mstWeight = graph->minimumSpanningTreeCost();
   cout << "MST Weight = " << fixed << setprecision(2) << mstWeight << endl;
   cout << "===================" << endl << endl;

   cout << "Shortest Paths on MST" << endl;
   cout << "=====================" << endl;
   graph->bfs(SOURCE);
   cout << endl;

   delete random;
   for (int i = 0; i < numCities; i++) {
      delete cities[i];
   }
   delete[] cities;
   delete graph;

   return 0;
}
