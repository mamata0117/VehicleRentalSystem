#include<iostream>
#include<conio.h>
#include<fstream>
#include<cctype>
#include<sstream>
#include<limits>
#include<vector>
#include "menu.h"
#include "driver.h"
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
        cout << "Enter Citizenship in the format 0X-0X-0X-XXXXX: ";
        cin >> citizenshipnum;

  //checking the length of citizenship number
        if(citizenshipnum.length() != 14) {
         cout << "Invalid length! Try again.\n";
            continue;
        }

        // checking the dashes in correct positions
        if(citizenshipnum[2] != '-' || citizenshipnum[5] != '-' || citizenshipnum[8] != '-') {
            cout << "Invalid format! Use 0X-0X-0X-XXXXX\n";
            continue;
        }

        // checking the digits in correct positions
        bool valid = true;
        for(int i = 0; i < citizenshipnum.length(); i++) {
            if(i == 2 || i == 5 || i == 8)
             continue;


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

    while(true) {
        cout << "Enter user phone number in the format  98XXXXXXXX: ";
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

    cout << "\n--- Enter User Details ---\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter name: ";
    getline(cin, name);

    cout << "Enter ID: ";
    cin >> id;

    cout << "Enter password: ";
    password = inputPassword();

    cout << "Confirm password: ";
    confirm = inputPassword();

    if(password != confirm) {
        cout << "Passwords do not match!\n";
        return;
    }

    phone = inputPhone();

    cout << "Enter email: ";
    cin >> email;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter role (Admin/Customer/Driver): ";
    getline(cin, role);
for (int i = 0; i < role.length(); i++) {
    role[i] = toupper(role[i]);
}
   if(role == "CUSTOMER")
        citizenshipnum = getCitizenship();
    else
      {  citizenshipnum = "Not Applicable";}

 //Duplicate checking
    ifstream fin("users.txt");
    while(getline(fin, line)) {

        if(line.empty())
         continue;
        
        stringstream ss(line);
        getline(ss, existingName, ',');

        ss >> existingId >> existingPassword
           >> existingPhone >> existingEmail
           >> existingRole >> existingCitizenship;

        if(existingId == id || existingName == name ||
           existingEmail == email || existingPhone == phone ||
           (role == "CUSTOMER" && existingCitizenship == citizenshipnum)) {

            cout << "User already exists with same details!\n";
            return;
        }
    }
//driver registration with license validation and duplicate checking
    if(role == "DRIVER") {
        Driver d;
   int charge;

        d.name = name;
        d.license = d.getLicense();

       ifstream din("drivers.txt");
while(getline(din, line)) {
    istringstream ds(line);

getline(ds, existingdriverName, ',');
getline(ds, driverlic, ',');
ds >> drivercharge;

    if(existingdriverName == d.name || driverlic == d.license) {
        cout << "Driver already exists!\n";
        return;
    }
}


cout << "Enter charge per day: ";
cin >> charge;

ofstream dout("drivers.txt", ios::app);
dout << d.name << " " << d.license << " " << charge << endl;
    }

  
    ofstream fout("users.txt", ios::app);
    fout << name << "," << id << " " << password << " "
         << phone << " " << email << " "
         << role << " " << citizenshipnum << endl;

    cout << "User registered successfully!\n";
}


bool User::loginUser()
{
    ifstream fin("users.txt");

    cout << "Enter Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, inputName);

    cout << "Enter Password: ";
    inputPass = inputPassword();

    while(getline(fin, line)) {
        stringstream ss(line);
   getline(ss, name, ','); 
        ss>> id >> password >> phone >> email >> role >> citizenshipnum;

        if(name == inputName && password == inputPass) {
            cout << "\nLogin Successful!\n";

            Menu m;

            string UpperRole = role;

for (int i = 0; i < UpperRole.length(); i++) {
    UpperRole[i] = toupper(UpperRole[i]);
}

            if(UpperRole == "ADMIN") {
                m.adminMenu();
            }
            else if(UpperRole == "DRIVER") {
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
cout << "\n--- Search User ---\n\n";
cout<<"Enter your choice :\n";
    cout <<"1. Search by Name\n";
     cout<<"2. Search by ID\n";
     cout<<"3. Back\n";
    cin >> choice;

    ifstream fin("users.txt");
    if(!fin) {
        cout << "Error opening file!\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(choice == 1) {
        cout << "Enter name: ";
        getline(cin, searchName);
    } 
    else if(choice == 2) {
        cout << "Enter ID: ";
        cin >> searchID;
    } 
    else if(choice == 3) {
        return;
    }
    else {
        cout << "Invalid choice!\n";
        return;
    }

    bool found = false;

    while(getline(fin, line)) {
        stringstream ss(line);

        getline(ss, name, ',');
        ss >> id >> password >> phone >> email >> role >> citizenshipnum;

        if((choice == 1 && name == searchName) ||
           (choice == 2 && id == searchID)) {

            cout << "\nUser Found:\n";
            cout << "Name: " << name << "\nID: " << id
                 << "\nEmail: " << email << "\nPhone: " << phone
                 << "\nRole: " << role << "\nCitizenship: " << citizenshipnum << endl;

            found = true;
        }
    }

    if(!found)
        cout << "User not found!\n";
}
 
  
