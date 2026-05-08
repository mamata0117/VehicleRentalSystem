#include <iostream>

#include "admin.h"
#include "vehicle.h"

using namespace std;

void Admin::adminMenu(BookingQueue& queue)
{
    int choice;

    do
    {
        cout << "\n----------- Admin Menu -----------\n";

        cout << "1. Add Vehicle\n";
        cout << "2. View All Vehicles\n";
        cout << "3. View Available Vehicles\n";
        cout << "4. View Bookings\n";
        cout << "5. Exit\n";

        cout << "Enter choice: ";

        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                Vehicle v;

                v.addVehicle();

                insertVehicle(v);

                break;
            }

            case 2:
                displayAllVehicles();
                break;

            case 3:
                displayAvailableVehicles();
                break;

            case 4:
                queue.display();
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while(choice != 5);
}