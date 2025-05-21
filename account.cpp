#include "account.h"
#include <iostream>
#include <cstdlib>

using namespace std;

unsigned int Account::cnt = 1000;

Account::Account(const string& name, const string& contact)
    : acc_no(cnt++), name(name), contact(contact), balance(0.0), next(nullptr) {}

unsigned int Account::get_acc_no() const { return acc_no; }
const string& Account::get_name() const { return name; }
double Account::get_balance() const { return balance; }
Account* Account::get_next() const { return next; }
void Account::set_next(Account* n) { next = n; }

void Account::deposit(double amount) {
    balance += amount;
    transactions.emplace_back(rand(), TransactionType::DEPOSIT, amount);
    cout << "Deposited successfully.\n";
}

void Account::withdraw(double amount) {
    if (balance >= amount) {
        balance -= amount;
        transactions.emplace_back(rand(), TransactionType::WITHDRAW, amount);
        cout << "Withdrawn successfully.\n";
    } else {
        cout << "Insufficient balance.\n";
    }
}

void Account::transfer_to(Account* other, double amount) {
    if (balance >= amount && other) {
        balance -= amount;
        other->balance += amount;
        transactions.emplace_back(rand(), TransactionType::WITHDRAW, amount);
        other->transactions.emplace_back(rand(), TransactionType::DEPOSIT, amount);
        cout << "Transfer successful.\n";
    } else {
        cout << "Transfer failed.\n";
    }
}

void Account::print_transactions(int recent) const {
    int count = 0;
    for (int i = transactions.size() - 1; i >= 0 && count < recent; --i, ++count) {
        cout << (transactions[i].type == TransactionType::DEPOSIT ? "Deposit" : "Withdraw")
             << ": " << transactions[i].amount << endl;
    }
}
 void Account::display() const {
    cout << "Acc No: " << acc_no << " | Name: " << name << " | Balance: " << balance << endl;
}

Account* find_account(Account* head, unsigned int acc_no) {
    while (head) {
        if (head->get_acc_no() == acc_no)
        {
                cout << "Account found:\n";
                head->display();
                return head;
        }
        head = head->get_next();
    }
    cout << "Account not found.\n";
    return nullptr;
}

bool is_duplicate(Account* head, unsigned int acc_no) {
    return find_account(head, acc_no) != nullptr;
}

void display_all(Account* head) {
    while (head) {
        head->display();
        head = head->get_next();
    }