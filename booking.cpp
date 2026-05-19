#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>

#include "booking.h"
#include "UI.h"
#include "idgenerator.h"
#include "vehicle.h"

using namespace std;

void saveBookingToFile(Booking b);

string generateBookingID()
{
    return IDGenerator::generateID("BOOKING");
}
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

    // Accurate day counting (approximation acceptable for rental system)
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Check for leap year
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        daysInMonth[2] = 29;

    // Calculate days from year 0
    int totalDays = year * 365 + year/4 - year/100 + year/400;

    // Add days from months
    for (int i = 1; i < month; i++)
        totalDays += daysInMonth[i];

    // Add remaining days
    totalDays += day;

    return totalDays;
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

    string line;

    while (getline(fin, line))
    {
        if (line.empty()) continue;

        size_t pipePos = line.find('|');
        if (pipePos != string::npos)
        {
            string id = line.substr(0, pipePos);

            if (id == vehicleID)
            {
                // Replace last status with "Booked"
                size_t lastPipe = line.rfind('|');
                if (lastPipe != string::npos)
                {
                    line = line.substr(0, lastPipe + 1) + "Booked";
                }
            }
        }

        fout << line << endl;
    }

    fin.close();
    fout.close();

    remove("vehicles.txt");
    rename("temp.txt", "vehicles.txt");
}


void BookingQueue::enqueue(Booking b, bool updateVehicle)
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

    if (updateVehicle)
    {
        updateVehicleStatus(b.vehicleID);
        saveBookingToFile(b);
    }

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
void BookingQueue::generateBill(Booking b)
{
    ofstream fout("bills.txt", ios::app);

    fout << "=========================================\n";
    fout << "           VEHICLE RENTAL BILL           \n";
    fout << "=========================================\n";

    fout << "Booking ID      : "
         << b.bookingID << endl;

    fout << "Customer ID     : "
         << b.customerID << endl;

    fout << "Vehicle ID      : "
         << b.vehicleID << endl;

    fout << "Pickup Date     : "
         << b.pickupDate << endl;

    fout << "Return Date     : "
         << b.returnDate << endl;

    fout << "Driving Mode    : "
         << b.drivingMode << endl;

    fout << "Assigned Driver : "
         << b.assignedDriver << endl;

    fout << "Total Amount    : Rs. "
         << b.totalCost << endl;

    fout << "Booking Status  : "
         << b.status << endl;

    fout << "=========================================\n\n";

    fout.close();

    // DISPLAY BILL

    system("cls");

    cout << "┌──────────────────────────────────────────┐\n";
    cout << "│               FINAL BILL                │\n";
    cout << "├──────────────────────────────────────────┤\n";

    cout << "│ Booking ID : "
         << b.bookingID << endl;

    cout << "│ Vehicle ID : "
         << b.vehicleID << endl;

    cout << "│ Amount     : Rs. "
         << b.totalCost << endl;

    cout << "│ Status     : "
         << b.status << endl;

    cout << "└──────────────────────────────────────────┘\n";
}

// Save booking to file
void saveBookingToFile(Booking b)
{
    ofstream fout("bookings.txt", ios::app);

    if (!fout)
    {
        printMessage("Error opening bookings.txt for writing.");
        return;
    }

    fout << b.bookingID << "|"
         << b.customerID << "|"
         << b.vehicleID << "|"
         << b.pickupLocation << "|"
         << b.destination << "|"
         << b.pickupDate << "|"
         << b.pickupTime << "|"
         << b.returnDate << "|"
         << b.drivingMode << "|"
         << b.customerLicense << "|"
         << b.assignedDriver << "|"
         << b.totalCost << "|"
         << b.advancePayment << "|"
         << b.status << "|"
         << b.deliveryOption << "|"
         << b.deliveryAddress << "|"
         << b.bookingCategory << "|"
         << b.goodsType << "|"
         << b.goodsWeight << "|"
         << (b.refrigeratedRequired ? "1" : "0") << endl;

    fout.close();
}

// Load bookings from file
void loadBookingsFromFile(BookingQueue& queue)
{
    ifstream fin("bookings.txt");

    if (!fin)
    {
        return;
    }

    string line;
    while (getline(fin, line))
    {
        if (line.empty()) continue;

        Booking b;
        size_t pos = 0;
        vector<string> fields;

        while (pos < line.length())
        {
            size_t pipePos = line.find('|', pos);
            if (pipePos == string::npos)
            {
                fields.push_back(line.substr(pos));
                break;
            }
            fields.push_back(line.substr(pos, pipePos - pos));
            pos = pipePos + 1;
        }

        if (fields.size() >= 15)
        {
            b.bookingID = fields[0];
            b.customerID = fields[1];
            b.vehicleID = fields[2];
            b.pickupLocation = fields[3];
            b.destination = fields[4];
            b.pickupDate = fields[5];
            b.pickupTime = fields[6];
            b.returnDate = fields[7];
            b.drivingMode = fields[8];
            b.customerLicense = fields[9];
            b.assignedDriver = fields[10];
           try {
    if (!fields[11].empty())
        b.totalCost = stof(fields[11]);
    else
        b.totalCost = 0;

    if (!fields[12].empty())
        b.advancePayment = stof(fields[12]);
    else
        b.advancePayment = 0;
}
catch (const invalid_argument& e) {
    cout << "Invalid numeric value in bookings.txt" << endl;
    cout << "fields[11]: " << fields[11] << endl;
    cout << "fields[12]: " << fields[12] << endl;

    b.totalCost = 0;
    b.advancePayment = 0;
}
            b.status = fields[13];
            b.deliveryOption = fields[14];
            b.deliveryAddress = (fields.size() > 15) ? fields[15] : "";
            b.bookingCategory = (fields.size() > 16) ? fields[16] : "";
            b.goodsType = (fields.size() > 17) ? fields[17] : "";
            b.goodsWeight = (fields.size() > 18) ? fields[18] : "";
            b.refrigeratedRequired = (fields.size() > 19 && fields[19] == "1") ? true : false;

            // Use special function to avoid vehicle status update during load
            enqueueBookingWithoutUpdateVehicle(queue, b);
        }
    }

    fin.close();
}

// Enqueue booking without updating vehicle status (used during file loading)
void enqueueBookingWithoutUpdateVehicle(BookingQueue& queue, Booking b)
{
    queue.enqueue(b, false);  // false = don't update vehicle status
}

// Validate Customer ID format (C-1, C-15, etc.)
bool isValidCustomerID(string customerID)
{
    if (customerID.length() < 2)
        return false;
    
    if (customerID[0] != 'C' || customerID[1] != '-')
        return false;
    
    for (size_t i = 2; i < customerID.length(); i++)
    {
        if (!isdigit(customerID[i]))
            return false;
    }
    
    return true;
}

// Check if customer has a pending booking without driver assignment
bool customerIDHasPendingBooking(string customerID)
{
    ifstream fin("bookings.txt");
    
    if (!fin)
        return false;
    
    string line;
    while (getline(fin, line))
    {
        if (line.empty()) continue;
        
        vector<string> fields;
        size_t pos = 0;
        while (pos < line.length())
        {
            size_t pipePos = line.find('|', pos);
            if (pipePos == string::npos)
            {
                fields.push_back(line.substr(pos));
                break;
            }
            fields.push_back(line.substr(pos, pipePos - pos));
            pos = pipePos + 1;
        }
        
        if (fields.size() >= 14 && fields[1] == customerID && 
            fields[13] == "PENDING" && fields[9].empty())
        {
            fin.close();
            return true;
        }
    }
    
    fin.close();
    return false;
}

// Set vehicle status to AVAILABLE
void setVehicleAvailable(string vehicleID)
{
    // Update in-memory vehicle object
    Vehicle* v = findVehicleByID(vehicleID);
    if (v != NULL)
    {
        v->setAvailability(true);
    }
    
    // Update file
    ifstream fin("vehicles.txt");
    ofstream fout("temp.txt");
    
    if (!fin || !fout)
    {
        printMessage("Error Opening Vehicle File.");
        return;
    }
    
    string line;
    
    while (getline(fin, line))
    {
        if (line.empty()) continue;
        
        size_t pipePos = line.find('|');
        if (pipePos != string::npos)
        {
            string id = line.substr(0, pipePos);
            
            if (id == vehicleID)
            {
                size_t lastPipe = line.rfind('|');
                if (lastPipe != string::npos)
                {
                    line = line.substr(0, lastPipe + 1) + "Available";
                }
            }
        }
        
        fout << line << endl;
    }
    
    fin.close();
    fout.close();
    
    remove("vehicles.txt");
    rename("temp.txt", "vehicles.txt");
}

// Update booking status
void updateBookingStatus(string bookingID, string newStatus)
{
    ifstream fin("bookings.txt");
    ofstream fout("temp.txt");
    
    if (!fin || !fout)
    {
        printMessage("Error opening bookings file.");
        return;
    }
    
    string line;
    
    while (getline(fin, line))
    {
        if (line.empty())
        {
            fout << line << endl;
            continue;
        }
        
        size_t firstPipe = line.find('|');
        if (firstPipe != string::npos)
        {
            string id = line.substr(0, firstPipe);
            
            if (id == bookingID)
            {
                vector<string> fields;
                size_t pos = 0;
                while (pos < line.length())
                {
                    size_t pipePos = line.find('|', pos);
                    if (pipePos == string::npos)
                    {
                        fields.push_back(line.substr(pos));
                        break;
                    }
                    fields.push_back(line.substr(pos, pipePos - pos));
                    pos = pipePos + 1;
                }
                
                if (fields.size() >= 14)
                {
                    fields[13] = newStatus;
                    
                    line = "";
                    for (size_t i = 0; i < fields.size(); i++)
                    {
                        line += fields[i];
                        if (i < fields.size() - 1)
                            line += "|";
                    }
                }
            }
        }
        
        fout << line << endl;
    }
    
    fin.close();
    fout.close();
    
    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");
}

// Find active booking (PENDING or APPROVED) for a given vehicle
Booking findActiveBookingForVehicle(string vehicleID)
{
    Booking emptyBooking;
    emptyBooking.vehicleID = "";
    
    ifstream fin("bookings.txt");
    
    if (!fin)
    {
        return emptyBooking;
    }
    
    string line;
    while (getline(fin, line))
    {
        if (line.empty()) continue;
        
        vector<string> fields;
        size_t pos = 0;
        while (pos < line.length())
        {
            size_t pipePos = line.find('|', pos);
            if (pipePos == string::npos)
            {
                fields.push_back(line.substr(pos));
                break;
            }
            fields.push_back(line.substr(pos, pipePos - pos));
            pos = pipePos + 1;
        }
        
        // Check if this is the vehicle we're looking for (field 2 is vehicleID)
        // and the booking is active (PENDING or APPROVED - field 13 is status)
        if (fields.size() >= 14 && fields[2] == vehicleID && 
            (fields[13] == "PENDING" || fields[13] == "APPROVED"))
        {
            Booking b;
            b.bookingID = fields[0];
            b.customerID = fields[1];
            b.vehicleID = fields[2];
            b.assignedDriver = fields[10];
            b.status = fields[13];
            
            fin.close();
            return b;
        }
    }
    
    fin.close();
    return emptyBooking;
}