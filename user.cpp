#include <iostream>
#include <fstream>
#include <limits>
#include <cctype>
#include <conio.h>
#include "user.h"
using namespace std;

string  User::inputPassword() 
{
    string password = "";
    char ch;

    while (true) 
    {
        ch = _getch();

        if (ch == 13)
        {
            break;
        }
        else if (ch == 8) 
        {
            if (password.length() > 0) 
            {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else 
        {
            password += ch;
            cout << "*";
        }
    }

    cout << endl;
    return password;
}
string  User:: getCitizenship()
{
   while(true) {
        cout << "Enter Citizenship in the format 0X-0X-0X-XXXXX: ";
        cin >> citizenship;

  //checking the length of citizenship number
        if(citizenship.length() != 14) {
         cout << "Invalid length! Try again.\n";
            continue;
        }

        // checking the dashes in correct positions
        if(citizenship[2] != '-' || citizenship[5] != '-' || citizenship[8] != '-') {
            cout << "Invalid format! Use 0X-0X-0X-XXXXX\n";
            continue;
        }

        // checking the digits in correct positions
        bool valid = true;
        for(int i = 0; i < citizenship.length(); i++) {
            if(i == 2 || i == 5 || i == 8)
             continue;


            if(isdigit(citizenship[i])==false) {
                valid = false;
                break;
            }
        }

        if(valid==false) {
            cout << "Only numbers allowed!\n";
            continue;
        }
            return citizenship;
    }
}  

string User::getLicense() {
    while(true) {
        cout << "Enter License in the format 0X-0X-XXXXXXXX: ";
        cin >> license;

        // Check length
        if(license.length() != 14) {
            cout << "Invalid length! Try again.\n";
            continue;
        }

        // Check dash positions
        if(license[2] != '-' || license[5] != '-') {
            cout << "Invalid format! Use 0X-0X-XXXXXXXX\n";
            continue;
        }

        // Check digits
        bool valid = true;
        for(int i = 0; i < license.length(); i++) {
            if(i == 2 || i == 5) continue;

            if(isdigit(license[i])==false) {
                valid = false;
                break;
            }
        }

        if(valid==false) {
            cout << "Only numbers allowed!\n";
            continue;
        }

        return license;
    }
}
//taking user input for phone number and validating it
string User::inputPhone() {

    while(true) {

        cin >> phone;

        if(phone.length() != 10) {
            cout << "Phone  number must be exactly 10 digits!\n";
            continue;
        }

        bool valid = true;
       for(int i = 0; i < phone.length(); i++) {
    if(isdigit(phone[i]) == false) {
        valid = false;
        break;
    }
}

        if(valid==false) {
            cout << "Only numbers allowed!\n";
            continue;
        }

        return phone;
    }
}

string User::generateUserID(string role) {
    static int c = 1, d = 1, a = 1;

    if (role == "CUSTOMER") {
        return (c < 10 ? "C0" : "C") + to_string(c++);
    }
    else if (role == "DRIVER") {
        return (d < 10 ? "D0" : "D") + to_string(d++);
    }
    else {
        return (a < 10 ? "A0" : "A") + to_string(a++);
    }
}
bool User::isDuplicate(string phone, string email) {
    ifstream fin("users.txt");

    string fileID, fileName, filePhone, fileEmail, filePassword, fileRole;
    int fileAge;

    while (fin >> fileID >> fileName >> fileAge >> filePhone >> fileEmail >> filePassword >> fileRole) {
        if (filePhone == phone || fileEmail == email) {
            return true;
        }
    }

    return false;
}
void User::setupCustomer() {
    citizenship = getCitizenship();

    cout << "Are you a student? (1 = Yes / 0 = No): ";
    cin >> isStudent;

    if (isStudent) {
        cout << "Enter student ID: ";
        cin >> studentID;

        cout << "Enter college name: ";
        cin.ignore();
        getline(cin, collegeName);
    }
}

// 🔹 Driver setup
void User::setupDriver() {
    citizenship = getCitizenship();
    license = getLicense();

    cout << "Enter experience (years): ";
    cin >> experience;
}

// 🔹 Admin setup
void User::setupAdmin() {
    cout << "Admin setup complete.\n";
}

//registering user by taking input and storing it in a text file named users.txt

void User::registerUser() {

    cout << "\n--- Register User ---\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
   
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter age: ";
    cin>>age;
    cout << "Enter user phone number in the format  98XXXXXXXX: ";
    phone = inputPhone();
    cout << "Enter password: ";
    password = inputPassword();

    cout << "Confirm password: ";
    string confirm = inputPassword();

    if(password != confirm) {
        cout << "Passwords do not match!\n";
        return;
    }

    cout << "Enter email: ";
    cin >> email;
    while (isDuplicate(phone, email)) {
        cout << "Phone or Email already exists!\n";
        phone = inputPhone();
        cout << "Enter email: ";
        cin >> email;
    }

    cout << "Enter role (Admin/Customer/Driver): ";
    getline(cin, role);
     for (int i = 0; i < role.length(); i++) {
    role[i] = toupper(role[i]);
}
   if(role == "CUSTOMER")
        setupCustomer();
    else if(role == "DRIVER")
        setupDriver();
        else
        setupAdmin();

        userID= generateUserID(role);

        cout<<"Your User ID is: "<<userID<<endl;

       ofstream fout("users.txt", ios::app);
    fout << userID << " "
         << name << " "
         << age << " "
         << phone << " "
         << email << " "
         << password << " "
         << role << endl;

    fout.close();

    cout << "Registration successful!\n";

          
}

    
 bool User::loginUser() {
    string inputID, inputPass;
    string fileID, fileName, filePhone, fileEmail, filePassword, fileRole;
    int fileAge;

    ifstream fin("users.txt");

    cout << "Enter User ID: ";
    cin >> inputID;

    cout << "Enter Password: ";
    inputPass = inputPassword();

    while (fin >> fileID >> fileName >> fileAge >> filePhone >> fileEmail >> filePassword >> fileRole) {
        if (fileID == inputID && filePassword == inputPass) {
            cout << "\nLogin Successful!\n";

            userID = fileID;
            role = fileRole;

            fin.close();
            return true;
        }
    }

    cout << "\nInvalid ID or Password!\n";
    fin.close();
    return false;
}


// 🔹 Getters
string User::getUserID() {
    return userID;
}

string User::getRole() {
    return role;
}
 
