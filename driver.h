#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include "user.h"

class Driver : public User {
private:
    // Driver-specific data
    std::string license;
    std::string citizenship;
    int experience;

public:
    // Setup (input + save)
    void setupDriver();

    // Driver actions
    void viewCustomers();
    void acceptCustomer();
    void rejectCustomer();
    void rateCustomer();

    // Getters (useful later)
    std::string getLicense();
    std::string getCitizenship();
    int getExperience();
};

#endif