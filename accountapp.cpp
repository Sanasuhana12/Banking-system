#include "account.h"
//#include "account.cpp"
#include "fileio.h"
//#include "fileio.cpp"
#include <iostream>

using namespace std;

int main() {
    Account* head = FileIO::load("accounts.dat");
    char choice;

    do {
        cout << "\n--- MENU ---\n";
        cout << "c: Create account\nh: History\nw: Withdraw\nd: Deposit\nb: Balance\nt: Transfer\ne: Show all\ns: Save\nf: Find\nq: Quit\n";
        cin >> choice;
        switch (choice) {
            case 'c': {
                string name, contact;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Contact: ";
                getline(cin, contact);
                Account* acc = new Account(name, contact);
                acc->set_next(head);
                head = acc;
                cout << "Account created. Account No: " << acc->get_acc_no() << endl;
                break;
            }
            case 'h': {
                unsigned int no;
                cout << "Enter Account No: ";
                cin >> no;
                if (Account* acc = find_account(head, no))
                    acc->print_transactions();
                break;
            }
            case 'w': {
                unsigned int no;
                double amt;
                cout << "Enter Account No and Amount: ";
                cin >> no >> amt;
                if (Account* acc = find_account(head, no))
                    acc->withdraw(amt);
                break;
            }
            case 'd': {
                unsigned int no;
                double amt;
                cout << "Enter Account No and Amount: ";
                cin >> no >> amt;
                if (Account* acc = find_account(head, no))
                    acc->deposit(amt);
                break;
            }
            case 'b': {
                unsigned int no;
                cout << "Enter Account No: ";
                cin >> no;
                if (Account* acc = find_account(head, no))
                    cout << "Balance: " << acc->get_balance() << endl;
                break;
            }
            case 't': {
                unsigned int from, to;
                double amt;
                cout << "From Account No: "; cin >> from;
                cout << "To Account No: "; cin >> to;
                cout << "Amount: "; cin >> amt;
                Account* acc1 = find_account(head, from);
                Account* acc2 = find_account(head, to);
                if (acc1 && acc2) acc1->transfer_to(acc2, amt);
                break;
            }
            case 'e': display_all(head); break;
            case 'f': {
                unsigned int no;
                cout << "Enter Account No: ";
                cin >> no;
                find_account(head, no);
                break;
            }
            case 's': FileIO::save(head, "accounts.dat"); break;
            case 'q': cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 'q');

    return 0;
}