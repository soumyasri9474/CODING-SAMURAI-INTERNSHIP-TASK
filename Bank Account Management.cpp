#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountHolder;
    double balance;

public:
    BankAccount(string name, double initialBalance) {
        accountHolder = name;
        balance = initialBalance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrew: $" << amount << endl;
        } else {
            cout << (amount > balance ? "Insufficient funds." : "Invalid withdrawal amount.") << endl;
        }
    }

    void checkBalance() const {
        cout << "Current balance: $" << balance << endl;
    }

    void transfer(BankAccount &toAccount, double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            toAccount.deposit(amount);
            cout << "Transferred: $" << amount << " to " << toAccount.getAccountHolder() << endl;
        } else {
            cout << (amount > balance ? "Insufficient funds for transfer." : "Invalid transfer amount.") << endl;
        }
    }

    string getAccountHolder() const {
        return accountHolder;
    }
};

int main() {
    // Create two accounts
    BankAccount account1("Alice", 1000.0);
    BankAccount account2("Bob", 500.0);

    int choice;
    double amount;

    cout << "Welcome to the Basic Banking System" << endl;

    while (true) {
        cout << "\nSelect an option:\n";
        cout << "1. Deposit\n2. Withdraw\n3. Check Balance\n4. Transfer Funds\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter amount to deposit: ";
            cin >> amount;
            account1.deposit(amount);
            break;
        case 2:
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            account1.withdraw(amount);
            break;
        case 3:
            account1.checkBalance();
            break;
        case 4:
            cout << "Enter amount to transfer to Bob: ";
            cin >> amount;
            account1.transfer(account2, amount);
            break;
        case 5:
            cout << "Exiting the system. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
