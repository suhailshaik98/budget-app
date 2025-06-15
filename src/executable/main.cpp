#include "crow.h"
#include "InitialAccountSetup.h"
#include "crow/middlewares/cors.h"
#include "database_module.h"

int main(){
    crow::App<crow::CORSHandler> app;  // <-- include middleware here

    auto& cors = app.get_middleware<crow::CORSHandler>();

    cors
      .global()
        .origin("*")
        .methods("GET"_method, "POST"_method, "OPTIONS"_method)
        .headers("Content-Type");
    // crow::SimpleApp app;
    // app.get_middleware<crow::middleware::CORS>().global(true);
    // IncomeBaseline baseline;
    // auto& cors = app.get_middleware<crow::CORSHandler>();

    // cors
    //   .global()
    //     .origin("*")  // Allow any origin
    //     .methods("GET"_method, "POST"_method, "PUT"_method, "DELETE"_method, "OPTIONS"_method)
    //     .headers("Content-Type", "X-Custom-Header", "Upgrade-Insecure-Requests", "*")
    //     .max_age(3600);

    std::string connStr = "host=localhost port=5432 dbname=budgetappdb user=budgetuser password=bUdgeTPa$$";
    DatabaseModule db(connStr);
    db.connect();
    CROW_ROUTE(app, "/")
    ([](){
        return "Welcome to the Budget App!";
    });

    CROW_ROUTE(app,"/setup")
    .methods(crow::HTTPMethod::POST)
    ([&db](const crow::request& req){
        auto body_json = crow::json::load(req.body);
        if (!body_json) {
            return crow::response(400, "Invalid JSON");
        }
        if (!body_json.has("account_name") || !body_json.has("account_type")|| !body_json.has("balance") || !body_json.has("user_id")) {
            return crow::response(400, "Missing or invalid 'savings' or 'checkings' fields.");
        }
        std::string name = body_json["account_name"].s();
        std::string type = body_json["account_type"].s();
        double balance = body_json["balance"].d();
        int userId = body_json["user_id"].i();
        db.insertAccount(userId, name, type, balance);
        // setup.addAccount(name, type, balance);

        std::cout << "name set to: " << name << "\n";
        std::cout << "type set to: " << type << "\n";
        std::ostringstream os;
        os << "Savings: $"<<name <<"<br>";
        os <<"Checkings: $"<<type<<"<br>";
        // os<<"Total: $"<<baseline.getTotal();
        auto res = crow::response(os.str());
return res;
        return crow::response(os.str());
    });
    // app.port(18080).multithreaded().run();
    app.bindaddr("0.0.0.0").port(18080).multithreaded().run();

}