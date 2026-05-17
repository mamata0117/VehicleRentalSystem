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
    std::string institutionName;
    std::string studentIDCard;

public:
    void setupCustomer();
    void reviewDriver();
    void customerMenu(BookingQueue& queue);
    // actions
    void viewVehicles();
    void bookVehicle(BookingQueue& queue);
    void bookPassengerVehicle(BookingQueue& queue);
    void bookGoodsVehicle(BookingQueue& queue);
    void cancelBooking();
    // optional getters
    std::string getCitizenship();
};

#endif
