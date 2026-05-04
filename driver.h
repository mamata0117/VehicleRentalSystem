#ifndef DRIVER_H
#define DRIVER_H

#include <string>

class Driver {
public:
  
    std::string license ;
    int charge;
    void driverMenu();
void viewCustomers();     // booking requests
void acceptCustomer();
void rejectCustomer();
    
};

#endif