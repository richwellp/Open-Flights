#include "fileToVector.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip> // for std::quoted

fileToVector::fileToVector(const std::string & filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string id, extra, lati, longi, rest;
        while(!file.eof()) {
            // ids and names are the exceptions in obtaining lat and long
            std::getline(file, id, '\"');
            file >> std::quoted(extra);
            // obtain latitude and longitude
            std::getline(file, lati, ',');
            while (!isdigit(lati.at(0)) && lati.at(0) != '-') {
                getline(file, lati, ',');
            }
            std::getline(file, longi, ',');
            
            // proceed to a new line
            std::getline(file, rest, '\n');
 
            // testing purposes
            //std::cout << "lat: " << lati << std::endl;
            //std::cout << "longi: " << longi << std::endl;
            //std::cout << "id: " << id << std::endl;

            // convert latitudes and longitudes to double
            lati.substr(1, lati.size() - 1);
            longi.substr(1, longi.size() - 1);

            // check if the value is a single digit (exception for std::stod)
            double lat = lati.size() <= 1 ?
                double(lati.at(0) - 48) : std::stod(lati);
            double longit = longi.size() <= 1 ?
                double(longi.at(0) - 48) : std::stod(longi);

            lats.push_back(lat);
            longs.push_back(longit);
        }
    } else {
        std::cout << "Invalid file:" << filename << std::endl;
    }
}


void fileToVector::readRoutes(const std::string & filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string extra, source, dest;
        while(!file.eof()) {
            // pass through unnecessary data
            std::getline(file, extra, ',');
            std::getline(file, extra, ',');
            std::getline(file, source, ',');
            std::getline(file, extra, ',');
            // only obtain the destination airport
            std::getline(file, dest, ',');
            // proceed to a new line
            std::getline(file, extra, '\n');
 
            // testing purposes
            //std::cout << "source: " << source << std::endl;
            //std::cout << "dest: " << dest << std::endl;

            routes.push_back(dest);
            vertices.push_back(source);
        }
    } else {
        std::cout << "Invalid file:" << filename << std::endl;
    }
}

std::vector<double> fileToVector::getLats() {
    return lats;
}

std::vector<double> fileToVector::getLongs() {
    return longs;
}

std::vector<std::string> fileToVector::getVertices() {
    return vertices;
}

std::vector<std::string> fileToVector::getRoutes() {
    return routes;
}