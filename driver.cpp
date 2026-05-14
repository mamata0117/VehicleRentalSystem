#include <iostream>
#include <fstream>
#include<sstream>
#include "driver.h"
#include "ui.h"

using namespace std;
void Driver::setupDriver()
{
    system("cls");

    printInputHeader("DRIVER SETUP");

    citizenship = inputCitizenship();

  
    license = inputLicense();

    cout << "Enter Experience  : ";
    cin >> experience;

    ofstream fout("drivers.txt", ios::app);

    fout << userID << " "
         << citizenship << " "
         << license << " "
         << experience << endl;

    fout.close();

    printMessage("Driver Setup Completed Successfully.");
}

void Driver::viewTotalRidesToday()
{
   

    ifstream fin("bookings.txt");

    if(!fin)
    {
        printMessage("No Booking Records Found.");
        return;
    }

    string todayDate;

    printInputHeader("TOTAL RIDES TODAY");

    cout << "Enter Today's Date : ";
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

    printMessage(
        "Total Rides Today : " +
        to_string(totalRides)
    );
}
   
void Driver::viewReviews()
{
    system("cls");

    ifstream fin("reviews.txt");

    if(!fin)
    {
        printMessage("No Reviews Found.");
        return;
    }

    string line;

    bool found = false;

    printMenuHeader("MY REVIEWS");

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

            printMenuItem(
                "Booking ID  : " + bookingID
            );

            printMenuItem(
                "Customer ID : " + customerID
            );

            printMenuItem(
                "Rating      : " + rating + "/5"
            );

            printMenuItem(
                "Review      : " + review
            );

            printLine();
        }
    }

    if(!found)
    {
        printMenuItem("No Reviews Yet.");
    }

    printMenuFooter();

    fin.close();
}

void Driver::acceptCustomer()
{
    system("cls");

    ifstream fin("bookings.txt");

    if(!fin)
    {
        printMessage("No Booking Records Found.");
        return;
    }

    string line;
    bool found = false;

    printMenuHeader("PENDING BOOKINGS");

    // Show pending bookings
    while(getline(fin, line))
    {
        if(line.find("PENDING") != string::npos)
        {
            printMenuItem(line);
            found = true;
        }
    }

    fin.close();

    if(!found)
    {
        printMessage("No Pending Bookings.");
        return;
    }

    printLine();

    string bookingID;

    cout << "Enter Booking ID To Accept : ";
    cin >> bookingID;

    fin.open("bookings.txt");
    ofstream fout("temp.txt");

    bool accepted = false;

    while(getline(fin, line))
    {
        if(
            line.find(bookingID) != string::npos &&
            line.find("PENDING") != string::npos
        )
        {
            size_t pos = line.find("PENDING");

            if(pos != string::npos)
            {
                line.replace(pos, 7, "ACCEPTED");
                accepted = true;
            }
        }

        fout << line << endl;
    }

    fin.close();
    fout.close();

    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    if(accepted)
    {
        printMessage(
            "Booking " + bookingID +
            " Accepted Successfully."
        );
    }
    else
    {
        printMessage("Invalid Booking ID.");
    }
}
void Driver::rejectCustomer()
{
    system("cls");

    ifstream fin("bookings.txt");

    if(!fin)
    {
        printMessage("No Booking Records Found.");
        return;
    }

    string line;
    bool found = false;

    printMenuHeader("PENDING BOOKINGS");

    while(getline(fin, line))
    {
        if(line.find("PENDING") != string::npos)
        {
            printMenuItem(line);
            found = true;
        }
    }

    fin.close();

    if(!found)
    {
        printMessage("No Pending Bookings.");
        return;
    }

    printLine();

    string bookingID;

    cout << "Enter Booking ID To Reject : ";
    cin >> bookingID;

    fin.open("bookings.txt");
    ofstream fout("temp.txt");

    bool rejected = false;

    while(getline(fin, line))
    {
        if(
            line.find(bookingID) != string::npos &&
            line.find("PENDING") != string::npos
        )
        {
            size_t pos = line.find("PENDING");

            if(pos != string::npos)
            {
                line.replace(pos, 7, "REJECTED");
                rejected = true;
            }
        }

        fout << line << endl;
    }

    fin.close();
    fout.close();

    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    if(rejected)
    {
        printMessage(
            "Booking " + bookingID +
            " Rejected Successfully."
        );
    }
    else
    {
        printMessage("Invalid Booking ID.");
    }
}

void Driver::rateCustomer()
{
    system("cls");

    string id;
    int rating;

    printInputHeader("RATE CUSTOMER");

    cout << "Enter Customer ID : ";
    cin >> id;

    cout << "Enter Rating (1-5): ";
    cin >> rating;

    ofstream fout("customer_ratings.txt", ios::app);

    fout << id << " "
         << rating << endl;

    fout.close();

    printMessage("Rating Submitted Successfully.");
}

string Driver::getCitizenship() {
    return citizenship;
}

int Driver::getExperience() {
    return experience;
}