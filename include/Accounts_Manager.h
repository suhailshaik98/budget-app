#ifdef ACCOUNTS_MANAGER_H
#define ACCOUNTS_MANAGER_H
#include "database_module.h"  // Include DB module
#include "accounts.h"  // Include Account struct

class Accounts_Manager {
public:
    Accounts_Manager(int userId, DatabaseModule& db) : userId(userId), db(db) {}

    void addAccount(const std::string& accountName, const std::string& accountType, double balance = 0.0) {
        db.insertAccount(userId, accountName, accountType, balance);
    }

    void updateAccountBalance(int accountId, double newBalance) {
        db.updateAccountBalance(accountId, newBalance);
    }

    std::vector<Account> getAccounts() {
        return db.getAccounts(userId);
    }
};

#endif

