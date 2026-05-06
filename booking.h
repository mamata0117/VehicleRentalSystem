#ifndef BOOKING_H
#define BOOKING_H

#include <string>

// Booking structure
class Booking {
public:
    std::string bookingID;
    std::string customerID;
    std::string vehicleID;
    std::string driverID;
    std::string status;   // PENDING / ACCEPTED / REJECTED
};

// Queue Node
struct BookingNode {
    Booking data;
    BookingNode* next;
};

// Queue class
class BookingQueue {
private:
    BookingNode* front;
    BookingNode* rear;

public:
    BookingQueue();

    void enqueue(Booking b);     // add booking
    void dequeue();              // remove booking
    void display();              // show bookings

    Booking getFront();          // get first booking
    bool isEmpty();
};

#endif