// Name: Ramona Ruth Fernandez
// Date: 09/14/25
// This program simulates a simple banking system using C++ classes and objects. It defines a  class with features like deposit, withdrawal, and balance tracking. Users interact through a menu to create accounts, manage funds, and view account details. Input validation is included to make sure data is clear. 

#include <iostream>
#include <vector>
#include <limits>
#include <iomanip> // For only 2 decimal places

class BankAccount {
private: // Cannot be accesed by user
    std::string accountNumber;
    std::string accountHolderName;
    double balance;

public: // Usable for user 
    // Default constructor
    BankAccount() {
        accountNumber = "000000";
        accountHolderName = "Unnamed";
        balance = 0.0;
    }

    // Constructor with parameters
    BankAccount(std::string accNum, std::string holderName, double initialBalance) {
        accountNumber = accNum;
        accountHolderName = holderName;
        balance = initialBalance;
    }

    // Our getters
    std::string getAccountNumber() { 
        return accountNumber; 
    }

    std::string getAccountHolderName() { 
        return accountHolderName; 
    }

    double getBalance() { 
        return balance; 
    }

    // Sets the name of the account holder (basically you can change it/ set it)
    void setAccountHolderName(std::string name) {
        accountHolderName = name;
    }

    // A function to deposit money 
    void deposit(double amount) {
        if (balance + amount > 1000000) { // Feel free to ignore this: I noticed that the program would have a spazz when seeing a number greater than that
            std::cout << "Deposit would exceed $1,000,000. Please withdraw before depositing.\n";
        } else if (amount > 0) {
            balance += amount;
            std::cout << "Deposit successful.\n";

        } else {
            std::cout << "Amount cannot be negative.\n";
        }
    }

    // Withdrawing money function
    void withdraw(double amount) {
        if (amount <= 0) { // Counting for negative input 
            std::cout << "Amount cannot be negative.\n";
        } else if (amount > balance) { // Counting for withdrawl to be greater than account's current balance
            std::cout << "Amount is greater than current balance in the account.\n";    
        } else {
            balance -= amount;
            std::cout << "Withdrawal successful.\n"; // Only happens when withdrawl input is NOT greater than balance or a negative number
        }
    }
};

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    std::vector<BankAccount> accounts;

    int choice = 0; // initialize with a value, so that 'while' command doesn't freak out

    // Menu Options
    while (choice != 5) {
    std::cout << "\n--- Bank Menu ---\n";
    std::cout << "1. Create Account\n";
    std::cout << "2. Show All Accounts\n";
    std::cout << "3. Deposit\n";
    std::cout << "4. Withdraw\n";
    std::cout << "5. Exit\n";
    std::cout << "Choose an option: ";
    std::cin >> choice;

    // Fail case
    if (std::cin.fail()) {
        clearInput();
        std::cout << "Please enter a number.\n";
        continue;
    }

    // Else ifs to do class functions
    if (choice == 1) {
            std::string accNum, name;
            double balance;

            std::cout << "Enter account number: ";
            std::cin >> accNum;
            clearInput();

            std::cout << "Enter account holder name: ";
            std::getline(std::cin, name);

            std::cout << "Enter starting balance: ";
            std::cin >> balance;

            if (std::cin.fail() || balance < 0) {
                clearInput();
                std::cout << "Invalid balance.\n";
            } else {
                BankAccount newAccount(accNum, name, balance);
                accounts.push_back(newAccount);
                std::cout << "Account created.\n";
            }

        } else if (choice == 2) {
            if (accounts.empty()) {
                std::cout << "No accounts yet.\n";
            } else {
                for (BankAccount& acc : accounts) {
                    std::cout << std::fixed << std::setprecision(2); // Ensures that balance is displayed with only 2 decimal places 
                    std::cout << "\nAccount #: " << acc.getAccountNumber() << "\nName: " << acc.getAccountHolderName() << "\nBalance: $" << acc.getBalance() << "\n";
                }
            }

        } else if (choice == 3) {
            std::string accNum;
            double amount;
            std::cout << "Enter account number: ";
            std::cin >> accNum;

            //  account exists checker
            bool accFound = false;
            for (BankAccount& acc : accounts) {
                if (acc.getAccountNumber() == accNum) {
                    std::cout << "Enter amount to deposit: ";
                    std::cin >> amount;

                // Just in case user plugs in a non double: Strings or characters
                if (std::cin.fail()) {
                    clearInput();
                    std::cout << "Invalid amount.\n";
                    continue; // Go back to the menu
                }

                    acc.deposit(amount);
                    accFound = true;
                    break;
                }
            }
            if (!accFound) std::cout << "Account not found.\n";

        } else if (choice == 4) {
            std::string accNum;
            double amount;
            std::cout << "Enter account number: ";
            std::cin >> accNum;

            bool accFound = false;
            for (BankAccount& acc : accounts) {
                if (acc.getAccountNumber() == accNum) {
                    std::cout << "Enter amount to withdraw: ";
                    std::cin >> amount;
                
                //Just in case, char or String is in user input
                if (std::cin.fail()) {
                    clearInput();
                    std::cout << "Invalid amount.\n";
                    continue; // Go back to the menu
                }

                    acc.withdraw(amount);
                    accFound = true;
                    break; // Stops loop
                }
            }
            if (!accFound) std::cout << "Account not found.\n";

        } else if (choice == 5) {
            std::cout << "Bye bye!\n";
        } else {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}
