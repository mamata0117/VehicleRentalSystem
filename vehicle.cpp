#include <iostream>
#include <fstream>
#include "vehicle.h"

using namespace std;

VehicleList::VehicleList() {
    head = nullptr;
     loadVehicles(); 
}

//Adding a new vehicle to the circular doubly linked list
void VehicleList::addVehicle() {
    Vehicle* newVehicle = new Vehicle;

    newVehicle->next = nullptr;
    newVehicle->prev = nullptr;

    cout << "Enter Vehicle ID: ";
    cin >> newVehicle->id;

    cout << "Enter Vehicle Name: ";
    cin.ignore();
    getline(cin, newVehicle->name);

    cout << "Enter Type (car/bike): ";
    cin >> newVehicle->type;

    cout << "Enter Price per day: ";
    cin >> newVehicle->price;

    newVehicle->available = true;

    // First node
    if (head == nullptr) {
        head = newVehicle;
        newVehicle->next = newVehicle;
        newVehicle->prev = newVehicle;
    }
    else {
        Vehicle*end = head->prev;

        end->next = newVehicle;
        newVehicle->prev = end;

        newVehicle->next = head;
        head->prev = newVehicle;
    }

    cout << "Vehicle added successfully!\n";
    saveVehicles(); 
}
void VehicleList::saveVehicles() {
    ofstream fout("vehicles.txt");

    if (head == nullptr)
    { return;
    }
    Vehicle* temp = head;

    do {
        fout << temp->id << "  "
             << temp->name << " "
             << temp->type << "  "
             << temp->price << "  "
             << temp->available << endl;

        temp = temp->next;
    } while (temp != head);

    fout.close();
}
void VehicleList::loadVehicles() {
    ifstream fin("vehicles.txt");

    if (!fin) return;

    while (true) {
        Vehicle* newVehicle = new Vehicle;

        if (!(fin >> newVehicle->id >> newVehicle->name
                  >> newVehicle->type >> newVehicle->price
                  >> newVehicle->available)) {
            delete newVehicle;
            break;
        }

        // insert like addVehicle (without input)
        if (head == nullptr) {
            head = newVehicle;
            newVehicle->next = newVehicle;
            newVehicle->prev = newVehicle;
        } else {
            Vehicle* tail = head->prev;

            tail->next = newVehicle;
            newVehicle->prev = tail;

            newVehicle->next = head;
            head->prev = newVehicle;
        }
    }

    fin.close();
}
// ================= VIEW VEHICLES =================
void VehicleList::viewVehicles() {
    if (head == nullptr) {
           loadVehicles(); 
        cout << "No vehicles available.\n";
        return;
    }

    Vehicle* temp = head;

    cout << "\n--- Vehicle List ---\n";

    do {
        cout << "ID: " << temp->id << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Type: " << temp->type << endl;
        cout << "Price: " << temp->price << endl;
        cout << "Status: " << (temp->available ? "Available" : "Booked") << endl;
        cout << "---------------------\n\n";

        temp = temp->next;
    } while (temp != head);
}

// ================= DELETE VEHICLE =================
void VehicleList::deleteVehicle() {
    if (head == nullptr) {
        cout << "List is empty.\n";
        return;
    }

    int delID;
    cout << "Enter Vehicle ID to delete: ";
    cin >> delID;

    Vehicle* temp = head;

    do {
        if (temp->id == delID) {

            // Only one node
            if (temp->next == head && temp->prev == head) {
                delete temp;
                head = nullptr;
            }

            // Deleting head
            else if (temp == head) {
                Vehicle* tail = head->prev;

                head = head->next;
                head->prev = tail;
                tail->next = head;

                delete temp;
            }

            // Deleting middle or last node
            else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;

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
