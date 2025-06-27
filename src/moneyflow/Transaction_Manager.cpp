#include "Transaction_Manager.h"
#include <iostream>
#include "database_module.h"  // Include DB module
Transaction_Manager::Transaction_Manager(int userId,
    const std::string& account_name,
    double amount,
    const std::string& category,
    const std::string& budget_item_name,
    const std::string& description,
    const std::string& transactionDate)
{
this->userId = userId;
this->account_name = account_name;
this->amount = amount;
this->category = category;
this->budget_item_name = budget_item_name;
this->description = description;
this->transactionDate = transactionDate;
}
Transaction_Manager::Transaction_Manager(int userId) {
    // Initialize the transaction with the provided parameters
    // This constructor can be used to set up a transaction object before adding it to the database
    this->userId = userId;
    this->account_name = "";
    this->amount = 0.0;
    this->category = "";
    this->budget_item_name = "";
    this->description = "";
    this->transactionDate = "";  // Store the transaction date if provided
}


void Transaction_Manager::addTransaction(DatabaseModule& db) {
    std::cout << "Attempting to add transaction for user ID: " << userId << std::endl;
    std::string error = "";
    int matched_account_id = -1; // Default if not found
    std::string usr_account_type = ""; // Default if not found

    try{
        std::vector<std::string> categories = db.getOnlyCategories(userId);
        if (std::find(categories.begin(), categories.end(), category) == categories.end()) {
            std::cerr << "Category '" << category << "' does not exist for user ID: " << userId << std::endl;
            error = "Category " + category + " does not exist.";
            throw std::runtime_error("Category does not exist.");
            // return;
        }else {
            std::cout << "Category '" << category << "' exists for user ID: " << userId << std::endl;
        }
        
        std::vector<Account> accounts = db.getAccounts(userId);
        auto it = std::find_if(accounts.begin(), accounts.end(), [&](const Account& acc) {
            return acc.account_name == account_name;
        });
        
        int usr_account_id = -1; // Default if not found
        double usr_balance = -500;
        std::string usr_account_type = "";
        if (it == accounts.end()) {
            std::cerr << "Account '" << account_name << "' does not exist for user ID: " << userId << std::endl;
            error = "Account " + account_name + " does not exist.";
            throw std::runtime_error("Account does not exist.");
        } else {
            usr_account_id = it->account_id;  // <- Assigning account_id here
            usr_balance = it->balance;  // <- Assigning balance here
            usr_account_type = it->account_type;  // <- Assigning account_type here
            std::cout << "Account '" << account_name << "' exists for user ID: " << userId
                      << " with account ID: " << usr_account_id << " and balance: " << usr_balance << std::endl;
            if (usr_account_type == "Credit Card") {
                usr_balance += amount; // Update balance with the transaction amount
            } else {
                usr_balance -= amount; // Update balance with the transaction amount
            }
            db.updateAccountBalance(usr_account_id, usr_balance);
            db.insertTransaction(userId, usr_account_id, amount, budget_item_name, description, transactionDate);
        }

        // std::cout << "Transaction added successfully for user ID: " << userId << std::endl;
     
        
        
    }catch (const std::exception& e) {
        std::cerr << "Error adding transaction: " << e.what() << std::endl;
        throw std::runtime_error("Error adding transaction: " + error);

    }
}

std::vector<Transaction> Transaction_Manager::getTimedTransactions(
    const std::string& start_date,
    const std::string& end_date,
    DatabaseModule& db) 
{
    try {
        std::cout << "at the class transaction manager the Timed Transactions" << std::endl;

        std::vector<Transaction> result = db.getTimedTransactions(userId, start_date, end_date);
        std::cout << "returning from class transaction manager the Timed Transactions" << std::endl;
        return result;  // ✅ returning by value (safe)
    } catch (const std::exception& e) {
        std::cerr << "Error query on timed transactions failed: " << e.what() << std::endl;
        return {};  // return empty vector
    }
}


