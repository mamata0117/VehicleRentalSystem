#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <queue>
#include <stack>

// ================= REVIEW SYSTEM =================
class ReviewSystem {
private:
    std::stack<std::string> reviews;

public:
    void addReview();
    void viewReviews();
};

// ================= BOOKING NODE =================
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

// ================= BOOKING LIST =================
class BookingList {
private:
    BookingNode* head;

public:
    BookingList();

    void createBooking();
    void viewBookings();
    void cancelBooking();
    void searchBooking();

    float calculateTotal(float vehiclePrice, std::string type, int driverCharge);
    float applyDiscount(float amount, bool isStudent);  // ✅ FIXED

    void saveToFile();
    void loadFromFile();
};

// ================= PRIORITY QUEUE =================
class PriorityBooking {
private:
    std::queue<int> bookingQueue;

public:
    void addPriorityBooking(int bookingID);
    void processBooking();
    void viewQueue();
};

#endif