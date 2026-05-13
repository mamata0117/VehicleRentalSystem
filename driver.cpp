#include <iostream>
#include <fstream>
#include<sstream>
#include "driver.h"
#include "ui.h"

using namespace std;
void Driver::setupDriver()
{
    system("cls");

    cout << "┌──────────────────────────────────────────┐\n";
    cout << "│               DRIVER SETUP              │\n";
    cout << "├──────────────────────────────────────────┤\n";

    cout << "│ Enter Citizenship : ";
    citizenship = inputCitizenship();

    cout << "│ Enter License No : ";
    license = inputLicense();

    cout << "│ Enter Experience (Years) : ";
    cin >> experience;

    ofstream fout("drivers.txt", ios::app);

    fout << userID << " "
         << citizenship << " "
         << license << " "
         << experience << endl;

    fout.close();

    cout << "├──────────────────────────────────────────┤\n";
    cout << "│ Driver setup completed successfully.    │\n";
    cout << "└──────────────────────────────────────────┘\n";
}
void Driver::viewTotalRidesToday()
{
    system("cls");

    ifstream fin("bookings.txt");

    if(!fin)
    {
        cout << "No booking records found.\n";
        return;
    }

    string todayDate;

    cout << "┌──────────────────────────────────────────┐\n";
    cout << "│            TOTAL RIDES TODAY            │\n";
    cout << "├──────────────────────────────────────────┤\n";

    cout << "│ Enter Today's Date (DD/MM/YYYY): ";
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

        if(assignedDriver == getUserID())
        {
            if(pickupDate == todayDate)
            {
                totalRides++;
            }
        }
    }

    fin.close();

    cout << "├──────────────────────────────────────────┤\n";

    cout << "│ Total rides completed today : "
         << totalRides;

    cout << "\n└──────────────────────────────────────────┘\n";
}
   
void Driver::viewReviews()
{
    system("cls");

    ifstream fin("reviews.txt");

    if(!fin)
    {
        cout << "No reviews found.\n";
        return;
    }

    string line;

    bool found = false;

    cout << "┌──────────────────────────────────────────┐\n";
    cout << "│               MY REVIEWS                │\n";
    cout << "├──────────────────────────────────────────┤\n";

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

        if(driverID == getUserID())
        {
            found = true;

            cout << "│ Booking ID : "
                 << bookingID << endl;

            cout << "│ Customer ID: "
                 << customerID << endl;

            cout << "│ Rating     : "
                 << rating << "/5" << endl;

            cout << "│ Review     : "
                 << review << endl;

            cout << "├──────────────────────────────────────────┤\n";
        }
    }

    if(!found)
    {
        cout << "│ No reviews yet.                         │\n";
    }

    cout << "└──────────────────────────────────────────┘\n";

    fin.close();
}
    
void Driver::acceptCustomer()
{
    system("cls");

    string id;

    cout << "┌──────────────────────────────────────────┐\n";
    cout << "│             ACCEPT CUSTOMER             │\n";
    cout << "├──────────────────────────────────────────┤\n";

    cout << "│ Enter Customer ID : ";
    cin >> id;

    cout << "├──────────────────────────────────────────┤\n";

    cout << "│ Customer "
         << id
         << " accepted successfully.\n";

    cout << "└──────────────────────────────────────────┘\n";
}

 void Driver::rejectCustomer()
{
    system("cls");

    string id;

    cout << "┌──────────────────────────────────────────┐\n";
    cout << "│             REJECT CUSTOMER             │\n";
    cout << "├──────────────────────────────────────────┤\n";

    cout << "│ Enter Customer ID : ";
    cin >> id;

    cout << "├──────────────────────────────────────────┤\n";

    cout << "│ Customer "
         << id
         << " rejected.\n";

    cout << "└──────────────────────────────────────────┘\n";
}

void Driver::rateCustomer()
{
    system("cls");

    string id;
    int rating;

    cout << "┌──────────────────────────────────────────┐\n";
    cout << "│              RATE CUSTOMER              │\n";
    cout << "├──────────────────────────────────────────┤\n";

    cout << "│ Enter Customer ID : ";
    cin >> id;

    cout << "│ Enter Rating (1-5): ";
    cin >> rating;

    ofstream fout("customer_ratings.txt", ios::app);

    fout << id << " "
         << rating << endl;

    fout.close();

    cout << "├──────────────────────────────────────────┤\n";
    cout << "│ Rating submitted successfully.          │\n";
    cout << "└──────────────────────────────────────────┘\n";
}

string Driver::getCitizenship() {
    return citizenship;
}

int Driver::getExperience() {
    return experience;
}