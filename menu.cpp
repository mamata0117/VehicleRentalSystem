#include <iostream>

#include "menu.h"
#include "UI.h"

using namespace std;

// CUSTOMER MENU
void customerMenu(Customer& c, BookingQueue& queue)
{
    int ch;

    while (true)
    {
        system("cls");

        printMenuHeader("CUSTOMER MENU");

        printMenuItem("    1. View Vehicles");
        printMenuItem("    2. Book Vehicle");
        printMenuItem("    3. Cancel Booking");
        printMenuItem("    4. Review Driver");
        printMenuItem("    5. View My Profile");

        printMenuItem("    6. Exit");

        printMenuFooter();

        cout << "\nEnter choice: ";
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
            system("cls");
            c.reviewDriver();
            system("pause");
        }

        else if (ch == 5)
        {
            system("cls");
            printMenuHeader(" CUSTOMER PROFILE");
            printMenuItem("________________________________________________");
            
            printMenuItem("  User ID      : " + c.getUserID());
            printMenuItem("  Citizenship  : " + c.getCitizenship());
            printMenuItem("________________________________________________");
          
            system("pause");
        }

       

        else if (ch == 6)
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
void driverMenu(Driver& d, BookingQueue& queue)
{
    int ch;

    while (true)
    {
        system("cls");

        printMenuHeader("DRIVER MENU");

        printMenuItem("  1. Accept Customer");
        printMenuItem("  2. Reject Customer");
        printMenuItem("  3. View Own Reviews");
        printMenuItem("  4. View Total Rides Today");
        printMenuItem("  5. View My Profile");
        printMenuItem("  6. Exit");

        printMenuFooter();

        cout << "\nEnter choice: ";
        cin >> ch;

        if (ch == 1)
        {  system("cls");
            d.acceptCustomer(queue);
            system("pause");
        }

        else if (ch == 2)
        {   system("cls");
            d.rejectCustomer(queue);
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
            system("cls");
            printMenuHeader("DRIVER PROFILE");
            printMenuItem("_________________________________________________");
            printMenuItem("  Driver ID    : " + d.getUserID());
            printMenuItem("  Citizenship  : " + d.getCitizenship());
            printMenuItem("  License      : " + d.getLicense());
            printMenuItem("_________________________________________________");
            printMenuFooter();
            system("pause");
        }

        else if (ch == 6)
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