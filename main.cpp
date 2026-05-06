#include <iostream>
#include "user.h"
#include "customer.h"
#include "driver.h"
#include "vehicle.h"
#include "booking.h"

using namespace std;

int main() {
    User user;
    BookingQueue queue;

    int choice;

    while (true) {
        cout << "\n--- Vehicle Rental System ---\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            user.registerUser();
        }

        else if (choice == 2) {
            if (user.loginUser()) {

                //  CUSTOMER FLOW
                if (user.getRole() == "CUSTOMER") {
                    Customer c;
                    c = *(Customer*)&user;

                    c.setupCustomer();

                    int ch;
                    while (true) {
                        cout << "\n--- Customer Menu ---\n";
                        cout << "1. View Vehicles\n";
                        cout << "2. Book Vehicle\n";
                        cout << "3. Cancel Booking\n";
                        cout << "4. Logout\n";
                        cout << "Enter choice: ";
                        cin >> ch;

                        if (ch == 1) {
                            c.viewVehicles();
                        }
                        else if (ch == 2) {
                            c.bookVehicle(queue);   //  adds booking
                        }
                        else if (ch == 3) {
                            c.cancelBooking();
                        }
                        else {
                            break;
                        }
                    }
                }

                // 🔹 DRIVER FLOW
                else if (user.getRole() == "DRIVER") {
                    Driver d;
                    d = *(Driver*)&user;

                    d.setupDriver();

                    int ch;
                    while (true) {
                        cout << "\n--- Driver Menu ---\n";
                        cout << "1. View Customers\n";
                        cout << "2. Accept Customer\n";
                        cout << "3. Reject Customer\n";
                        cout << "4. Rate Customer\n";
                        cout << "5. Logout\n";
                        cout << "Enter choice: ";
                        cin >> ch;

                        if (ch == 1) {
                            d.viewCustomers();   //  FIX
                        }
                        else if (ch == 2) {
                            d.acceptCustomer( );  // FIX
                        }
                        else if (ch == 3) {
                            d.rejectCustomer();  // FIX: rejectCustomer takes no arguments
                        }
                        else if (ch == 4) {
                            d.rateCustomer();
                        }
                        else {
                            break;
                        }
                    }
                }

                // 🔹 ADMIN FLOW
                else if (user.getRole() == "ADMIN") {
                    int ch;
                    while (true) {
                        cout << "\n--- Admin Menu ---\n";
                        cout << "1. Add Vehicle\n";
                        cout << "2. View All Vehicles\n";
                        cout << "3. Logout\n";
                        cout << "Enter choice: ";
                        cin >> ch;

                        if (ch == 1) {
                            Vehicle v;
                            v.addVehicle();
                            insertVehicle(v);
                        }
                        else if (ch == 2) {
                            displayAllVehicles();
                        }
                        else {
                            break;
                        }
                    }
                }
            }
        }

        else {
            cout << "Exiting...\n";
            break;
        }
    }

    return 0;
}