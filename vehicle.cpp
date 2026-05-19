#include <iostream>

#include <cctype>

#include <fstream>


#include <vector>
#include <string>
#include "vehicle.h"
#include "booking.h"
#include "idgenerator.h"
#include "UI.h"

using namespace std;

// Head pointer of linked list
VehicleNode* head = NULL;

namespace
{
    static string trimCopy(string value)
    {
        while (!value.empty() && isspace(static_cast<unsigned char>(value.front())))
        {
            value.erase(value.begin());
        }

        while (!value.empty() && isspace(static_cast<unsigned char>(value.back())))
        {
            value.pop_back();
        }

        return value;
    }

    static bool isValidMaintenanceDate(const string &date)
{
    if (date.length() != 10)
    {
        return false;
    }

    if (date[2] != '/' || date[5] != '/')
    {
        return false;
    }

    for (int i = 0; i < 10; ++i)
    {
        if (i == 2 || i == 5)
        {
            continue;
        }

        if (!isdigit(static_cast<unsigned char>(date[i])))
        {
            return false;
        }
    }

    return true;
}

    static string makeBorder(int width)
    {
        return "+" + string(width - 2, '-') + "+";
    }

    static string padRight(const string &text, int width)
    {
        if ((int)text.length() >= width)
        {
            return text.substr(0, width);
        }

        return text + string(width - (int)text.length(), ' ');
    }

    static string shorten(const string &text, int width)
    {
        if (width <= 0)
        {
            return "";
        }

        if ((int)text.length() <= width)
        {
            return text;
        }

        if (width <= 3)
        {
            return text.substr(0, width);
        }

        return text.substr(0, width - 3) + "...";
    }

    static vector<string> buildVehicleCard(Vehicle v, int width)
{
    vector<string> lines;

    string maintenance =
        v.getMaintenanceRecord();

    size_t pos =
        maintenance.find('|');

    string maintenanceDate =
        maintenance.substr(0, pos);

    string nextDate =
        maintenance.substr(pos + 1);

    // Get booking information if vehicle is booked
    Booking booking = findActiveBookingForVehicle(v.getVehicleID());
    bool isBooked = !booking.vehicleID.empty();

    lines.push_back(makeBorder(width));

    lines.push_back("| " + padRight(shorten(v.getVehicleID(), width - 4), width - 4) + " |");

    lines.push_back("| " + padRight(shorten(v.getCategory(), width - 4), width - 4) + " |");

    lines.push_back("| " + padRight(shorten(v.getFuelType(), width - 4), width - 4) + " |");

    lines.push_back("| " + padRight(shorten(v.getLicensePlate(), width - 4), width - 4) + " |");

    lines.push_back("| " + padRight(shorten("Maintenance : " + maintenanceDate, width - 4), width - 4) + " |");

    lines.push_back("| " + padRight(shorten("Next Date  : " + nextDate, width - 4), width - 4) + " |");

    lines.push_back("| " + padRight(shorten(string("Self: Rs. ") + to_string((int)v.getSelfDrivePrice()), width - 4), width - 4) + " |");

    lines.push_back("| " + padRight(shorten(string("Driver: Rs. ") + to_string((int)v.getDriverPrice()), width - 4), width - 4) + " |");

    lines.push_back("| " + padRight(shorten(string("Status: ") + (v.isAvailable() ? "Available" : "Booked"), width - 4), width - 4) + " |");

    // Add booking details if booked
    if (isBooked)
    {
        lines.push_back("| " + padRight(shorten("Customer: " + booking.customerID, width - 4), width - 4) + " |");
        
        if (!booking.assignedDriver.empty() && booking.assignedDriver != "")
        {
            lines.push_back("| " + padRight(shorten("Driver: " + booking.assignedDriver, width - 4), width - 4) + " |");
        }
        else
        {
            lines.push_back("| " + padRight(shorten("Driver: Not Assigned", width - 4), width - 4) + " |");
        }
    }

    lines.push_back(makeBorder(width));

    return lines;
}

    static void printVehicleGrid(const vector<Vehicle> &vehicles)
    {
        if (vehicles.empty())
        {
            printMessage("No Vehicles Available.");
            return;
        }

        const int cardWidth = 37;
        const size_t cardsPerRow = 3;
        const string gap = "  ";

        for (size_t index = 0; index < vehicles.size(); index += cardsPerRow)
        {
            vector<vector<string>> rowCards;
            size_t rowEnd = min(index + cardsPerRow, vehicles.size());

            for (size_t i = index; i < rowEnd; ++i)
            {
                rowCards.push_back(buildVehicleCard(vehicles[i], cardWidth));
            }

            for (size_t lineIndex = 0; lineIndex < rowCards[0].size(); ++lineIndex)
            {
                for (size_t cardIndex = 0; cardIndex < rowCards.size(); ++cardIndex)
                {
                    cout << rowCards[cardIndex][lineIndex];

                    if (cardIndex + 1 < rowCards.size())
                    {
                        cout << gap;
                    }
                }

                cout << '\n';
            }

            cout << '\n';
        }
    }
}
string generateVehicleID()
{
    return IDGenerator::generateID("VEHICLE");
}
// Add vehicle
void Vehicle::addVehicle()
{
    system("cls");

    printInputHeader("ADD VEHICLE");

    vehicleID = generateVehicleID();

cout << "Generated Vehicle ID : "
     << vehicleID << endl;
    // VEHICLE CATEGORY
    int option;

    cout << "\nSelect Vehicle Category\n";
    cout << "\nPassenger Transportation:\n";
    cout << "1. Car\n";
    cout << "2. Bike\n";
    cout << "3. Scooter\n";
    cout << "4. Van\n";
    cout << "\nGoods Transportation:\n";
    cout << "5. Truck\n";
    cout << "6. Mini Truck\n";
    cout << "7. Pickup Truck\n";
    cout << "8. Cargo Van\n";
    cout << "9. Refrigerated Van\n";

    cout << "\nEnter choice: ";
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
            category = "Scooter";
            break;

        case 4:
            category = "Van";
            break;

        case 5:
            category = "Truck";
            break;

        case 6:
            category = "Mini Truck";
            break;

        case 7:
            category = "Pickup Truck";
            break;

        case 8:
            category = "Cargo Van";
            break;

        case 9:
            category = "Refrigerated Van";
            break;

        default:
            printMessage("Invalid Choice.");
            return;
    }

    // FUEL TYPE SELECTION
    int fuelChoice;
    cout << "\nSelect Fuel Type:\n";
    cout << "1. Petrol\n";
    cout << "2. Diesel\n";
    cout << "3. Electric\n";
    cout << "\nEnter choice: ";
    cin >> fuelChoice;

    switch(fuelChoice)
    {
        case 1:
            fuelType = "Petrol";
            break;
        case 2:
            fuelType = "Diesel";
            break;
        case 3:
            fuelType = "Electric";
            break;
        default:
            printMessage("Invalid Fuel Type Choice.");
            return;
    }

    // LICENSE PLATE VALIDATION
    bool validPlate = false;

    while (!validPlate)
{

   cout << "\nSelect Province\n\n";

cout << "1.BA\t\t2.GA\n";
cout << "3.LU\t\t4.KO\n";
cout << "5.MA\t\t6.NA\n";
cout << "7.SU\n";

    int provinceChoice;

    cout << "\nEnter choice : ";
    cin >> provinceChoice;

    string province;

    switch (provinceChoice)
    {
        case 1: province = "BA"; break;
        case 2: province = "GA"; break;
        case 3: province = "LU"; break;
        case 4: province = "KO"; break;
        case 5: province = "MA"; break;
        case 6: province = "NA"; break;
        case 7: province = "SU"; break;

        default:
            printMessage("Invalid Province Choice.");
            continue;
    }


   cout << "\nSelect Vehicle Type\n\n";

cout << "1.PA  - Bike/Scooter\t2.CHA - Private Vehicle\n";
cout << "3.JA  - Rental/Taxi\t4.JHA - Government\n";
cout << "5.GA  - Bus\t\t6.GHA - Minibus\n";
cout << "7.NA  - Tanker\t\t8.BA  - Commercial\n";
cout << "9.TA  - Tractor\n";
    int typeChoice;

    cout << "\nEnter choice : ";
    cin >> typeChoice;

    string vehicleType;

    switch (typeChoice)
    {
        case 1: vehicleType = "PA";  break;
        case 2: vehicleType = "CHA"; break;
        case 3: vehicleType = "JA";  break;
        case 4: vehicleType = "JHA"; break;
        case 5: vehicleType = "GA";  break;
        case 6: vehicleType = "GHA"; break;
        case 7: vehicleType = "NA";  break;
        case 8: vehicleType = "BA";  break;
        case 9: vehicleType = "TA";  break;

        default:
            printMessage("Invalid Vehicle Type Choice.");
            continue;
    }

    string digits;

    cout << "\nEnter 4 Digit Number : ";
    cin >> digits;

    bool validDigits = true;

    if (digits.length() != 4)
    {
        validDigits = false;
    }

    for (char ch : digits)
    {
        if (!isdigit(static_cast<unsigned char>(ch)))
        {
            validDigits = false;
        }
    }

    if (!validDigits)
    {
        printMessage("Enter exactly 4 digits.");
        continue;
    }

    licensePlate =
        province + "-" +
        vehicleType + "-" +
        digits;

    cout << "\nGenerated License Plate : "
         << licensePlate << endl;

    validPlate = true;
}

    cin.ignore();

    // MAINTENANCE RECORD
   string maintenanceDate;
string nextMaintenanceDate;

cout << "\nEnter Maintenance Date\n";
cout << "Format : DD/MM/YYYY\n";

cout << "Maintenance Date      : ";
while (true)
{
    getline(cin, maintenanceDate);
    maintenanceDate = trimCopy(maintenanceDate);

    if (isValidMaintenanceDate(maintenanceDate))
    {
        break;
    }

    printMessage("Use DD/MM/YYYY.");
    cout << "Maintenance Date      : ";
}

cout << "Next Maintenance Date : ";
while (true)
{
    getline(cin, nextMaintenanceDate);
    nextMaintenanceDate = trimCopy(nextMaintenanceDate);

    if (isValidMaintenanceDate(nextMaintenanceDate))
    {
        break;
    }

    printMessage("Use DD/MM/YYYY.");
    cout << "Next Maintenance Date : ";
}

maintenanceRecord =
    maintenanceDate + "|" + nextMaintenanceDate;

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
    vector<Vehicle> vehicleRow;
    vehicleRow.push_back(*this);
    printVehicleGrid(vehicleRow);
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

    vector<Vehicle> vehicles;
    VehicleNode* temp = head;

    while (temp != NULL)
    {
        vehicles.push_back(temp->data);
        temp = temp->next;
    }

    printVehicleGrid(vehicles);
    printMenuFooter();
}

// Display only available vehicles
void displayAvailableVehicles()
{
    if (head == NULL)
    {
        printMessage("No Vehicles Available.");
        return;
    }

    system("cls");
    printMenuHeader("AVAILABLE VEHICLES");
    vector<Vehicle> vehicles;
    VehicleNode* temp = head;

    while (temp != NULL)
    {
        if (temp->data.isAvailable())
        {
            vehicles.push_back(temp->data);
        }

        temp = temp->next;
    }

    printVehicleGrid(vehicles);
}

// Check availability
bool Vehicle::isAvailable() const
{
    return available;
}

// Set availability
void Vehicle::setAvailability(bool status)
{
    available = status;
}

// Get vehicle ID
string Vehicle::getVehicleID() const
{
    return vehicleID;
}

// Get vehicle type
string Vehicle::getType() const
{
    return type;
}

// Get category
string Vehicle::getCategory() const
{
    return category;
}

// Get fuel type
string Vehicle::getFuelType() const
{
    return fuelType;
}

// Get self drive price
float Vehicle::getSelfDrivePrice() const
{
    return selfDrivePrice;
}

// Get driver price
float Vehicle::getDriverPrice() const
{
    return driverPrice;
}

// Get license plate
string Vehicle::getLicensePlate() const
{
    return licensePlate;
}

string Vehicle::getMaintenanceRecord() const
{
    return maintenanceRecord;
}

// Set vehicle ID
void Vehicle::setVehicleID(string id)
{
    vehicleID = id;
}

// Set category
void Vehicle::setCategory(string cat)
{
    category = cat;
}

// Set fuel type
void Vehicle::setFuelType(string fuel)
{
    fuelType = fuel;
}

// Set license plate
void Vehicle::setLicensePlate(string plate)
{
    licensePlate = plate;
}

// Set self drive price
void Vehicle::setSelfDrivePrice(float price)
{
    selfDrivePrice = price;
}

// Set driver price
void Vehicle::setDriverPrice(float price)
{
    driverPrice = price;
}

void Vehicle::setMaintenanceRecord(string record)
{
    maintenanceRecord = record;
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

// Save vehicle to file
void saveVehicleToFile(Vehicle v)
{
    ofstream fout("vehicles.txt", ios::app);

    if (!fout)
    {
        printMessage("Error opening vehicles.txt for writing.");
        return;
    }

    fout << v.getVehicleID() << "|"
         << v.getCategory() << "|"
         << v.getFuelType() << "|"
         << v.getLicensePlate() << "|"
            << v.getMaintenanceRecord() << "|"
         << v.getSelfDrivePrice() << "|"
         << v.getDriverPrice() << "|"
         << (v.isAvailable() ? "Available" : "Booked") << endl;

    fout.close();
}

// Load vehicles from file
void loadVehiclesFromFile()
{
    ifstream fin("vehicles.txt");

    if (!fin)
    {
        return;
    }

    string line;

    while (getline(fin, line))
    {
        if (line.empty()) continue;

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

        // Expected format: vehicleID|category|fuelType|licensePlate|maintenanceDate|nextMaintenanceDate|selfPrice|driverPrice|status
        if (fields.size() >= 9)
        {
            Vehicle v;
            v.setVehicleID(fields[0]);
            v.setCategory(fields[1]);
            v.setFuelType(fields[2]);
            v.setLicensePlate(fields[3]);
            
            // Combine maintenance dates into one record (format: date1|date2)
            string maintenanceRecord = fields[4] + "|" + fields[5];
            v.setMaintenanceRecord(maintenanceRecord);
            
            v.setSelfDrivePrice(stof(fields[6]));
            v.setDriverPrice(stof(fields[7]));
            v.setAvailability(fields[8] == "Available");

            insertVehicle(v);
        }
    }

    fin.close();
}