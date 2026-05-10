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

// ==========================================
// DATE VALIDATION
// ==========================================

bool validDateFormat(string date)
{
    if(date.length() != 10)
        return false;

    if(date[2] != '/' || date[5] != '/')
        return false;

    return true;
}

// ==========================================
// SIMPLE DATE TO DAYS CONVERTER
// ==========================================

int convertToDays(string date)
{
    int day = stoi(date.substr(0,2));
    int month = stoi(date.substr(3,2));
    int year = stoi(date.substr(6,4));

    return year * 365 + month * 30 + day;
}

// ==========================================
// DRIVER SELECTION
// ==========================================

int selectDriver(string &driverName)
{
    int choice;

    cout << "\n--- Available Drivers ---\n";
    cout << "1. Ram  (Rs.2000/day)\n";
    cout << "2. Hari (Rs.2500/day)\n";
    cout << "3. Shyam(Rs.3000/day)\n";

    cout << "Select Driver: ";
    cin >> choice;

    switch(choice)
    {
        case 1:
            driverName = "Ram";
            return 2000;

        case 2:
            driverName = "Hari";
            return 2500;

        case 3:
            driverName = "Shyam";
            return 3000;

        default:
            return 0;
    }
}

// ==========================================
// UPDATE VEHICLE STATUS
// ==========================================

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

    while (getline(fin, id))
    {
        getline(fin, brand);
        getline(fin, model);
        getline(fin, status);

        if (id == vehicleID)
        {
            status = "Booked";
        }

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

// ==========================================
// CREATE BOOKING
// ==========================================

void BookingQueue::createBooking()
{
    Booking b;

    string plate, t;
    float r;

    cout << "\nEnter Vehicle ID: ";
    cin >> plate;

    b.vehicleID = plate;

    cout << "Enter Customer ID: ";
    cin >> b.customerID;

    cout << "Enter Vehicle Type: ";
    cin >> t;

    cout << "Enter Rent Per Day: ";
    cin >> r;

    // ==========================================
    // DATE INPUT
    // ==========================================

    string startDate,endDate;

    cout<<"Start Date: ";
    cin>>startDate;

    cout<<"End Date: ";
    cin>>endDate;

    if (!validDateFormat(startDate) || !validDateFormat(endDate))
    {
        cout << "Invalid date format! Use DD/MM/YYYY\n";
        return;
    }

    int days=convertToDays(endDate)-convertToDays(startDate);

    if (days <= 0)
    {
        cout << "End date must be after start date!\n";
        return;
    }

    // ==========================================
    // TOTAL CALCULATION
    // ==========================================

    float total = days * r;

    cout<<"Days: "<<days<<" | Total: Rs."<<total<<endl;

    // ==========================================
    // DRIVER OPTION
    // ==========================================

    char choice;

    cout<<"Need Driver? (y/n): ";
    cin>>choice;

    string driverName="";
    int driverCharge=0;

    if(choice=='y' || choice=='Y')
    {
        driverCharge = selectDriver(driverName);

        if(driverCharge==0)
        {
            cout<<"Driver selection failed!\n";
            return;
        }

        total += driverCharge * days;
    }

    // ==========================================
    // SAVE RENTAL
    // ==========================================

    ofstream fout("rentals.txt",ios::app);

    fout<<plate<<" | "
        <<t<<" | "
        <<startDate<<" | "
        <<endDate<<" | Driver: "
        <<driverName<<" | Rs. "
        <<total<<endl;

    fout.close();

    // ==========================================
    // BOOKING DETAILS
    // ==========================================

    b.bookingID = "B001";
    b.status = "Booked";

    // ==========================================
    // ADD TO QUEUE
    // ==========================================

    enqueue(b);

    cout<<"Booked Successfully!\n";
}

// ==========================================
// ENQUEUE BOOKING
// ==========================================

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

    updateVehicleStatus(b.vehicleID);

    cout << "Booking added successfully!\n";
}

// ==========================================
// DEQUEUE BOOKING
// ==========================================

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

// ==========================================
// DISPLAY BOOKINGS
// ==========================================

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

// ==========================================
// GET FRONT BOOKING
// ==========================================

Booking BookingQueue::getFront()
{
    if (front == NULL)
    {
        cout << "Queue is empty!\n";
        return Booking();
    }

    return front->data;
}

// ==========================================
// CHECK EMPTY
// ==========================================

bool BookingQueue::isEmpty()
{
    return front == NULL;
}