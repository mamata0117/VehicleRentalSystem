#include <iostream>
#include <fstream>
#include<sstream>
#include "customer.h"
#include "vehicle.h"
#include "booking.h"
#include "ui.h"

using namespace std;

// Customer setup
void Customer::setupCustomer()
{
   

    printInputHeader("CUSTOMER SETUP");
    citizenship = inputCitizenship();

    cout << "Are you a student? 1 for Yes, 0 for No: ";
    cin >> isStudent;

    cin.ignore();

    if(isStudent == 1)
    {
        cout << " Enter Institution Name : ";
        getline(cin, institutionName);

        cout << " Enter Student ID Card Number : ";
        getline(cin, studentIDCard);
    }

    printMessage("Customer setup completed successfully.");
}
void Customer::reviewDriver()
{
    string driverID;
    string bookingID;
    int rating;
    string review;

   

    printInputHeader("DRIVER REVIEW");

    cout << " Enter Booking ID : ";
    cin >> bookingID;

    cout << " Enter Driver ID  : ";
    cin >> driverID;

    cout << " Rate Driver(1-5): ";
    cin >> rating;

    cin.ignore();

    cout << " Write Review     : ";
    getline(cin, review);

    ofstream fout("reviews.txt", ios::app);

    fout << driverID << "|"
         << getUserID() << "|"
         << bookingID << "|"
         << rating << "|"
         << review << endl;

    fout.close();

    printMessage("Review submitted successfully!");
}
// Customer menu
void Customer::customerMenu(BookingQueue& queue)
{
    int choice;

    do
{
    system("cls");

    cout << "┌──────────────────────────────────────────┐\n";
    cout << "│              CUSTOMER MENU               │\n";
    cout << "├──────────────────────────────────────────┤\n";
    cout << "│ 1. View Available Vehicles               │\n";
    cout << "│ 2. Book Vehicle                          │\n";
    cout << "│ 3. Cancel Booking                        │\n";
    cout << "│ 4. Exit                                  │\n";
    cout << "└──────────────────────────────────────────┘\n";

    cout << "\nEnter choice: ";
    cin >> choice;

    switch(choice)
    {
        case 1:
            viewVehicles();
            break;

        case 2:
            bookVehicle(queue);
            break;

        case 3:
            cancelBooking();
            break;

        case 4:
            exit(0);
            break;

        default:
            cout << "Invalid choice.\n";
    }

} while(choice != 4);
}

// View vehicles
void Customer::viewVehicles()
{
    displayAvailableVehicles();
}

// Book vehicle
void Customer::bookVehicle(BookingQueue& queue)
{
    system("cls");

    Booking b;

    printInputHeader("BOOK VEHICLE");

    cout << "Enter Booking ID : ";
    cin >> b.bookingID;

    // Logged in customer ID
    b.customerID = getUserID();

    cout << "Enter Vehicle ID : ";
    cin >> b.vehicleID;

    // FIND VEHICLE
    Vehicle* v = findVehicleByID(b.vehicleID);

    // Vehicle does not exist
    if (v == NULL)
    {
        printMessage("Vehicle Does Not Exist.");
        return;
    }

    // Vehicle already booked
    if (!v->isAvailable())
    {
        printMessage("Vehicle Already Booked.");
        return;
    }

    // Mark vehicle as booked
    v->setAvailability(false);

    b.assignedDriver = "NONE";
    b.status = "PENDING";

    queue.enqueue(b);

    printMessage("Booking Request Sent Successfully.");

}



// Cancel booking
void Customer::cancelBooking()
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

    printMenuHeader("YOUR BOOKINGS");

    // SHOW CUSTOMER BOOKINGS
    while(getline(fin, line))
    {
        if(line.find(getUserID()) != string::npos)
        {
            printMenuItem(line);

            found = true;
        }
    }

    fin.close();

    if(!found)
    {
        printMessage("No Bookings Found.");
        return;
    }

    printLine();

    string cancelID;

    cout << "Enter Booking ID To Cancel : ";
    cin >> cancelID;

    fin.open("bookings.txt");

    ofstream fout("temp.txt");

    bool deleted = false;

    while(getline(fin, line))
    {
        // KEEP OTHER BOOKINGS
        if(line.find(cancelID) == string::npos)
        {
            fout << line << endl;
        }

        else
        {
            deleted = true;
        }
    }

    fin.close();
    fout.close();

    remove("bookings.txt");

    rename("temp.txt", "bookings.txt");

    if(deleted)
    {
        printMessage("Booking Cancelled Successfully.");
    }

    else
    {
        printMessage("Booking ID Not Found.");
    }
}

void Customer::completeRide()
{
    string bookingID;

    cout << "Enter Completed Booking ID : ";
    cin >> bookingID;

    // update booking status to COMPLETED

    printMessage("Ride Completed Successfully.");

    char choice;

    cout << "Do You Want To Review Driver? (Y/N) : ";
    cin >> choice;

    if(choice == 'Y' || choice == 'y')
    {
        reviewDriver();
    }
}
// Getter
string Customer::getCitizenship()
{
    return citizenship;
}