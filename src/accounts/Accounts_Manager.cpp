#include "Accounts_Manager.h"
#include "database_module.h"  // Include DB module

// Constructor implementation for Accounts_Manager
Accounts_Manager::Accounts_Manager(int userId, DatabaseModule& db)
    : userId(userId), db(db) {}  // Initialize db in the initializer list


void Accounts_Manager::addAccount(const std::string& accountName, const std::string& accountType, double balance) {
    db.insertAccount(userId, accountName, accountType, balance);
}
void Accounts_Manager::updateAccountBalance(int accountId, double newBalance) {
    db.updateAccountBalance(accountId, newBalance);
}
std::vector<Account> Accounts_Manager::getAccounts() {
    accounts = db.getAccounts(userId);  // Fetch accounts from the database and store them in the accounts vector
    return accounts;
}
