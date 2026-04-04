#ifndef USER_H
#define USER_H

#include<string>

class User {
public:
    int id;
  int existingId,drivercharge;
   std::string name;
   std::string password,confirm,email,role,citizenshipnum,inputName, inputPass;
   std::string phone,existingdriverName,driverlic;
  std::string line, existingName, existingPassword, existingPhone, existingEmail, existingRole, existingCitizenship;
  std::string driverLine, existingLicense;

    void registerUser(); 
    void searchUser();  
    bool loginUser();    
  std::string getCitizenship();
 std::string inputPassword() ;
 std::string inputPhone();

};


#endif
