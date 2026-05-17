#include "UI.h"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>
#include <utility>

namespace
{
    struct AccountCard
    {
        string id;
        string name;
        string role;
        string firstLabel;
        string firstValue;
        string secondLabel;
        string secondValue;
    };

    static string trimText(string text)
    {
        while (!text.empty() && isspace(static_cast<unsigned char>(text.front())))
        {
            text.erase(text.begin());
        }

        while (!text.empty() && isspace(static_cast<unsigned char>(text.back())))
        {
            text.pop_back();
        }

        return text;
    }

    static string shortenText(const string &text, int width)
    {
        if (width <= 0)
        {
            return "";
        }

        if ((int)text.length() <= width)
        {
            return text;
        }

        if (width <= 3)
        {
            return text.substr(0, width);
        }

        return text.substr(0, width - 3) + "...";
    }

    static string makeBorderLine(int width)
    {
        return "+" + string(width - 2, '-') + "+";
    }

    static string makeBlankLine(int width)
    {
        return "| " + string(width - 4, ' ') + " |";
    }

    static string makeTitleLine(const string &text, int width)
    {
        string content = shortenText(text, width - 4);
        int totalPad = (width - 4) - (int)content.length();
        int leftPad = totalPad / 2;
        int rightPad = totalPad - leftPad;

        return "| " + string(leftPad, ' ') + content + string(rightPad, ' ') + " |";
    }

    static string makeLabelValueLine(const string &label, const string &value, int width)
    {
        string content = label + " : " + value;
        content = shortenText(content, width - 4);
        return "| " + content + string((width - 4) - (int)content.length(), ' ') + " |";
    }

    static vector<string> readNonEmptyLines(const string &filePath)
    {
        vector<string> lines;
        ifstream fin(filePath);

        if (!fin)
        {
            return lines;
        }

        string line;
        while (getline(fin, line))
        {
            line = trimText(line);
            if (!line.empty())
            {
                lines.push_back(line);
            }
        }

        return lines;
    }

    static string lookupCustomerCitizenship(const string &userID)
    {
        ifstream fin("customer_citizenship.txt");

        if (!fin)
        {
            return "Not Saved";
        }

        string line;
        while (getline(fin, line))
        {
            size_t pipePos = line.find('|');
            if (pipePos == string::npos)
            {
                continue;
            }

            string id = trimText(line.substr(0, pipePos));
            string citizenship = trimText(line.substr(pipePos + 1));

            if (id == userID)
            {
                return citizenship.empty() ? "Not Saved" : citizenship;
            }
        }

        return "Not Saved";
    }

    static pair<string, string> lookupDriverDetails(const string &userID)
    {
        ifstream fin("drivers.txt");

        if (!fin)
        {
            return {"Not Saved", "Not Saved"};
        }

        string line;
        while (getline(fin, line))
        {
            stringstream ss(line);
            string fileID;
            string citizenship;
            string license;
            string experience;

            if (ss >> fileID >> citizenship >> license >> experience)
            {
                if (fileID == userID)
                {
                    return {citizenship.empty() ? "Not Saved" : citizenship,
                            license.empty() ? "Not Saved" : license};
                }
            }
        }

        return {"Not Saved", "Not Saved"};
    }

    static vector<AccountCard> loadAccountsFromFile(const string &filePath, const string &role)
    {
        vector<AccountCard> cards;
        vector<string> lines = readNonEmptyLines(filePath);

        for (size_t i = 0; i + 6 < lines.size(); )
        {
            const string &id = lines[i];
            const string &name = lines[i + 1];
            const string &fileRole = lines[i + 6];

            if (fileRole == role)
            {
                AccountCard card;
                card.id = id;
                card.name = name;
                card.role = role;

                if (role == "CUSTOMER")
                {
                    card.firstLabel = "Citizenship";
                    card.firstValue = lookupCustomerCitizenship(id);
                    card.secondLabel = "";
                    card.secondValue = "";
                }
                else if (role == "DRIVER")
                {
                    pair<string, string> driverDetails = lookupDriverDetails(id);
                    card.firstLabel = "Citizenship";
                    card.firstValue = driverDetails.first;
                    card.secondLabel = "License";
                    card.secondValue = driverDetails.second;
                }
                else
                {
                    card.firstLabel = "Access";
                    card.firstValue = "Full Access";
                    card.secondLabel = "";
                    card.secondValue = "";
                }

                cards.push_back(card);
            }

            i += 7;
        }

        return cards;
    }

    static vector<AccountCard> loadAvailableAccounts()
    {
        vector<AccountCard> accounts;

        vector<AccountCard> admins = loadAccountsFromFile("admins.txt", "ADMIN");
        vector<AccountCard> customers = loadAccountsFromFile("customers.txt", "CUSTOMER");
        vector<AccountCard> drivers = loadAccountsFromFile("drivers.txt", "DRIVER");

        accounts.insert(accounts.end(), admins.begin(), admins.end());
        accounts.insert(accounts.end(), customers.begin(), customers.end());
        accounts.insert(accounts.end(), drivers.begin(), drivers.end());

        return accounts;
    }

    static vector<string> renderAccountCard(const AccountCard &card, int width)
    {
        vector<string> lines;
        lines.push_back(makeBorderLine(width));
        lines.push_back(makeTitleLine(card.name, width));
        lines.push_back(makeLabelValueLine("ID", card.id, width));
        lines.push_back(makeLabelValueLine("Role", card.role, width));
        lines.push_back(card.firstLabel.empty() ? makeBlankLine(width) : makeLabelValueLine(card.firstLabel, card.firstValue, width));

        if (!card.secondLabel.empty())
        {
            lines.push_back(makeLabelValueLine(card.secondLabel, card.secondValue, width));
        }
        else
        {
            lines.push_back(makeBlankLine(width));
        }

        lines.push_back(makeBorderLine(width));
        return lines;
    }

    static void printAccountRows(const vector<AccountCard> &accounts)
    {
        if (accounts.empty())
        {
            printMessage("No accounts found.");
            return;
        }

        const int cardWidth = 33;
        const size_t cardsPerRow = 3;
        const string gap = "  ";

        for (size_t index = 0; index < accounts.size(); index += cardsPerRow)
        {
            vector<vector<string>> rows;
            size_t rowEnd = min(index + cardsPerRow, accounts.size());

            for (size_t i = index; i < rowEnd; ++i)
            {
                rows.push_back(renderAccountCard(accounts[i], cardWidth));
            }

            for (size_t lineIndex = 0; lineIndex < rows[0].size(); ++lineIndex)
            {
                for (size_t cardIndex = 0; cardIndex < rows.size(); ++cardIndex)
                {
                    cout << rows[cardIndex][lineIndex];

                    if (cardIndex + 1 < rows.size())
                    {
                        cout << gap;
                    }
                }

                cout << '\n';
            }

            cout << '\n';
        }
    }
}

// Dynamic UI - adapts to content width
static int currentMaxWidth = 40; // Minimum width

static string centerText(const string &s, int width)
{
    if ((int)s.length() >= width) return s.substr(0, width);
    int totalPad = width - (int)s.length();
    int left = totalPad / 2;
    int right = totalPad - left;
    return string(left, ' ') + s + string(right, ' ');
}

static string leftPadText(const string &s, int width)
{
    if ((int)s.length() >= width) return s.substr(0, width);
    return s + string(width - (int)s.length(), ' ');
}

static int calculateWidth(const string &text)
{
    return max(40, (int)text.length() + 4);
}

void printMenuHeader(string title)
{
    currentMaxWidth = calculateWidth(title);
    cout << "\n";
    cout << string(currentMaxWidth, '-') << "\n";
    cout << "| " << leftPadText(title, currentMaxWidth - 4) << " |\n";
    cout << string(currentMaxWidth, '-') << "\n";
}

void printMenuItem(string text)
{
    currentMaxWidth = max(currentMaxWidth, calculateWidth(text));
    cout << left;
    cout << "| " << setw(currentMaxWidth - 4) << text << " |\n";
    cout << right;
}

void printMenuFooter()
{
    cout << string(currentMaxWidth, '-') << "\n";
}

void printInputHeader(string title)
{
    currentMaxWidth = calculateWidth(title);

    cout << "\n";
    cout << string(currentMaxWidth, '-') << "\n";
    cout << "| " << leftPadText(title, currentMaxWidth - 4) << " |\n";
    cout << string(currentMaxWidth, '-') << "\n\n";
}

void printMessage(string msg)
{
    currentMaxWidth = calculateWidth(msg);
    cout << "\n";
    cout << left;
    cout << "| " << setw(currentMaxWidth - 4) << msg << " |\n";
    cout << right;
    cout << string(currentMaxWidth, '-') << "\n";
}

void printLine()
{
    cout << string(currentMaxWidth, '-') << "\n";
}

void showAvailableUsers()
{
    vector<AccountCard> accounts = loadAvailableAccounts();

    printInputHeader("AVAILABLE ACCOUNTS");
    cout << '\n';

    printAccountRows(accounts);
}