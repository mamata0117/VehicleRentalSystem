Vehicle Rental System — Function Map

This README maps the main functions and where their core logic lives across the codebase. Use this as a quick reference when navigating or modifying behavior.

How to read this document
- File: link to the implementation file. - Function: `name()` : short description of the logic it contains.

Files & Functions

- File: [vehicle.cpp](vehicle.cpp)
  - `Vehicle::addVehicle()` : Interactive input for new vehicle details, license-plate format validation, maintenance dates, pricing, and sets availability to true.
  - `insertVehicle()` : Insert a `Vehicle` into the linked-list starting at global `head`.
  - `Vehicle::displayVehicle()` : Render a vehicle's fields via the UI helpers.
  - `displayAllVehicles()` / `displayAvailableVehicles()` : Iterate the vehicle linked list and display all/only-available vehicles.
  - `Vehicle::isAvailable()` / `Vehicle::setAvailability()` : Availability getter/setter.
  - `findVehicleByID()` : Linear search through the vehicle linked list and return pointer to matching `Vehicle`.

- File: [user.cpp](user.cpp)
  - `User::registerUser()` : Collects name/age/phone/email/password/role, validates inputs, generates a role-based ID, writes the record to a role-specific file (admins/customers/drivers).
  - `User::loginUser()` : Prompts for ID and password, opens the corresponding role file, validates credentials, and sets `userID`/`role`.
  - `User::inputPhone()`, `inputPassword()`, `inputCitizenship()`, `inputLicense()` : Interactive input helpers with format and character validation.
  - `User::generateUserID()` : Counts records in role files and returns a new ID string (`A-`, `C-`, `D-`).
  - `User::isDuplicate()` : Quick scan of `users.txt` for duplicate phone/email.

- File: [UI.cpp](UI.cpp)
  - `printMenuHeader()`, `printMenuItem()`, `printMenuFooter()`, `printInputHeader()`, `printMessage()`, `printLine()` : Console UI helpers used across the app.
  - `showAvailableUsers()` : Reads `admins.txt`, `customers.txt`, and `drivers.txt` and prints available accounts (used on login screen).

- File: [driver.cpp](driver.cpp)
  - `Driver::setupDriver()` : Collects driver-specific fields and appends them to `drivers.txt`.
  - `Driver::viewReviews()` : Parses `reviews.txt` and prints reviews for the logged-in driver.
  - `Driver::acceptCustomer()` / `rejectCustomer()` : Scan `bookings.txt` for `PENDING` entries, display them, then replace the chosen booking's status to `ACCEPTED` / `REJECTED` by rewriting the file.
  - `Driver::rateCustomer()` : Append a customer rating to `customer_ratings.txt`.
  - `Driver::viewTotalRidesToday()` : Parse `bookings.txt`, count bookings assigned to the driver that match a supplied pickup date.

- File: [admin.cpp](admin.cpp)
  - `Admin::adminMenu()` : Console menu for admin actions: add vehicle (calls `Vehicle::addVehicle()` + `insertVehicle()`), view all vehicles, view available vehicles, and view bookings (calls `BookingQueue::display()`).

- File: [booking.cpp](booking.cpp)
  - `BookingQueue::createBooking()` : Interactive booking flow: vehicle & customer IDs, date inputs (validated with `validDateFormat()`), day-count computed via `convertToDays()`, student discount, optional driver selection (calls `selectDriver()`), save to `rentals.txt`, set `Booking` fields and enqueue.
  - `validDateFormat()` / `convertToDays()` : Helpers for validating and computing day counts from `DD/MM/YYYY` strings.
  - `selectDriver()` : Simple driver selection menu returns driver name and daily rate.
  - `BookingQueue::enqueue()` / `dequeue()` / `display()` / `getFront()` / `isEmpty()` : Basic queue operations implemented with a singly linked list; `enqueue()` also calls `updateVehicleStatus()`.
  - `BookingQueue::updateVehicleStatus()` : Rewrites `vehicles.txt` marking a vehicle's status as `Booked` when a booking is enqueued.

- File: [menu.cpp](menu.cpp)
  - `customerMenu()`, `driverMenu()`, `adminMenu()` : Top-level loops that present choices and dispatch to the corresponding class methods (e.g., `Customer::bookVehicle()`, `Driver::acceptCustomer()`).

- File: [customer.cpp](customer.cpp)
  - `Customer::setupCustomer()` : Collect citizenship and student info.
  - `Customer::viewVehicles()` : Calls `displayAvailableVehicles()`.
  - `Customer::bookVehicle()` : Reads booking inputs, uses `findVehicleByID()` to validate, checks availability, sets `Vehicle::setAvailability(false)`, enqueues a `Booking` with `status = "PENDING"`.
  - `Customer::cancelBooking()` : Removes a booking line from `bookings.txt` by rewriting to a temporary file.
  - `Customer::completeRide()` : Placeholder to mark a booking completed and optionally call `reviewDriver()`.
  - `Customer::reviewDriver()` : Append a driver review to `reviews.txt`.

- File: [main.cpp](main.cpp)
  - `main()` : Program entry and main loop: displays top-level menu (Register / Login / Exit), calls `User::registerUser()` and `User::loginUser()`, constructs `Customer`/`Driver`/`Admin` objects after login, runs their `setup*()` routines and menus.

Storage & File Conventions
- Users are stored in `admins.txt`, `customers.txt`, and `drivers.txt` with each record spanning multiple lines (user fields). Other domain files include `vehicles.txt`, `bookings.txt`, `rentals.txt`, `reviews.txt`, and `customer_ratings.txt`.

