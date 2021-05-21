#pragma once

#include <string>
#include <vector>

class fileToVector {
public:

    /**
      * This constructor reads from an airports.dat file format
      * and initializes the vectors of latitudes and longitudes.
      * @param filename  The directory of the file to be read
      */
    fileToVector(const std::string & filename);

    /**
      * This method reads from an airlines.dat file format
      * and initializes the vectors of vertices.
      * @param filename  The directory of the file to be read
      */
    //void readAirlines(const std::string & filename);

    /**
      * This method reads from an routes.dat.txt file format
      * and initializes the vectors of vertices.
      * @param filename  The directory of the file to be read
      */
    void readRoutes(const std::string & filename);

    /**
     * Getter function.
     * @return the latitude vector
     */
    std::vector<double> getLats();

    /**
     * Getter function.
     * @return the longitude vector
     */
    std::vector<double> getLongs();

    /**
     * Getter function.
     * @return the vertices vector
     */
    std::vector<std::string> getVertices();

    /**
     * Getter function.
     * @return the routes vector
     */
    std::vector<std::string> getRoutes();

private:
    std::vector<double> lats;
    std::vector<double> longs;
    std::vector<std::string> vertices;
    std::vector<std::string> routes;
};