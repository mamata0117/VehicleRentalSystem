#ifndef BOOKING_H
#define BOOKING_H

#include <string>

using namespace std;

struct Booking
{
    string bookingID;

    string customerID;

    string vehicleID;

    string bookingCategory;

    // Passenger/Common fields
    string pickupLocation;

    string destination;

    string pickupDate;

    string pickupTime;

    string returnDate;

    string drivingMode;

    string customerLicense;

    string assignedDriver;

    float totalCost;

    float advancePayment;

    string status;

    string deliveryOption;

    string deliveryAddress;

    // Goods transportation fields
    string goodsType;

    string goodsWeight;

    bool refrigeratedRequired;
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

    void enqueue(Booking b, bool updateVehicle = true);

    void dequeue();

    void display();
    Booking getFront();

    bool isEmpty();
void generateBill(Booking b);
    void updateVehicleStatus(string vehicleID);
};

string generateBookingID();
bool validDateFormat(string date);
int convertToDays(string date);
void saveBookingToFile(Booking b);
void loadBookingsFromFile(BookingQueue& queue);
void enqueueBookingWithoutUpdateVehicle(BookingQueue& queue, Booking b);

// Validation and helper functions
bool isValidCustomerID(string customerID);
bool customerIDHasPendingBooking(string customerID);
void setVehicleAvailable(string vehicleID);
void updateBookingStatus(string bookingID, string newStatus);
Booking findActiveBookingForVehicle(string vehicleID);

#endif