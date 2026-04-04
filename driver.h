#ifndef DRIVER_H
#define DRIVER_H

#include <string>

class Driver {
public:
    std::string name,line;
    std::string license ;
 int charge;

    void addDriver();
    void viewDrivers();
    void deleteDriver();

    std::string getLicense();   
};

#endif