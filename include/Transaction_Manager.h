#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include "database_module.h"  // Include DB module
#include "accounts.h"  // Include Account struct


class Transaction_Manager{
    public:
        Transaction_Manager(int userId, const std::string& account_name, double amount, const std::string& category, const std::string& budget_item_name, const std::string& description, const std::string& transactionDate);
        void addTransaction(DatabaseModule& db);
        void updateTransaction(int userId, const std::string& account_name, double amount, const std::string& category, const std::string& description);
        void deleteTransaction(int transactionId);
        const std::vector<Transaction>& getTimedTransactions(int userId, const std::string& start_date, const std::string& end_date);
        const std::vector<Transaction>& getAllTransactions(int userId);
    private:
        int userId;
        std::string account_name;
        double amount;
        std::string category;
        std::string budget_item_name;
        std::string description;
        std::string transactionDate;  // Store the transaction date if provided
        
};
// Constructor for Transaction


#endif // TRANSACTION_H
