#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <iostream>
#include <vector>
#include <array>

#include "package.hpp"

enum class VehicleType {
    Van = 0,
    BoxTruck,
    SemiTruck,
    SmallPlane,
    BigPlane,
    Count
};
struct VehicleStats {
    double cost;
    double weight;
};
inline constexpr std::array<VehicleStats, (size_t)VehicleType::Count> vehicleStats = {{
    {1000.0, 100.0},       // Van
    {5000.0, 500.0},       // BoxTruck
    {50000.0, 5000.0},     // SemiTruck
    {100000.0, 10000.0},   // SmallPlane
    {500000.0, 50000.0}    // BigPlane
}};

class Vehicle {
    private:
        std::string id;
        int level;
        VehicleType type;
        double maxWeight;
        std::vector<Package> currentPackages;

    public:
        bool departed = false;

        Vehicle(int vehicleType);
        const std::string& getId() const;
        const int& getLevel() const;
        const double& getMaxWeight() const;
        const std::vector<Package>& getCurrentPackages() const;
        void addPackage(Package package);
        void emptyPackages();
        void upgradeVehicle();
};
extern std::vector<Vehicle> vehicles;

#endif