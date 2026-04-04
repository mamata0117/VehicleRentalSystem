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

//creating a new vehicle by taking input from user
Vehicle* createVehicle() {
    Vehicle* pnew = new Vehicle;

    cout << "Enter Vehicle ID: ";
    cin >> pnew->id;

    cout << "Enter Vehicle Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, pnew->name);

    cout << "Enter Type (car/bike): ";
    cin >> pnew->type;

    cout << "Enter Price per day: ";
    cin >> pnew->price;

    pnew->available = true;

    pnew->next = nullptr;
    pnew->prev = nullptr;

    return pnew;
}

// ADD VEHICLE 
void VehicleList::addVehicle() {
    Vehicle* pnew = createVehicle();

    if (head == nullptr) {
        head = pnew;
        pnew->next = pnew;
        pnew->prev = pnew;
    } 
    else {
        Vehicle* temp = head->prev;

        temp->next = pnew;
        pnew->prev = temp;

        pnew->next = head;
        head->prev = pnew;
    }

    cout << "Vehicle added successfully!\n";
    saveVehicles();
}

//SAVE VEHICLES to a text file named vehicles.txt
void VehicleList::saveVehicles() {
    if (head == nullptr) 
    {return;
    }
    ofstream fout("vehicles.txt");
    Vehicle* temp = head;

    while (true) {
        fout << temp->id << " "
             << temp->name << " "
             << temp->type << " "
             << temp->price << " "
             << temp->available << "\n";

        temp = temp->next;
        if (temp == head) break;
    }
}

//  LOAD VEHICLES
void VehicleList::loadVehicles() {
    ifstream fin("vehicles.txt");

    if (!fin) return;

    while (true) {
        Vehicle* pnew = new Vehicle;

        if (!(fin >> pnew->id >> pnew->name
                  >> pnew->type >> pnew->price
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
            Vehicle* temp = head->prev;

            temp->next = pnew;
            pnew->prev = temp;

            pnew->next = head;
            head->prev = pnew;
        }
    }
}

// VIEW VEHICLES 
void VehicleList::viewVehicles() {
    if (head == nullptr) {
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
        cout << "---------------------\n";

        temp = temp->next;
    } while (temp != head);
}

//  DELETE VEHICLE 
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

            // only one node case
            if (temp->next == head && temp->prev == head) {
                delete temp;
                head = nullptr;
            }

            // deleting head
            else if (temp == head) {
                Vehicle* plast = head->prev;

                head = head->next;
                head->prev = plast;
                plast->next = head;

                delete temp;
            }

            // deleting middle or last
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

//  GET PRICE 
float VehicleList::getVehiclePrice(int vehicleID) {
    if (head == nullptr)
    { cout << "No vehicles available!\n";
        return -1;
    }

    Vehicle* temp = head;

    do {
        if (temp->id == vehicleID) {
            return temp->price;
        }
        temp = temp->next;
    } while (temp != head);
cout << "Vehicle not found!\n";
    return -1;
}