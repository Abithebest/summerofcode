#include <iostream>
#include <random>

#include "vehicle.hpp"
#include "package.hpp"
#include "utils.hpp"

std::vector<Vehicle> vehicles;
Vehicle::Vehicle(int vehicleType) {
    id = get_random_string(6);
    level = 1;
    type = static_cast<VehicleType>(vehicleType);
    maxWeight = (vehicleStats[(size_t)type]).weight;
}

const std::string& Vehicle::getId() const {
    return id;
}
const int& Vehicle::getLevel() const {
    return level;
}
const double& Vehicle::getMaxWeight() const {
    return maxWeight;
}
const std::vector<Package>& Vehicle::getCurrentPackages() const {
    return currentPackages;
}

void Vehicle::addPackage(Package package) {
    currentPackages.push_back(package);
}
void Vehicle::emptyPackages() {
    currentPackages.clear();
}
void Vehicle::upgradeVehicle() {
    double cost = vehicleStats[(size_t)type].cost * (level + 1);
}