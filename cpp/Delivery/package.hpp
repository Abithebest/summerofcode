#ifndef PACKAGE_HPP
#define PACKAGE_HPP
#include <iostream>
#include <string>
#include <map>

class Package {
    private:
        std::string trackingNumber;
        std::string destination;
        double weight;

    public:
        Package();
        const std::string& getTrackingNumber() const;
        const std::string& getDestination() const;
        const double& getWeight() const;
};
extern std::map<std::string, Package> packages;
std::string formatPackages();

#endif