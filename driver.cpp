#include <iostream>
#include <fstream>
#include<sstream>
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
void Driver::viewTotalRidesToday()
{
    ifstream fin("bookings.txt");

    if(!fin)
    {
        cout << "No booking records found.\n";
        return;
    }

    string todayDate;

    cout << "Enter Today's Date (DD/MM/YYYY): ";
    cin >> todayDate;

    string line;

    int totalRides = 0;

    while(getline(fin, line))
    {
        stringstream ss(line);

        string bookingID;
        string customerID;
        string vehicleID;
        string pickupDate;
        string returnDate;
        string drivingMode;
        string customerLicense;
        string assignedDriver;
        string totalCost;
        string advancePayment;
        string status;

        getline(ss, bookingID, '|');
        getline(ss, customerID, '|');
        getline(ss, vehicleID, '|');
        getline(ss, pickupDate, '|');
        getline(ss, returnDate, '|');
        getline(ss, drivingMode, '|');
        getline(ss, customerLicense, '|');
        getline(ss, assignedDriver, '|');
        getline(ss, totalCost, '|');
        getline(ss, advancePayment, '|');
        getline(ss, status);

        // Match current driver
        if(assignedDriver == getUserID())
        {
            // Match today's ride
            if(pickupDate == todayDate)
            {
                totalRides++;
            }
        }
    }

    fin.close();

    cout << "\nTotal rides completed today: "
         << totalRides
         << endl;
}
   
void Driver::viewReviews()
{
    ifstream fin("reviews.txt");

    if(!fin)
    {
        cout << "No reviews found.\n";
        return;
    }

    string line;

    bool found = false;

    cout << "\n----------- My Reviews -----------\n";

    while(getline(fin, line))
    {
        stringstream ss(line);

        string driverID;
        string customerID;
        string bookingID;
        string rating;
        string review;

        getline(ss, driverID, '|');
        getline(ss, customerID, '|');
        getline(ss, bookingID, '|');
        getline(ss, rating, '|');
        getline(ss, review);

        // ONLY SHOW THIS DRIVER'S REVIEWS
        if(driverID == getUserID())
        {
            found = true;

            cout << "\nBooking ID: "
                 << bookingID << endl;

            cout << "Customer ID: "
                 << customerID << endl;

            cout << "Rating: "
                 << rating << "/5" << endl;

            cout << "Review: "
                 << review << endl;
        }
    }

    if(!found)
    {
        cout << "No reviews yet.\n";
    }

    fin.close();
}
    
void Driver::acceptCustomer() {
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