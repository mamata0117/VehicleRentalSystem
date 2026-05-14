#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "user.h"
#include "booking.h"
#include "vehicle.h"

class Customer : public User {
private:
    std::string citizenship,institutionName,studentIDCard;
    bool isStudent;

public:
    void setupCustomer();
    void customerMenu(BookingQueue& queue);
void reviewDriver();
    // actions
    void viewVehicles();
    void bookVehicle(BookingQueue& queue);
    void cancelBooking(); // we’ll wire stack later
void completeRide();
    // optional getters
    std::string getCitizenship();
};

#endif