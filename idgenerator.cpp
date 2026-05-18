#include "idgenerator.h"
#include <fstream>
#include <sstream>

map<string, int> IDGenerator::counters;
const string IDGenerator::COUNTER_FILE = "id_counters.txt";

void IDGenerator::loadCounters()
{
    ifstream fin(COUNTER_FILE);

    if (!fin.is_open())
    {
        counters["VEHICLE"] = 0;
        counters["CUSTOMER"] = 0;
        counters["ADMIN"] = 0;
        counters["DRIVER"] = 0;
        counters["BOOKING"] = 0;
        return;
    }

    string line;
    while (getline(fin, line))
    {
        if (line.empty()) continue;

        size_t colonPos = line.find(':');
        if (colonPos == string::npos) continue;

        string entityType = line.substr(0, colonPos);
        int counter = stoi(line.substr(colonPos + 1));

        counters[entityType] = counter;
    }

    fin.close();

    if (counters.find("VEHICLE") == counters.end())
        counters["VEHICLE"] = 0;
    if (counters.find("CUSTOMER") == counters.end())
        counters["CUSTOMER"] = 0;
    if (counters.find("ADMIN") == counters.end())
        counters["ADMIN"] = 0;
    if (counters.find("DRIVER") == counters.end())
        counters["DRIVER"] = 0;
    if (counters.find("BOOKING") == counters.end())
        counters["BOOKING"] = 0;
}

void IDGenerator::saveCounters()
{
    ofstream fout(COUNTER_FILE);

    if (!fout.is_open())
    {
        return;
    }

    for (const auto& pair : counters)
    {
        fout << pair.first << ":" << pair.second << "\n";
    }

    fout.close();
}

int IDGenerator::getNextCounter(const string& entityType)
{
    if (counters.find(entityType) == counters.end())
    {
        counters[entityType] = 0;
    }

    counters[entityType]++;
    saveCounters();

    return counters[entityType];
}

void IDGenerator::initCounters()
{
    loadCounters();
}

string IDGenerator::generateID(const string& entityType)
{
    int counter = getNextCounter(entityType);

    if (entityType == "VEHICLE")
    {
        return "V-" + to_string(counter);
    }
    else if (entityType == "CUSTOMER")
    {
        return "C-" + to_string(counter);
    }
    else if (entityType == "ADMIN")
    {
        return "A-" + to_string(counter);
    }
    else if (entityType == "DRIVER")
    {
        return "D-" + to_string(counter);
    }
    else if (entityType == "BOOKING")
    {
        return "B-" + to_string(counter);
    }

    return "";
}
