#pragma once

#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include "graph.h"
#include "edge.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <unordered_map>

using namespace cs225;
using std::unordered_map;
using std::pair;
using std::string;

/**
 * Represents a map of Airports and the routes that connect them.
 */
class AirportMap {
public:
  // Constructor to build graph from vectors of vertice names, lattitudes, and longitudes
  AirportMap(const std::vector<string> vertices, const std::vector<double> lats, const std::vector<double> longs, const std::vector<string> routes);

void graphicalOutput(const std::vector<Vertex> &path);

//Function to convert latitude/longitude values to correct pixel location on worldMap.
 int convertToPixel(double val, bool lat);

 void plotLineLow(int x0, int y0, int x1, int x2, PNG &png);
 
 void plotLineHigh(int x0, int y0, int x1, int x2, PNG &png);

// Function to find the distance between two location on the globe
 double findDistance(double lat1, double long1, double lat2, double long2);

  int vertices;    // Number of vertices
  vector<Vertex> *path; // path taken by DFS

  //AirportMap(int vertices); // constructor for vertices

  void DFS_helper(int vertices, bool visited[]); // helper function for DFS function

  vector<Vertex> DFS(Vertex start, Vertex destination); //DFS traversal function

private:

  Graph g_;
  Vertex startingVertex_;
  PNG worldMap;
  // pair in form <lat, long>
  unordered_map<Vertex, pair<double, double>> locations;
};
