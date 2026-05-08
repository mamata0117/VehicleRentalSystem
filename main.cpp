#include <iostream>

#include "user.h"
#include "customer.h"
#include "driver.h"
#include "admin.h"
#include "booking.h"
#include "menu.h"

using namespace std;

int main()
{
    User user;

    BookingQueue queue;

    int choice;

    while (true)
    {
        cout << "\n--- Vehicle Rental System ---\n";

        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        cout << "Enter choice: ";

        cin >> choice;

        // REGISTER
        if (choice == 1)
        {
            user.registerUser();
        }

        // LOGIN
        else if (choice == 2)
        {
            if (user.loginUser())
            {
                // CUSTOMER
                if (user.getRole() == "CUSTOMER")
                {
                    Customer c;

                    c.setUserID(user.getUserID());

                    c.setRole(user.getRole());

                    c.setupCustomer();

                    customerMenu(c, queue);
                }

                // DRIVER
                else if (user.getRole() == "DRIVER")
                {
                    Driver d;

                    d.setUserID(user.getUserID());

                    d.setRole(user.getRole());

                    d.setupDriver();

                    driverMenu(d);
                }

                // ADMIN
                else if (user.getRole() == "ADMIN")
                {
                    Admin a;

                    a.setUserID(user.getUserID());

                    a.setRole(user.getRole());

                    adminMenu(a, queue);
                }
            }
        }

        // EXIT
        else if (choice == 3)
        {
            cout << "Exiting...\n";

            break;
        }

        else
        {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}