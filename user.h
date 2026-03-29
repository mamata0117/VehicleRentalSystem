#ifndef USER_H
#define USER_H

#include<string>

class User {
public:
    int id;
   std::string name;
   std::string password,confirm,email,role,citizenshipnum,inputName, inputPass;
   std::string phone;

    void registerUser(); 
    void searchUser();  
    bool loginUser();    
  std::string getCitizenship();
 std::string inputPassword() ;
 std::string inputPhone();

};


#endif
