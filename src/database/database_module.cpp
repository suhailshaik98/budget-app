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
        connection-> prepare("insert transaction",
            "INSERT INTO transactions (user_id, account_id, amount, category, description, transaction_date) VALUES ($1,$2,$3,$4,$5,COALESCE($6, CURRENT_DATE));");
        connection->prepare("update_account_balance", "UPDATE accounts SET balance = $1 WHERE account_id = $2");
            std::cout << "Database connected and statments prepared."<<std::endl;
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