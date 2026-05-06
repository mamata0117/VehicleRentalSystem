#include <iostream>
#include <fstream>
#include "driver.h"

using namespace std;
void Driver::setupDriver() {
    cout << "\n--- Driver Setup ---\n";

    // Reuse from User
    citizenship = inputCitizenship();
    license = inputLicense();

    cout << "Enter experience (years): ";
    cin >> experience;

    ofstream fout("drivers.txt", ios::app);

    fout << userID << " "
         << citizenship << " "
         << license << " "
         << experience << endl;

    fout.close();

    cout << "Driver setup complete!\n";
}
void Driver::viewCustomers() {
    ifstream fin("bookings.txt");

    string driverID, customerID, vehicleID, status;

    cout << "\n--- Customer Requests ---\n";

    while (fin >> driverID >> customerID >> vehicleID >> status) {
        if (status == "PENDING") {
            cout << "Customer ID: " << customerID
                 << " | Vehicle: " << vehicleID << endl;
        }
    }

    fin.close();
}void Driver::acceptCustomer() {
    string id;
    cout << "Enter Customer ID to accept: ";
    cin >> id;

    cout << "Customer " << id << " accepted.\n";
}void Driver::rejectCustomer() {
    string id;
    cout << "Enter Customer ID to reject: ";
    cin >> id;

    cout << "Customer " << id << " rejected.\n";
}void Driver::rateCustomer() {
    string id;
    int rating;

    cout << "Enter Customer ID: ";
    cin >> id;

    cout << "Enter rating (1-5): ";
    cin >> rating;

    ofstream fout("customer_ratings.txt", ios::app);
    fout << id << " " << rating << endl;
    fout.close();

    cout << "Rating submitted.\n";
}string Driver::getLicense() {
    return license;
}

string Driver::getCitizenship() {
    return citizenship;
}

int Driver::getExperience() {
    return experience;
}