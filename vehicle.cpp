#include <iostream>
#include <fstream>
#include <limits>
#include "vehicle.h"

using namespace std;

// Constructor
VehicleList::VehicleList() {
    head = nullptr;
    loadVehicles();
}

// 🔹 CREATE VEHICLE
Vehicle* createVehicle() {
    Vehicle* pnew = new Vehicle;

    cout << "Enter Vehicle ID: ";
    cin >> pnew->id;

    cout << "Enter Type (BIKE/CAR/VAN/TRUCK/SCOOTER): ";
    cin >> pnew->type;

    cout << "Enter Category (REGULAR/COMFORT): ";
    cin >> pnew->category;

    cout << "Enter Fuel Type (PETROL/DIESEL): ";
    cin >> pnew->fuelType;

    cout << "Enter License Plate: ";
    cin >> pnew->licensePlate;

    cout << "Enter Maintenance Date: ";
    cin >> pnew->maintenanceDate;

    cout << "Enter Price: ";
    cin >> pnew->price;

    pnew->available = true;

    pnew->next = nullptr;
    pnew->prev = nullptr;

    return pnew;
}

// 🔹 SAVE VEHICLES
void VehicleList::saveVehicles() {
    if (head == nullptr) return;

    ofstream fout("vehicles.txt");

    Vehicle* temp = head;

    do {
        fout << temp->id << " "
             << temp->type << " "
             << temp->category << " "
             << temp->fuelType << " "
             << temp->licensePlate << " "
             << temp->maintenanceDate << " "
             << temp->price << " "
             << temp->available << "\n";

        temp = temp->next;

    } while (temp != head);
}

// 🔹 LOAD VEHICLES
void VehicleList::loadVehicles() {
    ifstream fin("vehicles.txt");
    if (!fin) return;

    while (true) {
        Vehicle* pnew = new Vehicle;

        if (!(fin >> pnew->id
                  >> pnew->type
                  >> pnew->category
                  >> pnew->fuelType
                  >> pnew->licensePlate
                  >> pnew->maintenanceDate
                  >> pnew->price
                  >> pnew->available)) {

            delete pnew;
            break;
        }

        if (head == nullptr) {
            head = pnew;
            pnew->next = pnew;
            pnew->prev = pnew;
        } 
        else {
            Vehicle* last = head->prev;

            last->next = pnew;
            pnew->prev = last;

            pnew->next = head;
            head->prev = pnew;
        }
    }
}

// 🔹 ADD VEHICLE
void VehicleList::addVehicle() {
    Vehicle* pnew = createVehicle();

    if (head == nullptr) {
        head = pnew;
        pnew->next = pnew;
        pnew->prev = pnew;
    } 
    else {
        Vehicle* last = head->prev;

        last->next = pnew;
        pnew->prev = last;

        pnew->next = head;
        head->prev = pnew;
    }

    cout << "Vehicle added successfully!\n";
    saveVehicles();
}

// 🔹 VIEW ALL VEHICLES
void VehicleList::viewVehicles() {
    if (head == nullptr) {
        cout << "No vehicles available.\n";
        return;
    }

    Vehicle* temp = head;

    cout << "\n--- Vehicle List ---\n";

    do {
        cout << "ID: " << temp->id << endl;
        cout << "Type: " << temp->type << endl;
        cout << "Category: " << temp->category << endl;
        cout << "Fuel: " << temp->fuelType << endl;
        cout << "Plate: " << temp->licensePlate << endl;
        cout << "Maintenance: " << temp->maintenanceDate << endl;
        cout << "Price: " << temp->price << endl;
        cout << "Status: " << (temp->available ? "Available" : "Booked") << endl;
        cout << "---------------------\n";

        temp = temp->next;

    } while (temp != head);
}

// 🔹 VIEW AVAILABLE VEHICLES (FILTER)
void VehicleList::viewAvailableVehicles() {
    if (head == nullptr) {
        cout << "No vehicles available.\n";
        return;
    }

    string type, category;
    cout << "Enter type: ";
    cin >> type;

    cout << "Enter category: ";
    cin >> category;

    Vehicle* temp = head;
    bool found = false;

    do {
        if (temp->type == type &&
            temp->category == category &&
            temp->available) {

            cout << "\nID: " << temp->id;
            cout << " | Price: " << temp->price;
            cout << " | Plate: " << temp->licensePlate << endl;

            found = true;
        }

        temp = temp->next;

    } while (temp != head);

    if (!found) {
        cout << "No matching vehicles found.\n";
    }
}

// 🔹 FIND VEHICLE
Vehicle* VehicleList::findVehicle(int id) {
    if (head == nullptr) return nullptr;

    Vehicle* temp = head;

    do {
        if (temp->id == id)
            return temp;

        temp = temp->next;

    } while (temp != head);

    return nullptr;
}

// 🔹 DELETE VEHICLE
void VehicleList::deleteVehicle() {
    int delID;
    cout << "Enter Vehicle ID to delete: ";
    cin >> delID;

    if (head == nullptr) {
        cout << "List is empty.\n";
        return;
    }

    Vehicle* temp = head;

    do {
        if (temp->id == delID) {

            // only one node
            if (temp->next == head) {
                delete temp;
                head = nullptr;
            }
            else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;

                if (temp == head)
                    head = temp->next;

                delete temp;
            }

            cout << "Vehicle deleted successfully!\n";
            saveVehicles();
            return;
        }

        temp = temp->next;

    } while (temp != head);

    cout << "Vehicle not found.\n";
}

//  GET PRICE
float VehicleList::getVehiclePrice(int vehicleID) {
    Vehicle* v = findVehicle(vehicleID);

    if (v != nullptr)
        return v->price;

    cout << "Vehicle not found!\n";
    return -1;
}