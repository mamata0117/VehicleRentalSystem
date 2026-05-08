#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string userID;
    std::string name;
    int age;
    std::string phone;
    std::string email;
    std::string password;
    std::string role;

public:
    void registerUser();
    bool loginUser(),isDuplicate(std::string phone, std::string email);

    std::string getUserID();
    std::string getName();
    std::string getRole();
    std::string getPhone();
    std::string inputPhone(),inputPassword();
std::string inputCitizenship();
std::string inputLicense();
    std::string generateUserID(std::string role);
    void setUserID(std::string id);
    void setRole(std::string r);
};

#endif