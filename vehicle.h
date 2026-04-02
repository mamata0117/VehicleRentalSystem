#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

struct Vehicle {
    int id;
    std::string name;
    std::string type;
   float price;
    bool available;

    Vehicle* next;  
    Vehicle* prev;  

};

class VehicleList {

    
    public:
    Vehicle* head;
    VehicleList();
float getVehiclePrice(int vehicleID);
    void addVehicle();
    void saveVehicles();
    void loadVehicles();
    void viewVehicles();
    void deleteVehicle();
};

#endif