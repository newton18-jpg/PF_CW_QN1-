#include <iostream>
#include <string>
#include <cstdlib> // For system("cls") and system("pause")
using namespace std;

struct User {
    User *next;
    string UserId;
    string password;
    double depositMoney;
    double WithdrawMoney;
    double balance;

    User() : next(NULL), depositMoney(0), WithdrawMoney(0), balance(0) {}
};

User *users = NULL; // Initialize the user list
int userCount = 0; // Change 'cout' to 'userCount'

void Welcome() {
    cout << "Welcome to the Banking System!" << endl;
}

char MainMenu() {
    char choice;
    cout << "Main Menu:" << endl;
    cout << "c -> Create Account" << endl;
    cout << "1 -> Login" << endl;
    cout << "q -> Quit" << endl;
    cout << "> ";
    cin >> choice;
    return choice;
}

User *Authorization(const string &uId, const string &pass) {
    User *temp = users;
    while (temp != NULL) {
        if (temp->UserId == uId && temp->password == pass) {
            return temp; // Return the found user
        }
        temp = temp->next;
    }
    return NULL; // User not found
}

char UserMenu() {
    char choice;
    cout << "User Menu:" << endl;
    cout << "d -> Deposit Money" << endl;
    cout << "w -> Withdraw Money" << endl;
    cout << "r -> Request Balance" << endl;
    cout << "q -> Logout" << endl;
    cout << "> ";
    cin >> choice;
    
    if (choice == 'd' || choice == 'w' || choice == 'r' || choice == 'q') {
        return choice;
    } else {
        cout << "Invalid Input, Please select correct choice" << endl;
        return UserMenu(); // Ask again
    }
}

void CreateAccount() {
    User *u = new User();
    cout << "Enter your User Id: ";
    cin >> u->UserId;

    cout << "Enter your password: ";
    cin >> u->password;

    u->next = users; // Add new user to the front of the list
    users = u; // Update head of the list
}

void Deposit(User *u, double amount) {
    if (u != NULL) {
        u->balance += amount;
        cout << "Deposit successful! New balance: UGX " << u->balance << endl;
    } else {
        cout << "You must be logged in to deposit money." << endl;
    }
}

void Withdraw(User *u, double amount) {
    if (u != NULL) {
        if (u->balance >= amount) {
            u->balance -= amount;
            cout << "Withdrawal successful! New balance: UGX " << u->balance << endl;
        } else {
            cout << "Insufficient balance! Please deposit more funds." << endl;
        }
    } else {
        cout << "You must be logged in to withdraw money." << endl;
    }
}

double BalanceRequest(User *u) {
    return u ? u->balance : 0; // Return balance or 0 if user is NULL
}

int main() {
    Welcome();
    
    char ch;
    do {
        ch = MainMenu();
        
        switch (ch) {
            case 'c':
                CreateAccount();
                system("cls");
                break;

            case '1': {
                string uId, password;
                cout << "Enter User Id: ";
                cin >> uId;
                cout << "Enter password: ";
                cin >> password;

                User *user = Authorization(uId, password);
                if (user != NULL) {
                    char uchoice;
                    do {
                        system("cls");
                        uchoice = UserMenu();
        switch (uchoice) {
                            case 'd': {
                                double deposit;
                                cout << "Enter Deposit amount: UGX ";
                                cin >> deposit;
                                Deposit(user, deposit);
                                break;
                            }
                            case 'w': {
                                double withdraw;
                                cout << "Enter Withdraw amount: UGX ";
                                cin >> withdraw;
                                if (withdraw > 0) {
                                    Withdraw(user, withdraw);
                                } else {
                                    cout << "Withdraw amount must be greater than 0." << endl;
                                }
                                break;
                            }
                            case 'r':
                                cout << "Your Balance is: UGX " << BalanceRequest(user) << endl;
                                system("pause");
                                break;
                        }
                    } while (uchoice != 'q');
                } else {
                    cout << "Invalid user Id or password!" << endl;
                    system("pause");
                }
                break;
            }
        }
        system("cls");
    } while (ch != 'q');

    return 0;
}
