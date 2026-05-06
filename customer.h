#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "user.h"
#include "booking.h"
#include "vehicle.h"

class Customer : public User {
private:
    std::string citizenship;
    bool isStudent;

public:
    void setupCustomer();

    // actions
    void viewVehicles();
    void bookVehicle(BookingQueue& queue);
    void cancelBooking(); // we’ll wire stack later

    // optional getters
    std::string getCitizenship();
};

#endif