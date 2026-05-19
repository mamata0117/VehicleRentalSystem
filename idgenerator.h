#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include <string>

using namespace std;

class IDGenerator
{
private:
    static int countRecordsInFile(const string& filename);
    static string getFilenameForEntity(const string& entityType);

public:
    static string generateID(const string& entityType);
};

#endif
