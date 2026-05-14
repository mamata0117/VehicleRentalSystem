// ui.cpp

#include "ui.h"


void printMenuHeader(string title)
{
    cout << "\n ______________________________________\n";

    cout << "|"
         << setw(22 + title.length()/2)
         << title
         << setw(18 - title.length()/2)
         << "|\n";

    cout << "|______________________________________|\n";
}

void printMenuItem(string text)
{
    cout << "| "
         << left << setw(36)
         << text
         << "|\n";
}

void printMenuFooter()
{
    cout << "|______________________________________|\n";
}

// ================= INPUT UI =================

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