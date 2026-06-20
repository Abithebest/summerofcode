#include <iostream>
#include <random>
#include <map>

#include <sstream>
#include <iomanip>

#include <algorithm>

#include "vehicle.hpp"
#include "package.hpp"
#include "utils.hpp"

//1. Next Day
//  Instad of just one package, random amount of packages
//  Depart all vehicles with packages in them
//  Return vehicles that departed the day before
//2. Assign Packages
//  Add packages to a vehicle

//3. Buy Vehicle
//  Buy a vehicle
//5. View Vehicles

int main() {
    int menuChoice;
    bool continueCommands = true;

    Vehicle startingVehicle(0);
    vehicles.push_back(startingVehicle);

    while(continueCommands) {
        std::cout << menu;
        std::cin >> menuChoice;

        if (!menuChoice) {
            std::cout << "Invalid input...\n";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }

        switch(menuChoice) {
            case 1: { // Next Day
                std::string packageString = "";
                std::string vehicleString = "";

                // Package Delivery
                int packageCount = get_random_int(0, 5);
                for(int i=0; i<packageCount; i++) {
                    Package package;
                    packages[package.getTrackingNumber()] = package;
                    packageString += "New package #" + package.getTrackingNumber() + "\n";

                    totalPackages++;
                    totalWeight += package.getWeight();
                }
                if(packageCount == 0) {
                    packageString = "No Packages Today...\n";
                }

                // Depart & Return Vehicles
                for(Vehicle& vehicle : vehicles) {
                    if(vehicle.departed == true) {
                        vehicle.departed = false;
                        for(const Package& package : vehicle.getCurrentPackages()) {
                            packages.erase(package.getTrackingNumber());
                        }

                        vehicle.emptyPackages();
                        vehicleString += vehicle.getId() + " returned.\n";
                    } else if(!vehicle.getCurrentPackages().empty()) {
                        vehicle.departed = true;
                        vehicleString += vehicle.getId() + " departed.\n";
                    }
                }
                if(vehicleString.length() == 0) {
                    vehicleString = "No Vehicle Departures.";
                }

                std::cout << packageString + "\n" + vehicleString + "\n\n";
                break;
            }

            case 2: { // Assign Packages
                std::string vehicleString = "";
                for(const Vehicle& vehicle : vehicles) {
                    double vehicleWeight = 0.0;
                    std::string vehiclePackages = "";
                    for(const Package& package : vehicle.getCurrentPackages()) {
                        vehiclePackages += "#" + package.getTrackingNumber() + " - ";
                    }
                    
                    vehicleString += "- " + vehicle.getId() + " | " + toFixed(vehicleWeight) + "/" + toFixed(vehicle.getMaxWeight()) + " lbs.\n" + vehiclePackages;
                }

                std::cout << vehicleString + "\nChoose a vehicle to assign to > ";

                std::string vehicleAssign;
                std::cin >> vehicleAssign;

                vehicleAssign = uppercase(vehicleAssign);

                auto vehicleData = std::find_if(
                    vehicles.begin(),
                    vehicles.end(),
                    [&vehicleAssign](const Vehicle& v) {
                        return v.getId() == vehicleAssign;
                    }
                );
                if (vehicleData == vehicles.end()) {
                    std::cout << "Vehicle does not exist...\n";
                    break;
                }

                Vehicle& vehicle = *vehicleData;
                std::cout << formatPackages() + "\nChoose a package to assign > ";

                std::string transferNumber;
                std::cin >> transferNumber;

                transferNumber = remove_char(transferNumber, '#');
                transferNumber = uppercase(transferNumber);
                break;
            }

            case 3: // Buy Vehicle
                break;

            case 4: // View Packages
                std::cout << formatPackages() + "\n";
                break;

            case 5: // View Vehicles
                break;

            case 6: { // View Depot Statistics
                double averageWeight = totalWeight / totalPackages;

                std::cout << "Packages Stored: " + toFixed(totalPackages) + "\nTotal Weight: " + toFixed(totalWeight) + " lbs.\nAverage Weight: " + toFixed(averageWeight) + " lbs.\n\n";
                break;
            }

            case 7: // Exit
                continueCommands = false;
                std::cout << "Exited instance...\n";
                break;

            default: // Not a command
                std::cout << "Not a command...\n";
                break;
        }
    }

    return 0;
}