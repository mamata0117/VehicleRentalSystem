#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
private:
    std::string vehicleID;
    std::string type;        // car, bike, etc.
    std::string fuelType;    // petrol / diesel
    std::string category;    // regular / comfort
    int pricePerDay;
    bool available;

public:
    // setup
    void addVehicle();

    // display
    void displayVehicle();

    // availability
    bool isAvailable();
    void setAvailability(bool status);

    // getters
    std::string getVehicleID();
    std::string getType();
    std::string getCategory();
    int getPrice();
};


// 🔗 Linked List Node
struct VehicleNode {
    Vehicle data;
    VehicleNode* next;
};
void insertVehicle(Vehicle v);
void displayAllVehicles();
void displayAvailableVehicles();

#endif