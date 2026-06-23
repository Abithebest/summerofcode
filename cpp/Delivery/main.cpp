#include <iostream>
#include <random>
#include <map>
#include <algorithm>

#include "vehicle.hpp"
#include "package.hpp"
#include "worker.hpp"
#include "utils.hpp"

//get workers working (next day)
//test workers extensively

//workers
//  hire either driver, loader, or mechanic
//  pay wage each day
//  upgrade workers (lvl. 5 max) - higher wages but can do more work
//      driver - uses less fuel & less maintenance
//          lvl.1 - 18% less, lvl.2 - 36% less, lvl.3 - 54% less, lvl.4 - 72% less, lvl.5 - 90% less
//      loader - adds more packages at a time
//          lvl.1 - 1 package at a time, lvl.2 - 2 packages at a time, lvl.3 - 3 packages at a time, lvl. 4 - 4 packages at a time, lvl.5 - takes weight out of packages randomly
//      mechanic - removes costs from maintenance
//          lvl.1 - 15% less, lvl.2 - 30% less, lvl.3 - 45% less, lvl.4 - 60% less, lvl.5 - Fixes vehicles randomly for 50% of cost.

//1. Next Day
//2. View Packages
//3. Assign Packages
//4. View Vehicles
//5. Buy Vehicle
//6. Maintain Vehicle
//7. View Workers
//8. Hire Worker
//9. Train Worker
//10. View Depot Statistis
//11. Upgrade Depot
//12. Exit

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
                std::string workerString = "";

                // Package Delivery
                int packageCount = get_random_int(0, 5);
                int packagesAdded = 0;
                for(int i=0; i<packageCount; i++) {
                    Package package;
                    if((depotCurrentWeight + package.getWeight()) > depotMaxWeight) {
                        continue;
                    }
                    packages[package.getTrackingNumber()] = package;
                    packageString += "New package #" + package.getTrackingNumber() + "\n";

                    totalPackages++;
                    packagesAdded++;
                    totalWeight += package.getWeight();
                    depotCurrentWeight += package.getWeight();
                    depotMoney += package.getWeight() * depotMoneyPerLbs;
                }
                if(packageCount == 0 || packagesAdded == 0) {
                    packageString = "No Packages Today...\n";
                }

                /*// Workers Working
                std::vector<double> driverSpecialties;
                for(auto worker : workers) {
                    Worker& workerData = worker.second;
                    depotMoney -= workerData.getWage();

                    if(workerData.getType() == WorkerType::Driver) {
                        driverSpecialties.push_back(workerData.getLevel() * 0.18);
                    } else if(workerData.getType() == WorkerType::Loader) {
                        //load packages to non departured vehicles (if any)
                    } else {
                        //mechanic lvl.5 fixes random vehicle
                    }
                }*/

                // Depart & Return Vehicles
                for(Vehicle& vehicle : vehicles) {
                    if(vehicle.departed == true) {
                        vehicle.departed = false;
                        for(const Package& package : vehicle.getCurrentPackages()) {
                            depotCurrentWeight -= package.getWeight();
                            packages.erase(package.getTrackingNumber());
                        }

                        vehicle.emptyPackages();

                        vehicle.maintenance.fuel -= get_random_double(5.0, 25.0);
                        if(vehicle.maintenance.fuel < 0) {
                            vehicle.maintenance.fuel = 0;
                        }
                        vehicle.maintenance.chasis += get_random_double(0.0, 5.0);
                        vehicle.maintenance.engine += get_random_double(0.0, 2.0);
                        vehicle.maintenance.tires += get_random_double(0.0, 20.0);

                        vehicleString += vehicle.getId() + " returned.\n";
                    } else if(!vehicle.getCurrentPackages().empty()) {
                        if(vehicle.maintenance.fuel == 0) {
                            vehicleString += vehicle.getId() + " needs fuel to depart.\n";
                        }
                        if(vehicle.maintenance.chasis >= 100 || vehicle.maintenance.engine >= 100 || vehicle.maintenance.tires >= 100) {
                            vehicleString += vehicle.getId() + " needs maintenance.\n";
                        }

                        vehicle.departed = true;
                        vehicleString += vehicle.getId() + " departed.\n";
                    }
                }
                if(vehicleString.length() == 0) {
                    vehicleString = "No Vehicle Departures.\n";
                }

                std::cout << packageString + "\n" + vehicleString + "\n" + workerString + "\n";
                break;
            }

            case 2: { // View Packages
                std::string packageString = "Max Weight: " + toFixed(depotCurrentWeight, 1) + "/" + toFixed(depotMaxWeight, 1) + " lbs.";
                if(packages.empty() == true) {
                    packageString += "\nNo packages.\n";
                }

                packageString += "\n" + formatPackages();
                std::cout << packageString + "\n";
                break;
            }

            case 3: { // Assign Packages
                if(packages.empty() == true) {
                    std::cout << "No packages to assign...\n\n";
                    break;
                }

                std::cout << formatVehicles(false, true) + "\nChoose a vehicle to assign to > ";

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
                Package& assignmentPackage = packages[transferNumber];
                if(packages.find(transferNumber) == packages.end()) {
                    std::cout << "Package does not exist...\n\n";
                    break;
                }

                if(assignmentPackage.getWeight() + vehicle.getCurrentWeight() > vehicle.getMaxWeight()) {
                    std::cout << "Package assignment exceeds max weight for vehicle...\n\n";
                    break;
                }

                depotCurrentWeight -= assignmentPackage.getWeight();
                vehicle.addPackage(assignmentPackage);
                packages.erase(transferNumber);

                std::cout << "Assigned package #" + transferNumber + " to vehicle " + vehicle.getId() + "\n\n";
                break;
            }

            case 4: // View Vehicles
                std::cout << formatVehicles(true, true) + "\n";
                break;

            case 5: { // Buy Vehicle
                std::string vehicleString = "";
                for(int i=0; i<5; i++) {
                    VehicleType vType = static_cast<VehicleType>(i);
                    VehicleStats vStats = VehicleStatData[i];
                    std::string vName{vStats.name};

                    vehicleString += std::to_string(i + 1) + ". " + vName + " - " + toFixed(vStats.weight, 1) + " max lbs. | $" + toFixed(vStats.cost, 0) + "\n";
                }

                std::cout << "Depot Money: $" + toFixed(depotMoney, 0) + "\n\n" + vehicleString + "\nChoose vehicle to buy > ";
                int vehicleNum;
                std::cin >> vehicleNum;
                if(vehicleNum > 5 || vehicleNum < 1) {
                    std::cout << "Vehicle does not exist for purchase...\n\n";
                    break;
                }

                VehicleStats vehicle = VehicleStatData[vehicleNum - 1];
                std::string vName{vehicle.name};
                if(depotMoney < vehicle.cost) {
                    std::cout << "Not enough money...\n\n";
                    break;
                }

                depotMoney -= vehicle.cost;
                Vehicle newVehicle(vehicleNum - 1);
                vehicles.push_back(newVehicle);

                std::cout << "Bought new " + vName + " for $" + toFixed(vehicle.cost, 0) + "!\n\n";
                break;
            }

            case 6: { // Maintain Vehicle
                std::cout << formatVehicles(true, false) + "\nChoose a vehicle to maintain > ";

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
                VehicleStats vehicleStats = VehicleStatData[(size_t)vehicle.type];

                double fuelCost = (vehicleStats.maxFuel - vehicle.maintenance.fuel) * get_random_double(4.5, 6.5);
                std::string fuelMaintenance = "1. Refuel : $" + toFixed(fuelCost, 1) + "\n";
                double chasisCost = vehicle.maintenance.chasis * 50.5;
                std::string chasisMaintenance = "2. Chasis : $" + toFixed(chasisCost, 1) + "\n";
                double engineCost = vehicle.maintenance.engine * 150.7;
                std::string engineMaintenance = "3. Engine : $" + toFixed(engineCost, 1) + "\n";
                double tiresCost = vehicle.maintenance.tires * 10.0;
                std::string tiresMaintenance = "4. Tires : $" + toFixed(tiresCost, 1) + "\n";

                std::cout << "Depot Money: $" + toFixed(depotMoney, 0) + "\n\n" + fuelMaintenance + chasisMaintenance + engineMaintenance + tiresMaintenance + "\nChoose maintenace type > ";

                std::string maintenanceChoice;
                std::cin >> maintenanceChoice;

                if(maintenanceChoice == "1") {
                    if(depotMoney < fuelCost) {
                        std::cout << "Not enough money to refuel.\n";
                        break;
                    }

                    vehicle.maintenance.fuel = vehicleStats.maxFuel;
                    depotMoney -= fuelCost;
                    std::cout << "Refueled " + vehicle.getId() + "\n";
                    break;
                } else if(maintenanceChoice == "2") {
                    if(depotMoney < chasisCost) {
                        std::cout << "Not enough money to fix chasis.\n";
                        break;
                    }

                    vehicle.maintenance.chasis = 0.0;
                    depotMoney -= chasisCost;
                    std::cout << "Fixed chasis of " + vehicle.getId() + "\n";
                    break;
                } else if(maintenanceChoice == "3") {
                    if(depotMoney < engineCost) {
                        std::cout << "Not enough money to fix engine.\n";
                        break;
                    }

                    vehicle.maintenance.engine = 0.0;
                    depotMoney -= engineCost;
                    std::cout << "Fixed engine of " + vehicle.getId() + "\n";
                    break;
                } else if(maintenanceChoice == "4") {
                    if(depotMoney < tiresCost) {
                        std::cout << "Not enough money to fix tires.\n";
                        break;
                    }

                    vehicle.maintenance.tires = 0.0;
                    depotMoney -= tiresCost;
                    std::cout << "Fixed tires of " + vehicle.getId() + "\n";
                    break;
                }
                break;
            }

            case 7: // View Workers
                if(workers.empty() == true) {
                    std::cout << "No workers.\n\n";
                    break;
                }
                std::cout << formatWorkers(false) + "\n";
                break;
            
            case 8: { // Hire Worker
                std::string workerString = "";
                for(int i=0; i<3; i++) {
                    WorkerType wType = static_cast<WorkerType>(i);
                    WorkerStats wStats = WorkerStatData[i];
                    std::string wName{wStats.name};
                    workerString += std::to_string(i + 1) + ". " + wName + " - $" + toFixed(wStats.hireCost, 0) + " (" + toFixed(wStats.startingWage, 2) + " $/day)\n";
                }

                std::cout << "Depot Money: $" + toFixed(depotMoney, 0) + "\n\n" + workerString + "\nChoose worker to hire > ";
                int workerNum;
                std::cin >> workerNum;
                if(workerNum > 3 || workerNum < 1) {
                    std::cout << "Worker does not exist for purchase...\n\n";
                    break;
                }

                WorkerStats worker = WorkerStatData[workerNum - 1];
                std::string wName{worker.name};
                if(depotMoney < worker.hireCost) {
                    std::cout << "Not enough money...\n\n";
                    break;
                }

                depotMoney -= worker.hireCost;
                Worker newWorker(workerNum - 1);
                workers.insert({newWorker.getId(), newWorker});

                std::cout << "Hired new " + wName + " for $" + toFixed(worker.hireCost, 0) + "!\n\n";
                break;
            }
            
            case 9: { // Train Worker
                if(workers.empty() == true) {
                    std::cout << "No workers.\n\n";
                    break;
                }
                std::cout << formatWorkers(true) + "\nChoose a worker to train > ";

                std::string workerPick;
                std::cin >> workerPick;
                workerPick = uppercase(workerPick);

                if(workers.find(workerPick) == workers.end()) {
                    std::cout << "Worker does not exist.\n\n";
                    break;
                }
                Worker& worker = workers.at(workerPick);

                std::cout << worker.train();
                break;
            }

            case 10: { // View Depot Statistics
                double averageWeight = (totalWeight / totalPackages) || 0.0;
                std::cout << "Packages Stored: " + toFixed(totalPackages, 0) + "\nTotal Weight: " + toFixed(totalWeight, 1) + " lbs.\nAverage Weight: " + toFixed(averageWeight, 1) + " lbs.\nTotal Vehicles: " + toFixed(vehicles.size(), 0) + "\n\n";
                break;
            }

            case 11: { // Upgrade Depot
                double upgradeCost = depotLevel * 1500;
                if(depotMoney < upgradeCost) {
                    std::cout << "Not enough money to upgrade. $" + toFixed(upgradeCost, 0) + "\n\n";
                    break;
                }

                depotMoney -= upgradeCost;
                depotLevel++;
                depotMaxWeight += 150.0;
                depotMoneyPerLbs += 1.5;
                std::cout << "Upgraded depot!\n\n";
                break;
            }

            case 12: // Exit
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