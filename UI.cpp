#include "ui.h"
#include <fstream>

void printMenuHeader(string title)
{
    cout << "\n ______________________________________\n";

    cout << "| "
         << left
         << setw(36)
         << title
         << "|\n";

    cout << "|______________________________________|\n";

    cout << right;
}

void printMenuItem(string text)
{
    cout << "| "
         << left
         << setw(36)
         << text
         << "|\n";

    cout << right;
}

void printMenuFooter()
{
    cout << "|______________________________________|\n";
}

void printInputHeader(string title)
{
    cout << "\n______________________________________\n\n";

    cout << title << endl;

    cout << "______________________________________\n";
}

void printMessage(string msg)
{
    cout << "\n______________________________________\n";

    cout << " " << msg << endl;

    cout << "______________________________________\n";
}

void printLine()
{
    cout << "______________________________________\n";
}

void showAvailableUsers()
{
    ifstream fin;

    string id;
    string name;
    string age;
    string phone;
    string email;
    string password;
    string role;

    printMenuHeader("AVAILABLE ACCOUNTS");

    // ================= ADMINS =================

    fin.open("admins.txt");

    while(getline(fin, id))
    {
        getline(fin, name);
        getline(fin, age);
        getline(fin, phone);
        getline(fin, email);
        getline(fin, password);
        getline(fin, role);

        printLine();

        printMenuItem("ID       : " + id);
        printMenuItem("Name     : " + name);
        printMenuItem("Phone    : " + phone);
        printMenuItem("Password : " + password);
        printMenuItem("Role     : " + role);
    }

    fin.close();

    // ================= CUSTOMERS =================

    fin.open("customers.txt");

    while(getline(fin, id))
    {
        getline(fin, name);
        getline(fin, age);
        getline(fin, phone);
        getline(fin, email);
        getline(fin, password);
        getline(fin, role);

        printLine();

        printMenuItem("ID       : " + id);
        printMenuItem("Name     : " + name);
        printMenuItem("Phone    : " + phone);
        printMenuItem("Password : " + password);
        printMenuItem("Role     : " + role);
    }

    fin.close();

    // ================= DRIVERS =================

    fin.open("drivers.txt");

    while(getline(fin, id))
    {
        getline(fin, name);
        getline(fin, age);
        getline(fin, phone);
        getline(fin, email);
        getline(fin, password);
        getline(fin, role);

        printLine();

        printMenuItem("ID       : " + id);
        printMenuItem("Name     : " + name);
        printMenuItem("Phone    : " + phone);
        printMenuItem("Password : " + password);
        printMenuItem("Role     : " + role);
    }

    fin.close();

    printMenuFooter();
}