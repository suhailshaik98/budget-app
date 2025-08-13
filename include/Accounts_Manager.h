#ifndef ACCOUNTS_MANAGER_H
#define ACCOUNTS_MANAGER_H
#include "database_module.h"  // Include DB module
#include "accounts.h"  // Include Account struct

class Accounts_Manager {
public:
    Accounts_Manager(int userId, DatabaseModule& db);
    // Constructor to initialize Accounts_Manager with userId and DatabaseModule reference
    // This constructor initializes the Accounts_Manager with a user ID and a reference to the DatabaseModule.
    // It sets the userId and initializes the accounts vector.
    // The userId is used to identify the user for whom accounts are managed, and the DatabaseModule is used for database operations.
    // The accounts vector is initialized to an empty state, ready to be populated with account data.
    // The DatabaseModule reference is used to perform database operations related to accounts.
    // This constructor initializes the Accounts_Manager with a user ID and a reference to the DatabaseModule.
    // It sets the userId and initializes the accounts vector.
    // ~Accounts_Manager();  // Destructor to clean up resources
    void addAccount(const std::string& accountName, const std::string& accountType, double balance = 0.0);
    void updateAccountBalance(int accountId, double newBalance) ;

    std::vector<Account> getAccounts();
private:
    int userId;
    DatabaseModule& db;
    std::vector<Account> accounts;  // Cache for accounts
};

#endif

