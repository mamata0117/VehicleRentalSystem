#include <iostream>
#include <fstream>
#include<sstream>
#include <vector>
#include "driver.h"
#include "UI.h"

using namespace std;

void Driver::setupDriver()
{
    system("cls");

    printInputHeader("DRIVER SETUP");

    citizenship = inputCitizenship();
    license = inputLicense();
    experience = getExperience();

    // Save citizenship and license to driver_citizenship.txt
    ifstream fin("driver_citizenship.txt");
    bool exists = false;
    string line;
    
    if (fin)
    {
        while (getline(fin, line))
        {
            if (!line.empty())
            {
                size_t pipePos = line.find('|');
                if (pipePos != string::npos)
                {
                    string fileID = line.substr(0, pipePos);
                    if (fileID == userID)
                    {
                        exists = true;
                        break;
                    }
                }
            }
        }
        fin.close();
    }

    if (!exists)
    {
        // Append new record to driver_citizenship.txt
        ofstream fout("driver_citizenship.txt", ios::app);
        fout << userID << "|" << citizenship << "|" << license << endl;
        fout.close();
    }
    else
    {
        // Update existing record
        ifstream fin("driver_citizenship.txt");
        ofstream fout("driver_citizenship_temp.txt");
        
        while (getline(fin, line))
        {
            if (!line.empty())
            {
                size_t pipePos = line.find('|');
                if (pipePos != string::npos)
                {
                    string fileID = line.substr(0, pipePos);
                    if (fileID == userID)
                    {
                        fout << userID << "|" << citizenship << "|" << license << endl;
                    }
                    else
                    {
                        fout << line << endl;
                    }
                }
            }
        }
        
        fin.close();
        fout.close();
        
        remove("driver_citizenship.txt");
        rename("driver_citizenship_temp.txt", "driver_citizenship.txt");
    }

    printMessage("Driver Setup Completed Successfully.");
}

void Driver::viewTotalRidesToday()
{
    ifstream fin("bookings.txt");

    if(!fin)
    {
        printMessage("No Booking Records Found.");
        return;
    }

    string todayDate;

    printInputHeader("TOTAL RIDES TODAY");

    cout << "Enter Today's Date : ";
    cin >> todayDate;

    string line;
    int totalRides = 0;

    while(getline(fin, line))
    {
        if(line.empty()) continue;
        
        stringstream ss(line);

        string bookingID;
        string customerID;
        string vehicleID;
        string pickupDate;
        string returnDate;
        string drivingMode;
        string customerLicense;
        string assignedDriver;

        getline(ss, bookingID, '|');
        getline(ss, customerID, '|');
        getline(ss, vehicleID, '|');
        getline(ss, pickupDate, '|');
        getline(ss, returnDate, '|');
        getline(ss, drivingMode, '|');
        getline(ss, customerLicense, '|');
        getline(ss, assignedDriver, '|');

        if(assignedDriver == getUserID() && pickupDate == todayDate && drivingMode == "With Driver")
        {
            totalRides++;
        }
    }

    fin.close();

    printMessage(
        "Total Rides Today : " +
        to_string(totalRides)
    );
}
   
void Driver::viewReviews()
{
    system("cls");

    ifstream fin("reviews.txt");

    if(!fin)
    {
        printMessage("No Reviews Found.");
        return;
    }

    string line;
    Stack<string> reviewStack;

    while(getline(fin, line))
    {
        stringstream ss(line);

        string driverID;
        string customerID;
        string bookingID;
        string rating;
        string review;

        getline(ss, driverID, '|');
        getline(ss, customerID, '|');
        getline(ss, bookingID, '|');
        getline(ss, rating, '|');
        getline(ss, review);

        if(driverID == getUserID())
        {
            stringstream out;
            out << "Booking ID  : " << bookingID << '\n';
            out << "Customer ID : " << customerID << '\n';
            out << "Rating      : " << rating << "/5" << '\n';
            out << "Review      : " << review << '\n';
            reviewStack.push(out.str());
        }
    }

    fin.close();

    printMenuHeader("MY REVIEWS (MOST RECENT FIRST)");

    if(reviewStack.isEmpty())
    {
        printMenuItem("No Reviews Yet.");
    }
    else
    {
        // Pop from stack displays most recent first (LIFO)
        while(!reviewStack.isEmpty())
        {
            stringstream ss(reviewStack.peek());
            string l;
            while (getline(ss, l))
            {
                printMenuItem(l);
            }
            printLine();
            reviewStack.pop();
        }
    }

    printMenuFooter();
}

void Driver::acceptCustomer(BookingQueue& queue)
{
    system("cls");

    ifstream fin("bookings.txt");

    if(!fin)
    {
        printMessage("No Booking Records Found.");
        return;
    }

    string line;
    bool found = false;

    printMenuHeader("PENDING BOOKINGS (FOR APPROVAL)");
    printf("\n %-12s | %-12s | %-12s | %-12s | %-15s\n", 
           "Booking ID", "Customer ID", "Vehicle ID", "Pickup Date", "Driving Mode");
    printLine();

    while(getline(fin, line))
    {
        if(line.empty()) continue;
        
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
        
        if (fields.size() >= 14 && fields[13] == "PENDING" && fields[9].empty())
        {
            printf(" %-12s | %-12s | %-12s | %-12s | %-15s\n", 
                   fields[0].c_str(),           // Booking ID
                   fields[1].c_str(),           // Customer ID
                   fields[2].c_str(),           // Vehicle ID
                   fields[5].c_str(),           // Pickup Date
                   fields[8].c_str());          // Driving Mode
            found = true;
        }
    }

    fin.close();

    if(!found)
    {
        printMessage("No Pending Bookings Without Driver Assignment.");
        return;
    }

    printLine();

    string customerID;

    cout << "\nEnter Customer ID To Accept : ";
    cin >> customerID;

    if (!isValidCustomerID(customerID))
    {
        printMessage("Invalid Customer ID Format. Must be C-# (e.g., C-1, C-15).");
        return;
    }

    fin.open("bookings.txt");

    if (!fin)
    {
        printMessage("Error opening bookings file.");
        return;
    }

    found = false;
    string bookingID = "";
    string vehicleID = "";
    string pickupLocation = "";
    string destination = "";
    string pickupDate = "";
    string returnDate = "";
    string drivingMode = "";
    string totalCost = "";

    while(getline(fin, line))
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
            bookingID = fields[0];
            vehicleID = fields[2];
            pickupLocation = fields[3];
            destination = fields[4];
            pickupDate = fields[5];
            returnDate = fields[7];
            drivingMode = fields[8];
            totalCost = fields[11];
            found = true;
            break;
        }
    }

    fin.close();

    if (!found)
    {
        printMessage("Invalid Customer ID or no pending booking found.");
        return;
    }

    system("cls");
    printMenuHeader("REVIEW BOOKING DETAILS");
    printMenuItem("Booking ID          : " + bookingID);
    printMenuItem("Customer ID         : " + customerID);
    printMenuItem("Vehicle ID          : " + vehicleID);
    printMenuItem("Pickup Location     : " + pickupLocation);
    printMenuItem("Destination         : " + destination);
    printMenuItem("Pickup Date         : " + pickupDate);
    printMenuItem("Return Date         : " + returnDate);
    printMenuItem("Driving Mode        : " + drivingMode);
    printMenuItem("Total Cost          : Rs. " + totalCost);
    printLine();

    string confirm;
    cout << "Do you want to ACCEPT this booking? (yes/no) : ";
    cin >> confirm;

    if (confirm != "yes" && confirm != "YES" && confirm != "Yes")
    {
        printMessage("Booking Acceptance Cancelled!");
        return;
    }

    fin.open("bookings.txt");
    ofstream fout("temp.txt");

    if (!fin || !fout)
    {
        printMessage("Error opening files.");
        return;
    }

    bool accepted = false;

    while(getline(fin, line))
    {
        if (line.empty())
        {
            fout << line << endl;
            continue;
        }

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
            fields[9] = getUserID();  // Assign driver
            fields[13] = "APPROVED"; // Update status

            line = "";
            for (size_t i = 0; i < fields.size(); i++)
            {
                line += fields[i];
                if (i < fields.size() - 1)
                    line += "|";
            }

            accepted = true;
        }

        fout << line << endl;
    }

    fin.close();
    fout.close();

    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    if(accepted)
    {
        system("cls");
        printMenuHeader("BOOKING APPROVED");
        printMenuItem("Booking ID          : " + bookingID);
        printMenuItem("Customer ID         : " + customerID);
        printMenuItem("Vehicle ID          : " + vehicleID);
        printMenuItem("Pickup Location     : " + pickupLocation);
        printMenuItem("Destination         : " + destination);
        printMenuItem("Pickup Date         : " + pickupDate);
        printMenuItem("Return Date         : " + returnDate);
        printMenuItem("Driving Mode        : " + drivingMode);
        printMenuItem("Total Cost          : Rs. " + totalCost);
        printMenuItem("Driver ID           : " + getUserID());
        printLine();
        
        printMessage("Booking Approved Successfully!");
        printMenuFooter();
        
        system("pause");
        
        rateCustomer();
    }
    else
    {
        printMessage("Error: Could not update booking status.");
    }
}
void Driver::rejectCustomer(BookingQueue& queue)
{
    system("cls");

    ifstream fin("bookings.txt");

    if(!fin)
    {
        printMessage("No Booking Records Found.");
        return;
    }

    string line;
    bool found = false;

    printMenuHeader("PENDING BOOKINGS (FOR REJECTION)");
    printf("\n %-12s | %-12s | %-12s | %-12s | %-15s\n", 
           "Booking ID", "Customer ID", "Vehicle ID", "Pickup Date", "Driving Mode");
    printLine();

    while(getline(fin, line))
    {
        if(line.empty()) continue;
        
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
        
        if (fields.size() >= 14 && fields[13] == "PENDING" && fields[9].empty())
        {
            printf(" %-12s | %-12s | %-12s | %-12s | %-15s\n", 
                   fields[0].c_str(),           // Booking ID
                   fields[1].c_str(),           // Customer ID
                   fields[2].c_str(),           // Vehicle ID
                   fields[5].c_str(),           // Pickup Date
                   fields[8].c_str());          // Driving Mode
            found = true;
        }
    }

    fin.close();

    if(!found)
    {
        printMessage("No Pending Bookings Without Driver Assignment.");
        return;
    }

    printLine();

    string customerID;

    cout << "\nEnter Customer ID To Reject : ";
    cin >> customerID;

    if (!isValidCustomerID(customerID))
    {
        printMessage("Invalid Customer ID Format. Must be C-# (e.g., C-1, C-15).");
        return;
    }

    fin.open("bookings.txt");

    if (!fin)
    {
        printMessage("Error opening bookings file.");
        return;
    }

    ofstream fout("temp.txt");

    if (!fout)
    {
        printMessage("Error creating temp file.");
        fin.close();
        return;
    }

    bool rejected = false;
    string bookingID = "";
    string vehicleID = "";
    string pickupLocation = "";
    string destination = "";
    string pickupDate = "";
    string drivingMode = "";

    while(getline(fin, line))
    {
        if (line.empty())
        {
            fout << line << endl;
            continue;
        }

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
            bookingID = fields[0];
            vehicleID = fields[2];
            pickupLocation = fields[3];
            destination = fields[4];
            pickupDate = fields[5];
            drivingMode = fields[8];
            
            fields[13] = "REJECTED";
            
            line = "";
            for (size_t i = 0; i < fields.size(); i++)
            {
                line += fields[i];
                if (i < fields.size() - 1)
                    line += "|";
            }
            
            rejected = true;
        }

        fout << line << endl;
    }

    fin.close();
    fout.close();

    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    if(rejected)
    {
        system("cls");
        printMenuHeader("BOOKING REJECTED");
        printMenuItem("Booking ID       : " + bookingID);
        printMenuItem("Customer ID      : " + customerID);
        printMenuItem("Vehicle ID       : " + vehicleID);
        printMenuItem("Pickup Location  : " + pickupLocation);
        printMenuItem("Destination      : " + destination);
        printMenuItem("Pickup Date      : " + pickupDate);
        printMenuItem("Driving Mode     : " + drivingMode);
        printLine();
        
        // Make vehicle available
        setVehicleAvailable(vehicleID);
        
        printMessage("Booking Rejected Successfully. Vehicle is now Available.");
        printMenuFooter();
    }
    else
    {
        printMessage("Invalid Customer ID or no pending booking found.");
    }
}

void Driver::rateCustomer()
{
    system("cls");

    string id;
    int rating;

    printInputHeader("RATE CUSTOMER");

    cout << "Enter Customer ID : ";
    cin >> id;

    cout << "Enter Rating (1-5): ";
    cin >> rating;

    ofstream fout("customer_ratings.txt", ios::app);

    fout << id << " "
         << rating << endl;

    fout.close();

    printMessage("Rating Submitted Successfully.");
}

string Driver::getLicense() {
    // If already loaded, return it
    if (!license.empty())
        return license;

    // Load from driver_citizenship.txt file
    ifstream fin("driver_citizenship.txt");
    if (fin)
    {
        string line;
        while (getline(fin, line))
        {
            if (line.empty()) continue;
            size_t pipePos = line.find('|');
            if (pipePos != string::npos)
            {
                string fileID = line.substr(0, pipePos);
                if (fileID == userID)
                {
                    size_t secondPipe = line.find('|', pipePos + 1);
                    if (secondPipe != string::npos)
                    {
                        license = line.substr(secondPipe + 1);
                    }
                    fin.close();
                    return license;
                }
            }
        }
        fin.close();
    }

    return "Not Found";
}

string Driver::getCitizenship() {
    // If already loaded, return it
    if (!citizenship.empty())
        return citizenship;

    // Load from driver_citizenship.txt file
    ifstream fin("driver_citizenship.txt");
    if (fin)
    {
        string line;
        while (getline(fin, line))
        {
            if (line.empty()) continue;
            size_t pipePos = line.find('|');
            if (pipePos != string::npos)
            {
                string fileID = line.substr(0, pipePos);
                if (fileID == userID)
                {
                    size_t secondPipe = line.find('|', pipePos + 1);
                    if (secondPipe != string::npos)
                    {
                        citizenship = line.substr(pipePos + 1, secondPipe - pipePos - 1);
                    }
                    fin.close();
                    return citizenship;
                }
            }
        }
        fin.close();
    }

    return "Not Found";
}

// View document status


int Driver::getExperience() {
    return experience;
}