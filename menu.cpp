#include <iostream>

#include "menu.h"

using namespace std;

// CUSTOMER MENU
void customerMenu(Customer& c, BookingQueue& queue)
{
    int ch;

    while (true)
    {
        cout << "\n--- Customer Menu ---\n";

        cout << "1. View Vehicles\n";
        cout << "2. Book Vehicle\n";
        cout << "3. Cancel Booking\n";
        cout << "4. Exit\n";

        cout << "Enter choice: ";
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
            cout << "Exiting...\n";
            break;
        }

        else
        {
            cout << "Invalid choice!\n";
        }
    }
}

// DRIVER MENU
void driverMenu(Driver& d)
{
    int ch;

    while (true)
    {
        cout << "\n--- Driver Menu ---\n";

        cout << "1. Accept Customer\n";
        cout << "2. Reject Customer\n";
        cout << "3. View Own Reviews\n";
        cout << "4. View Total Rides Today\n";
        cout << "5. Exit\n";

        cout << "Enter choice: ";
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
            cout << "Exiting...\n";
            break;
        }

        else
        {
            cout << "Invalid choice!\n";
        }
    }
}

// ADMIN MENU
void adminMenu(Admin& a, BookingQueue& queue)
{
    a.adminMenu(queue);
}