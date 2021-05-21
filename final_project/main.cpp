#include <vector>
#include <iostream>
#include "fileToVector.h"
#include "AirportMap.h"


int main() {
    //std::cout<<"test"<<std::endl;
    fileToVector ap("data/airports.dat");
    std::vector<double> lats = ap.getLats();
    std::vector<double> longs = ap.getLongs();
    //ap.readAirlines("data/airlines.dat");
    ap.readRoutes("data/routes.dat.txt");
    std::vector<std::string> vertices = ap.getVertices();
    std::vector<std::string> routes = ap.getRoutes();

    AirportMap am(vertices, lats, longs, routes);
    //am.DFS();
    am.graphicalOutput(am.DFS("LHR", "YBB"));
    
    return 0;
}
