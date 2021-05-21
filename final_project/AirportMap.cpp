#include "AirportMap.h"
#include <math.h>
#include <algorithm>
#include <stack>

AirportMap::AirportMap(const std::vector<string> vertices, const std::vector<double> lats, const std::vector<double> longs, const std::vector<string> routes) : g_(Graph(true,true)) {
  // TODO
  worldMap.readFromFile("world_map.png");
  for (unsigned i = 0; i < vertices.size(); i++) {
    Vertex airport = vertices[i];
    locations[vertices[i]] = std::make_pair(lats[i], longs[i]);
    if (i == 0)
      startingVertex_ = airport;
    g_.insertVertex(airport);
  }
  for (string route : routes) {
    string source = route.substr(0,3);
    string dest = route.substr(3,3);
    g_.insertEdge(source, dest);
    std::pair<double, double> s = locations[source];
    std::pair<double, double> d = locations[dest];
    g_.setEdgeWeight(source, dest, findDistance(s.first, s.second, d.first, d.second));
  }
  this->vertices = g_.getVertices().size(); // This replaces AirportMap(int vertices)
}

void AirportMap::graphicalOutput(const std::vector<Vertex> &path) {
  //double vertRatio = 72/25;
  //double horizRatio = 126/50;
  PNG output = PNG(worldMap);
  //int originX = 551;
  //int originY = 269;
  
  Vertex source;
  Vertex dest;
  for (unsigned i = 0; i < path.size(); i++) {
    double sourceLat, sourceLong, destLat, destLong;
    bool destination = false;
    source = path[i];
    sourceLat = locations[source].first;
    sourceLong = locations[source].second;
    if (i+1 < path.size()) {
      dest = path[i+1];
      destLat = locations[dest].first;
      destLong = locations[dest].second;
      destination = true;
    }
    int sourceX = convertToPixel(sourceLong, false);
    int sourceY = convertToPixel(sourceLat, true);
    
    
    
    for (int x = -1; x < 2; x++) { // Draw 3x3 red square centered on source location
      for (int y = -1; y < 2; y++) {
	HSLAPixel pixel = output.getPixel(sourceX + x, sourceY + y);
	pixel.h = 0;
      }
    }
    if (destination) { // Using Bresenham's algorithm to draw lines
      int destX = convertToPixel(destLong, false);
      int destY = convertToPixel(destLat, true);
      if (std::abs(destY-sourceY) < std::abs(destX-sourceX)) {
	if ( sourceX > destX) {
	  plotLineLow(destX, destY, sourceX, sourceY, output);
	} else {
	  plotLineLow(sourceX, sourceY, destX, destY, output);
	}
      } else {
	if (sourceY > destY) {
	  plotLineHigh(destX, destY, sourceX, sourceY, output);
	} else {
	  plotLineHigh(sourceX, sourceY, destX, destY, output);
	}
      }
      for (int x = -1; x < 2; x++) { // Draw 3x3 red square centered on dest location
	for (int y = -1; y < 2; y++) {
	  HSLAPixel pixel = output.getPixel(destX + x, destY + y);
	  pixel.h = 0;
	}
      }
    }
  }
  output.writeToFile("output_map.png");
}

void AirportMap::plotLineLow(int x0, int y0, int x1, int y1, PNG &png) {
  int deltaX = x1 - x0;
  int deltaY = y1-y0;
  int yi = 1;
  
  if (deltaY < 0) {
    yi = -1;
    deltaY *= -1;
  }
  int D = (2 * deltaY) - deltaX;
  int y = y0;
  
  for (int x = x0; x < x1; x++) {
    HSLAPixel pixel = png.getPixel(x, y);
    pixel.h = 0;
    if (D > 0) {
      y += yi;
      D += (2 * (deltaY-deltaX));
    } else {
      D += 2*deltaY;
    }
  }
}

void AirportMap::plotLineHigh(int x0, int y0, int x1, int y1, PNG &png) {
  int deltaX = x1 - x0;
  int deltaY = y1-y0;
  int xi = 1;
  
  if (deltaX < 0) {
    xi = -1;
    deltaX *= -1;
  }
  int D = (2 * deltaX) - deltaY;
  int x = x0;
  
  for (int y = y0; y < y1; y++) {
    HSLAPixel pixel = png.getPixel(x, y);
    pixel.h = 0;
    if (D > 0) {
      x += xi;
      D += (2 * (deltaX-deltaY));
    } else {
      D += 2*deltaX;
    }
  }
}

// Graphical Output Helper Function
int AirportMap::convertToPixel(double val, bool lat) {
  double vertRatio = 72/25;
  double horizRatio = 126/50;
  int result;
  if (lat) {
    result = 269 - int(val*vertRatio);
  } else {
    result = 551 + int(val*horizRatio);
  }
  return result;
}

//AirportMap(int vertices) {
//    vertices = this->vertices;
//}


// DFS traversal
vector<Vertex> AirportMap::DFS(Vertex start, Vertex destination)
{
    vector<Vertex> path;

    // Initially mark all vertices as not visited
    unordered_map<Vertex, bool> visited;
    for (auto i = g_.getVertices().begin(); i != g_.getVertices().end(); ++i) {
      visited[*i] = false;
    } 

    // Create a stack for DFS
    std::stack<Vertex> stack;

    // Push the current source node.
    stack.push(start);

    while (!stack.empty()) {
      Vertex curr = stack.top();
      stack.pop();
      path.push_back(curr);
      
      if (!visited[curr]) {
	  visited[curr] = true;
	  if (curr == destination) {
            break;
	  }
      }
	  
	  // Get all adjacent vertices of the popped vertex s
	  // If a adjacent has not been visited, then push it
	  // to the stack.
	  
	  vector<Vertex> adjList = g_.getAdjacent(start);
	  
	  bool canVisit = false;
	  for (auto i = adjList.begin(); i != adjList.end(); ++i) {
	    if (!visited[*i]) {
	      stack.push(*i);
	      canVisit = true;
	    }
	  }
	  if (canVisit) {
	    path.pop_back();
	  }
    }
    reverse(path.begin(), path.end());
    return path;
}

double AirportMap::findDistance(double lat1, double long1, double lat2, double long2) {
  double result = 3963.0 * acos((sin(lat1) * sin(lat2)) + (cos(lat1) * cos(lat2) * cos(long2-long1)));
  return result;
}

