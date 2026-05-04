struct Vehicle {
    int id;

    std::string type;        // BIKE / CAR / VAN / TRUCK / SCOOTER
    std::string category;    // REGULAR / COMFORT
    std::string fuelType;    // PETROL / DIESEL

    std::string licensePlate;
    std::string maintenanceDate;

    float price;
    bool available;

    Vehicle* next;
    Vehicle* prev;
};

class VehicleList {
private:
    Vehicle* head=nullptr;

public:
    VehicleList();

    void addVehicle();
    void viewVehicles();
    void deleteVehicle();

    void saveVehicles();
    void loadVehicles();
    float getVehiclePrice(int vehicleID);
    void viewAvailableVehicles();   // 
    Vehicle* findVehicle(int id);   // 
};