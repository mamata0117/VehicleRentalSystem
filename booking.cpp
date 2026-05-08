#include <iostream>
#include <fstream>
#include <cstdio>

#include "booking.h"

using namespace std;

// Constructor
BookingQueue::BookingQueue()
{
    front = rear = NULL;
}

// Update vehicle status in file
void BookingQueue::updateVehicleStatus(string vehicleID)
{
    ifstream fin("vehicles.txt");
    ofstream fout("temp.txt");

    if (!fin || !fout)
    {
        cout << "Error opening vehicle file.\n";
        return;
    }

    string id, brand, model, status;

    // Reading vehicle records
    while (getline(fin, id))
    {
        getline(fin, brand);
        getline(fin, model);
        getline(fin, status);

        // Change status if vehicle matches
        if (id == vehicleID)
        {
            status = "Booked";
        }

        // Write updated data
        fout << id << endl;
        fout << brand << endl;
        fout << model << endl;
        fout << status << endl;
    }

    fin.close();
    fout.close();

    remove("vehicles.txt");
    rename("temp.txt", "vehicles.txt");
}

// Enqueue booking
void BookingQueue::enqueue(Booking b)
{
    BookingNode* newNode = new BookingNode;

    newNode->data = b;
    newNode->next = NULL;

    if (rear == NULL)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

    // Update vehicle status
    updateVehicleStatus(b.vehicleID);

    cout << "Booking added successfully!\n";
}

// Dequeue booking
void BookingQueue::dequeue()
{
    if (front == NULL)
    {
        cout << "No bookings to remove.\n";
        return;
    }

    BookingNode* temp = front;

    front = front->next;

    if (front == NULL)
    {
        rear = NULL;
    }

    delete temp;

    cout << "Booking removed.\n";
}

// Display bookings
void BookingQueue::display()
{
    if (front == NULL)
    {
        cout << "No bookings available.\n";
        return;
    }

    BookingNode* temp = front;

    cout << "\n--- Booking Queue ---\n";

    while (temp != NULL)
    {
        cout << "Booking ID: " << temp->data.bookingID
             << " | Customer: " << temp->data.customerID
             << " | Vehicle: " << temp->data.vehicleID
             << " | Status: " << temp->data.status
             << endl;

        temp = temp->next;
    }
}

// Get front booking
Booking BookingQueue::getFront()
{
    if (front == NULL)
    {
        cout << "Queue is empty!\n";
        return Booking();
    }

    return front->data;
}

// Check if queue is empty
bool BookingQueue::isEmpty()
{
    return front == NULL;
}