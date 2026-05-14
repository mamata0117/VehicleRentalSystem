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
    cout << "│                 CUSTOMER SETUP                   │\n";
    cout << "├──────────────────────────────────────────────────┤\n";

    cout << "│";
    citizenship = inputCitizenship();

    cout << "│ Are you a student? 1 for Yes, 0 for No: ";
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
    cout << "│ Customer setup completed successfully.           │\n";
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
    cout << "│              DRIVER REVIEW               │\n";
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
    cout << "│ Review submitted successfully!           │\n";
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

    printMessage(
        "Cancel Feature Will Be Added Later Using Stack."
    );
}

// Getter
string Customer::getCitizenship()
{
    return citizenship;
}