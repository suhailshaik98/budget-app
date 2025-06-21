/**
 * @file database_module.cpp
 * @brief Implementation of the DatabaseModule class for managing database connections and operations.
 *
 * This file contains the implementation of the DatabaseModule class, which provides functionality
 * for connecting to a PostgreSQL database, preparing SQL statements, and performing database
 * operations such as inserting users, accounts, and transactions. It uses the libpqxx library
 * for interacting with the PostgreSQL database.
 *
 * The DatabaseModule class is designed to be used as part of a larger application, such as a
 * budget management application. It connects to the database using a connection string provided
 * during initialization and prepares SQL statements for common operations. The class provides
 * methods for inserting data into the database, ensuring that the application can interact with
 * the database in a structured and reusable manner.
 *
 * Dependencies:
 * - database_module.h: The header file that declares the DatabaseModule class and its methods.
 * - libpqxx: A C++ library for interacting with PostgreSQL databases.
 *
 * Usage:
 * - Include "database_module.h" in the files where database operations are required.
 * - Create an instance of the DatabaseModule class, passing the database connection string.
 * - Call the `connect` method to establish a connection and prepare SQL statements.
 * - Use the provided methods (e.g., `insertUser`, `insertAccount`, `insertTransaction`) to
 *   perform database operations.
 *  You can find the examples of usage of functions in the header file `database_module.h`.
 *
 * Note:
 * - Ensure that the database schema matches the prepared SQL statements.
 * - Handle exceptions appropriately when using this class, as database operations may fail.
 */
#include "database_module.h"
#include <iostream>
#include <stdexcept>

DatabaseModule::DatabaseModule(const std::string& connStr)
    : connectionString(connStr){
}


pqxx::connection DatabaseModule::createConnection() const {
    return pqxx::connection(connectionString);
}
void DatabaseModule::connect(){
    try{
        auto conn = createConnection();
        // pqxx::connection conn(connectionString);

        if (!conn.is_open()){
            std::cerr << "Failed to open database connection." << std::endl;
            throw std::runtime_error("Connection to database failed.");
        } 
                std::cout << "Database connection successful." << std::endl;

    }catch (const std::exception& e) {
        std::cerr << "Error connecting to database: " << e.what() << std::endl;
        throw; // Re-throw the exception for further handling
    }
}

void DatabaseModule::insertUser(const std::string &username, const std::string& passwordHash, const std::string&email){
    try{
        auto conn = createConnection();
        pqxx::work txn(conn);
        conn.prepare("insert user",
            "INSERT INTO users (username, password_hash, email) VALUES ($1,$2,$3);");
        txn.exec_prepared("insert user", username, passwordHash, email);
        txn.commit();
        std::cout << "User inserted successfully." <<std::endl;
        
    }catch(const std::exception& e){
        std::cerr << "Error inserting user: " << e.what() << std::endl;
    }

}

void DatabaseModule::insertCategory(int userId, const std::string& categoryName, double budget, std::vector<std::pair<std::string, double>> budgetItems){
    try{
        auto conn = createConnection();
        pqxx::work txn(conn);
                    conn.prepare("insert category_returning_id",
                "INSERT INTO categories (user_id, category, budget) VALUES ($1,$2,$3) RETURNING category_id;");
        std::cout << "in database module Inserting category: " << categoryName << " with budget: " << budget << std::endl;
        for (const auto& item : budgetItems) {
            std::cout << "in database module Inserting budget item: " << item.first << " with amount: " << item.second << std::endl;
            // txn.exec_prepared("insert_budget_item", categoryId, item.first, item.second);
        }  
        pqxx::result r = txn.exec_prepared("insert category_returning_id", userId, categoryName, budget);
        if (r.size() == 0) {
            throw std::runtime_error("Failed to insert category.");
        }
        std::cout << "Category inserted successfully with name: " << categoryName << " and budget: " << budget << std::endl;
        int categoryId = r[0][0].as<int>();
        conn.prepare("insert_budget_item",
            "INSERT INTO budget_items (category_id, item_name, amount) VALUES ($1, $2, $3);");
        for (const auto& item : budgetItems) {
            std::cout << "Inserting budget item: " << item.first << " with amount: " << item.second << std::endl;
            txn.exec_prepared("insert_budget_item", categoryId, item.first, item.second);
        }
        // pqxx::result r = txn.exec_prepared("insert category_returning_id", userId, categoryName, budget);
        // If budgetItems are provided, insert them into the budget_items table
        txn.commit();
        std::cout<<"category inserted successfully."<<std::endl;
    }catch(const std::exception& e){
        std::cerr << "Error inserting category: " << e.what() << std::endl;
    }
}

void DatabaseModule::insertAccount(int userId, const std::string& accountName, const std::string& accountType, double balance){
    try{
        auto conn = createConnection();
        pqxx::work txn(conn);
        conn.prepare("insert account",
            "INSERT INTO accounts (user_id, account_name, account_type, balance) VALUES ($1,$2,$3,$4);");
        txn.exec_prepared("insert account",userId, accountName, accountType, balance);
        txn.commit();
        std::cout<<"Account inserted successfully."<<std::endl;
    }catch(const std::exception& e){
        std::cerr << "Error inserting account: " << e.what() << std::endl;
    }
}

void DatabaseModule::updateAccountBalance(int accountId, double newBalance) {
    try {
        auto conn = createConnection();
        pqxx::work txn(conn);
        conn.prepare("update_account_balance", "UPDATE accounts SET balance = $1 WHERE account_id = $2");
        txn.exec_prepared("update_account_balance", newBalance, accountId);
        txn.commit();
        std::cout << "Account balance updated successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error updating account balance: " << e.what() << std::endl;
    }
}

void DatabaseModule::insertTransaction(int userId, int accountId, double amount, const std::string& category, const std::string& description, const std::string& transactionDate){
    try{
        auto conn = createConnection();
        pqxx::work txn(conn);
        conn.prepare("insert_transaction",
            "INSERT INTO transactions (user_id, account_id, amount, budget_item, description, transaction_date) "
            "VALUES ($1, $2, $3, $4, $5, $6);");

            txn.exec_prepared("insert_transaction",
                              userId, accountId, amount, category, description, transactionDate);
        
        txn.commit();
        std::cout << "Transaction inserted successfully." << std::endl;
    }catch(const std::exception& e){
        std::cerr << "Error inserting transaction: " << e.what() << std::endl;
    }
}

std::vector<std::string> DatabaseModule::getOnlyCategories(int userId){
    std::vector<std:: string> categoryNames;
    try{
        auto conn = createConnection();
        pqxx::work txn(conn);
        conn.prepare("get_categories",
            "SELECT category FROM categories WHERE user_id = $1;");
        pqxx::result r = txn.exec_prepared("get_categories", userId);
        for (const auto&row :r){
            categoryNames.push_back(row[0].as<std::string>());
        }
        txn.commit();
        std::cout << "Categories retrieved successfully." << std::endl;

    }catch(const std::exception& e){
        std::cerr << "Error retrieving categories: "<< e.what() << std::endl;
    }
    return categoryNames;
}

std::vector<Account> DatabaseModule::getAccounts(int userId){
    std::vector<Account> accountNames;
    try{
        auto conn = createConnection();
        pqxx::work txn(conn);
        conn.prepare("get_account_info",
            "SELECT account_id, account_name, balance, account_type FROM accounts WHERE user_id = $1;");
        pqxx::result r = txn.exec_prepared("get_account_info", userId);
        for (const auto& row : r){
            Account account;
            account.account_id = row[0].as<int>();
            account.account_name = row[1].as<std::string>();
            account.balance = row[2].as<double>();
            account.account_type = row[3].as<std::string>();
            accountNames.push_back(account);
        }
        txn.commit();
        std::cout << "Accounts retrieved successfully." << std::endl;

    }catch(const std::exception& e){
        std::cerr << "Error retrieving accounts: "<< e.what() << std::endl;
    }
    return accountNames;
}

std::vector<std::tuple<std::string,std::string ,double, int>> DatabaseModule::getBudgetItemsforUser(int userId) {
    // This function retrieves budget items for a specific user.
    // It returns a vector of tuples, where each tuple contains the item name, its amount, and the category ID.
    std::vector<std::tuple<std::string, std::string, double, int>> budgetItems;
    try {
        auto conn = createConnection();
        pqxx::work txn(conn);
        conn.prepare("get_budget_items_by_user",
            "SELECT bi.item_name, c.category, bi.amount, bi.id "
            "FROM budget_items bi "
            "JOIN categories c ON bi.category_id = c.category_id "
            "WHERE c.user_id = $1;");
        pqxx::result r = txn.exec_prepared("get_budget_items_by_user", userId);
        for (const auto& row : r) {
            budgetItems.emplace_back(row[0].as<std::string>(), row[1].as<std::string>(), row[2].as<double>(), row[3].as<int>());
        }
        txn.commit();
        std::cout << "Budget items retrieved successfully for user " << userId << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error retrieving budget items: " << e.what() << std::endl;
    }
    return budgetItems;
}
const std::vector<Transaction> &DatabaseModule::getTimedTransactions(int userId, std::string &start_date, std::string &end_date){
    std::vector<Transaction> transactions_result; 
    try{
        auto conn= createConnection();
        pqxx::work txn(conn);
        conn.prepare("get_timed_transactions_for_user",
            "SELECT * FROM transactions"
            "WHERE user_id $1"
            "AND transaction_date between $2 and $3"
        );
        pqxx::result r = txn.exec_prepared("get_timed_transactions_for_user",userId,start_date,end_date);
        for (const auto&row: r){
            Transaction transaction;
            transaction.transaction_id = row[0].as<int>();
            transaction.account_id = row[4].as<int>();
            transaction.amount = row[2].as<double>();
            transaction.description = row[3].as<std::string>();
            transaction.date = row[4].as<std::string>();
            transaction.budget_item = row[5].as<std::string>();
            transactions_result.push_back(transaction);
        }   
        txn.commit();

    }catch(const std::exception& e){
        std::cerr << "Error retrieving timed transactions for the user "<< e.what() << std::endl;
    }
    return transactions_result;


}