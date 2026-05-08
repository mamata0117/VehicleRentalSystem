#include <iostream>
#include <cctype>
#include "vehicle.h"

using namespace std;

// Head pointer of linked list
VehicleNode* head = NULL;

// Add vehicle
void Vehicle::addVehicle()
{
    cout << "\n----------- Add Vehicle -----------\n";

    cout << "Enter Vehicle ID: ";
    cin >> vehicleID;

    // VEHICLE CATEGORY
    int option;

    cout << "\nSelect Vehicle Category:\n";
    cout << "1. Car\n";
    cout << "2. Bike\n";
    cout << "3. Truck\n";
    cout << "4. Van\n";
    cout << "5. Scooter\n";

    cout << "Enter choice: ";
    cin >> option;

    switch( option)
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
            cout << "Invalid choice.\n";
            return;
            break;
    }

  

    cout << "Enter Fuel Type (Petrol/Diesel/Electric): ";
    cin >> fuelType;

   
    // LICENSE PLATE VALIDATION
bool validPlate = false;

while (!validPlate)
{
    cout << "\nEnter License Plate\n";
    cout << "Nepal Format Example: BA-PA-1234\n";
    cout << "Format: [Province]-[VehicleType]-[4Digits]\n";

    cin >>licensePlate;
    string UpperlisensePlate = licensePlate;
    for(char &ch : UpperlisensePlate) {
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
        cout << "Invalid format.\n";
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
        cout << "Invalid License Plate Format.Try again.\n";
      
    }
}

    cin.ignore();

    // MAINTENANCE RECORD
    string repairedDate;
    string nextDueDate;

    cout << "\nEnter Last Maintenance/Repaired Date\n";
    cout << "Format: DD/MM/YYYY\n";
    getline(cin, repairedDate);

    cout << "Enter Next Maintenance Due Date\n";
    cout << "Format: DD/MM/YYYY\n";
    getline(cin, nextDueDate);

    maintenanceRecord =
        "Last Repaired: " + repairedDate +
        " | Next Due: " + nextDueDate;

    // PRICING
    cout << "\nEnter Self Drive Price Per Day: ";
    cin >> selfDrivePrice;

    cout << "Enter With Driver Price Per Day: ";
    cin >> driverPrice;

    available = true;

    cout << "\nVehicle added successfully!\n";
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
    cout << "\n\n---------------Vehicle Details------------------\n\n";

    cout << "Vehicle ID: "
         << vehicleID << endl;

  

    cout << "Fuel Type: "
         << fuelType << endl;

    cout << "Category: "
         << category << endl;

    cout << "License Plate: "
         << licensePlate << endl;

    cout << "Maintenance Record: "
         << maintenanceRecord << endl;

    cout << "Self Drive Price: Rs."
         << selfDrivePrice
         << " per day\n";

    cout << "With Driver Price: Rs."
         << driverPrice
         << " per day\n";

    cout << "Status: "
         << (available ? "Available" : "Booked")
         << endl;
}

// Display all vehicles
void displayAllVehicles()
{
    if (head == NULL)
    {
        cout << "No vehicles available.\n";
        return;
    }

    VehicleNode* temp = head;

    cout << "\n----------- All Vehicles -----------\n";

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
        cout << "No vehicles available.\n";
        return;
    }

    VehicleNode* temp = head;

    cout << "\n----------- Available Vehicles -----------\n";

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