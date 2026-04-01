#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include "booking.h"

using namespace std;
//initilizing head to null
BookingList::BookingList() {
    head = NULL;
}
//calculating total amount based on booking type and driver charge
float BookingList::calculateTotal(float vehiclePrice, string type, int driverCharge) {
    if (type == "driver") {
        return vehiclePrice + driverCharge;
    }
    else {
    return vehiclePrice;
    }
}

// Booking the vehicle and calculating total amount and advance payment
void BookingList::createBooking() {
    BookingNode* newNode = new BookingNode();

    cout << "Enter Booking ID: ";
    cin >> newNode->bookingID;

    cout << "Enter User ID: ";
    cin >> newNode->userID;

    cout << "Enter Vehicle ID: ";
    cin >> newNode->vehicleID;

    float price;
    cout << "Enter Vehicle Price: ";
    cin >> price;

    if (price < 0) {
        cout << "Invalid price!\n";
        delete newNode;
        return;
    }

    cout << "Booking Type (self/driver): ";
    cin >> newNode->bookingType;


    if (newNode->bookingType != "self" && newNode->bookingType != "driver") {
        cout << "Invalid booking type!\n";
        delete newNode;
        return;
    }

    int driverCharge = 0;
    if (newNode->bookingType == "driver") {
        cout << "Enter Driver Charge: ";
        cin >> driverCharge;
    }

    cout << "Are you a student? (1 = Yes / 0 = No): ";
    cin >> newNode->isStudent;

    float total = calculateTotal(price, newNode->bookingType, driverCharge);
    total = applyDiscount(total, newNode->isStudent);

    newNode->totalAmount = total;
    newNode->advancePayment = total * 0.3;

    cout << "Total: " << total << endl;
    cout << "Advance: " << newNode->advancePayment << endl;

    newNode->next = head;
    head = newNode;

    saveToFile();

    cout << "Booking Added Successfully!\n";
}

// ================= VIEW BOOKINGS =================
void BookingList::viewBookings() {
    BookingNode* temp = head;

    if (temp == NULL) {
        cout << "No bookings available.\n";
        return;
    }

    while (temp != NULL) {
        cout << "\nBooking ID: " << temp->bookingID << endl;
        cout << "User ID: " << temp->userID << endl;
        cout << "Vehicle ID: " << temp->vehicleID << endl;
        cout << "Type: " << temp->bookingType << endl;
        cout << "Total: " << temp->totalAmount << endl;
        cout << "Advance: " << temp->advancePayment << endl;
        cout << "----------------------\n";

        temp = temp->next;
    }
}

// ================= CANCEL BOOKING =================
void BookingList::cancelBooking() {
    int id;
    cout << "Enter Booking ID to cancel: ";
    cin >> id;

    BookingNode* temp = head;
    BookingNode* prev = NULL;

    while (temp != NULL) {
        if (temp->bookingID == id) {

            if (prev == NULL) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }

            delete temp;
            saveToFile();

            cout << "Booking Cancelled!\n";
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    cout << "Booking not found!\n";
}

// ================= SAVE TO FILE =================
void BookingList::saveToFile() {
    ofstream fout("bookings.txt");

    BookingNode* temp = head;

    while (temp != NULL) {
        fout << temp->bookingID << " "
             << temp->userID << " "
             << temp->vehicleID << " "
             << temp->bookingType << " "
             <<temp->isStudent<<" "
             << temp->totalAmount << " "
             << temp->advancePayment << endl;

        temp = temp->next;
    }

    fout.close();
}

// ================= LOAD FROM FILE =================
void BookingList::loadFromFile() {
    ifstream fin("bookings.txt");

    if (!fin) return;

    BookingNode* temp;

    while (true) {
        temp = new BookingNode;

        if (!(fin >> temp->bookingID >> temp->userID >> temp->vehicleID
              >> temp->bookingType >> temp->totalAmount >> temp->advancePayment)) {
            delete temp;
            break;
        }

        temp->next = head;
        head = temp;
    }

    fin.close();
}
// ================= SEARCH BOOKING =================
void BookingList::searchBooking() {
    int id;
    cout << "Enter Booking ID to search: ";
    cin >> id;

    BookingNode* temp = head;

    while (temp != NULL) {
        if (temp->bookingID == id) {
            cout << "\nBooking Found!\n";
            cout << "Booking ID: " << temp->bookingID << endl;
            cout << "User ID: " << temp->userID << endl;
            cout << "Vehicle ID: " << temp->vehicleID << endl;
            cout << "Type: " << temp->bookingType << endl;
            cout << "Total: " << temp->totalAmount << endl;
            cout << "Advance: " << temp->advancePayment << endl;
            return;
        }
        temp = temp->next;
    }

    cout << "Booking not found!\n";
}

// ================= ADD TO QUEUE =================
void PriorityBooking::addPriorityBooking(int bookingID) {
    bookingQueue.push(bookingID);
    cout << "Booking added to priority queue!\n";
}

// ================= PROCESS QUEUE =================
void PriorityBooking::processBooking() {
    if (bookingQueue.empty()) {
        cout << "No priority bookings!\n";
        return;
    }

    cout << "Processing Booking ID: " << bookingQueue.front() << endl;
    bookingQueue.pop();
}

// ================= VIEW QUEUE =================
void PriorityBooking::viewQueue() {
    if (bookingQueue.empty()) {
        cout << "Queue is empty!\n";
        return;
    }

    queue<int> temp = bookingQueue;

    cout << "\n--- Priority Queue ---\n";
    while (!temp.empty()) {
        cout << temp.front() << endl;
        temp.pop();
    }
}



// ================= ADD REVIEW =================
void ReviewSystem::addReview() {
    string review;
    cin.ignore();
    cout << "Enter your review: ";
    getline(cin, review);

    reviews.push(review);

    cout << "Review added!\n";
}

// ================= VIEW REVIEWS =================
void ReviewSystem::viewReviews() {
    if (reviews.empty()) {
        cout << "No reviews yet.\n";
        return;
    }

    stack<string> temp = reviews;

    cout << "\n--- Driver Reviews ---\n";

    while (!temp.empty()) {
        cout << temp.top() << endl;
        temp.pop();
    }
}
float BookingList::applyDiscount(float amount, bool isStudent) {
    if (isStudent) {
        cout << "Student discount applied (10%)\n";
        return amount * 0.9;
    }
    return amount;
}