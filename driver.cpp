#include <iostream>
#include <fstream>
#include <cctype>
#include "driver.h"

using namespace std;

string Driver::getLicense() {
    while(true) {
        cout << "Enter License (Format: 0X-0X-XXXXXXXX): ";
        cin >> license;

        // Check length
        if(license.length() != 14) {
            cout << "Invalid length! Try again.\n";
            continue;
        }

        // Check dash positions
        if(license[2] != '-' || license[5] != '-') {
            cout << "Invalid format! Use 0X-0X-XXXXXXXX\n";
            continue;
        }

        // Check digits
        bool valid = true;
        for(int i = 0; i < license.length(); i++) {
            if(i == 2 || i == 5) continue;

            if(isdigit(license[i])==false) {
                valid = false;
                break;
            }
        }

        if(valid==false) {
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
cout<<"Enter Driver License: ";
    license = getLicense();

    cout << "Enter Charge per day: ";
    cin.ignore();
    cin >> charge;

    fout << name << " " << license << " " << charge << endl;
    fout.close();

    cout << "Driver added successfully!\n";
}

// viewing the list of drivers stored in a text file named drivers.txt
void Driver::viewDrivers() {
    ifstream fin("drivers.txt");

    if(!fin) {
        cout << "No drivers available.\n";
        return;
    }

    cout << "\n-------------------------------------------------\n\n";
    cout<<"\t\t  DRIVER DETAILS\n";
    cout << "\n-------------------------------------------------\n\n";
while(getline(fin, line)) {
        cout<<line<<endl;
    }

    fin.close();
}

    
//eliminating the driver details
void Driver::deleteDriver() {
    ifstream fin("drivers.txt");
    ofstream temp("temp.txt");

    string deleteDriver;
    bool found = false;

    cout << "Enter Driver Name to delete: ";
   cin.ignore();
getline(cin, deleteDriver);

  while(getline(fin, line)) {
        if(name != deleteDriver) {
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