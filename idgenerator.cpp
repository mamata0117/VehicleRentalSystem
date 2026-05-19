#include "idgenerator.h"
#include <fstream>
#include <sstream>

int IDGenerator::countRecordsInFile(const string& filename)
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        return 0;
    }

    int count = 0;
    string line;
    
    // For customer, driver, admin files

    bool isUserFile = (filename == "customers.txt" || 
                       filename == "drivers.txt" || 
                       filename == "admins.txt");
    
    int lineCount = 0;
    while (getline(fin, line))
    {
        if (!line.empty())
        {
            lineCount++;
        }
    }
    fin.close();
    
    // Calculate actual record count based on file type
    if (isUserFile)
    {
        count = lineCount / 7;  
    }
    else
    {
        count = lineCount; 
    }
    
    return count;
}

string IDGenerator::getFilenameForEntity(const string& entityType)
{
    if (entityType == "CUSTOMER")
        return "customers.txt";
    else if (entityType == "ADMIN")
        return "admins.txt";
    else if (entityType == "DRIVER")
        return "drivers.txt";
    else if (entityType == "VEHICLE")
        return "vehicles.txt";
    else if (entityType == "BOOKING")
        return "bookings.txt";
    return "";
}

string IDGenerator::generateID(const string& entityType)
{
    string filename = getFilenameForEntity(entityType);
    int recordCount = countRecordsInFile(filename);
    int nextID = recordCount + 1;

    if (entityType == "VEHICLE")
    {
        return "V-" + to_string(nextID);
    }
    else if (entityType == "CUSTOMER")
    {
        return "C-" + to_string(nextID);
    }
    else if (entityType == "ADMIN")
    {
        return "A-" + to_string(nextID);
    }
    else if (entityType == "DRIVER")
    {
        return "D-" + to_string(nextID);
    }
    else if (entityType == "BOOKING")
    {
        return "B-" + to_string(nextID);
    }

    return "";
}
