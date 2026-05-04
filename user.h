#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string userID, name;
    int age = 0;
    std::string email, password;
    std::string phone; 
    std::string citizenship;
    std::string license; 
    std::string role;   // CUSTOMER / DRIVER / ADMIN

    // Customer
    bool isStudent = false;
    std::string studentID;
    std::string collegeName;

    // Driver
    int experience = 0;

public:
    void registerUser();
    bool loginUser();

    std::string inputPassword(),inputPhone();
    std::string getCitizenship(),getLicense();
    std::string generateUserID(std::string role);
    std::string getUserID();
    std::string getRole();

    void setupCustomer();
      void setupDriver();
    void setupAdmin();

    bool isDuplicate(std::string phone, std::string email);
};

#endif