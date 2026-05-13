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
    system("cls");

    cout << "┌──────────────────────────────────────────────────┐\n";
    cout << "│                 CUSTOMER SETUP                  │\n";
    cout << "├──────────────────────────────────────────────────┤\n";

    cout << "│ Enter Citizenship : ";
    citizenship = inputCitizenship();

    cout << "│ Are you a student? (1 = Yes, 0 = No): ";
    cin >> isStudent;

    cin.ignore();

    if(isStudent == 1)
    {
        cout << "│ Enter Institution Name : ";
        getline(cin, institutionName);

        cout << "│ Enter Student ID Card Number : ";
        getline(cin, studentIDCard);
    }

    cout << "├──────────────────────────────────────────────────┤\n";
    cout << "│ Customer setup completed successfully.          │\n";
    cout << "└──────────────────────────────────────────────────┘\n";
}
void Customer::reviewDriver()
{
    string driverID;
    string bookingID;
    int rating;
    string review;

    system("cls");

    cout << "┌──────────────────────────────────────────┐\n";
    cout << "│              DRIVER REVIEW              │\n";
    cout << "├──────────────────────────────────────────┤\n";

    cout << "│ Enter Booking ID : ";
    cin >> bookingID;

    cout << "│ Enter Driver ID  : ";
    cin >> driverID;

    cout << "│ Rate Driver(1-5): ";
    cin >> rating;

    cin.ignore();

    cout << "│ Write Review     : ";
    getline(cin, review);

    ofstream fout("reviews.txt", ios::app);

    fout << driverID << "|"
         << getUserID() << "|"
         << bookingID << "|"
         << rating << "|"
         << review << endl;

    fout.close();

    cout << "├──────────────────────────────────────────┤\n";
    cout << "│ Review submitted successfully!          │\n";
    cout << "└──────────────────────────────────────────┘\n";
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
    Booking b;

    cout << "Enter Booking ID: ";
    cin >> b.bookingID;

    // Logged in customer ID
    b.customerID = getUserID();

    cout << "Enter Vehicle ID: ";
    cin >> b.vehicleID;

    // FIND VEHICLE
    Vehicle* v = findVehicleByID(b.vehicleID);

    // Vehicle does not exist
    if (v == NULL)
    {
        cout << "Vehicle does not exist.\n";
        return;
    }

    // Vehicle already booked
    if (!v->isAvailable())
    {
        cout << "Vehicle is already booked.\n";
        return;
    }

    // Mark vehicle as booked
    v->setAvailability(false);

    b.assignedDriver = "NONE";
    b.status = "PENDING";

    queue.enqueue(b);

    cout << "Booking request sent successfully!\n";
}

// Cancel booking
void Customer::cancelBooking()
{
    cout << "Cancel feature will be added later using stack.\n";
}

// Getter
string Customer::getCitizenship()
{
    return citizenship;
}