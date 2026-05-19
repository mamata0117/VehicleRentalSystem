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
#include "idgenerator.h"

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    system("chcp 65001");

    // Load data from files on startup
    loadVehiclesFromFile();

    User user;

    BookingQueue queue;

    // Load bookings from file
    loadBookingsFromFile(queue);

    int choice;

    while(true)
    {
        system("cls");

        printMenuHeader("VEHICLE RENTAL SYSTEM");

        printMenuItem("1. Register");
        printMenuItem("2. Login");
        printMenuItem("3. Exit");

        printMenuFooter();

        cout << "\nEnter choice: ";

        cin >> choice;
        if(cin.fail())
{
    cin.clear();

    cin.ignore(1000, '\n');

    printMessage("Invalid Choice.");

    system("pause");

    continue;
}
        // REGISTER
        if(choice == 1)
        { system("cls");
            user.registerUser();
            
            if(user.getRole() == "CUSTOMER")
            {
                Customer c;
                c.setUserID(user.getUserID());
                c.setRole(user.getRole());
                c.setupCustomer();
                system("pause");
            }
            else if(user.getRole() == "DRIVER")
            {
                Driver d;
                d.setUserID(user.getUserID());
                d.setRole(user.getRole());
                d.setupDriver();
                system("pause");
            }
        }

        // LOGIN
        else if(choice == 2)
        {    system("cls");
            showAvailableUsers();
            if(user.loginUser())
            {
                // CUSTOMER
                if(user.getRole() == "CUSTOMER")
                {
                    Customer c;

                    c.setUserID(user.getUserID());

                    c.setRole(user.getRole());

                    c.loadCustomerData();
                    system("pause");
                    system("cls");
                    customerMenu(c, queue);
                }

                // DRIVER
                else if(user.getRole() == "DRIVER")
                {
                    Driver d;

                    d.setUserID(user.getUserID());

                    d.setRole(user.getRole());

                    system("pause");
                    system("cls");
                    driverMenu(d, queue);
                }

                // ADMIN
                else if(user.getRole() == "ADMIN")
                {
                    Admin a;

                    a.setUserID(user.getUserID());

                    a.setRole(user.getRole());
                    system("cls");
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