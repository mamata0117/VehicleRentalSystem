#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <limits>
#include "vehicle.h"
#include "booking.h"

using namespace std;

BookingList::BookingList() {
    head = nullptr;
}

float BookingList::calculateTotal(float vehiclePrice, string type, int driverCharge) {
    if (type == "driver") {
        return vehiclePrice + driverCharge;
    }
    return vehiclePrice;
}

float BookingList::applyDiscount(float amount, bool isStudent) {
    if (isStudent) {
        cout << "Student discount applied (10%)\n";
        return amount * 0.9;
    }
    return amount;
}

void BookingList::createBooking(VehicleList &vList) {
    BookingNode* newNode = new BookingNode();

    cout << "Enter Booking ID: ";
    cin >> newNode->bookingID;

    BookingNode* check = head;
    while (check != nullptr) {
        if (check->bookingID == newNode->bookingID) {
            cout << "Booking ID already exists!\n";
            delete newNode;
            return;
        }
        check = check->next;
    }

    cout << "Enter User ID: ";
    cin >> newNode->userID;

    cout << "Enter Vehicle ID: ";
    cin >> newNode->vehicleID;

    float price = vList.getVehiclePrice(newNode->vehicleID);

    if (price == -1) {
        delete newNode;
        return;
    }

    Vehicle* temp = vList.head;

    if (temp == nullptr) {
        cout << "No vehicles available!\n";
        delete newNode;
        return;
    }

    bool found = false;

    do {
        if (temp->id == newNode->vehicleID) {
            if (!temp->available) {
                cout << "Vehicle already booked!\n";
                delete newNode;
                return;
            }

            temp->available = false;
            found = true;
            break;
        }
        temp = temp->next;
    } while (temp != vList.head);

    if (!found) {
        cout << "Vehicle not found!\n";
        delete newNode;
        return;
    }

    vList.saveVehicles();

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

void BookingList::viewBookings() {
    BookingNode* temp = head;

    if (temp == nullptr) {
        cout << "No bookings available.\n";
        return;
    }

    while (temp != nullptr) {
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

void BookingList::cancelBooking(VehicleList &vList) {
    int id;
    cout << "Enter Booking ID to cancel: ";
    cin >> id;

    BookingNode* temp = head;
    BookingNode* prev = nullptr;

    while (temp != nullptr) {
        if (temp->bookingID == id) {

            if (prev == nullptr) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }

            Vehicle* v = vList.head;

            if (v != nullptr) {
                do {
                    if (v->id == temp->vehicleID) {
                        v->available = true;
                        break;
                    }
                    v = v->next;
                } while (v != vList.head);
            }

            vList.saveVehicles();

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

void BookingList::searchBooking() {
    int id;
    cout << "Enter Booking ID to search: ";
    cin >> id;

    BookingNode* temp = head;

    while (temp != nullptr) {
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

void BookingList::saveToFile() {
    ofstream fout("bookings.txt");

    BookingNode* temp = head;

    while (temp != nullptr) {
        fout << temp->bookingID << " "
             << temp->userID << " "
             << temp->vehicleID << " "
             << temp->bookingType << " "
             << temp->isStudent << " "
             << temp->totalAmount << " "
             << temp->advancePayment << endl;

        temp = temp->next;
    }

    fout.close();
}

void BookingList::loadFromFile() {
    ifstream fin("bookings.txt");

    if (!fin) return;

    while (head != nullptr) {
        BookingNode* temp = head;
        head = head->next;
        delete temp;
    }

    BookingNode* temp;

    while (true) {
        temp = new BookingNode;

        if (!(fin >> temp->bookingID >> temp->userID >> temp->vehicleID
              >> temp->bookingType >> temp->isStudent
              >> temp->totalAmount >> temp->advancePayment)) {
            delete temp;
            break;
        }

        temp->next = head;
        head = temp;
    }

    fin.close();
}

void PriorityBooking::addPriorityBooking(int bookingID) {
    bookingQueue.push(bookingID);
    cout << "Booking added to priority queue!\n";
}

void PriorityBooking::processBooking() {
    if (bookingQueue.empty()) {
        cout << "No priority bookings!\n";
        return;
    }

    cout << "Processing Booking ID: " << bookingQueue.front() << endl;
    cout << "Booking processed and removed from queue.\n";
    bookingQueue.pop();
}

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

void ReviewSystem::addReview() {
    string review;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter your review: ";
    getline(cin, review);

    reviews.push(review);
    cout << "Review added!\n";
}

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