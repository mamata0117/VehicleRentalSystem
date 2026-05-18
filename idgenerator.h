#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include <string>
#include <map>

using namespace std;

class IDGenerator
{
private:
    static map<string, int> counters;
    static const string COUNTER_FILE;

    static void loadCounters();
    static void saveCounters();
    static int getNextCounter(const string& entityType);

public:
    static void initCounters();
    static string generateID(const string& entityType);
};

#endif
