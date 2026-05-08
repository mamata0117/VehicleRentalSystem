#include <iostream>
#include <fstream>
#include<sstream>
#include "customer.h"
#include "vehicle.h"
#include "booking.h"

using namespace std;

// Customer setup
void Customer::setupCustomer()
{
    cout << "\n\n----------- Customer Setup ----------------------\n\n";

    citizenship = inputCitizenship();

    cout << "Are you a student? Enter 1 for yes and 0 for no: ";
    cin >> isStudent;
    cin.ignore();

    if (isStudent == 1)
    {
        cout << "Enter Institution Name: ";
        getline(cin, institutionName);

        cout << "Enter Student ID Card Number: ";
        getline(cin, studentIDCard);
    }

    cout << "Customer setup completed.\n";
}
void Customer::reviewDriver()
{
    string driverID;
    string bookingID;
    int rating;
    string review;

    cout << "\n----------- Driver Review -----------\n";

    cout << "Enter Booking ID: ";
    cin >> bookingID;

    cout << "Enter Driver ID: ";
    cin >> driverID;

    cout << "Rate Driver (1-5): ";
    cin >> rating;

    cin.ignore();

    cout << "Write Review: ";
    getline(cin, review);

    ofstream fout("reviews.txt", ios::app);

    fout << driverID << "|"
         << getUserID() << "|"
         << bookingID << "|"
         << rating << "|"
         << review << endl;

    fout.close();

    cout << "Review submitted successfully!\n";
}
// Customer menu
void Customer::customerMenu(BookingQueue& queue)
{
    int choice;

    do
    {
        cout << "\n\n----------- Customer Menu ----------------------\n";
        cout << "1. View Available Vehicles\n";
        cout << "2. Book Vehicle\n";
        cout << "3. Cancel Booking\n";
        cout << "4. Exit\n";

        cout << "Enter choice: ";
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
                cout << "Invalid choice!\n";
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