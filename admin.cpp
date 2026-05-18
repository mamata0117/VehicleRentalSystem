#include <iostream>

#include "admin.h"
#include "vehicle.h"
#include "UI.h"

using namespace std;

void Admin::adminMenu(BookingQueue& queue)
{
    int choice;
    do
    {
        system("cls");
        cout << "┌─────────────────────────────────────────┐\n";
        cout << "│                ADMIN MENU               │\n";
        cout << "├─────────────────────────────────────────┤\n";
        cout << "│ 1. Add Vehicle                          │\n";
        cout << "│ 2. View All Vehicles                    │\n";
        cout << "│ 3. View Available Vehicles              │\n";
        cout << "│ 4. View Bookings                        │\n";
        cout << "│ 5. Exit                                 │\n";
        cout << "└─────────────────────────────────────────┘\n\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                Vehicle v;
                v.addVehicle();
                insertVehicle(v);
                saveVehicleToFile(v);
                break;
            }
            case 2:
                system("cls");
                displayAllVehicles();
                system("pause");
                break;
            case 3:
                system("cls");
                displayAvailableVehicles();
                system("pause");
                break;
            case 4:
                system("cls");
                queue.display();
                system("pause");
                break;
            case 5:
                printMessage("Exiting Admin Menu...");
                break;
            default:
                printMessage("Invalid Choice.");
                system("pause");
        }
    } while(choice != 5);
}
