#include <iostream>
#include "menu.h"
#include "vehicle.h"
#include "driver.h"
#include "user.h"
#include "booking.h"
#include <limits>
#include <cctype>

using namespace std;

// ================= UTILITY FUNCTIONS =================
void clearScreen() {
    system("cls"); // (You can replace for cross-platform later)
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int getValidInput() {
    int choice;
    while (true) {
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Try again.\n";
        } else {
            return choice;
        }
    }
}

// ================= MAIN MENU =================
void Menu::mainMenu() {
    User u;
    int choice;

    do {
        clearScreen();
        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        choice = getValidInput();

        switch(choice) {
            case 1:
                clearScreen();
                u.registerUser();
                break;

            case 2: {
                clearScreen();
                bool loginSuccess = u.loginUser();

                if (loginSuccess) {
                    string role;
                    cout << "Enter role (admin/customer/driver): ";
                    cin >> role;
                    for(char& ch : role) {
                        ch = static_cast<char>(toupper(static_cast<unsigned char>(ch)));
                    }

                    if (role == "ADMIN")
                        adminMenu();
                    else if (role == "CUSTOMER")
                        customerMenu();
                    else if (role == "DRIVER")
                        driverMenu();
                    else
                        cout << "Invalid role!\n";
                } else {
                    cout << "Login failed!\n";
                }

                break;
            }

            case 3:
                cout << "Exiting system...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

        pauseScreen();

    } while(choice != 3);
}

// ================= ADMIN MENU =================
void Menu::adminMenu() {
    VehicleList v;
    Driver d;
    int choice;

    do {
        clearScreen();
        cout << "\n===== ADMIN MENU =====\n";
        cout << "1. Manage Vehicles\n";
        cout << "2. Manage Drivers\n";
        cout << "3. Back\n";

        choice = getValidInput();

        switch(choice) {

            case 1: {
                int vchoice;
                do {
                    clearScreen();
                    cout << "\n--- Vehicle Menu ---\n";
                    cout << "1. Add Vehicle\n";
                    cout << "2. View Vehicles\n";
                    cout << "3. Delete Vehicle\n";
                    cout << "0. Back\n";

                    vchoice = getValidInput();

                    switch(vchoice) {
                        case 1: v.addVehicle(); break;
                        case 2: v.viewVehicles(); break;
                        case 3: v.deleteVehicle(); break;
                    }

                    pauseScreen();

                } while(vchoice != 0);
                break;
            }

            case 2: {
                int dchoice;
                do {
                    clearScreen();
                    cout << "\n--- Driver Menu ---\n";
                    cout << "1. Add Driver\n";
                    cout << "2. View Drivers\n";
                    cout << "3. Delete Driver\n";
                    cout << "0. Back\n";

                    dchoice = getValidInput();

                    switch(dchoice) {
                        case 1: d.addDriver(); break;
                        case 2: d.viewDrivers(); break;
                        case 3: d.deleteDriver(); break;
                    }

                    pauseScreen();

                } while(dchoice != 0);
                break;
            }

            case 3:
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while(choice != 3);
}

// ================= DRIVER MENU =================
void Menu::driverMenu() {
    Driver d;
    int choice;

    do {
        clearScreen();
        cout << "\n===== DRIVER MENU =====\n";
        cout << "1. View Drivers\n";
        cout << "2. Back\n";

        choice = getValidInput();

        switch(choice) {
            case 1:
                d.viewDrivers();
                break;
            case 2:
                break;
            default:
                cout << "Invalid choice!\n";
        }

        pauseScreen();

    } while(choice != 2);
}

// ================= CUSTOMER MENU =================
void Menu::customerMenu() {
    VehicleList v;
    BookingList b;
    PriorityBooking p;
    int choice;

    do {
        clearScreen();
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

        choice = getValidInput();

        switch(choice) {

            case 1:
                v.viewVehicles();
                break;

            case 2:
                b.createBooking(v);
                break;

            case 3:
                b.viewBookings();
                break;

            case 4:
                b.cancelBooking(v);
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

        pauseScreen();

    } while(choice != 0);
}