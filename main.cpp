#include <iostream>
#include <iomanip>
#include <windows.h>

#include "UI.h"
#include "user.h"
#include "customer.h"
#include "driver.h"
#include "admin.h"
#include "booking.h"
#include "menu.h"

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    system("chcp 65001");

    User user;

    BookingQueue queue;

    int choice;

    while(true)
    {
        system("cls");

        // MAIN MENU BOX
        cout << "┌──────────────────────────────────────────────────────────────┐\n";

        cout << "│ "
             << left << setw(60)
             << "VEHICLE RENTAL SYSTEM"
             << "│\n";

        cout << "├──────────────────────────────────────────────────────────────┤\n";

        cout << "│ 1. Register                                                 │\n";

        cout << "│ 2. Login                                                    │\n";

        cout << "│ 3. Exit                                                     │\n";

        cout << "└──────────────────────────────────────────────────────────────┘\n";

        cout << "\nEnter choice : ";

        cin >> choice;

        // REGISTER
        if(choice == 1)
        {
            user.registerUser();

            system("pause");
        }

        // LOGIN
        else if(choice == 2)
        {
            if(user.loginUser())
            {
                // CUSTOMER
                if(user.getRole() == "CUSTOMER")
                {
                    Customer c;

                    c.setUserID(user.getUserID());

                    c.setRole(user.getRole());

                    c.setupCustomer();

                    customerMenu(c, queue);
                }

                // DRIVER
                else if(user.getRole() == "DRIVER")
                {
                    Driver d;

                    d.setUserID(user.getUserID());

                    d.setRole(user.getRole());

                    d.setupDriver();

                    driverMenu(d);
                }

                // ADMIN
                else if(user.getRole() == "ADMIN")
                {
                    Admin a;

                    a.setUserID(user.getUserID());

                    a.setRole(user.getRole());

                    adminMenu(a, queue);
                }
            }

            system("pause");
        }

        // EXIT
        else if(choice == 3)
        {
            system("cls");

            cout << "┌──────────────────────────────────────────────────────────────┐\n";

            cout << "│ "
                 << left << setw(60)
                 << "THANK YOU FOR USING VEHICLE RENTAL SYSTEM"
                 << "│\n";

            cout << "└──────────────────────────────────────────────────────────────┘\n";

            break;
        }

        // INVALID CHOICE
        else
        {
            cout << "\n┌──────────────────────────────────────────────────────────────┐\n";

            cout << "│ "
                 << left << setw(60)
                 << "Invalid Choice"
                 << "│\n";

            cout << "└──────────────────────────────────────────────────────────────┘\n";

            system("pause");
        }
    }

    return 0;
}