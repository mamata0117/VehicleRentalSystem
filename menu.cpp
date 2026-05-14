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
    system("cls");

    c.viewVehicles();

    system("pause");
           }

        else if (ch == 2)
        { system("cls");
            c.bookVehicle(queue);
            system("pause");
        }

        else if (ch == 3)
        { system("cls");
            c.cancelBooking();
            system("pause");
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
        {  system("cls");
            d.acceptCustomer();

            d.rateCustomer();
            system("pause");
        }

        else if (ch == 2)
        {   system("cls");
            d.rejectCustomer();
            system("pause");
        }

        else if (ch == 3)
        {  system("cls");
            d.viewReviews();
            system("pause");
        }

        else if (ch == 4)
        {  system("cls");
            d.viewTotalRidesToday();
            system("pause");
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