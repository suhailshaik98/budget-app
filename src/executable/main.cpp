#include "crow.h"
#include "InitialAccountSetup.h"
#include "crow/middlewares/cors.h"
#include "database_module.h"
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
        for (const auto& cat : categoriesArray) {
            if (cat.size() != 2) continue;
            std::string catName = cat["category_name"].s();
            double catBudget = std::stod(cat["budget"].s());
            setup.addCategory(catName, catBudget);
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

        os << "<br>Categories:<br>";
        for (const auto& [cat, budget] : setup.getCategories()) {
            os << "- " << cat << ": $" << budget << "<br>";
        }
        setup.saveToDatabase(db);
        return crow::response(200, os.str());
    });
    // app.port(18080).multithreaded().run();
    app.bindaddr("0.0.0.0").port(18080).multithreaded().run();

}