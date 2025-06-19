#include "crow.h"
#include "InitialAccountSetup.h"
#include "crow/middlewares/cors.h"
#include "database_module.h"
#include "Transaction_Manager.h"
#include "Accounts_Manager.h"
#include "Category_Manager.h"
// #include "../include/Accounts_Manager.h"
DatabaseModule db("host=localhost port=5432 dbname=budgetappdb user=budgetuser password=bUdgeTPa$$");

int main(){
    crow::App<crow::CORSHandler> app;  // <-- include middleware here
    db.connect();
    auto& cors = app.get_middleware<crow::CORSHandler>();

    cors
      .global()
        .origin("*")
        .methods("GET"_method, "POST"_method, "OPTIONS"_method)
        .headers("Content-Type");

    CROW_ROUTE(app, "/setup-initial")
    .methods(crow::HTTPMethod::POST)
    ([](const crow::request& req) {
        std::cout << "Received request: " << req.body << std::endl;

        auto body_json = crow::json::load(req.body);
        if (!body_json) {
            return crow::response(400, "Invalid JSON.");
        }

        if (!body_json.has("user_id") || !body_json.has("accounts") || !body_json.has("categories")) {
            return crow::response(400, "Missing one of: user_id, accounts, or categories.");
        }else{
            std::cout << "Parsed JSON: " << body_json << std::endl;
        }

        int userId = body_json["user_id"].i();
        InitialAccountSetup setup(userId);
        std::cout << "User ID: " << userId << std::endl;

        // Parse accounts
        const auto& accountsArray = body_json["accounts"];
        std::cout << "Accounts Array Size: " << accountsArray.size() << std::endl;
        for (const auto& acc : accountsArray) {
            std::cout << "Account: " << acc << std::endl;
            if (acc.size() != 3) continue;
            std::cout << "Account Size: " << acc.size() << std::endl;
            std::string accName = acc["account_name"].s();
            std::cout << "Account Name: " << accName << std::endl;
            std::string accType = acc["account_type"].s();
            std::cout << "Account Type: " << accType << std::endl;
            double accBalance = std::stod(acc["balance"].s());
            std::cout << "Account Balance: " << accBalance << std::endl;
            std::cout << "Adding Account: " << accName << ", Type: " << accType << ", Balance: " << accBalance << std::endl;
            setup.addAccount(accName, accType, accBalance);
        }

        // Parse categories
        const auto& categoriesArray = body_json["categories"];
        std::cout << "Categories Array Size: " << categoriesArray.size() << std::endl;
        if (categoriesArray.size() == 0) {
            std::cout << "No categories found." << std::endl;
            return crow::response(400, "No categories found.");
        }
        for (const auto& cat : categoriesArray) {
            if (!cat.has("category_name") || !cat.has("budget") || !cat.has("budget_items")) {
                std::cout << "Missing one of: category_name, budget, or budget_items in category JSON object." << std::endl;
                return crow::response(400, "Missing one of: category_name, budget, or budget_items.");
            }
        
            std::string catName = cat["category_name"].s();
            if (catName.empty()) {
                std::cout << "Category name is empty. Rejecting request." << std::endl;
                return crow::response(400, "Category name cannot be empty.");
            }
            std::cout << "Category Name: " << catName << std::endl;
        
            double catBudget = std::stod(cat["budget"].s());
            std::cout << "Category Budget: " << catBudget << std::endl;
        
            const auto& itemsArray = cat["budget_items"];
            std::cout << "Budget Items Array Size: " << itemsArray.size() << std::endl;
        
            std::vector<BudgetItem> budgetItems;
            for (const auto& item : itemsArray) {
                if (!item.has("name") || !item.has("amount")) {
                    std::cout << "Budget item missing 'item' or 'amount'. Rejecting request." << std::endl;
                    return crow::response(400, "Each budget item must include 'item' and 'amount'.");
                }
        
                std::string itemName = item["name"].s();
                double amount = std::stod(item["amount"].s());
                budgetItems.push_back({ itemName, amount });
            }
        
            setup.addCategory(catName, catBudget, budgetItems);
        }
        

        // Build response with totals
        std::ostringstream os;
        os << "User ID: " << userId << "<br>";
        os << "Total Balance: $" << setup.getTotalBalance() << "<br>";
        os << "Total Budget: $" << setup.getTotalBudget() << "<br>";

        os << "<br>Accounts:<br>";
        for (const auto& [name, type, balance] : setup.getAccounts()) {
            os << "- " << name << " (" << type << "): $" << balance << "<br>";
        }

        // os << "<br>Categories:<br>";
        // for (const auto& [cat, budget] : setup.getCategories()) {
        //     os << "- " << cat << ": $" << budget << "<br>";
        // }
        setup.saveToDatabase(db);
        return crow::response(200, os.str());
    });


    CROW_ROUTE(app, "/add-transaction")
    .methods(crow::HTTPMethod::POST)
    ([](const crow::request& req) {
        try{
            std::cout << "Received request for add-transaction: " << req.body << std::endl;

            auto body_json = crow::json::load(req.body);
            if (!body_json) {
                return crow::response(400, "Invalid JSON.");
            }

            if (!body_json.has("user_id") || !body_json.has("account_name") || !body_json.has("amount") || !body_json.has("budget_item_name") || !body_json.has("category_name") || !body_json.has("transaction_name") || !body_json.has("date_of_transaction")) {
                return crow::response(400, "Missing one of: user_id, account_name, amount, budget_item_name, category_name, transaction_name, or date_of_transaction.");
            }
    
            int userId = body_json["user_id"].i();
            std::string account_name = body_json["account_name"].s();
            double amount = std::stod(body_json["amount"].s());
            std::string budget_item_name = body_json["budget_item_name"].s();
            std::string category_name = body_json["category_name"].s();
            std::string description = body_json["transaction_name"].s();
            std::string date_of_transaction = body_json["date_of_transaction"].s();
            // std::string type_of_transaction = ""; // Placeholder for transaction type
            Transaction_Manager transaction_manager(userId, account_name, amount, category_name, budget_item_name, description,date_of_transaction);
            transaction_manager.addTransaction(db);
    
    
            // db.insertTransaction(userId, account_name, amount, category, description, "");
    
            return crow::response(200, "Transaction added successfully.");
        }catch(const std::exception& e) {
            std::cerr << "Error processing add-transaction request: " << e.what() << std::endl;
            return crow::response(500, std::string(e.what()) + " Internal server error.");
        }

    });
    CROW_ROUTE(app, "/accounts_info/<string>")
    ([](std::string user_id){
        int userId = std::stoi(user_id);
        Accounts_Manager accounts_manager(userId, db);
        std::vector<Account> accounts = accounts_manager.getAccounts();
    
        crow::json::wvalue response_json;
        std::vector<crow::json::wvalue> accounts_array;
    
        for (const auto& account : accounts) {
            crow::json::wvalue account_json;
            account_json["account_name"] = account.account_name;
            account_json["account_type"] = account.account_type;
            account_json["balance"] = account.balance;
            account_json["account_id"] = account.account_id;
            accounts_array.push_back(account_json);
        }
    
        response_json["accounts"] = std::move(accounts_array);
        std::cout << "Returning accounts info for user ID: " << userId << std::endl;
    
        return crow::response(200, response_json);  // ✅ valid JSON response
    });
    CROW_ROUTE(app, "/categories_info/<string>")
    ([](std::string user_id){
        int userId = std::stoi(user_id);
        Category_Manager category_manager(userId, "", 0.0, {});
        std::vector<std::tuple<std::string,std::string ,double, int>> budget_items = category_manager.getBudgetItemsforUser(db, userId);
    
        crow::json::wvalue response_json;
        std::vector<crow::json::wvalue> budget_items_array;

        for (const auto& items : budget_items) {
            crow::json::wvalue budget_json;
            budget_json["budget_item_name"] = std::get<0>(items);
            budget_json["category"] = std::get<1>(items);
            budget_json["allocated_budget"] = std::get<2>(items);
            budget_json["budget_item_id"] = std::get<3>(items);
            budget_items_array.push_back(budget_json);
        }

        response_json["budget_items"] = std::move(budget_items_array);
        std::cout << "Returning budget items info for user ID: " << userId << std::endl;

        return crow::response(200, response_json);  // ✅ valid JSON response
    });


    // app.port(18080).multithreaded().run();
    app.bindaddr("0.0.0.0").port(18080).multithreaded().run();

}