#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include "customer.h"
#include "vehicle.h"
#include "booking.h"
#include "UI.h"

using namespace std;

// Customer setup
void Customer::setupCustomer()
{
    system("cls");
    printInputHeader("CUSTOMER SETUP");

    cout << "Are you a student? 1 for Yes, 0 for No: ";
    cin >> isStudent;

    cin.ignore();

    citizenship = inputCitizenship();

    // Save customer citizenship to file
    ofstream fout("customer_citizenship.txt", ios::app);
    fout << userID << "|" << citizenship << endl;
    fout.close();

    printMessage("Customer setup completed successfully.");
}

void Customer::loadCustomerData()
{
    // Load customer data from citizenship file
    ifstream fin("customer_citizenship.txt");
    if (fin)
    {
        string line;
        while (getline(fin, line))
        {
            if (line.empty()) continue;
            
            size_t pos1 = line.find('|');
            if (pos1 != string::npos)
            {
                string id = line.substr(0, pos1);
                if (id == userID)
                {
                    size_t pos2 = line.find('|', pos1 + 1);
                    if (pos2 != string::npos)
                    {
                        citizenship = line.substr(pos1 + 1, pos2 - pos1 - 1);
                        string studentStr = line.substr(pos2 + 1);
                        isStudent = (stoi(studentStr) == 1);
                    }
                    else
                    {
                        citizenship = line.substr(pos1 + 1);
                        isStudent = false;
                    }
                    fin.close();
                    return;
                }
            }
        }
        fin.close();
    }
    isStudent = false;
}

void Customer::reviewDriver()
{
    string driverID;
    string bookingID;
    int rating;
    string review;

    system("cls");
    printInputHeader("DRIVER REVIEW");

    cout << "Enter Booking ID : ";
    cin >> bookingID;

    cout << "Enter Driver ID  : ";
    cin >> driverID;

    // Validate driver exists
    ifstream driverFile("drivers.txt");
    bool driverExists = false;
    string driverName = "";
    
    if (driverFile)
    {
        string fileID, fileCitizenship, fileLicense, experienceStr;
        while (getline(driverFile, fileID) && getline(driverFile, fileCitizenship) && 
               getline(driverFile, fileLicense) && getline(driverFile, experienceStr))
        {
            if (fileID == driverID)
            {
                driverExists = true;
               
                break;
            }
        }
        driverFile.close();
    }

    if (!driverExists)
    {
        printMessage("Driver ID not found. Invalid Driver.");
        return;
    }

    // Rating validation
    bool validRating = false;
    while (!validRating)
    {
        cout << "Rate Driver (1-5): ";
        cin >> rating;

        if (rating < 1 || rating > 5)
        {
            cout << "Invalid rating! Please enter a value between 1 and 5.\n";
        }
        else
        {
            validRating = true;
        }
    }

    cin.ignore();

    cout << "Write Review: ";
    getline(cin, review);

    // Saving the review to file
    ofstream fout("reviews.txt", ios::app);

    fout << driverID << "|"
         << getUserID() << "|"
         << bookingID << "|"
         << rating << "|"
         << review << endl;

    fout.close();

    system("cls");
    printMenuHeader("REVIEW SUBMITTED");
    printMenuItem("Driver ID    : " + driverID);
    printMenuItem("Booking ID   : " + bookingID);
    printMenuItem("Rating       : " + to_string(rating) + "/5");
    printMenuItem("Review       : " + review);
    printLine();
    printMessage("Review Submitted Successfully!");
    printMenuFooter();
}

// Customer menu
void Customer::customerMenu(BookingQueue& queue)
{
    int choice;

    do
{
    system("cls");

    printMenuHeader("CUSTOMER MENU");
    printMenuItem("1. View Available Vehicles");
    printMenuItem("2. Book Vehicle");
    printMenuItem("3. Cancel Booking");
    printMenuItem("4. View My Ratings");
    printMenuItem("5. Exit");
    printMenuFooter();

    cout << "\nEnter choice: ";
    cin >> choice;

    switch(choice)
    {
        case 1:
            viewVehicles();
            break;

        case 2:
            bookVehicle(queue);
            break;

        case 3:
            cancelBooking();
            break;

        case 4:
            viewRatings();
            break;

        case 5:
            exit(0);
            break;

        default:
            cout << "Invalid choice.\n";
    }

} while(choice != 5);
}

// View vehicles
void Customer::viewVehicles()
{
    displayAvailableVehicles();
}

// Checks if vehicle is passenger type
bool isPassengerVehicle(string category)
{
    return (category == "Car" || category == "Bike" || 
            category == "Scooter" || category == "Van");
}

// Checks if vehicle is goods type
bool isGoodsVehicle(string category)
{
    return (category == "Truck" || category == "Mini Truck" || 
            category == "Pickup Truck" || category == "Cargo Van" || 
            category == "Refrigerated Van");
}

// Book passenger vehicle
void Customer::bookPassengerVehicle(BookingQueue& queue)
{
    system("cls");

    if (head == NULL)
    {
        printMessage("No Vehicles Available.");
        return;
    }

    // Count only passenger vehicles
    VehicleNode* temp = head;
    int vehicleCount = 0;
    int available_count = 0;
    vector<string> vehicleIDs;

    while (temp != NULL)
    {
        if (isPassengerVehicle(temp->data.getCategory()))
        {
            if (temp->data.isAvailable())
                available_count++;
        }
        temp = temp->next;
    }

    if (available_count == 0)
    {
        printMessage("No Available Passenger Vehicles.");
        return;
    }

    system("cls");
   printMenuHeader("SELECT PASSENGER VEHICLE");

printf("\n %-3s %-12s %-10s %-10s %-14s %-14s\n\n",
       "No.",
       "Vehicle ID",
       "Type",
       "Fuel",
       "Self Price",
       "Driver Price");

temp = head;

while (temp != NULL)
{
    if (isPassengerVehicle(temp->data.getCategory()) &&
        temp->data.isAvailable())
    {
        vehicleCount++;

        vehicleIDs.push_back(
            temp->data.getVehicleID());

        string fuelType =
            temp->data.getFuelType();

        printf(" %-3d %-12s %-10s %-10s Rs%-12d Rs%-12d\n",
               vehicleCount,
               temp->data.getVehicleID().c_str(),
               temp->data.getCategory().c_str(),
               fuelType.c_str(),
               (int)temp->data.getSelfDrivePrice(),
               (int)temp->data.getDriverPrice());
    }

    temp = temp->next;
}

cout << "\n";

int selectedNumber;

cout << "Enter Vehicle Number to Book (1-"
     << vehicleCount << "): ";

cin >> selectedNumber;

if (selectedNumber < 1 ||
    selectedNumber > vehicleCount)
{
    printMessage("Invalid Selection.");
    return;
}

    string selectedVehicleID = vehicleIDs[selectedNumber - 1];
    Vehicle* v = findVehicleByID(selectedVehicleID);

    if (v == NULL || !v->isAvailable())
    {
        printMessage("Vehicle not available.");
        return;
    }

    // Check if vehicle is electric - ask about charging availability
    bool needsCharging = false;
    if (v->getFuelType() == "Electric")
    {
        system("cls");
        printInputHeader("ELECTRIC VEHICLE CHARGING");
        printMenuItem("This is an electric vehicle");
        printMenuItem("Do you have access to charging at your location?");
        printMenuFooter();
        
        cout << "1. Yes, I have charging facility\n";
        cout << "2. No, I need charging support\n";
        cout << "\nSelect Option: ";
        int chargeChoice;
        cin >> chargeChoice;
        
        if (chargeChoice == 2)
        {
            needsCharging = true;
            printMessage("Note: Extra charging support fee may apply");
        }
    }

    system("cls");
    printMenuHeader("SELECT DRIVING MODE");
    printMenuItem("  1. Self Drive ");
    printMenuItem("  2. With Driver ");
    printMenuFooter();
    
    cout << "Select Driving Mode: ";
    int drivingModeChoice;
    cin >> drivingModeChoice;

    cin.ignore();

    Booking b;
    b.bookingID = generateBookingID();
    b.customerID = getUserID();
    b.vehicleID = selectedVehicleID;
    b.bookingCategory = "Passenger Transportation";
    b.goodsType = "";
    b.goodsWeight = "";
    b.refrigeratedRequired = false;

    if (drivingModeChoice == 1)
    {
        b.drivingMode = "Self Drive";

        system("cls");
        printInputHeader("SELF DRIVE BOOKING");

        cout << "Enter Pickup Location: ";
        getline(cin, b.pickupLocation);

        cout << "Enter Pickup Date (DD/MM/YYYY): ";
        cin >> b.pickupDate;

        cout << "Enter Pickup Time (24 hr format): ";
        cin >> b.pickupTime;

        cout << "Enter Return Date (DD/MM/YYYY): ";
        cin >> b.returnDate;

        if (!validDateFormat(b.pickupDate) || !validDateFormat(b.returnDate))
        {
            printMessage("Invalid Date Format. Use DD/MM/YYYY");
            return;
        }

        int pickupDays = convertToDays(b.pickupDate);
        int returnDays = convertToDays(b.returnDate);
        
        if (returnDays < pickupDays)
        {
            printMessage("Return Date Must Be Same Or After Pickup Date.");
            return;
        }

        cin.ignore();
        b.customerLicense = inputLicense();

        system("cls");
        printInputHeader("VEHICLE DELIVERY OPTION");
        printMenuItem("  1. Pickup Myself (Self pickup)");
        printMenuItem("  2. Deliver Vehicle To Me (Home delivery)");
        printMenuFooter();
        
        cout << "Select Option: ";
        int deliveryChoice;
        cin >> deliveryChoice;

        if (deliveryChoice == 1)
        {
            b.deliveryOption = "Pickup Myself";
            b.deliveryAddress = "";
        }
        else if (deliveryChoice == 2)
        {
            b.deliveryOption = "Deliver Vehicle To Me";
            cin.ignore();
            cout << "Enter Delivery Address: ";
            getline(cin, b.deliveryAddress);
        }
        else
        {
            printMessage("Invalid Choice.");
            return;
        }

        b.destination = "";
        b.assignedDriver = "";

        int days = returnDays - pickupDays;
        b.totalCost = days * v->getSelfDrivePrice();

        if (isStudent)
            b.totalCost = b.totalCost * 0.9;
    }
    else if (drivingModeChoice == 2)
    {
        b.drivingMode = "With Driver";

        system("cls");
        printInputHeader("WITH DRIVER BOOKING");

        cout << "Enter Pickup Location: ";
        getline(cin, b.pickupLocation);

        cout << "Enter Destination : ";
        getline(cin, b.destination);

        cout << "Enter Pickup Date (DD/MM/YYYY): ";
        cin >> b.pickupDate;

        cout << "Enter Pickup Time (24 hr format): ";
        cin >> b.pickupTime;

        cout << "Enter Return Date (DD/MM/YYYY): ";
        cin >> b.returnDate;

        if (!validDateFormat(b.pickupDate) || !validDateFormat(b.returnDate))
        {
            printMessage("Invalid Date Format. Use DD/MM/YYYY");
            return;
        }

        int pickupDays2 = convertToDays(b.pickupDate);
        int returnDays2 = convertToDays(b.returnDate);
        
        if (returnDays2 < pickupDays2)
        {
            printMessage("Return Date Must Be Same Or After Pickup Date.");
            return;
        }

        b.customerLicense = "";
        b.deliveryOption = "";
        b.deliveryAddress = "";
        b.assignedDriver = "PENDING";

        int days = returnDays2 - pickupDays2;
        if (days < 1) days = 1;  // Minimum 1 day charge
        b.totalCost = days * (v->getSelfDrivePrice() + v->getDriverPrice());

        if (isStudent)
            b.totalCost = b.totalCost * 0.9;
    }
    else
    {
        printMessage("Invalid Choice.");
        return;
    }

    b.advancePayment = b.totalCost * 0.2;
    
    // For Self Drive: status is directly BOOKED. For With Driver: status is PENDING
    if (b.drivingMode == "Self Drive")
    {
        b.status = "BOOKED";
    }
    else
    {
        b.status = "PENDING";
    }

    v->setAvailability(false);
    queue.enqueue(b);
    queue.generateBill(b);

    printMessage("Passenger Booking Created Successfully.");
}

// Book goods vehicle
void Customer::bookGoodsVehicle(BookingQueue& queue)
{
    system("cls");

    if (head == NULL)
    {
        printMessage("No Vehicles Available.");
        return;
    }

    // Count only goods vehicles
    VehicleNode* temp = head;
    int vehicleCount = 0;
    int available_count = 0;
    vector<string> vehicleIDs;

    while (temp != NULL)
    {
        if (isGoodsVehicle(temp->data.getCategory()))
        {
            if (temp->data.isAvailable())
                available_count++;
        }
        temp = temp->next;
    }

    if (available_count == 0)
    {
        printMessage("No Available Goods Vehicles.");
        return;
    }

    system("cls");
   printMenuHeader("SELECT GOODS VEHICLE");

printf("\n %-3s %-12s %-15s %-10s %-10s\n\n",
       "No.",
       "Vehicle ID",
       "Type",
       "Fuel",
       "Driver");

temp = head;

while (temp != NULL)
{
    if (isGoodsVehicle(temp->data.getCategory()) &&
        temp->data.isAvailable())
    {
        vehicleCount++;

        vehicleIDs.push_back(
            temp->data.getVehicleID());

        string fuelType =
            temp->data.getFuelType();

        printf(" %-3d %-12s %-15s %-10s %-10s\n",
               vehicleCount,
               temp->data.getVehicleID().c_str(),
               temp->data.getCategory().c_str(),
               fuelType.c_str(),
               "Yes");
    }

    temp = temp->next;
}

cout << "\n";

int selectedNumber;

cout << "Enter Vehicle Number to Book (1-"
     << vehicleCount << "): ";

cin >> selectedNumber;

if (selectedNumber < 1 ||
    selectedNumber > vehicleCount)
{
    printMessage("Invalid Selection.");
    return;
}
    string selectedVehicleID = vehicleIDs[selectedNumber - 1];
    Vehicle* v = findVehicleByID(selectedVehicleID);

    if (v == NULL || !v->isAvailable())
    {
        printMessage("Vehicle not available.");
        return;
    }

    // Check if vehicle is electric - ask about charging availability
    if (v->getFuelType() == "Electric")
    {
        system("cls");
        printInputHeader("ELECTRIC VEHICLE CHARGING");
        printMenuItem("This is an electric goods vehicle");
        printMenuItem("Note: Charging support is automatically included");
        printMenuFooter();
        system("pause");
    }

    cin.ignore();

    system("cls");
    printInputHeader("GOODS BOOKING DETAILS");

    Booking b;
    b.bookingID = generateBookingID();
    b.customerID = getUserID();
    b.vehicleID = selectedVehicleID;
    b.bookingCategory = "Goods Transportation";
    b.drivingMode = "With Driver";
    b.assignedDriver = "PENDING";

    cout << "Enter Pickup Location: ";
    getline(cin, b.pickupLocation);

    cout << "Enter Delivery Location: ";
    getline(cin, b.destination);

    cout << "Enter Goods Type: ";
    getline(cin, b.goodsType);

    cout << "Enter Approx Weight (e.g. 2 Ton): ";
    getline(cin, b.goodsWeight);

    cout << "Enter Pickup Date (DD/MM/YYYY): ";
    cin >> b.pickupDate;

    cout << "Enter Pickup Time (24 hr format): ";
    cin >> b.pickupTime;

    cout << "Enter Return Date (DD/MM/YYYY): ";
    cin >> b.returnDate;

    if (!validDateFormat(b.pickupDate) || !validDateFormat(b.returnDate))
    {
        printMessage("Invalid Date Format. Use DD/MM/YYYY");
        return;
    }

    int pickupDays2 = convertToDays(b.pickupDate);
    int returnDays2 = convertToDays(b.returnDate);
    
    if (returnDays2 < pickupDays2)
    {
        printMessage("Return Date Must Be Same Or After Pickup Date.");
        return;
    }

    cout << "Refrigerated transport needed? (1: Yes, 0: No): ";
    int refrigerated;
    cin >> refrigerated;
    b.refrigeratedRequired = (refrigerated == 1);

    b.customerLicense = "";
    b.deliveryOption = "";
    b.deliveryAddress = "";

    int days = returnDays2 - pickupDays2;
    if (days < 1) days = 1;  // Minimum 1 day charge
    b.totalCost = days * (v->getSelfDrivePrice() + v->getDriverPrice());

    if (isStudent)
        b.totalCost = b.totalCost * 0.9;

    b.advancePayment = b.totalCost * 0.2;
    b.status = "PENDING";

    v->setAvailability(false);
    queue.enqueue(b);
    queue.generateBill(b);

    printMessage("Goods Booking Created Successfully.");
}

// Book vehicle 
void Customer::bookVehicle(BookingQueue& queue)
{
    system("cls");

    printMenuHeader("SELECT BOOKING CATEGORY");

    printMenuItem("  1. Passenger Transportation");
    printMenuItem("    (Car, Bike, Scooter, Van)");
    printMenuItem("");
    printMenuItem("  2. Goods Transportation");
    printMenuItem("   (Truck, Mini Truck, Cargo Van, etc.)");

    printMenuFooter();

    cout << "Select Category: ";
    int categoryChoice;
    cin >> categoryChoice;

    if (categoryChoice == 1)
    {
        bookPassengerVehicle(queue);
    }
    else if (categoryChoice == 2)
    {
        bookGoodsVehicle(queue);
    }
    else
    {
        printMessage("Invalid Choice.");
    }
}



// Cancel booking
void Customer::cancelBooking()
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
    
    printMenuHeader("YOUR ACTIVE BOOKINGS");
    printf("\n %-12s | %-12s | %-12s | %-12s | %-15s | %-10s\n", 
           "Booking ID", "Vehicle ID", "Pickup Date", "Return Date", "Total Cost", "Status");
    printLine();

    vector<string> bookingLines;
    
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
        
        if (fields.size() >= 14 && fields[1] == getUserID() && 
            (fields[13] == "PENDING" || fields[13] == "ACCEPTED" || fields[13] == "APPROVED"))
        {
            printf(" %-12s | %-12s | %-12s | %-12s | %-15s | %-10s\n", 
                   fields[0].c_str(),           // Booking ID
                   fields[2].c_str(),           // Vehicle ID
                   fields[5].c_str(),           // Pickup Date
                   fields[7].c_str(),           // Return Date
                   fields[11].c_str(),          // Total Cost
                   fields[13].c_str());         // Status
            bookingLines.push_back(line);
            found = true;
        }
    }

    fin.close();

    if(!found)
    {
        printMessage("No Active Bookings Found.");
        return;
    }

    printLine();

    string cancelID;
    cout << "Enter Booking ID To Cancel : ";
    cin >> cancelID;

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

    bool cancelled = false;
    string vehicleID = "";
    string bookingStatus = "";

    while(getline(fin, line))
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

            if (id == cancelID)
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
                
                if (fields.size() >= 14 && fields[1] == getUserID() && 
                    (fields[13] == "PENDING" || fields[13] == "ACCEPTED" || fields[13] == "APPROVED"))
                {
                    vehicleID = fields[2];
                    bookingStatus = fields[13];
                    
                    // Update status to CANCELLED
                    fields[13] = "CANCELLED";
                    
                    line = "";
                    for (size_t i = 0; i < fields.size(); i++)
                    {
                        line += fields[i];
                        if (i < fields.size() - 1)
                            line += "|";
                    }
                    
                    cancelled = true;
                }
            }
        }

        fout << line << endl;
    }

    fin.close();
    fout.close();

    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    if(cancelled)
    {
        system("cls");
        printMenuHeader("BOOKING CANCELLED");
        printMenuItem("Booking ID       : " + cancelID);
        printMenuItem("Vehicle ID       : " + vehicleID);
        printMenuItem("Previous Status  : " + bookingStatus);
        printMenuItem("New Status       : CANCELLED");
        printLine();
        
        // Make vehicle available
        setVehicleAvailable(vehicleID);
        
        printMessage("Booking Cancelled Successfully. Vehicle is now Available.");
        printMenuFooter();
    }
    else
    {
        printMessage("Booking ID Not Found or Not Eligible For Cancellation.");
    }
}

// Getter
string Customer::getCitizenship()
{
    // If already loaded, return it
    if (!citizenship.empty())
        return citizenship;

    // Load from file
    ifstream fin("customer_citizenship.txt");
    if (fin)
    {
        string line;
        while (getline(fin, line))
        {
            size_t pipePos = line.find('|');
            if (pipePos != string::npos)
            {
                string id = line.substr(0, pipePos);
                if (id == userID)
                {
                    citizenship = line.substr(pipePos + 1);
                    fin.close();
                    return citizenship;
                }
            }
        }
        fin.close();
    }

    return "Not Found";
}

void Customer::viewRatings()
{
    system("cls");

    ifstream fin("customer_ratings.txt");

    if(!fin)
    {
        printMessage("No Ratings Found.");
        return;
    }

    string line;
    vector<string> ratings;

    while(getline(fin, line))
    {
        if(line.empty()) continue;
        stringstream ss(line);
        string id;
        int rating;
        ss >> id >> rating;

        if(id == getUserID())
        {
            stringstream out;
            out << "Rating : " << rating << "/5";
            ratings.push_back(out.str());
        }
    }

    fin.close();

    printMenuHeader("MY RATINGS (MOST RECENT FIRST)");

    if(ratings.empty())
    {
        printMenuItem("No Ratings Yet.");
    }
    else
    {
        // Display in reverse order (most recent first)
        for(int i = ratings.size() - 1; i >= 0; i--)
        {
            printMenuItem(ratings[i]);
            printLine();
        }
    }

    printMenuFooter();
}