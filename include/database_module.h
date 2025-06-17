// The DatabaseModule class provides an interface for interacting with a PostgreSQL database.
// It uses the pqxx library to manage database connections and execute queries.
// Example usage in another module:

/*
#include "database_module.h"

int main() {
    try {
        // Initialize the DatabaseModule with a connection string
        DatabaseModule db("dbname=mydb user=myuser password=mypassword hostaddr=127.0.0.1 port=5432");

        // Connect to the database
        db.connect();

        // Insert a new user
        db.insertUser("john_doe", "hashed_password", "john@example.com");

        // Insert a new account for the user
        db.insertAccount(1, "Savings Account", "Savings", 1000.0);

        // Insert a new transaction for the user's account
        db.insertTransaction(1, 1, -200.0, "Groceries", "Bought groceries", "2023-01-01");

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
*/


#ifndef DATABASE_MODULE_H
#define DATABASE_MODULE_H

#include <pqxx/pqxx>
#include <string>
#include<vector>

class DatabaseModule {
    public:

        DatabaseModule(const std::string& connStr);
        ~DatabaseModule();

        void connect();
        void insertUser(const std::string& username, const std::string& passwordHash, const std::string& email);
        void insertAccount(int userId, const std::string& accountName, const std::string& accountType, double balance=0.0);
        void insertCategory(int userId, const std::string& categoryName, double budget=0.0, 
            std::vector<std::pair<std::string, double>> budgetItems = {});
        void updateAccountBalance(int accountId, double newBalance);
        void insertTransaction(int userId, int accountId, double amount, const std::string& category, 
            const std::string& description, const std::string& transactionDate = "");
        std::vector<std::string> getOnlyCategories(int userId);
        std::vector<Account> getAccounts(int userId);
    private:
        std:: string connectionString;
        pqxx::connection* connection;
};
#endif // DATABASE_MODULE_H

