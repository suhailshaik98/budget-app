#include "crow.h"
#include "IncomeBaseline.h"
#include "crow/middlewares/cors.h"

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
    IncomeBaseline baseline;
    // auto& cors = app.get_middleware<crow::CORSHandler>();

    // cors
    //   .global()
    //     .origin("*")  // Allow any origin
    //     .methods("GET"_method, "POST"_method, "PUT"_method, "DELETE"_method, "OPTIONS"_method)
    //     .headers("Content-Type", "X-Custom-Header", "Upgrade-Insecure-Requests", "*")
    //     .max_age(3600);
    CROW_ROUTE(app, "/")
    ([](){
        return "Welcome to the Budget App!";
    });

    CROW_ROUTE(app,"/set")
    .methods(crow::HTTPMethod::POST)
    ([](const crow::request& req){
        auto body_json = crow::json::load(req.body);
        if (!body_json) {
            return crow::response(400, "Invalid JSON");
        }
        if (!body_json.has("savings") || !body_json.has("checkings")) {
            return crow::response(400, "Missing or invalid 'savings' or 'checkings' fields.");
        }
        double savings = body_json["savings"].d();
        double checkings = body_json["checkings"].d();

        static IncomeBaseline baseline;
        baseline.setSavings(savings);
        baseline.setCheckings(checkings);
        std::cout << "Savings set to: " << savings << "\n";
        std::cout << "Checkings set to: " << checkings << "\n";
        std::ostringstream os;
        os << "Savings: $"<<baseline.getSavings() <<"<br>";
        os <<"Checkings: $"<<baseline.getCheckings()<<"<br>";
        os<<"Total: $"<<baseline.getTotal();
        auto res = crow::response(os.str());
return res;
        return crow::response(os.str());
    });
    // app.port(18080).multithreaded().run();
    app.bindaddr("0.0.0.0").port(18080).multithreaded().run();

}