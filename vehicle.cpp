#include <iostream>
#include "vehicle.h"

using namespace std;

// 🔗 Head pointer (start of linked list)
VehicleNode* head = NULL;
void Vehicle::addVehicle() {
    cout << "\n--- Add Vehicle ---\n";

    cout << "Enter Vehicle ID: ";
    cin >> vehicleID;

    cout << "Enter type (Car/Bike/Scooter): ";
    cin >> type;

    cout << "Enter fuel type (Petrol/Diesel): ";
    cin >> fuelType;

    cout << "Enter category (Regular/Comfort): ";
    cin >> category;

    cout << "Enter price per day: ";
    cin >> pricePerDay;

    available = true;
}
void insertVehicle(Vehicle v) {
    VehicleNode* newNode = new VehicleNode;

    newNode->data = v;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        VehicleNode* temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    cout << "Vehicle added successfully!\n";
}
void Vehicle::displayVehicle() {
    cout << "ID: " << vehicleID
         << " | Type: " << type
         << " | Fuel: " << fuelType
         << " | Category: " << category
         << " | Price: " << pricePerDay
         << " | Status: " << (available ? "Available" : "Booked")
         << endl;
}
void displayAllVehicles() {
    if (head == NULL) {
        cout << "No vehicles available.\n";
        return;
    }

    VehicleNode* temp = head;

    cout << "\n--- All Vehicles ---\n";

    while (temp != NULL) {
        temp->data.displayVehicle();
        temp = temp->next;
    }
}
void displayAvailableVehicles() {
    if (head == NULL) {
        cout << "No vehicles available.\n";
        return;
    }

    VehicleNode* temp = head;

    cout << "\n--- Available Vehicles ---\n";

    while (temp != NULL) {
        if (temp->data.isAvailable()) {
            temp->data.displayVehicle();
        }
        temp = temp->next;
    }
}
bool Vehicle::isAvailable() {
    return available;
}

void Vehicle::setAvailability(bool status) {
    available = status;
}
string Vehicle::getVehicleID() {
    return vehicleID;
}

string Vehicle::getType() {
    return type;
}

string Vehicle::getCategory() {
    return category;
}

int Vehicle::getPrice() {
    return pricePerDay;
}
