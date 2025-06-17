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
    : connectionString(connStr), connection(nullptr) {
}

DatabaseModule::~DatabaseModule(){
    if (connection){
        // Resetting the connection object to close the connection
        delete connection;
    }
}
void DatabaseModule::connect(){
    try{
        connection = new pqxx::connection(connectionString);
        if (!connection->is_open()){
            
            throw std::runtime_error("Connection to database failed.");
        } 
        connection -> prepare("insert user",
            "INSERT INTO users (username, password_hash, email) VALUES ($1,$2,$3);");
        connection -> prepare("insert account",
            "INSERT INTO accounts (user_id, account_name, account_type, balance) VALUES ($1,$2,$3,$4);");
            connection -> prepare("insert category_returning_id",
                "INSERT INTO categories (user_id, category, budget) VALUES ($1,$2,$3) RETURNING category_id;");
        connection-> prepare("insert transaction",
            "INSERT INTO transactions (user_id, account_id, amount, category, description, transaction_date) VALUES ($1,$2,$3,$4,$5,COALESCE($6, CURRENT_DATE));");
        connection->prepare("update_account_balance", "UPDATE accounts SET balance = $1 WHERE account_id = $2");
            std::cout << "Database connected and statments prepared."<<std::endl;
        connection->prepare("insert_budget_item",
            "INSERT INTO budget_items (category_id, item_name, amount) VALUES ($1, $2, $3);");

        // Get the data from the database
        // Get transaction for the user
        // Get categories for the user
        connection->prepare("get_only_categories",
            "SELECT category FROM categories WHERE user_id = $1;");
        // Get accounts for the user
        connection->prepare("get_account_info",
            "SELECT account_id, account_name, balance, account_type FROM accounts WHERE user_id = $1;");
    }catch (const std::exception& e) {
        std::cerr << "Error connecting to database: " << e.what() << std::endl;
        throw; // Re-throw the exception for further handling
    }
}

void DatabaseModule::insertUser(const std::string &username, const std::string& passwordHash, const std::string&email){
    try{
        pqxx::work txn(*connection);
        txn.exec_prepared("insert user", username, passwordHash, email);
        txn.commit();
        std::cout << "User inserted successfully." <<std::endl;
        
    }catch(const std::exception& e){
        std::cerr << "Error inserting user: " << e.what() << std::endl;
    }

}

void DatabaseModule::insertCategory(int userId, const std::string& categoryName, double budget, std::vector<std::pair<std::string, double>> budgetItems){
    try{
        pqxx::work txn(*connection);
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
        pqxx::work txn(*connection);
        txn.exec_prepared("insert account",userId, accountName, accountType, balance);
        txn.commit();
        std::cout<<"Account inserted successfully."<<std::endl;
    }catch(const std::exception& e){
        std::cerr << "Error inserting account: " << e.what() << std::endl;
    }
}

void DatabaseModule::updateAccountBalance(int accountId, double newBalance) {
    try {
        pqxx::work txn(*connection);
        txn.exec_prepared("update account balance", newBalance, accountId);
        txn.commit();
        std::cout << "Account balance updated successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error updating account balance: " << e.what() << std::endl;
    }
}

void DatabaseModule::insertTransaction(int userId, int accountId, double amount, const std::string& category, const std::string& description, const std::string& transactionDate){
    try{
        pqxx::work txn(*connection);
        txn.exec_prepared("insert transaction", userId, accountId, amount, category, description, transactionDate);
        txn.commit();
        std::cout << "Transaction inserted successfully." << std::endl;
    }catch(const std::exception& e){
        std::cerr << "Error inserting transaction: " << e.what() << std::endl;
    }
}

std::vector<std::string> DatabaseModule::getOnlyCategories(int userId){
    std::vector<std:: string> categoryNames;
    try{
        pqxx::work txn(*connection);
        pqxx::result r = txn.exec_prepared("get_only_categories", userId);
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
        pqxx::work txn(*connection);
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