#include<iostream>
#include<conio.h>
#include<fstream>
#include<cctype>
#include "menu.h"
#include "user.h"
using namespace std;
string  User::inputPassword() 
{
    string password = "";
    char ch;

    while (1) 
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
        cout << "Enter Citizenship (Format: 0X-0X-0X-XXXXX): ";
        cin >> citizenshipnum;

  //checking the length of citizenship number
        if(citizenshipnum.length() != 14) {
            std::cout << "Invalid length! Try again.\n";
            continue;
        }

        // checking the dashes in correct positions
        if(citizenshipnum[2] != '-' || citizenshipnum[5] != '-' || citizenshipnum[8] != '-') {
            std::cout << "Invalid format! Use 0X-0X-0X-XXXXX\n";
            continue;
        }

        // checking the digits in correct positions
        bool valid = true;
        for(int i = 0; i < citizenshipnum.length(); i++) {
            if(i == 2 || i == 5 || i == 8) continue;


            if(isdigit(citizenshipnum[i])==false) {
                valid = false;
                break;
            }
        }

        if(valid==false) {
            cout << "Only numbers allowed!\n";
            continue;
        }
            return citizenshipnum;
    }
}  


//taking user input for phone number and validating it
string User::inputPhone() {
    string phone;

    while(true) {
        cout << "Enter user phone number ( must be 10 digits): ";
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
//registering user by taking input and storing it in a text file named users.txt

void User::registerUser() {
    ofstream fout("users.txt", ios::app);

  cout<<"If you are a new user ,please register yourself by providing the following details\n";
    cout<<"-------------"<<"Enter User Details"<<"-------------"<<endl;
    cout<<"Enter user name:";
    cin.ignore(); 
getline(cin, name);
    cout<<"Enter user ID :";
    cin>>id;
 
cout<<"Enter password: ";
password = inputPassword();

cout<<"Confirm password: ";
confirm = inputPassword();

if(password != confirm) {
    cout<<"Passwords do not match!\n";
    return; }

    cout<<"Enter user phone number :";
  phone = inputPhone();
    cout<<"Enter user email :";
    cin>>email;
cin.ignore(); 
    cout << "Enter your Role (Admin/Customer/Driver): ";
  getline(cin, role);

if(role == "Customer") {
    citizenshipnum = getCitizenship();  
} else {
    citizenshipnum = " Invalid ";
}
    // storing user details in a text file named users.txt
 fout<<name<<" ,"<<id<<" "<<password<<" "<<phone<<" "<<email<<" " << role << " " << citizenshipnum <<endl;
 fout.close();
 cout<<"User have been registered successfully "<<endl;
 }

#include <sstream>
#include <limits>

bool User::loginUser()
{
    ifstream fin("users.txt");

    cout << "Enter Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, inputName);

    cout << "Enter Password: ";
    inputPass = inputPassword();

    string line;

    while(getline(fin, line)) {
        stringstream ss(line);
   getline(ss, name, ','); 
        ss >> name >> id >> password >> phone >> email >> role >> citizenshipnum;

        if(name == inputName && password == inputPass) {
            cout << "\nLogin Successful!\n";

            Menu m;

            if(role == "Admin") {
                m.adminMenu();
            }
            else if(role == "Driver") {
                m.driverMenu();
            }
            else {
                m.customerMenu();
            }

            fin.close();
            return true;
        }
    }

    cout << "\nInvalid Username or Password!\n";
    fin.close();
    return false;
}


void User::searchUser() {

    int choice, searchID;
    string searchName;

    cout << "-------Select any one of the options below------\n";
    cout << "1. Search by Name\n";
    cout << "2. Search by ID\n";
    cout << "Enter your choice: ";
    cin >> choice;

    ifstream fin("users.txt");

    if(!fin) {
        cout << "Error opening file!\n";
        return;
    }

    bool foundinfo = false;

    if(choice == 1) {
        cout << "Enter the name to be searched: ";
        cin >> searchName;

        while(fin >> name >> id >> password >> phone >> email >> role >> citizenshipnum) {
            if(name == searchName) {
                cout << "\nUser Found:\n";
                cout << "Name: " << name << endl;
                cout << "ID: " << id << endl;
                cout << "Email: " << email << endl;
                cout << "Phone: " << phone << endl;
                cout << "Role: " << role << endl;
                cout << "Citizenship: " << citizenshipnum << endl;

                foundinfo = true;
            }
        }
    }

    else if(choice == 2) {
        cout << "Enter the ID to be searched: ";
        cin >> searchID;

        while(fin >> name >> id >> password >> phone >> email >> role >> citizenshipnum) {
            if(id == searchID) {
                cout << "\nUser Found:\n";
                cout << "Name: " << name << endl;
                cout << "ID: " << id << endl;
                cout << "Email: " << email << endl;
                cout << "Phone: " << phone << endl;
                cout << "Role: " << role << endl;
                cout << "Citizenship: " << citizenshipnum << endl;

                foundinfo = true;
            }
        }
    }

    else {
        cout << "Invalid choice!\n";
    }

    if(!foundinfo) {
        cout << "User not found!\n";
    }

    fin.close();
   
}
 
  
