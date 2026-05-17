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

    bool isAvailable() const;

    void setAvailability(bool status);

    string getVehicleID() const;

    string getType() const;

    string getCategory() const;

    string getFuelType() const;

    float getSelfDrivePrice() const;

    float getDriverPrice() const;

    string getLicensePlate() const;

    string getMaintenanceRecord() const;

    void setVehicleID(string id);

    void setCategory(string cat);

    void setFuelType(string fuel);

    void setLicensePlate(string plate);

    void setSelfDrivePrice(float price);

    void setDriverPrice(float price);

    void setMaintenanceRecord(string record);
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

void saveVehicleToFile(Vehicle v);

void loadVehiclesFromFile();

#endif