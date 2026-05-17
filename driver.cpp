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

    cout << "Enter Experience  : ";
    cin >> experience;

    ofstream fout("drivers.txt", ios::app);

    fout << userID << " "
         << citizenship << " "
         << license << " "
         << experience << endl;

    fout.close();

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
        stringstream ss(line);

        string bookingID;
        string customerID;
        string vehicleID;
        string pickupDate;
        string returnDate;
        string drivingMode;
        string customerLicense;
        string assignedDriver;
        string totalCost;
        string advancePayment;
        string status;

        getline(ss, bookingID, '|');
        getline(ss, customerID, '|');
        getline(ss, vehicleID, '|');
        getline(ss, pickupDate, '|');
        getline(ss, returnDate, '|');
        getline(ss, drivingMode, '|');
        getline(ss, customerLicense, '|');
        getline(ss, assignedDriver, '|');
        getline(ss, totalCost, '|');
        getline(ss, advancePayment, '|');
        getline(ss, status);

        if(assignedDriver == getUserID())
        {
            if(pickupDate == todayDate)
            {
                totalRides++;
            }
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

    bool found = false;

    printMenuHeader("MY REVIEWS");

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
            found = true;

            printMenuItem(
                "Booking ID  : " + bookingID
            );

            printMenuItem(
                "Customer ID : " + customerID
            );

            printMenuItem(
                "Rating      : " + rating + "/5"
            );

            printMenuItem(
                "Review      : " + review
            );

            printLine();
        }
    }

    if(!found)
    {
        printMenuItem("No Reviews Yet.");
    }

    printMenuFooter();

    fin.close();
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

    printMenuHeader("PENDING BOOKINGS");

    // Show pending bookings
    while(getline(fin, line))
    {
        if(line.find("PENDING") != string::npos)
        {
            printMenuItem(line);
            found = true;
        }
    }

    fin.close();

    if(!found)
    {
        printMessage("No Pending Bookings.");
        return;
    }

    printLine();

    string bookingID;

    cout << "Enter Booking ID To Accept : ";
    cin >> bookingID;

    fin.open("bookings.txt");
    ofstream fout("temp.txt");

    bool accepted = false;
    string customerID = "";

    while(getline(fin, line))
    {
        if (line.empty())
        {
            fout << line << endl;
            continue;
        }

        // Parse first field (BookingID)
        size_t firstPipe = line.find('|');
        if (firstPipe != string::npos)
        {
            string id = line.substr(0, firstPipe);

            if (id == bookingID)
            {
                // Check if booking is PENDING
                if (line.find("PENDING") != string::npos)
                {
                    // Parse all fields
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

                    if (fields.size() >= 13)
                    {
                        customerID = fields[1];  // Get customer ID
                        // Update driver ID (field 9) and status (field 12)
                        fields[9] = getUserID();  // Assign driver
                        fields[12] = "ACCEPTED"; // Update status

                        // Reconstruct line
                        line = "";
                        for (size_t i = 0; i < fields.size(); i++)
                        {
                            line += fields[i];
                            if (i < fields.size() - 1)
                                line += "|";
                        }

                        accepted = true;
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

    if(accepted)
    {
        system("cls");
        printMenuHeader("BOOKING ACCEPTED");
        printMenuItem("Booking ID      : " + bookingID);
        printMenuItem("Customer ID     : " + customerID);
        
        // Load customer details from file
        ifstream custFile("customers.txt");
        if (custFile)
        {
            string fileID, fileName, fileAge, filePhone, fileEmail, filePassword, fileRole;
            while (getline(custFile, fileID) && getline(custFile, fileName) && 
                   getline(custFile, fileAge) && getline(custFile, filePhone) && 
                   getline(custFile, fileEmail) && getline(custFile, filePassword) &&
                   getline(custFile, fileRole))
            {
                if (fileID == customerID)
                {
                    printMenuItem("Customer Name   : " + fileName);
                    printMenuItem("Customer Phone  : " + filePhone);
                    printMenuItem("Customer Email  : " + fileEmail);
                    printLine();
                    printMessage("Booking Accepted Successfully!");
                    break;
                }
            }
            custFile.close();
        }
        printMenuFooter();
    }
    else
    {
        printMessage("Invalid Booking ID or not PENDING.");
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

    printMenuHeader("PENDING BOOKINGS");

    while(getline(fin, line))
    {
        if(line.find("PENDING") != string::npos)
        {
            printMenuItem(line);
            found = true;
        }
    }

    fin.close();

    if(!found)
    {
        printMessage("No Pending Bookings.");
        return;
    }

    printLine();

    string bookingID;

    cout << "Enter Booking ID To Reject : ";
    cin >> bookingID;

    fin.open("bookings.txt");
    ofstream fout("temp.txt");

    bool rejected = false;
    string customerID = "";
    string vehicleID = "";
    string pickupLocation = "";
    string destination = "";
    string pickupDate = "";

    while(getline(fin, line))
    {
        if (line.empty())
        {
            fout << line << endl;
            continue;
        }

        // Parse first field (BookingID)
        size_t firstPipe = line.find('|');
        if (firstPipe != string::npos)
        {
            string id = line.substr(0, firstPipe);

            if (id == bookingID)
            {
                // Check if booking is PENDING
                if (line.find("PENDING") != string::npos)
                {
                    // Parse fields to get details
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

                    if (fields.size() >= 13)
                    {
                        customerID = fields[1];
                        vehicleID = fields[2];
                        pickupLocation = fields[3];
                        destination = fields[4];
                        pickupDate = fields[5];
                    }

                    // Replace last field (status) from PENDING to REJECTED
                    size_t lastPipe = line.rfind('|');
                    if (lastPipe != string::npos)
                    {
                        line = line.substr(0, lastPipe + 1) + "REJECTED";
                        rejected = true;
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

    if(rejected)
    {
        system("cls");
        printMenuHeader("BOOKING CANCELLED");
        printMenuItem("Booking ID      : " + bookingID);
        printMenuItem("Customer ID     : " + customerID);
        printMenuItem("Vehicle ID      : " + vehicleID);
        printMenuItem("Pickup Location : " + pickupLocation);
        printMenuItem("Destination     : " + destination);
        printMenuItem("Pickup Date     : " + pickupDate);
        printLine();
        printMessage("Booking Rejected Successfully!");
        printMenuFooter();
    }
    else
    {
        printMessage("Invalid Booking ID or not PENDING.");
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

    // Load from file
    ifstream fin("drivers.txt");
    if (fin)
    {
        string line;
        while (getline(fin, line))
        {
            if (line.empty()) continue;
            stringstream ss(line);
            string fileID, fileCitizenship, fileLicense;
            int exp;
            if (ss >> fileID >> fileCitizenship >> fileLicense >> exp)
            {
                if (fileID == userID)
                {
                    license = fileLicense;
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

    // Load from file
    ifstream fin("drivers.txt");
    if (fin)
    {
        string line;
        while (getline(fin, line))
        {
            if (line.empty()) continue;
            stringstream ss(line);
            string fileID, fileCitizenship, fileLicense;
            int exp;
            if (ss >> fileID >> fileCitizenship >> fileLicense >> exp)
            {
                if (fileID == userID)
                {
                    citizenship = fileCitizenship;
                    fin.close();
                    return citizenship;
                }
            }
        }
        fin.close();
    }

    return "Not Found";
}

int Driver::getExperience() {
    return experience;
}