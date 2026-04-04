#include <iostream>
#include <limits>
#include <cctype>
#include "menu.h"
#include "vehicle.h"
#include "driver.h"
#include "user.h"
#include "booking.h"

using namespace std;

static ReviewSystem reviewSystem;

void clearScreen() {
    system("cls");
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Try again.\n";
        } else {
            return choice;
        }
    }
}

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

    if (!loginSuccess) {
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

void Menu::adminMenu() {
    static VehicleList v;
    static Driver d;
    User u;
    int choice;

    do {
        clearScreen();
        cout << "\n===== ADMIN MENU =====\n";
        cout << "1. Manage Vehicles\n";
        cout << "2. Manage Drivers\n";
        cout << "3. Search Users\n";
        cout << "4. View Reviews\n";
        cout << "5. Back\n";

        choice = getValidInput();

        switch(choice) {

            case 1: {
                int choices;
                do {
                    clearScreen();
                    cout << "\n--- Vehicle Menu ---\n";
                    cout << "1. Add Vehicle\n";
                    cout << "2. View Vehicles\n";
                    cout << "3. Delete Vehicle\n";
                    cout << "4. Back\n";

                    choices = getValidInput();

                    switch(choices) {
                        case 1: v.addVehicle(); break;
                        case 2: v.viewVehicles(); break;
                        case 3: v.deleteVehicle(); break;
                        case 4: break;
                    }

                    pauseScreen();

                } while(choices != 4);
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
                    cout << "4. Back\n";

                    dchoice = getValidInput();

                    switch(dchoice) {
                        case 1: d.addDriver(); break;
                        case 2: d.viewDrivers(); break;
                        case 3: d.deleteDriver(); break;
                        case 4: break;
                    }

                    pauseScreen();

                } while(dchoice != 4);
                break;
            }

            case 3:
                u.searchUser();
                pauseScreen();
                break;

            case 4:
                reviewSystem.viewReviews();
                pauseScreen();
                break;

            case 5:
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while(choice != 5);
}

void Menu::driverMenu() {
    Driver d;
    int choice;

    do {
        clearScreen();
        cout << "\n===== DRIVER MENU =====\n";
        cout << "1. View Drivers\n";
        cout << "2. View Reviews\n";
        cout << "3. Back\n";

        choice = getValidInput();

        switch(choice) {
            case 1:
                d.viewDrivers();
                break;

            case 2:
                reviewSystem.viewReviews();
                pauseScreen();
                break;

            case 3:
                break;

            default:
                cout << "Invalid choice!\n";
        }

      

    } while(choice != 3);
}

void Menu::customerMenu() {
    static VehicleList v;
    static BookingList b;
    static PriorityBooking p;

    b.loadFromFile();

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
        cout << "9. Add Review\n";
        cout << "10. Back\n";

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
            case 9:
                reviewSystem.addReview();
                pauseScreen();
                break;

            case 10:
                break;

            default:
                cout << "Invalid choice!\n";
        }

      

    } while(choice != 10);
}