#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <cctype>
#include <conio.h>
#include "user.h"
#include "ui.h"

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
    system("cls");

    printHeader("USER REGISTRATION");

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // NAME
    cout << "│ "
         << left << setw(22)
         << "Enter Name : ";

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
    cout << "│ "
         << left << setw(22)
         << "Enter Age : ";

    cin >> age;

    // PHONE
    cout << "│ "
         << left << setw(22)
         << "Enter Phone : ";

    phone = inputPhone();

    // PASSWORD
    cout << "│ "
         << left << setw(22)
         << "Enter Password : ";

    password = inputPassword();

    // CONFIRM PASSWORD
    cout << "│ "
         << left << setw(22)
         << "Confirm Password : ";

    string confirm = inputPassword();

    if(password != confirm)
    {
        printLine();

        printMessage("Passwords do not match. Try again.");

        cout << "└──────────────────────────────────────────────────────────────┘\n";

        return;
    }

    // EMAIL
    cout << "│ "
         << left << setw(22)
         << "Enter Email : ";

    cin >> email;

    while(isDuplicate(phone, email))
    {
        printLine();

        printMessage("Phone or Email already exists.");

        cout << "└──────────────────────────────────────────────────────────────┘\n";

        return;
    }

    // ROLE
    cout << "│ "
         << left << setw(22)
         << "Enter Role : ";

    cin >> role;

    // Convert role to uppercase
    for(char &c : role)
    {
        c = toupper(c);
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

    else
    {
        printLine();

        printMessage("Invalid role. Try again.");

        cout << "└──────────────────────────────────────────────────────────────┘\n";

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

    

    printMessage("Registration Successfully Done.");

    printMessage("User ID : " + userID);

    cout << "└──────────────────────────────────────────────────────────────┘\n";
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