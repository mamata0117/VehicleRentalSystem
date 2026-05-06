#include <iostream>
#include "booking.h"

using namespace std;

// Constructor
BookingQueue::BookingQueue() {
    front = rear = NULL;
}

// Enqueue
void BookingQueue::enqueue(Booking b) {
    BookingNode* newNode = new BookingNode;
    newNode->data = b;
    newNode->next = NULL;

    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    cout << "Booking added successfully!\n";
}

// Dequeue
void BookingQueue::dequeue() {
    if (front == NULL) {
        cout << "No bookings to remove.\n";
        return;
    }

    BookingNode* temp = front;
    front = front->next;

    if (front == NULL) {
        rear = NULL;
    }

    delete temp;

    cout << "Booking removed.\n";
}

// Display
void BookingQueue::display() {
    if (front == NULL) {
        cout << "No bookings available.\n";
        return;
    }

    BookingNode* temp = front;

    cout << "\n--- Booking Queue ---\n";

    while (temp != NULL) {
        cout << "Booking ID: " << temp->data.bookingID
             << " | Customer: " << temp->data.customerID
             << " | Vehicle: " << temp->data.vehicleID
             << " | Status: " << temp->data.status
             << endl;

        temp = temp->next;
    }
}

// Get front (FIXED)
Booking BookingQueue::getFront() {
    if (front == NULL) {
        cout << "Queue is empty!\n";
        return Booking(); // return empty object
    }
    return front->data;
}

// Check empty
bool BookingQueue::isEmpty() {
    return front == NULL;
}