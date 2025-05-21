#include "fileio.h"
#include <fstream>
#include <iostream>

using namespace std;

void FileIO::save(Account* head, const string& filename) {
    ofstream fout(filename, ios::binary | ios::out);
    if (!fout) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    while (head) {
        size_t name_len = head->name.length();
        size_t contact_len = head->contact.length();

        fout.write(reinterpret_cast<char*>(&head->acc_no), sizeof(head->acc_no));
        fout.write(reinterpret_cast<char*>(&name_len), sizeof(name_len));
        fout.write(head->name.c_str(), name_len);
        fout.write(reinterpret_cast<char*>(&contact_len), sizeof(contact_len));
        fout.write(head->contact.c_str(), contact_len);
        fout.write(reinterpret_cast<char*>(&head->balance), sizeof(head->balance));

        size_t txn_count = head->transactions.size();
        fout.write(reinterpret_cast<char*>(&txn_count), sizeof(txn_count));
        for (auto& txn : head->transactions) {
            fout.write(reinterpret_cast<char*>(&txn.id), sizeof(txn.id));
            fout.write(reinterpret_cast<char*>(&txn.type), sizeof(txn.type));
            fout.write(reinterpret_cast<char*>(&txn.amount), sizeof(txn.amount));
        }

        head = head->next;
    }

    fout.close();
    cout << "Accounts saved successfully.\n";
}

Account* FileIO::load(const string& filename) {
    ifstream fin(filename, ios::binary | ios::in);
    if (!fin) {
        cerr << "No previous data to load.\n";
        return nullptr;
    }

    Account* head = nullptr;

    while (fin.peek() != EOF) {
        unsigned int acc_no;
        string name, contact;
        size_t name_len, contact_len;
        double balance;

        fin.read(reinterpret_cast<char*>(&acc_no), sizeof(acc_no));
        fin.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
        name.resize(name_len);
        fin.read(&name[0], name_len);
        fin.read(reinterpret_cast<char*>(&contact_len), sizeof(contact_len));
        contact.resize(contact_len);
        fin.read(&contact[0], contact_len);
        fin.read(reinterpret_cast<char*>(&balance), sizeof(balance));

        Account* acc = new Account(name, contact);
        acc->acc_no = acc_no; // Override auto-gen
        acc->balance = balance;

        size_t txn_count;
        fin.read(reinterpret_cast<char*>(&txn_count), sizeof(txn_count));
        for (size_t i = 0; i < txn_count; ++i) {
            unsigned int id;
            TransactionType type;
            double amount;
            fin.read(reinterpret_cast<char*>(&id), sizeof(id));
            fin.read(reinterpret_cast<char*>(&type), sizeof(type));
            fin.read(reinterpret_cast<char*>(&amount), sizeof(amount));
            acc->transactions.emplace_back(id, type, amount);
        }

        acc->set_next(head);
        head = acc;
    }

    fin.close();
    cout << "Accounts loaded successfully.\n";
    return head;
}