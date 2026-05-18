#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <cctype>
#include <conio.h>
#include <windows.h>
#include "user.h"
#include "idgenerator.h"
#include "UI.h"

using namespace std;

string User::inputPassword() {
    string password = "";
    char ch;

    while (true) {
        ch = _getch();

        if (ch == 13) break;
        else if (ch == 8 && password.length() > 0) {
            password.pop_back();
            cout << "\b \b";
        }
        else {
            password += ch;
            cout << "*";
        }
    }
    cout << endl;
    return password;
}


string User::inputPhone() {
    while (true) {
        getline(cin, phone);

        if (phone.empty()) {
            cout << "Phone number cannot be empty.\n";
            continue;
        }

        if (phone.length() != 10) {
            cout << "Phone number must be exactly 10 digits.\n";
            continue;
        }

        if (phone[0] != '9') {
            cout << "Phone number must start with 9.\n";
            continue;
        }

        bool valid = true;
        for (char c : phone) {
            if (!isdigit(c)) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            cout << "Only numbers are allowed.\n";
            continue;
        }

        return phone;
    }
}
string User::inputCitizenship() {
    string citizenship;

    while (true) {
        cout << "Enter Citizenship in format of 0X-0X-0X-XXXXX: ";
        cin >> citizenship;

        if (citizenship.length() != 14) {
            cout << "Invalid length!\n";
            continue;
        }

        if (citizenship[2] != '-' || citizenship[5] != '-' || citizenship[8] != '-') {
            cout << "Invalid format!\n";
            continue;
        }

        bool valid = true;
        for (int i = 0; i < citizenship.length(); i++) {
            if (i == 2 || i == 5 || i == 8) continue;

            if (!isdigit(citizenship[i])) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            cout << "Only numbers are allowed.\n";
            continue;
        }

        return citizenship;
    }
} 
string User::inputLicense() {
    string license;

    while (true) {
        cout << "Enter License in format of 0X-0X-XXXXXXXX: ";
        cin >> license;

        if (license.length() != 14) {
            cout << "Invalid length!\n";
            continue;
        }

        if (license[2] != '-' || license[5] != '-') {
            cout << "Invalid format!\n";
            continue;
        }

        bool valid = true;
        for (int i = 0; i < license.length(); i++) {
            if (i == 2 || i == 5) continue;

            if (!isdigit(license[i])) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            cout << "Only numbers are allowed.\n";
            continue;
        }

        return license;
    }
}

string User::generateUserID(string role)
{
    return IDGenerator::generateID(role);
}


bool User::isDuplicate(string phone, string email) {
    // Check all role-specific files
    string files[] = {"customers.txt", "drivers.txt", "admins.txt"};

    for (int f = 0; f < 3; f++)
    {
        ifstream fin(files[f]);

        string fileID, fileName, fileAge, filePhone, fileEmail, filePassword, fileRole;

        // Each user spans 7 lines in role files
        while (getline(fin, fileID) && getline(fin, fileName) && getline(fin, fileAge) &&
               getline(fin, filePhone) && getline(fin, fileEmail) && getline(fin, filePassword) &&
               getline(fin, fileRole))
        {
            if (filePhone == phone || fileEmail == email)
            {
                fin.close();
                return true;
            }
        }

        fin.close();
    }

    return false;
}


void User::registerUser()
{
    system("cls");

    printInputHeader("USER REGISTRATION");

    
    // NAME
    cout << "Enter Name     : ";
    cin.ignore();
    getline(cin, name);

    // Convert Name to Proper Case
    bool newWord = true;
    
    for(char &c : name)
    {
        if(c == ' ')
        {
            newWord = true;
        }
        
        else
        {
            if(newWord)
            {
                c = toupper(c);
                newWord = false;
            }

            else
            {
                c = tolower(c);
            }
        }
    }
   
    
    // AGE
    cout << "Enter Age      : ";
    cin >> age;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // PHONE
    cout << "Enter Phone    : ";
    phone = inputPhone();

    // PASSWORD
    cout << "Enter Password : ";
    password = inputPassword();

    // CONFIRM PASSWORD
    cout << "Confirm Password   : ";
    string confirm = inputPassword();

    if(password != confirm)
    {
        printMessage("Passwords do not match. Try again.");
        system("pause");
        return;
    }

    // EMAIL
    cout << "Enter Email    : ";
    getline(cin, email);

    if(isDuplicate(phone, email))
    {
        printMessage("Phone or Email already exists.");
        system("pause");
        return;
    }

    // ROLE
    while (true)
    {
        cout << "Enter Role(Customer/Driver/Admin)    : ";
        getline(cin, role);

        while (!role.empty() && isspace(static_cast<unsigned char>(role.front())))
        {
            role.erase(role.begin());
        }

        while (!role.empty() && isspace(static_cast<unsigned char>(role.back())))
        {
            role.pop_back();
        }

        if(role.empty())
        {
            printMessage("Role cannot be empty.");
            continue;
        }

        for(char &c : role)
        {
            c = toupper(c);
        }

        if(role == "1" || role == "CUSTOMER")
        {
            role = "CUSTOMER";
            break;
        }

        if(role == "2" || role == "DRIVER")
        {
            role = "DRIVER";
            break;
        }

        if(role == "3" || role == "ADMIN")
        {
            role = "ADMIN";
            break;
        }

        printMessage("Invalid role. Please choose Customer, Driver, or Admin.");
    }
    

    userID = generateUserID(role);

    ofstream fout;

    if(role == "ADMIN")
    {
        fout.open("admins.txt", ios::app);
    }

    else if(role == "CUSTOMER")
    {
        fout.open("customers.txt", ios::app);
    }

    else if(role == "DRIVER")
    {
        fout.open("drivers.txt", ios::app);
    }

    // SAVE DATA
    fout << userID << endl;
    fout << name << endl;
    fout << age << endl;
    fout << phone << endl;
    fout << email << endl;
    fout << password << endl;
    fout << role << endl;

    fout.close();

    printMessage("Registration Successfully Done.");
    printMessage("User ID : " + userID);
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}



bool User::loginUser()
{
    ifstream fin;

    string inputPass, inputID;

    string fileID;
    string fileName;
    string ageStr;
    string filePhone;
    string fileEmail;
    string filePassword;
    string fileRole;

    printInputHeader("USER LOGIN");

    cout << "Enter User ID  : ";
    cin >> inputID;

    // OPEN FILE BASED ON USER ID
    if(inputID[0] == 'A')
    {
        fin.open("admins.txt");
    }

    else if(inputID[0] == 'C')
    {
        fin.open("customers.txt");
    }

    else if(inputID[0] == 'D')
    {
        fin.open("drivers.txt");
    }

    else
    {
        printMessage("Invalid User ID format.");
        return false;
    }

    // FILE CHECK
    if (!fin)
    {
        printMessage("Error opening file.");
        return false;
    }

    cout << "Enter Password : ";
    inputPass = inputPassword();

    // READ RECORDS
    while (getline(fin, fileID))
    {
        getline(fin, fileName);
        getline(fin, ageStr);
        getline(fin, filePhone);
        getline(fin, fileEmail);
        getline(fin, filePassword);
        getline(fin, fileRole);

        // LOGIN MATCH
        if (fileID == inputID && filePassword == inputPass)
        {
            printMessage("Login Successfully Done.");
            cout << "Loading your dashboard, please wait...\n";
            Sleep(2000);

            userID = fileID;
            role = fileRole;

            fin.close();

            return true;
        }
    }

    printMessage("Invalid ID or Password.");

    fin.close();

    return false;
}

//  Getters
string User::getUserID() { return userID; }
string User::getName() { return name; }
string User::getRole() { return role; }
string User::getPhone() { return phone; }
string User::getEmail() { return email; }
int User::getAge() { return age; }
void User::setUserID(string id)
{
    userID = id;
}

void User::setRole(string r)
{
    role = r;
}