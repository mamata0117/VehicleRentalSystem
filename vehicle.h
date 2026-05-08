#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

using namespace std;

class Vehicle
{
private:

    string vehicleID;
    string type;
    string fuelType;
    string category;

    string licensePlate;
    string maintenanceRecord;

    float selfDrivePrice;
    float driverPrice;

    bool available;

public:

    void addVehicle();

    void displayVehicle();

    bool isAvailable();

    void setAvailability(bool status);

    string getVehicleID();

    string getType();

    string getCategory();

    float getSelfDrivePrice();

    float getDriverPrice();

    string getLicensePlate();
};

struct VehicleNode
{
    Vehicle data;
    VehicleNode* next;
};

extern VehicleNode* head;

void insertVehicle(Vehicle v);

void displayAllVehicles();

void displayAvailableVehicles();

Vehicle* findVehicleByID(string id);

#endif