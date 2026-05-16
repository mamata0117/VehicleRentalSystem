#ifndef BOOKING_H
#define BOOKING_H

#include <string>

using namespace std;

struct Booking
{
    string bookingID;

    string customerID;

    string vehicleID;

    // NEW
    string pickupLocation;

    string destination;

    string pickupDate;

    string returnDate;

    string drivingMode;

    string customerLicense;

    string assignedDriver;

    float totalCost;

    float advancePayment;

    string status;
};

struct BookingNode
{
    Booking data;

    BookingNode* next;
};

class BookingQueue
{
private:

    BookingNode* front;

    BookingNode* rear;

public:

    BookingQueue();

    void enqueue(Booking b);

    void dequeue();

    void display();
     void createBooking();
    Booking getFront();

    bool isEmpty();
void generateBill(Booking b);
    void updateVehicleStatus(string vehicleID);
};

#endif