#include <iostream>
#include "driver.h"

using namespace std;

void Driver::driverMenu() {
    int choice;

    while (true) {
        cout << "\n--- Driver Menu ---\n";
        cout << "1. View Customer Requests\n";
        cout << "2. Accept Customer\n";
        cout << "3. Reject Customer\n";
        cout << "4. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewCustomers();
                break;
            case 2:
                acceptCustomer();
                break;
            case 3:
                rejectCustomer();
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

void Driver::viewCustomers() {
    cout << "Showing customer requests...\n";
}

void Driver::acceptCustomer() {
    cout << "Customer accepted.\n";
}

void Driver::rejectCustomer() {
    cout << "Customer rejected.\n";
}
/*void Driver::addDriver() {
    ofstream fout("drivers.txt", ios::app);

    cout << "Enter Driver Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    license = getLicense();

    ifstream fin("drivers.txt");
    string existingLine;
    while(getline(fin, existingLine)) {
        if(existingLine.empty()) {
            continue;
        }

        istringstream ss(existingLine);
      

string existingName, existingLicense;
int existingCharge;

getline(ss, existingName, ',');
getline(ss, existingLicense, ',');
ss >> existingCharge;
       

        if(existingLicense == license) {
            cout << "Driver license already exists!\n";
            fout.close();
            return;
        }

        if(existingName == name) {
            cout << "Driver name already exists!\n";
            fout.close();
            return;
        }
    }

    cout << "Enter Charge per day: ";
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

    string deleteDriverName;
    bool found = false;

    cout << "Enter Driver Name to delete: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, deleteDriverName);

  while(getline(fin, line)) {
      istringstream ss(line);

        string existingName, license;
      

        ss >> existingName >> license >> charge;
        if(existingName != deleteDriverName) {
            temp << existingName << " " << license << " " << charge << endl;
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
}*/