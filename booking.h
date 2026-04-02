#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <queue>
#include <stack>

using namespace std;

// 🔥 ADD THIS LINE (VERY IMPORTANT)
class VehicleList;

// ================= REVIEW SYSTEM =================
class ReviewSystem {
private:
    stack<string> reviews;

public:
    void addReview();
    void viewReviews();
};

// ================= BOOKING NODE =================
struct BookingNode {
    int bookingID;
    int userID;
    int vehicleID;
    string bookingType;
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

    void createBooking(VehicleList &vList);   // ✅ correct now
    void cancelBooking(VehicleList &vList);   // ✅ correct now

    void viewBookings();
    void searchBooking();

    float calculateTotal(float vehiclePrice, string type, int driverCharge);
    float applyDiscount(float amount, bool isStudent);

    void saveToFile();
    void loadFromFile();
};

// ================= PRIORITY QUEUE =================
class PriorityBooking {
private:
    queue<int> bookingQueue;

public:
    void addPriorityBooking(int bookingID);
    void processBooking();
    void viewQueue();
};

#endif