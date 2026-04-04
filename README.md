# Vehicle Rental System

A console-based C++ project for managing a small vehicle rental workflow with role-based menus for admin, driver, and customer users.

## Features

- User registration and login with role support (`ADMIN`, `DRIVER`, `CUSTOMER`)
- Vehicle management (add, view, delete)
- Driver management (add, view, delete)
- Booking management:
  - Create booking
  - View bookings
  - Search booking by ID
  - Cancel booking
- Priority booking queue (FIFO)
- Simple review system (stack-based, available in code)
- File-based persistence using `.txt` files

## Project Structure

- `main.cpp`: Entry point
- `menu.cpp`, `menu.h`: Main, admin, driver, and customer menus
- `user.cpp`, `user.h`: Registration, login, and user search
- `vehicle.cpp`, `vehicle.h`: Vehicle list using a circular doubly linked list
- `driver.cpp`, `driver.h`: Driver add/view/delete and license validation
- `booking.cpp`, `booking.h`: Booking linked list, priority queue, and review stack
- `users.txt`, `vehicles.txt`, `drivers.txt`, `bookings.txt`: Data storage files

## Requirements

- Windows OS (project uses `conio.h` and `system("cls")`)
- C++ compiler with C++11 or later support
- Recommended: MinGW g++

## Build And Run (Windows, g++)

From the project root:

```powershell
g++ -std=c++11 main.cpp menu.cpp user.cpp vehicle.cpp driver.cpp booking.cpp -o output/VehicleRentalSystem.exe
./output/VehicleRentalSystem.exe
```

If `output` does not exist, create it first:

```powershell
mkdir output
```

## Default Flow

1. Start the program.
2. Register a user with role `ADMIN`, `DRIVER`, or `CUSTOMER`.
3. Login with name and password.
4. Role-based menu opens:
   - Admin: manage vehicles, drivers, and search users
   - Driver: view drivers
   - Customer: view vehicles and manage bookings

## Data File Notes

- `users.txt` stores user identity, credentials, role, and citizenship data.
- `vehicles.txt` stores vehicle inventory and availability.
- `drivers.txt` stores driver records and daily charges.
- `bookings.txt` stores booking entries and calculated amounts.

Keep these files in the project root so the application can load/save data correctly.

## Known Limitations

- Data parsing uses space-separated fields in several places, so names with spaces may not reload correctly from some files.
- No encryption/hashing is used for passwords (plain text storage).
- Input validation is basic and focused on console usage.

## License

See `LICENSE`.
