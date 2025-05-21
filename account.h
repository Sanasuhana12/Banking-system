#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

enum class TransactionType { DEPOSIT, WITHDRAW };

class Transaction {
public:
    unsigned int id;
    TransactionType type;
    double amount;

    Transaction(unsigned int id, TransactionType type, double amt)
        : id(id), type(type), amount(amt) {}
};

class Account {
private:
    static unsigned int cnt;
    unsigned int acc_no;
    std::string name;
    std::string contact;
    double balance;
    std::vector<Transaction> transactions;
    Account* next;

public:
    Account(const std::string& name, const std::string& contact);

    unsigned int get_acc_no() const;
    const std::string& get_name() const;
    double get_balance() const;
    Account* get_next() const;
    void set_next(Account* n);

    void deposit(double amount);
    void withdraw(double amount);
    void transfer_to(Account* other, double amount);
    void print_transactions(int recent = 5) const;
    void display() const;

    const std::vector<Transaction>& get_transactions() const;
    const std::string& get_contact() const;

    friend class FileIO;
};

Account* find_account(Account* head, unsigned int acc_no);
bool is_duplicate(Account* head, unsigned int acc_no);
void display_all(Account* head);

#endif