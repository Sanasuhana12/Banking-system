# Banking-system
-------------------------------
PROJECT OVERVIEW
-------------------------------
This is a basic Banking Management System built using C++ classes.
It lets users create bank accounts, deposit and withdraw money, transfer funds, check balance, view last 5 transactions, and more.

All data is saved in a file so you don’t lose anything after closing the app.

-------------------------------
FEATURES
-------------------------------
- Auto-generated account number
- Create a new account
- Deposit money
- Withdraw money
- Balance enquiry
- Transfer money to another account
- Show last 5 transactions (history)
- View all accounts
- Save/load account data from file

-------------------------------
FILES USED
-------------------------------
1. `Account.h`       – contains the Account class
2. `Account.cpp`     – defines all functions of the Account class
3. `FileIO.h`        – header for file operations
4. `FileIO.cpp`      – handles saving/loading accounts to/from file
5. `accountapp.cpp`  – the main file with menu and logic
6. `accounts.dat`    – binary file where all account info is saved
7. `README.txt`      – this file :)

-------------------------------
HOW TO COMPILE & RUN
-------------------------------
Using g++:

g++ -std=c++17 account.cpp fileio.cpp accountapp.cpp -o banking_app ./banking_app

Or if you have a Makefile:

make ./banking_app


-------------------------------
EXTRA INFO
-------------------------------
- It uses a singly linked list to store multiple accounts in memory.
- Transactions are stored as objects (with ID, type, amount).
- Each account keeps track of its last 5 transactions.
- The account number is generated automatically using a static counter.
- All accounts are saved in a file called `accounts.dat`.

-------------------------------
WHAT CAN BE IMPROVED?
-------------------------------
- Adding a login system using account number + PIN
- Deleting accounts feature

Thank you for checking out my project!
