#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <cctype>
#include <conio.h>
#include "user.h"

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
        cout<<"Enter your phone number in format  98-XXXXXXXX: ";
        cin >> phone;

        if (phone.length() != 10) {
            cout << "Phone number must be exactly 10 digits!\n";
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
            cout << "Only numbers are allowed!\n";
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

string User::generateUserID(string role) {
    static int c = 1, d = 1, a = 1;

    if (role == "CUSTOMER") {
        return "C-" + to_string(c++);
    }
    else if (role == "DRIVER") {
        return "D-" + to_string(d++);
    }
    else {
        return "A-" + to_string(a++);
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


void User::registerUser()
{
    cout << "\n------------- Register User ------------------\n\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter your details to register:\n\n";

    cout << "Enter name: ";
    getline(cin, name);

    cout << "Enter age: ";
    cin >> age;

    phone = inputPhone();

    cout << "Enter password: ";
    password = inputPassword();

    cout << "Confirm password: ";
    string confirm = inputPassword();

    if (password != confirm)
    {
        cout << "Passwords do not match.\n";
        return;
    }

    cout << "Enter email: ";
    cin >> email;

    while (isDuplicate(phone, email))
    {
        cout << "Phone or Email already exists!\n";

        phone = inputPhone();

        cout << "Enter email: ";
        cin >> email;
    }

    cout << "Enter role (CUSTOMER / DRIVER / ADMIN): ";
    cin >> role;

    // convert to uppercase
    for(char &c : role)
    {
        c = toupper(c);
    }

    userID = generateUserID(role);

    // FILE SELECTION
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

    else
    {
        cout << "Invalid role!\n";
        return;
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

    cout << "\nYour User ID: "
         << userID << endl;

    cout << "Registration successful!\n";
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

    cout << "Enter User ID: ";
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
        cout << "Invalid User ID format.\n";
        return false;
    }

    // FILE CHECK
    if (!fin)
    {
        cout << "Error opening file!\n";
        return false;
    }

    cout << "Enter Password: ";
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
            cout << "\nLogin successfully done.\n";

            userID = fileID;

            role = fileRole;

            fin.close();

            return true;
        }
    }

    cout << "\nInvalid ID or Password. Please try again.\n";

    fin.close();

    return false;
}

//  Getters
string User::getUserID() { return userID; }
string User::getName() { return name; }
string User::getRole() { return role; }
string User::getPhone() { return phone; }
void User::setUserID(string id)
{
    userID = id;
}

void User::setRole(string r)
{
    role = r;
}