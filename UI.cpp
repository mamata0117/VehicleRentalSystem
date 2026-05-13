#include "ui.h"

void printHeader(string title)
{
    cout << "┌──────────────────────────────────────┐\n";

    cout << "│ "
         << left << setw(36)
         << title
         << "│\n";

    cout << "└──────────────────────────────────────┘\n";
}

void printField(string label, string value)
{
    cout << "│ "
         << left << setw(18)
         << label
         << setw(19)
         << value
         << "│\n";
}

void printMessage(string msg)
{
    cout << "├──────────────────────────────────────┤\n";

    cout << "│ "
         << left << setw(36)
         << msg
         << "│\n";

    cout << "└──────────────────────────────────────┘\n";
}

void printLine()
{
    cout << "├──────────────────────────────────────┤\n";
}