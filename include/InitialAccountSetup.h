

/**
 * @file InitialAccountSetup.h
 * @brief This file defines the InitialAccountSetup class, which is responsible for setting up initial accounts for a budgeting application.
 */

/**
 * @class InitialAccountSetup
 * @brief This class allows the user to set up initial accounts with names, types, and balances.
 *
 * It provides functionality to add new accounts, retrieve a list of all accounts, and calculate the total balance across all accounts.
 */

/**
 * @brief Constructor for the InitialAccountSetup class.
 *
 * Initializes the accounts vector.
 */

/**
 * @brief Adds a new account to the list of accounts.
 *
 * @param accountName The name of the account (e.g., "Checking Account", "Savings Account").
 * @param accountType The type of the account (e.g., "Checking", "Savings", "Credit Card").
 * @param balance The initial balance of the account.
 *
 * @return void.  The function does not return a value.
 */

/**
 * @brief Retrieves the list of accounts.
 *
 * @return A constant reference to a vector of tuples, where each tuple contains the account name (std::string),
 *         account type (std::string), and balance (double).
 */

/**
 * @brief Calculates the total balance across all accounts.
 *
 * @return The sum of the balances of all accounts.
 */
#ifndef INITIAL_ACCOUNT_SETUP_H
#define INITIAL_ACCOUNT_SETUP_H



#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include "database_module.h"  // Include DB module


struct BudgetItem {
    std::string item;
    double amount;
};

struct Category {
    std::string name;
    double total_budget;
    std::vector<std::pair<std::string, double>> budgetItems;
    Category(const std::string& name, double budget, const std::vector<BudgetItem>& items)
    : name(name), total_budget(budget), budgetItems() {
        for (const auto& item : items) {
            budgetItems.emplace_back(item.item, item.amount);
        }
    }
};
class InitialAccountSetup{
    public: 
        InitialAccountSetup(int userId);
        void addAccount(const std::string& accountName, const std::string& accountType, double balance);
        const std::vector<std::tuple<std::string, std::string, double>>& getAccounts() const;
        double getTotalBalance() const;
        void addCategory(const std::string& categoryName, double budget, const std::vector<BudgetItem>& budgetItems);
        const std::vector<Category>& getCategories() const;
        double getTotalBudget() const;
        void saveToDatabase(DatabaseModule& db);

    private:
        int userId;
        std::vector<std::tuple<std::string, std::string,double>> accounts;
        std::vector<Category> categories;
// 

};
#endif // INITIAL_ACCOUNT_SETUP_H