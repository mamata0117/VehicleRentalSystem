#include <iostream>
#include <fstream>
#include <cctype>
#include "driver.h"

using namespace std;

string Driver::getLicense() {
    while(true) {
        cout << "Enter License (Format: 01-09-12345678): ";
        cin >> license;

        // Check length
        if(license.length() != 14) {
            cout << "Invalid length! Try again.\n";
            continue;
        }

        // Check dash positions
        if(license[2] != '-' || license[5] != '-') {
            cout << "Invalid format! Use 01-09-12345678\n";
            continue;
        }

        // Check digits
        bool valid = true;
        for(int i = 0; i < license.length(); i++) {
            if(i == 2 || i == 5) continue;

            if(!isdigit(license[i])) {
                valid = false;
                break;
            }
        }

        if(!valid) {
            cout << "Only numbers allowed!\n";
            continue;
        }

        return license;
    }
}
void Driver::addDriver() {
    ofstream fout("drivers.txt", ios::app);

    cout << "Enter Driver Name: ";
    cin.ignore();
    getline(cin, name);

    license = getLicense();

    cout << "Enter Charge per day: ";
    cin >> charge;

    fout << name << " " << license << " " << charge << endl;
    fout.close();

    cout << "Driver added successfully!\n";
}

// ================= VIEW DRIVERS =================
void Driver::viewDrivers() {
    ifstream fin("drivers.txt");

    if(!fin) {
        cout << "No drivers available.\n";
        return;
    }

    cout << "\n----- DRIVER LIST -----\n";

    while(fin >> name >> license >> charge) {
        cout << "Name: " << name
             << " | License: " << license
             << " | Charge: " << charge << endl;
    }

    fin.close();
}

    

void Driver::deleteDriver() {
    ifstream fin("drivers.txt");
    ofstream temp("temp.txt");

    string del;
    bool found = false;

    cout << "Enter Driver Name to delete: ";
    cin >> del;

    while(fin >> name >> license >> charge) {
        if(name != del) {
            temp << name << " " << license << " " << charge << endl;
        } else {
            found = true;
        }
    }

    fin.close();
    temp.close();

    remove("drivers.txt");
    rename("temp.txt", "drivers.txt");

    if(found)
        cout << "Driver deleted successfully!\n";
    else
        cout << "Driver not found!\n";
}