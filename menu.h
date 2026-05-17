#ifndef MENU_H
#define MENU_H

#include "customer.h"
#include "driver.h"
#include "admin.h"
#include "booking.h"

void customerMenu(Customer& c, BookingQueue& queue);

void driverMenu(Driver& d, BookingQueue& queue);

void adminMenu(Admin& a, BookingQueue& queue);

#endif