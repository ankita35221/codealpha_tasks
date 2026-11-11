#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class Transaction {
private:
    string type;
    double amount;
    string details;

public:
    Transaction(string transactionType, double transactionAmount, string info)
        : type(transactionType), amount(transactionAmount), details(info) {}

    void display() const {
        cout << left << setw(15) << type
             << setw(12) << fixed << setprecision(2) << amount
             << details << '\n';
    }
};

class Customer {
private:
    int customerId;
    string name;

public:
    Customer(int id, string customerName) : customerId(id), name(customerName) {}

    int getId() const { return customerId; }
    string getName() const { return name; }

    void display() const {
        cout << "Customer ID: " << customerId << "\nCustomer Name: " << name << '\n';
    }
};

class Account {
private:
    int accountNumber;
    int customerId;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int number, int ownerId)
        : accountNumber(number), customerId(ownerId), balance(0.0) {}

    int getAccountNumber() const { return accountNumber; }
    int getCustomerId() const { return customerId; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Amount must be greater than zero.\n";
            return;
        }
        balance += amount;
        transactions.emplace_back("Deposit", amount, "Cash deposited");
        cout << "Deposit successful.\n";
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Amount must be greater than zero.\n";
            return false;
        }
        if (amount > balance) {
            cout << "Insufficient balance.\n";
            return false;
        }
        balance -= amount;
        transactions.emplace_back("Withdrawal", amount, "Cash withdrawn");
        cout << "Withdrawal successful.\n";
        return true;
    }

    bool transferTo(Account& receiver, double amount) {
        if (amount <= 0) {
            cout << "Amount must be greater than zero.\n";
            return false;
        }
        if (accountNumber == receiver.accountNumber) {
            cout << "Cannot transfer money to the same account.\n";
            return false;
        }
        if (amount > balance) {
            cout << "Insufficient balance.\n";
            return false;
        }

        balance -= amount;
        receiver.balance += amount;
        transactions.emplace_back("Transfer out", amount,
                                  "To account " + to_string(receiver.accountNumber));
        receiver.transactions.emplace_back("Transfer in", amount,
                                           "From account " + to_string(accountNumber));
        cout << "Transfer successful.\n";
        return true;
    }

    void displayDetails(const Customer& customer) const {
        customer.display();
        cout << "Account Number: " << accountNumber
             << "\nCurrent Balance: Rs. " << fixed << setprecision(2) << balance << '\n';
    }

    void displayRecentTransactions() const {
        cout << "\nRecent transactions (latest first):\n";
        cout << left << setw(15) << "Type" << setw(12) << "Amount" << "Details\n";
        if (transactions.empty()) {
            cout << "No transactions yet.\n";
            return;
        }

        int shown = 0;
        for (int i = static_cast<int>(transactions.size()) - 1;
             i >= 0 && shown < 5; i--, shown++) {
            transactions[i].display();
        }
    }
};

int findAccountIndex(const vector<Account>& accounts, int accountNumber) {
    for (int i = 0; i < static_cast<int>(accounts.size()); i++) {
        if (accounts[i].getAccountNumber() == accountNumber)
            return i;
    }
    return -1;
}

int findCustomerIndex(const vector<Customer>& customers, int customerId) {
    for (int i = 0; i < static_cast<int>(customers.size()); i++) {
        if (customers[i].getId() == customerId)
            return i;
    }
    return -1;
}

int main() {
    vector<Customer> customers;
    vector<Account> accounts;
    int nextCustomerId = 1001;
    int nextAccountNumber = 5001;
    int choice;

    do {
        cout << "\n========== BANKING SYSTEM ==========\n";
        cout << "1. Create customer and account\n";
        cout << "2. Deposit money\n";
        cout << "3. Withdraw money\n";
        cout << "4. Transfer money\n";
        cout << "5. View account information\n";
        cout << "6. View recent transactions\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Please enter a valid menu number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            string name;
            cout << "Enter customer name (use _ instead of spaces): ";
            cin >> name;

            customers.emplace_back(nextCustomerId, name);
            accounts.emplace_back(nextAccountNumber, nextCustomerId);

            cout << "\nCustomer and account created successfully.\n";
            cout << "Customer ID: " << nextCustomerId
                 << "\nAccount Number: " << nextAccountNumber << '\n';
            nextCustomerId++;
            nextAccountNumber++;
        }
        else if (choice >= 2 && choice <= 6) {
            int accountNumber;
            cout << "Enter account number: ";
            cin >> accountNumber;

            int index = findAccountIndex(accounts, accountNumber);
            if (index == -1) {
                cout << "Account not found. Please create an account first.\n";
                continue;
            }

            if (choice == 2) {
                double amount;
                cout << "Enter deposit amount: Rs. ";
                cin >> amount;
                accounts[index].deposit(amount);
            }
            else if (choice == 3) {
                double amount;
                cout << "Enter withdrawal amount: Rs. ";
                cin >> amount;
                accounts[index].withdraw(amount);
            }
            else if (choice == 4) {
                int receiverNumber;
                double amount;
                cout << "Enter receiver account number: ";
                cin >> receiverNumber;
                int receiverIndex = findAccountIndex(accounts, receiverNumber);
                if (receiverIndex == -1) {
                    cout << "Receiver account not found.\n";
                    continue;
                }
                cout << "Enter transfer amount: Rs. ";
                cin >> amount;
                accounts[index].transferTo(accounts[receiverIndex], amount);
            }
            else if (choice == 5) {
                int customerIndex = findCustomerIndex(
                    customers, accounts[index].getCustomerId());
                if (customerIndex != -1)
                    accounts[index].displayDetails(customers[customerIndex]);
            }
            else if (choice == 6) {
                accounts[index].displayRecentTransactions();
            }
        }
        else if (choice == 7) {
            cout << "Thank you for using the Banking System.\n";
        }
        else {
            cout << "Invalid choice. Please select 1 to 7.\n";
        }

    } while (choice != 7);

    return 0;
}
