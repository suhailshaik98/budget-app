#include "crow.h"
#include "IncomeBaseline.h"

int main(){
    crow::SimpleApp app;
    IncomeBaseline baseline;

    CROW_ROUTE(app, "/")
    ([](){
        return "Welcome to the Budget App!";
    });

    CROW_ROUTE(app,"/set")
    ([](const crow::request& req){
        auto savingsStr = req.url_params.get("savings");
        auto checkingsStr = req.url_params.get("checkings");
        if (!savingsStr||!checkingsStr){
            return crow::response(400,"Missing 'savings' or 'checkings' query parameters.");
        }
        double savings = std::stod(savingsStr);
        double checkings = std::stod(checkingsStr);

        static IncomeBaseline baseline;
        baseline.setSavings(savings);
        baseline.setCheckings(checkings);

        std::ostringstream os;
        os << "Savings: $"<<baseline.getSavings() <<"<br>";
        os <<"Checkings: $"<<baseline.getCheckings()<<"<br>";
        os<<"Total: $"<<baseline.getTotal();
        return crow::response(os.str());
    });
    app.port(18080).multithreaded().run();
}