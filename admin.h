#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include "booking.h"

class Admin : public User
{
public:

    void adminMenu(BookingQueue& queue);
};

#endif