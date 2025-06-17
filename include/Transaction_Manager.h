#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include "database_module.h"  // Include DB module
#include "accounts.h"  // Include Account struct

struct Transaction {
    int userId;
    std::string account_name;
    double amount;
    std::string category;
    std::string description;
};

class Transaction_Manager{
    public:
        Transaction_Manager(int userId, const std::string& account_name, double amount, const std::string& category, const std::string& description);
        void addTransaction(DatabaseModule& db);
        // void updateTransaction(int userId, const std::string& account_name, double amount, const std::string& category, const std::string& description);
        // void deleteTransaction(int transactionId);
    private:
        int userId;
        std::string account_name;
        double amount;
        std::string category;
        std::string description;
        
};
// Constructor for Transaction


#endif // TRANSACTION_H
