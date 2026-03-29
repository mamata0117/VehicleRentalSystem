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
private:
    Vehicle* head;

public:
    VehicleList();

    void addVehicle();
    void viewVehicles();
    void deleteVehicle();
};

#endif