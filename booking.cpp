#include <iostream>
#include <fstream>
#include <cstdio>

#include "booking.h"
#include "ui.h"

using namespace std;

// Constructor
BookingQueue::BookingQueue()
{
    front = rear = NULL;
}




bool validDateFormat(string date)
{
    if(date.length() != 10)
        return false;

    if(date[2] != '/' || date[5] != '/')
        return false;

    return true;
}



int convertToDays(string date)
{
    int day = stoi(date.substr(0,2));
    int month = stoi(date.substr(3,2));
    int year = stoi(date.substr(6,4));

    return year * 365 + month * 30 + day;
}


int selectDriver(string &driverName)
{
    int choice;

    system("cls");

    cout << "┌──────────────────────────────────────────┐\n";
    cout << "│            AVAILABLE DRIVERS             │\n";
    cout << "├──────────────────────────────────────────┤\n";
    cout << "│ 1. Ram    (Rs.2000/day)                  │\n";
    cout << "│ 2. Hari   (Rs.2500/day)                  │\n";
    cout << "│ 3. Shyam  (Rs.3000/day)                  │\n";
    cout << "└──────────────────────────────────────────┘\n";



    cout << "\nSelect Driver: ";
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

            cout<<"\n┌────────────────────────────────────────┐\n";
            cout << "│ Invalid Driver Selection               │\n";
            cout << "└────────────────────────────────────────┘\n";

            return 0;
    }
}



void BookingQueue::updateVehicleStatus(string vehicleID)
{
    ifstream fin("vehicles.txt");
    ofstream fout("temp.txt");

    if (!fin || !fout)
{
    printMessage("Error Opening Vehicle File.");
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



void BookingQueue::createBooking()
{
    system("cls");

    Booking b;

    string plate, t;
    float r;

    printInputHeader("CREATE BOOKING");

    cout << "Enter Vehicle ID   : ";
    cin >> plate;

    b.vehicleID = plate;

    cout << "Enter Customer ID  : ";
    cin >> b.customerID;

    cout << "Enter Vehicle Type : ";
    cin >> t;

    cout << "Enter Rent Per Day : ";
    cin >> r;

    // DATE INPUT

    string startDate, endDate;

    cout << "Start Date (DD/MM/YYYY) : ";
    cin >> startDate;

    cout << "End Date   (DD/MM/YYYY) : ";
    cin >> endDate;

    if(!validDateFormat(startDate) || !validDateFormat(endDate))
    {
        printMessage("Invalid Date Format. Use DD/MM/YYYY");
        return;
    }

    int days =
        convertToDays(endDate) -
        convertToDays(startDate);

    if(days <= 0)
    {
        printMessage("End Date Must Be After Start Date.");
        return;
    }

    // TOTAL CALCULATION

    float total = days * r;
    char studentChoice;

cout << "\nAre You Student? (y/n) : ";
cin >> studentChoice;

if(studentChoice == 'y' || studentChoice == 'Y')
{
    float discount = total * 0.10;

    total = total - discount;

    printMessage("10% Student Discount Applied.");
}
    printMenuHeader("BOOKING SUMMARY");

    printMenuItem(
        "Total Days : " +
        to_string(days)
    );

    printMenuItem(
        "Total Cost : Rs. " +
        to_string((int)total)
    );

    printMenuFooter();

    // DRIVER OPTION

    char choice;

    cout << "\nNeed Driver? (y/n) : ";
    cin >> choice;

    string driverName = "";
    int driverCharge = 0;

    if(choice == 'y' || choice == 'Y')
    {
        driverCharge = selectDriver(driverName);

        if(driverCharge == 0)
        {
            printMessage("Driver Selection Failed.");
            return;
        }

        total += driverCharge * days;
    }

    // SAVE RENTAL

    ofstream fout("rentals.txt", ios::app);

    fout << plate << " | "
         << t << " | "
         << startDate << " | "
         << endDate << " | Driver: "
         << driverName << " | Rs. "
         << total << endl;

    fout.close();

    // BOOKING DETAILS

    b.bookingID = "B001";
    b.status = "Booked";

    // ADD TO QUEUE

    enqueue(b);

    printMessage("Booking Created Successfully.");
}


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

    printMessage("Booking Added Successfully.");
}



void BookingQueue::dequeue()
{
    if (front == NULL)
    {
        printMessage("No Bookings To Remove.");
        return;
    }

    BookingNode* temp = front;

    front = front->next;

    if (front == NULL)
    {
        rear = NULL;
    }

    delete temp;

    printMessage("Booking Removed.");
}



void BookingQueue::display()
{
    if (front == NULL)
    {
        printMessage("No Bookings Available.");
        return;
    }

    BookingNode* temp = front;

    printMenuHeader("BOOKING QUEUE");

    while(temp != NULL)
    {
        printMenuItem(
            "Booking ID : " +
            temp->data.bookingID
        );

        printMenuItem(
            "Customer   : " +
            temp->data.customerID
        );

        printMenuItem(
            "Vehicle    : " +
            temp->data.vehicleID
        );

        printMenuItem(
            "Status     : " +
            temp->data.status
        );

        printLine();

        temp = temp->next;
    }

    printMenuFooter();
}



Booking BookingQueue::getFront()
{
    if (front == NULL)
    {
        printMessage("Queue Is Empty.");
        return Booking();
    }

    return front->data;
}



bool BookingQueue::isEmpty()
{
    return front == NULL;
}