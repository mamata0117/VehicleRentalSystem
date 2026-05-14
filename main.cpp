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

        printMenuHeader("VEHICLE RENTAL SYSTEM");

        printMenuItem("1. Register");
        printMenuItem("2. Login");
        printMenuItem("3. Exit");

        printMenuFooter();

        cout << "\nEnter Choice : ";

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

            printMessage("THANK YOU FOR USING VEHICLE RENTAL SYSTEM");

            break;
        }

        // INVALID CHOICE
        else
        {
            printMessage("Invalid Choice.");

            system("pause");
        }
    }

    return 0;
}