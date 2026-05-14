#include <iostream>

#include "menu.h"
#include "ui.h"

using namespace std;

// CUSTOMER MENU
void customerMenu(Customer& c, BookingQueue& queue)
{
    int ch;

    while (true)
    {
        system("cls");

        printMenuHeader("CUSTOMER MENU");

        printMenuItem("1. View Vehicles");
        printMenuItem("2. Book Vehicle");
        printMenuItem("3. Cancel Booking");
        printMenuItem("4. Exit");

        printMenuFooter();

        cout << "\nEnter Choice : ";
        cin >> ch;

        if (ch == 1)
        {
            c.viewVehicles();
        }

        else if (ch == 2)
        {
            c.bookVehicle(queue);
        }

        else if (ch == 3)
        {
            c.cancelBooking();
        }

        else if (ch == 4)
        {
            printMessage("Exiting...");
            break;
        }

        else
        {
            printMessage("Invalid Choice.");
        }
    }
}

// DRIVER MENU
void driverMenu(Driver& d)
{
    int ch;

    while (true)
    {
        system("cls");

        printMenuHeader("DRIVER MENU");

        printMenuItem("1. Accept Customer");
        printMenuItem("2. Reject Customer");
        printMenuItem("3. View Own Reviews");
        printMenuItem("4. View Total Rides Today");
        printMenuItem("5. Exit");

        printMenuFooter();

        cout << "\nEnter Choice : ";
        cin >> ch;

        if (ch == 1)
        {
            d.acceptCustomer();

            d.rateCustomer();
        }

        else if (ch == 2)
        {
            d.rejectCustomer();
        }

        else if (ch == 3)
        {
            d.viewReviews();
        }

        else if (ch == 4)
        {
            d.viewTotalRidesToday();
        }

        else if (ch == 5)
        {
            printMessage("Exiting...");
            break;
        }

        else
        {
            printMessage("Invalid Choice.");
        }
    }
}

// ADMIN MENU
void adminMenu(Admin& a, BookingQueue& queue)
{
    a.adminMenu(queue);
}