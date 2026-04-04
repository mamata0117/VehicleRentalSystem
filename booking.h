#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <queue>
#include <stack>

class VehicleList;

class ReviewSystem {
private:
    std::stack<std::string> reviews;

public:
    void addReview();
    void viewReviews();
};

struct BookingNode {
    int bookingID;
    int userID;
    int vehicleID;
    std::string bookingType;
    float totalAmount;
    float advancePayment;
    bool isStudent;

    BookingNode* next;
};

class BookingList {
private:
    BookingNode* head;

public:
    BookingList();

    void createBooking(VehicleList &vList);
    void cancelBooking(VehicleList &vList);

    void viewBookings();
    void searchBooking();

    float calculateTotal(float vehiclePrice, std::string type, int driverCharge);
    float applyDiscount(float amount, bool isStudent);

    void saveToFile();
    void loadFromFile();
};

class PriorityBooking {
private:
    std::queue<int> bookingQueue;

public:
    void addPriorityBooking(int bookingID);
    void processBooking();
    void viewQueue();
};

#endif