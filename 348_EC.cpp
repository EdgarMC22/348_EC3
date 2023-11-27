#include <iostream>
#include <iomanip>

class Account {
protected:
    std::string accountNumber;
    std::string accountHolder;
    double balance;

public:
    Account(const std::string& number, const std::string& holder, double initialBalance)
        : accountNumber(number), accountHolder(holder), balance(initialBalance) {}

    void displayDetails() const {
        std::cout << "Account Details for Account (ID: " << accountNumber << "):\n"
                  << "   Holder: " << accountHolder << "\n"
                  << "   Balance: $" << std::fixed << std::setprecision(2) << balance << "\n";
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited $" << amount << " into the account.\n";
        } else {
            std::cout << "Invalid deposit amount.\n";
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            std::cout << "Withdrawn $" << amount << " from the account.\n";
        } else {
            std::cout << "Invalid withdrawal amount or insufficient balance.\n";
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Account& account) {
        os << "Account Details for Account (ID: " << account.accountNumber << "):\n"
           << "   Holder: " << account.accountHolder << "\n"
           << "   Balance: $" << std::fixed << std::setprecision(2) << account.balance << "\n";
        return os;
    }

    void transferTo(Account& toAccount, double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            toAccount.balance += amount;
            std::cout << "Transferred $" << amount << " from Account (ID: " << accountNumber
                      << ") to Account (ID: " << toAccount.accountNumber << ").\n";
        } else {
            std::cout << "Invalid transfer amount or insufficient balance.\n";
        }
    }
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(const std::string& number, const std::string& holder, double initialBalance, double rate)
        : Account(number, holder, initialBalance), interestRate(rate) {}

    void displayDetails() const {
        std::cout << "Account Details for Savings Account (ID: " << accountNumber << "):\n"
                  << "   Holder: " << accountHolder << "\n"
                  << "   Balance: $" << std::fixed << std::setprecision(2) << balance << "\n"
                  << "   Interest Rate: " << std::fixed << std::setprecision(2) << (interestRate * 100) << "%\n";
    }

    void withdraw(double amount) {
        if (amount > 0 && balance - amount >= 100) {
            balance -= amount;
            std::cout << "Withdrawn $" << amount << " from the Savings Account.\n";
        } else {
            std::cout << "Invalid withdrawal amount or minimum balance requirement not met.\n";
        }
    }
};

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(const std::string& number, const std::string& holder, double initialBalance, double limit)
        : Account(number, holder, initialBalance), overdraftLimit(limit) {}

    void displayDetails() const {
        std::cout << "Account Details for Current Account (ID: " << accountNumber << "):\n"
                  << "   Holder: " << accountHolder << "\n"
                  << "   Balance: $" << std::fixed << std::setprecision(2) << balance << "\n"
                  << "   Overdraft Limit: $" << std::fixed << std::setprecision(2) << overdraftLimit << "\n";
    }

    void withdraw(double amount) {
        if (amount > 0 && balance + overdraftLimit >= amount) {
            balance -= amount;
            std::cout << "Withdrawn $" << amount << " from the Current Account.\n";
        } else {
            std::cout << "Invalid withdrawal amount or overdraft limit exceeded.\n";
        }
    }
};

int main() {
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    savings.displayDetails();
    current.displayDetails();

    savings.deposit(500);
    current.withdraw(1000);

    savings.displayDetails();
    current.displayDetails();

    // Transfer 300 from savings to current
    savings.transferTo(current, 300);

    savings.displayDetails();
    current.displayDetails();

    return 0;
}
