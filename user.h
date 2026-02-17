#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

class User {
public:
    int id;
    string name;
    string password,email;
    long int phone;

    void registerUser(); 
    void searchUser();  
    bool loginUser();   
    void driverMenu();   
    void AdminMenu();   
    void CustomerMenu();   
};

#endif
