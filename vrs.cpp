#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdio>
#include <ctime>
using namespace std;

/* =============== Utility ============== */

void clearScreen() 
{
    system("cls");
}

string getCurrentDateTime()
{
    time_t now = time(0);

    char* dt = ctime(&now);

    return string(dt);
}

string inputPassword() 
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

/* =============== Validation ============== */

bool validCitizenship(string c) 
{
    return (c.length() == 11 && c[2] == '-' && c[5] == '-');
}

bool validLicense(string l) 
{
    return (l.length() == 14 && l[2] == '-' && l[8] == '-');
}

bool validDateFormat(string d) 
{
    return (d.length() == 10 && d[2] == '/' && d[5] == '/');
}

int convertToDays(string date) 
{
    int day = stoi(date.substr(0,2));
    int month = stoi(date.substr(3,2));
    int year = stoi(date.substr(6,4));

    return year*365 + month*30 + day;
}

/* =============== Login ============== */

bool login(string filename) 
{
    string user, pass;
    string u,p;

    cout<<"Username: ";
    cin>>user;

    cout<<"Password: ";
    pass=inputPassword();

    ifstream fin(filename);

    while(fin>>u>>p)
    {
        if(u==user && p==pass)
        {
            fin.close();
            return true;
        }

    }

    fin.close();
    return false;
}

/* =============== Register ============== */

void registerAdmin()
{
    ofstream fout("admin.txt",ios::app);

    string user,pass;

    cout<<"New Username: ";
    cin>>user;

    cout<<"Password: ";
    pass=inputPassword();

    fout<<user<<" "<<pass<<endl;

    fout.close();

    cout<<"Admin Registered Successfully!\n";

}

void registerCustomer()
{

    ofstream fout("customer.txt",ios::app);

    string user,pass,cit;

    cout<<"Username: ";
    cin>>user;

    cout<<"Password: ";
    pass=inputPassword();

    cout<<"Citizenship (01-01-12345): ";
    cin>>cit;

    if(!validCitizenship(cit))
    {
        cout<<"Invalid Citizenship Format!\n";
        return;
    }

    fout<<user<<" "<<pass<<" "<<cit<<endl;

    fout.close();

    cout<<"Customer Registered Successfully!\n";

}

/* =============== Vehicle ============== */

class Vehicle
{
    public:

    void addVehicle()
    {
        ofstream fout("vehicles.txt",ios::app);

        string type,brand,plate;
        float rent;

        cout<<"Vehicle Type: ";
        cin>>type;

        cout<<"Brand: ";
        cin>>brand;

        cin.ignore();

        cout<<"License Plate (BA 1 PA 1234): ";
        getline(cin,plate);

        cout<<"Rent per Day: ";
        cin>>rent;

        fout<<type<<"|"<<brand<<"|"<<plate<<"|"<<rent<<endl;

        fout.close();

        cout<<"Vehicle Added Successfully!\n";

    }

    void viewVehicles()
    {

        ifstream fin("vehicles.txt");

        string line;

        cout<<"\n========== VEHICLE LIST ==========\n";

        while(getline(fin,line))
        {
            cout<<line<<endl;
        }

        fin.close();

    }

};

/* =============== Vehicle Delete ============== */

void deleteVehicle()
{

    ifstream fin("vehicles.txt");
    ofstream temp("temp.txt");

    string line;
    string type;

    bool found=false;

    cout<<"Enter Vehicle Type to Delete: ";
    cin>>type;

    while(getline(fin,line))
    {

        if(line.find(type)==string::npos)
        {
            temp<<line<<endl;
        }
        else
        {
            found=true;
        }
    }

    fin.close();
    temp.close();

    remove("vehicles.txt");
    rename("temp.txt","vehicles.txt");

    if(found)
    {
        cout<<"Vehicle Deleted Successfully!\n";
    }
    else
    {
        cout<<"Vehicle Not Found!\n";
    }
}

/* =============== Drivers ============== */

void addDriver(){

    ofstream fout("drivers.txt",ios::app);

    string name,license;
    int charge;

    cout<<"Driver Name: ";
    cin>>name;

    cout<<"License (01-12345-67890): ";
    cin>>license;

    if(!validLicense(license))
    {
        cout<<"Invalid License Format!\n";
        return;
    }

    cout<<"Driver Charge Per Day: ";
    cin>>charge;

    fout<<name<<" "<<license<<" "<<charge<<endl;

    fout.close();

    cout<<"Driver Added Successfully!\n";
}

void viewDrivers(){

    ifstream fin("drivers.txt");

    string name,license;
    int charge;

    cout<<"\n------ DRIVER LIST ------\n";

    while(fin>>name>>license>>charge)
    {

        cout<<"Name: "<<name
            <<" | License: "<<license
            <<" | Charge/Day: "<<charge<<endl;

    }

    fin.close();

}

int selectDriver(string &driverName)
{

    ifstream fin("drivers.txt");

    string name,license;
    int charge;

    string chosen;

    cout<<"Enter Driver Name You Want: ";
    cin>>chosen;

    while(fin>>name>>license>>charge)
    {
        if(name==chosen)
        {
            driverName=name;

            fin.close();

            return charge;
        }

    }

    fin.close();

    cout<<"Driver Not Found!\n";

    return 0;
}

void deleteDriver()
{

    ifstream fin("drivers.txt");
    ofstream temp("temp.txt");

    string name,license;
    string del;

    bool found=false;

    cout<<"Enter Driver Name to Delete: ";
    cin>>del;

    while(fin>>name>>license)
    {

        if(name!=del)
        {
            temp<<name<<" "<<license<<endl;
        }
        else
        {
            found=true;
        }

    }

    fin.close();
    temp.close();

    remove("drivers.txt");
    rename("temp.txt","drivers.txt");

    if(found)
    {
        cout<<"Driver Deleted Successfully!\n";
    }
    else
    {
        cout<<"Driver Not Found!\n";
    }

}

/* =============== Rent ============== */

void rentVehicle()
{

    string type;
    float rent;

    string startDate,endDate;

    char driverChoice;

    int driverCharge=0;
    string driverName="None";

    cout<<"Vehicle Type: ";
    cin>>type;

    cout<<"Rent per Day: ";
    cin>>rent;

    cout<<"Start Date (DD/MM/YYYY): ";
    cin>>startDate;

    cout<<"End Date (DD/MM/YYYY): ";
    cin>>endDate;

    if(!validDateFormat(startDate)||!validDateFormat(endDate))
    {
        cout<<"Invalid Date Format!\n";
        return;
    }

    int start=convertToDays(startDate);
    int end=convertToDays(endDate);

    if(end<=start)
    {
        cout<<"Invalid Date Range!\n";
        return;
    }

    int days=end-start;

    cout<<"Need Driver? (Y/N): ";
    cin>>driverChoice;

    if(driverChoice=='Y'||driverChoice=='y')
    {

        viewDrivers();

        driverCharge=selectDriver(driverName);

    }

    float vehicleCost=days*rent;
    float driverCost=days*driverCharge;
    float total=vehicleCost+driverCost;

    cout<<"\n========== BILL ==========\n";

    cout<<"Vehicle Type : "<<type<<endl;
    cout<<"Total Days   : "<<days<<endl;

    cout<<"Vehicle Cost : Rs."<<vehicleCost<<endl;

    if(driverName!="None")
    {

        cout<<"Driver Name  : "<<driverName<<endl;
        cout<<"Driver Cost  : Rs."<<driverCost<<endl;

    }

    cout<<"---------------------------\n";
    cout<<"TOTAL AMOUNT : Rs."<<total<<endl;

    ofstream fout("rentals.txt",ios::app);

    string bookingTime = getCurrentDateTime();

    fout<<type<<" | "
        <<driverName<<" | "
        <<startDate<<" | "
        <<endDate<<" | "
        <<total<<" | "
        <<bookingTime;

    fout.close();

    cout<<"Booking Confirmed!\n";

}

/* =============== View Booking History ============== */

void viewBookings()
{

    ifstream fin("rentals.txt");

    string line;

    cout<<"\n====== BOOKING HISTORY ======\n";

    while(getline(fin,line))
    {
        cout<<line<<endl;
    }

    fin.close();

}

/* =============== Cancel Booking ============== */

void cancelRent()
{

    ifstream fin("rentals.txt");
    ofstream temp("temp.txt");

    string type,date;
    float amount;

    string del;

    bool found=false;

    cout<<"Enter Vehicle Type to Cancel: ";
    cin>>del;

    while(fin>>type>>amount>>date)
    {

        if(type!=del)
        {
            temp<<type<<" "<<amount<<" "<<date<<endl;
        }
        else
        {
            found=true;
        }

    }

    fin.close();
    temp.close();

    remove("rentals.txt");
    rename("temp.txt","rentals.txt");

    if(found)
    {
        cout<<"Booking Cancelled Successfully!\n";
    }
    else
    {
        cout<<"Booking Not Found!\n";
    }

}

/* =============== Late Fine ============== */

void calculateLateFine()
{

    string bookedEnd,actual;

    cout<<"Booked End Date (DD/MM/YYYY): ";
    cin>>bookedEnd;

    cout<<"Actual Return Date (DD/MM/YYYY): ";
    cin>>actual;

    if(!validDateFormat(bookedEnd)||!validDateFormat(actual))
    {
        cout<<"Invalid Date Format!\n";
        return;
    }

    int booked=convertToDays(bookedEnd);
    int act=convertToDays(actual);

    if(act<=booked)
    {
        cout<<"No Late Fine\n";
        return;
    }

    int lateDays=act-booked;
    int fine=lateDays*500;

    cout<<"Late Days: "<<lateDays<<endl;
    cout<<"Fine: Rs."<<fine<<endl;

}

/* =============== Delete Account ============== */

void deleteAccount(string file)
{

    ifstream fin(file);
    ofstream temp("temp.txt");

    string u,p,extra;
    string del;

    bool found=false;

    cout<<"Enter Username to Delete: ";
    cin>>del;

    while(fin>>u>>p)
    {

        if(file=="customer.txt")
        {
            fin>>extra;
        }
        if(u!=del)
        {
            temp<<u<<" "<<p;

            if(file=="customer.txt")
            {
                temp<<" "<<extra;
            }
            temp<<endl;

        }
        else
        {
            found=true;
        }

    }

    fin.close();
    temp.close();

    remove(file.c_str());
    rename("temp.txt",file.c_str());

    if(found)
    {
        cout<<"Account Deleted Successfully!\n";
    }
    else
    {
        cout<<"Account Not Found!\n";
    }
}

/* =============== Admin Menu ============== */

void adminMenu()
{
    Vehicle v;
    int choice;

    do
    {
        clearScreen();

        cout<<"\n====== ADMIN MENU ======\n";
        cout<<"1 Add Vehicle\n";
        cout<<"2 View Vehicles\n";
        cout<<"3 Delete Vehicle\n";
        cout<<"4 Add Driver\n";
        cout<<"5 View Drivers\n";
        cout<<"6 Delete Driver\n";
        cout<<"7 Delete Admin Account\n";
        cout<<"8 Late Fine\n";
        cout<<"9 View Booking History\n";
        cout<<"10 Logout\n";

        cout<<"Choice: ";
        cin>>choice;

        clearScreen();

        switch(choice)
        {

        case 1: 
             v.addVehicle(); 
             break;
        case 2: 
             v.viewVehicles(); 
             break;
        case 3: 
             deleteVehicle(); 
             break;
        case 4: 
             addDriver(); 
             break;
        case 5: 
             viewDrivers(); 
             break;
        case 6: 
             deleteDriver(); 
             break;
        case 7: 
             deleteAccount("admin.txt"); 
             break;
        case 8: 
             calculateLateFine(); 
             break;
        case 9: 
             viewBookings(); 
             break;
        case 10: 
             cout<<"Logged Out.\n"; 
             break;

        }

        system("pause");

    }while(choice!=10);

}

/* =============== Customer Menu ============== */

void customerMenu()
{
    Vehicle v;
    int choice;

    do
    {
        clearScreen();

        cout<<"\n========== CUSTOMER MENU ==========\n";
        cout<<"1 View Vehicles\n";
        cout<<"2 Rent Vehicle\n";
        cout<<"3 Cancel Booking\n";
        cout<<"4 Delete My Account\n";
        cout<<"5 Logout\n";

        cout<<"Choice: ";
        cin>>choice;

        clearScreen();

        switch(choice)
        {
        case 1: 
             v.viewVehicles(); 
             break;
        case 2: 
             rentVehicle(); 
             break;
        case 3: 
             cancelRent(); 
             break;
        case 4: 
             deleteAccount("customer.txt"); 
             break;
        }

        system("pause");

    }while(choice!=5);

}

/* =============== MAIN ============== */

int main()
{
    int choice;
    do
    {
        clearScreen();

        cout<<"========== VEHICLE RENTAL SYSTEM ==========\n";
        cout<<"1 Admin\n";
        cout<<"2 Customer\n";
        cout<<"3 Exit\n";

        cout<<"Choice: ";
        cin>>choice;

        clearScreen();

        if(choice==1||choice==2)
        {
            int sub;

            do
            {

                cout<<"1 Login\n";
                cout<<"2 Register\n";
                cout<<"3 Back\n";

                cout<<"Choice: ";
                cin>>sub;

                clearScreen();

                if(sub==1)
                {

                    if(choice==1)
                    {

                        if(login("admin.txt"))
                        {
                            adminMenu();
                        }
                        else
                        {
                            cout<<"Invalid Admin Login\n";
                        }

                    }

                    else
                    {

                        if(login("customer.txt"))
                        {
                            customerMenu();
                        }
                        else
                        {
                            cout<<"Invalid Customer Login\n";
                        }

                    }

                    system("pause");

                }

                else if(sub==2)
                {

                    if(choice==1)
                    {
                        registerAdmin();
                    }
                    else
                    {
                        registerCustomer();
                    }

                    system("pause");

                }

            }while(sub!=3);

        }

    }while(choice!=3);

    cout<<"Thank you for using the system.\n";

    return 0;
}