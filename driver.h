#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include "user.h"
#include "booking.h"

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
    void viewTotalRidesToday();
    void viewReviews();
    void acceptCustomer(BookingQueue& queue);
    void rejectCustomer(BookingQueue& queue);
    void rateCustomer();
  
    // Getters (useful later)
    std::string getLicense();
    std::string getCitizenship();
    int getExperience();
};

#endif