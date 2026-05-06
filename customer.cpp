#include <iostream>
#include "customer.h"

using namespace std;
void Customer::setupCustomer() {
    cout << "\n--- Customer Setup ---\n";

    citizenship = inputCitizenship();  // from User

    cout << "Are you a student? (1/0): ";
    cin >> isStudent;

    cout << "Customer setup complete!\n";
}
void Customer::viewVehicles() {
    // you already wrote this in vehicle.cpp
    displayAvailableVehicles();  // make sure it’s declared in vehicle.h
}
void Customer::bookVehicle(BookingQueue& queue) {
    Booking b;

    cout << "Enter Booking ID: ";
    cin >> b.bookingID;

    b.customerID = getUserID();

    cout << "Enter Vehicle ID: ";
    cin >> b.vehicleID;

    b.driverID = "NONE";   // assigned later
    b.status = "PENDING";

    queue.enqueue(b);

    cout << "Booking request sent!\n";
}
void Customer::cancelBooking() {
    cout << "Cancel feature will use stack later.\n";
}
string Customer::getCitizenship() {
    return citizenship;
}
