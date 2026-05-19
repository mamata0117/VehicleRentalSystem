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
    void loadCustomerData();
    void reviewDriver();
    void customerMenu(BookingQueue& queue);
    void viewRatings();
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
