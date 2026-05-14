#include <iostream>
#include <cctype>
#include "vehicle.h"
#include "ui.h"

using namespace std;

// Head pointer of linked list
VehicleNode* head = NULL;

// Add vehicle
void Vehicle::addVehicle()
{
    system("cls");

    printInputHeader("ADD VEHICLE");

    cout << "Enter Vehicle ID : ";
    cin >> vehicleID;

    // VEHICLE CATEGORY
    int option;

    cout << "\nSelect Vehicle Category\n";
    cout << "1. Car\n";
    cout << "2. Bike\n";
    cout << "3. Truck\n";
    cout << "4. Van\n";
    cout << "5. Scooter\n";

    cout << "\nEnter Choice      : ";
    cin >> option;

    switch(option)
    {
        case 1:
            category = "Car";
            break;

        case 2:
            category = "Bike";
            break;

        case 3:
            category = "Truck";
            break;

        case 4:
            category = "Van";
            break;

        case 5:
            category = "Scooter";
            break;

        default:
            printMessage("Invalid Choice.");
            return;
    }

    cout << "Enter Fuel Type  : ";
    cin >> fuelType;

    // LICENSE PLATE VALIDATION
    bool validPlate = false;

    while (!validPlate)
    {
        cout << "\nEnter License Plate\n";
        cout << "Example : BA-PA-1234\n";
        cout << "Format  : [Province]-[Type]-[4Digits]\n";

        cout << "\nEnter Plate       : ";

        cin >> licensePlate;

        string UpperlisensePlate = licensePlate;

        for(char &ch : UpperlisensePlate)
        {
            ch = toupper(ch);
        }

        int dashCount = 0;

        for(char ch : UpperlisensePlate)
        {
            if(ch == '-')
            {
                dashCount++;
            }
        }

        // Must contain 2 dashes
        if(dashCount != 2)
        {
            printMessage("Invalid Format.");
            continue;
        }

        // Split manually
        size_t firstDash =
            UpperlisensePlate.find('-');

        size_t secondDash =
            UpperlisensePlate.find('-',
            firstDash + 1);

        string province =
            UpperlisensePlate.substr(0, firstDash);

        string vehiclePart =
            UpperlisensePlate.substr(
                firstDash + 1,
                secondDash - firstDash - 1
            );

        string digits =
            UpperlisensePlate.substr(secondDash + 1);

        // Province validation
        bool validProvince =
        (
            province == "BA" ||
            province == "GA" ||
            province == "LU" ||
            province == "KO" ||
            province == "MA" ||
            province == "NA" ||
            province == "SU"
        );

        // 4 digit validation
        bool validDigits = true;

        if(digits.length() != 4)
        {
            validDigits = false;
        }

        for(char ch : digits)
        {
            if(!isdigit(ch))
            {
                validDigits = false;
            }
        }

        // Final validation
        if(validProvince &&
           vehiclePart.length() >= 2 &&
           validDigits)
        {
            validPlate = true;
        }

        else
        {
            printMessage("Invalid License Plate Format.");
        }
    }

    cin.ignore();

    // MAINTENANCE RECORD
    string repairedDate;
    string nextDueDate;

    cout << "\nEnter Last Maintenance Date\n";
    cout << "Format : DD/MM/YYYY\n";

    cout << "Date              : ";
    getline(cin, repairedDate);

    cout << "\nEnter Next Due Date\n";
    cout << "Format : DD/MM/YYYY\n";

    cout << "Date              : ";
    getline(cin, nextDueDate);

    maintenanceRecord =
        "Last Repaired: " + repairedDate +
        " | Next Due: " + nextDueDate;

    // PRICING
    cout << "\nEnter Self Drive Price : ";
    cin >> selfDrivePrice;

    cout << "Enter Driver Price     : ";
    cin >> driverPrice;

    available = true;

    printMessage("Vehicle Added Successfully.");
}

// Insert vehicle into linked list
void insertVehicle(Vehicle v)
{
    VehicleNode* newNode = new VehicleNode;

    newNode->data = v;
    newNode->next = NULL;

    // Empty list
    if (head == NULL)
    {
        head = newNode;
    }

    // Insert at end
    else
    {
        VehicleNode* temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

// Display single vehicle
void Vehicle::displayVehicle()
{
    printMenuHeader("VEHICLE DETAILS");

    printMenuItem("Vehicle ID      : " + vehicleID);

    printMenuItem("Fuel Type       : " + fuelType);

    printMenuItem("Category        : " + category);

    printMenuItem("License Plate   : " + licensePlate);

    printMenuItem("Maintenance     : " + maintenanceRecord);

    printMenuItem(
        "Self Drive Rs.  : " +
        to_string((int)selfDrivePrice) +
        " per day"
    );

    printMenuItem(
        "Driver Price Rs.: " +
        to_string((int)driverPrice) +
        " per day"
    );

    printMenuItem(
        "Status          : " +
        string(available ? "Available" : "Booked")
    );

    printMenuFooter();
}

// Display all vehicles
void displayAllVehicles()
{
    if (head == NULL)
    {
        printMessage("No Vehicles Available.");
        return;
    }

    printMenuHeader("ALL VEHICLES");

    VehicleNode* temp = head;

    while (temp != NULL)
    {
        temp->data.displayVehicle();

        temp = temp->next;
    }
}

// Display only available vehicles
void displayAvailableVehicles()
{
    if (head == NULL)
    {
        printMessage("No Vehicles Available.");
        return;
    }

    printMenuHeader("AVAILABLE VEHICLES");

    VehicleNode* temp = head;

    while (temp != NULL)
    {
        if (temp->data.isAvailable())
        {
            temp->data.displayVehicle();
        }

        temp = temp->next;
    }
}

// Check availability
bool Vehicle::isAvailable()
{
    return available;
}

// Set availability
void Vehicle::setAvailability(bool status)
{
    available = status;
}

// Get vehicle ID
string Vehicle::getVehicleID()
{
    return vehicleID;
}

// Get vehicle type
string Vehicle::getType()
{
    return type;
}

// Get category
string Vehicle::getCategory()
{
    return category;
}

// Get self drive price
float Vehicle::getSelfDrivePrice()
{
    return selfDrivePrice;
}

// Get driver price
float Vehicle::getDriverPrice()
{
    return driverPrice;
}

// Get license plate
string Vehicle::getLicensePlate()
{
    return licensePlate;
}

// Find vehicle by ID
Vehicle* findVehicleByID(string id)
{
    VehicleNode* temp = head;

    while (temp != NULL)
    {
        if (temp->data.getVehicleID() == id)
        {
            return &(temp->data);
        }

        temp = temp->next;
    }

    return NULL;
}