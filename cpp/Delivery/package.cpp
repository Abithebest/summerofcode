#include <iostream>
#include <random>
#include <map>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "package.hpp"
#include "utils.hpp"

Package::Package() {
    trackingNumber = get_random_string(6);
    destination = destinations[get_random_index(2)];
    weight = get_random_double(5.0, 70.0);
}
const std::string& Package::getTrackingNumber() const {
    return trackingNumber;
}
const std::string& Package::getDestination() const {
    return destination;
}
const double& Package::getWeight() const {
    return weight;
}

std::map<std::string, Package> packages;
std::string formatPackages() {
    std::string packageString = "";
    for(auto package : packages) {
        Package& packageData = package.second;
        
        std::ostringstream weightStream;
        weightStream << std::fixed << std::setprecision(1)
                    << packageData.getWeight();

        packageString += "#" + packageData.getTrackingNumber() + 
                        " -> " + packageData.getDestination() + 
                        " -> " + weightStream.str() + " lbs.\n";
    }

    return packageString;
}