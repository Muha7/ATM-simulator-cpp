#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cctype>
#include <fstream>
#include <ctime>
using namespace std;

const string FileName = "Client.txt";

void ShowMainMenu();
void ShowQuickWithdrawScreen();
void ShowNormalWithdrawScreen();
void Login();

struct Client
{
    string AC;
    string CName;
    string phoneNumber;
    string BinCode;
    double AB;
    bool MarkClient = false;
};

Client currentClient;

enum enATMMainMenuOptions
{
    eQuickWithdraw = 1,
    eNormalWithdraw = 2,
    eDeposit = 3,
    eCheckBalance = 4,
    eLogOut = 5
};

short ReadATMMainMenuOptions()
{
    short choice;
    cout << "Choose what do you want to do? [1 To 5]? ";
    cin >> choice;

    return choice;
}

short ReadQWithdrawMenuOptions()
{
    short choice;
    cout << "Choose what to withdraw from? [1 To 8]? ";
    cin >> choice;

    return choice;
}

void GoBackToMainMenu()
{
    cout << "Press any key to go back to main menu. . .";
    system("pause>0");
    ShowMainMenu();
}

string convertRecordToLine(Client sClient, string separator = "#//#")
{
    string S = "";

    S += sClient.AC + separator;
    S += sClient.CName + separator;
    S += sClient.phoneNumber + separator;
    S += sClient.BinCode + separator;
    S += to_string(sClient.AB);

    return S;
}

vector<Client> saveClientsTofile(string FileName, vector<Client> vClient)
{
    fstream Myfile;
    Myfile.open(FileName, ios::out);

    if (Myfile.is_open())
    {

        for (Client C : vClient)
        {
            if (C.MarkClient == false)
            {
                string line = convertRecordToLine(C);
                Myfile << line << endl;
            }
        }

        Myfile.close();
    }
    return vClient;
}

vector<string> splitWords(string S, string D)
{
    short pos = 0;
    string sword;
    vector<string> vWord;

    while ((pos = S.find(D)) != std::string::npos)
    {
        sword = S.substr(0, pos);

        if (sword != "")
        {
            vWord.push_back(sword);
            // count++;
        }

        S.erase(0, pos + D.length());
    }

    if (sword != "")
    {
        vWord.push_back(S);
        // count++;
    }
    return vWord;
    // return count;
}

Client ConvertLineToRecord(string Line, string delim)
{
    Client sClient;
    vector<string> CDetails = splitWords(Line, delim);

    if (CDetails.size() < 5)
    {
        cout << "Error in line: " << Line << endl;
        return sClient;
    }

    sClient.AC = CDetails[0];
    sClient.CName = CDetails[1];
    sClient.phoneNumber = CDetails[2];
    sClient.BinCode = CDetails[3];
    sClient.AB = stod(CDetails[4]);

    return sClient;
}

vector<Client> LoadClientsFromFile()
{
    vector<Client> vClient;
    fstream MyFile;
    MyFile.open("client.txt", ios::in);
    string line;

    Client sClient;
    while (getline(MyFile, line))
    {
        sClient = ConvertLineToRecord(line, "#//#");
        vClient.push_back(sClient);
    }

    return vClient;
}

void performDepositeToClient(int amount, vector<Client> vClient, string AC)
{
    char check;

    cout << "\nAre u sure to perform this transaction ?";
    cin >> check;

    if (check == 'y' || check == 'Y')
    {
        for (Client &C : vClient)
        {
            if (C.AC == AC)
            {
                C.AB = C.AB + amount;
                cout << "\nDone successfuly ! New balance is = " << C.AB << endl;
            }
        }

        saveClientsTofile(FileName, vClient);
    }
    else
    {
        cout << "Transaction failed\n";
    }
}

short GetQuickWithdrawAmount(short QuickWithrawOption)
{
    switch (QuickWithrawOption)
    {
    case 1:
        return 20;
    case 2:
        return 50;
    case 3:
        return 100;
    case 4:
        return 200;
    case 5:
        return 400;
    case 6:
        return 600;
    case 7:
        return 800;
    case 8:
        return 1000;
    default:
        return 0;
    }
}

void performQuickWithdrawOperations(short QWithdrawOption)
{
    if (QWithdrawOption == 9)
        return;

    short WithdrawAmount = GetQuickWithdrawAmount(QWithdrawOption);

    if (WithdrawAmount > currentClient.AB)
    {
        cout << "\nThe amount exceeds your balance, make another choice.\n ";
        cout << "Press Anykey to continue...";
        system("pause>0");
        ShowQuickWithdrawScreen();
        return;
    }

    vector<Client> vClient = LoadClientsFromFile();
    performDepositeToClient(WithdrawAmount * -1, vClient, currentClient.AC);
    currentClient.AB -= WithdrawAmount;
}

void ShowQuickWithdrawScreen()
{
    cout << "\n---------------------------------------------------------------------\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "                          Quick Withdraw                                 \n";
    cout << "\n---------------------------------------------------------------------\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "[1]" << " 20" << right << setw(30) <<  "[2]" << " 50\n";
    cout << "[3]" << " 100" << right << setw(30) << "[4]" << " 200\n";
    cout << "[5]" << " 400" << right << setw(30) << "[6]" << " 600\n";
    cout << "[7]" << " 800" << right << setw(30) << "[8]" << " 1000\n";
    cout << "[9]" << " Exite";
    
    cout << "\n---------------------------------------------------------------------\n";
    cout << "-----------------------------------------------------------------------\n";

    cout << "Your balance is " << currentClient.AC;

    performQuickWithdrawOperations(ReadQWithdrawMenuOptions());
}

short ReadAmountMultipleOf(short M)
{
    short num;
    do
    {
        cout << "\n Enter amount multiple of 5: ";
        cin >> num;

    } while (num % M != 0);

    return num;
}

void performNormalWithdraw(short WithdrawAmount)
{
    if (WithdrawAmount > currentClient.AB)
    {
        cout << "\nThe amount exceeds your balance, make another choice.\n ";
        cout << "Press Anykey to continue...";
        system("pause>0");
        ShowNormalWithdrawScreen();
        return;
    }

    vector<Client> vClient = LoadClientsFromFile();
    performDepositeToClient(WithdrawAmount * -1, vClient, currentClient.AC);
    currentClient.AB -= WithdrawAmount;
}

void ShowNormalWithdrawScreen()
{
    cout << "\n---------------------------------------------------------------------\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "                          Normal Withdraw                                 \n";
    cout << "\n---------------------------------------------------------------------\n";
    cout << "-----------------------------------------------------------------------\n";

    performNormalWithdraw(ReadAmountMultipleOf(5));
}

short ReadPositiveAmount()
{
    short num;

    do
    {
        cout << "\nEnter positive amount: ";
        cin >> num;

    } while (num < 0);

    return num;
}

void ShowDepositScreen()
{
    cout << "\n---------------------------------------------------------------------\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "                          Deposite screen                                 \n";
    cout << "\n---------------------------------------------------------------------\n";
    cout << "-----------------------------------------------------------------------\n";

    short WithdrawAmount = ReadPositiveAmount();
    vector<Client> vClient = LoadClientsFromFile();
    performDepositeToClient(WithdrawAmount, vClient, currentClient.AC);
    currentClient.AB += WithdrawAmount;
}

void showBalanceScreen()
{
    cout << "\n---------------------------------------------------------------------\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "                          Show Balance screen                                 \n";
    cout << "\n---------------------------------------------------------------------\n";
    cout << "-----------------------------------------------------------------------\n";

    cout << "Your balance is " << currentClient.AB << endl;
}

void performATMMainMenuOperation(enATMMainMenuOptions ATMMainMenuOption)
{

    switch (ATMMainMenuOption)
    {
    case enATMMainMenuOptions::eQuickWithdraw:
        system("cls");
        ShowQuickWithdrawScreen();
        GoBackToMainMenu();
        break;
    case enATMMainMenuOptions::eNormalWithdraw:
        system("cls");
        ShowNormalWithdrawScreen();
        GoBackToMainMenu();
        break;
    case enATMMainMenuOptions::eDeposit:
        system("cls");
        ShowDepositScreen();
        GoBackToMainMenu();
        break;
    case enATMMainMenuOptions::eCheckBalance:
        system("cls");
        showBalanceScreen();
        GoBackToMainMenu();
        break;
    case enATMMainMenuOptions::eLogOut:
        system("cls");
        Login();
        break;
        
    }
}

void ShowMainMenu()
{
    system("cls");

    cout << "-------------------------------------------------------\n";
    cout << "\t\t\t Main Menu Screen\n";
    cout << "-------------------------------------------------------\n";

    cout << "\t\t [1] Quick Withdraw.\n";
    cout << "\t\t [2] Normal Withdraw.\n";
    cout << "\t\t [3] Deposit.\n";
    cout << "\t\t [4] Check balance.\n";
    cout << "\t\t [5]Log out.\n";

    cout << "-------------------------------------------------------\n";

    performATMMainMenuOperation((enATMMainMenuOptions)ReadATMMainMenuOptions());
}

bool FindClientByACAndPin(string AC, string PinCode, Client &sClient)
{
    vector<Client> vClient = LoadClientsFromFile();

    for (Client C : vClient)
    {
        if (AC == C.AC && PinCode == C.BinCode)
        {
            sClient = C;
            return true;
        }
    }
    return false;
}

bool LaodClientInfo(string AccountNumber, string PinCode, Client &sClient)
{
    if (FindClientByACAndPin(AccountNumber, PinCode, sClient))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Login()
{
    string AccountNumber, PinCode;
    bool LoginFailed = false;

    do
    {
        system("cls");

        if (LoginFailed)
        {
            cout << "invalid AccountNumber or PinCode, try again\n\n";
        }

        cout << "Enter Account Number:";
        cin >> AccountNumber;

        cout << "Enter PinCode:";
        cin >> PinCode;

        LoginFailed = !LaodClientInfo(AccountNumber, PinCode, currentClient);

    } while (LoginFailed);

    ShowMainMenu();
}

int main()
{
    Login();
}
