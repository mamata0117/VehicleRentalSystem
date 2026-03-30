#include <iostream>
#include "menu.h"
#include "vehicle.h"
#include "driver.h"
#include "user.h"
#include "booking.h"
#include <fstream>
#include <cstdlib>

using namespace std;

// ================= MAIN MENU =================
void Menu::mainMenu() {
    int choice;
    User u;

    do {
        system("cls");
        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                system("cls");
                u.registerUser();
                break;

            case 2:
                system("cls");
                u.loginUser();    
                break;

            case 3:
                cout << "Exiting system...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }
        system("pause");
    } while(choice != 3);
}

// ================= ADMIN MENU =================
void Menu::adminMenu() {
    VehicleList v;
    Driver d;

    int choice;

    do {
        system("cls");
        cout << "\n===== ADMIN MENU =====\n";
        cout << "1. Manage Vehicles\n";
        cout << "2. Manage Drivers\n";
        cout << "3. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {

            case 1: {
                int vchoice;
                do {
                    system("cls");
                    cout << "\n--- Vehicle Menu ---\n";
                    cout << "1. Add Vehicle\n";
                    cout << "2. View Vehicles\n";
                    cout << "3. Delete Vehicle\n";
                    cout << "0. Back\n";
                    cout << "Enter choice: ";
                    cin >> vchoice;

                    switch(vchoice) {
                        case 1: v.addVehicle(); break;
                        case 2: v.viewVehicles(); break;
                        case 3: v.deleteVehicle(); break;
                    }
                    system("pause");

                } while(vchoice != 0);
                break;
            }

            case 2: {
                int dchoice;
                do {
                    system("cls");
                    cout << "\n--- Driver Menu ---\n";
                    cout << "1. Add Driver\n";
                    cout << "2. View Drivers\n";
                    cout << "3. Delete Driver\n";
                    cout << "0. Back\n";
                    cout << "Enter choice: ";
                    cin >> dchoice;

                    switch(dchoice) {
                        case 1: d.addDriver(); break;
                        case 2: d.viewDrivers(); break;
                        case 3: d.deleteDriver(); break;
                    }
                    system("pause");

                } while(dchoice != 0);
                break;
            }

            case 3:
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while(choice != 0);
}



// ================= DRIVER MENU =================
void Menu::driverMenu() {
    Driver d;

    int choice;

    do {
        system("cls");
        cout << "\n===== DRIVER MENU =====\n";
        cout << "1. View Drivers\n";
        cout << "2. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                d.viewDrivers();
                break;
            case 2:
                break;
            default:
                cout << "Invalid choice!\n";
        }
        system("pause");

    } while(choice != 0);
}

void Menu::customerMenu() {
    VehicleList v;
    BookingList b;
    PriorityBooking p;

    int choice;

    do {
        system("cls");
        cout << "\n===== CUSTOMER MENU =====\n";
        cout << "1. View Vehicles\n";
        cout << "2. Create Booking\n";
        cout << "3. View Bookings\n";
        cout << "4. Cancel Booking\n";
        cout << "5. Search Booking\n";
        cout << "6. Priority Booking\n";
        cout << "7. Process Priority Booking\n";
        cout << "8. View Priority Queue\n";
        cout << "0. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                v.viewVehicles();
                break;

            case 2:
                b.createBooking();
                break;

            case 3:
                b.viewBookings();
                break;

            case 4:
                b.cancelBooking();
                break;

            case 5:
                b.searchBooking();
                break;

            case 6: {
                int id;
                cout << "Enter Booking ID: ";
                cin >> id;
                p.addPriorityBooking(id);
                break;
            }

            case 7:
                p.processBooking();
                break;

            case 8:
                p.viewQueue();
                break;

            case 0:
                break;

            default:
                cout << "Invalid choice!\n";
        }

        system("pause");

    } while(choice != 0);
}