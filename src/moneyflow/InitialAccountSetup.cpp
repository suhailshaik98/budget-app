#include "InitialAccountSetup.h"
#include <sstream>  // Make sure this header is included at the top of your file


InitialAccountSetup::InitialAccountSetup() {}
void InitialAccountSetup::addAccount(const std::string& accountName, const std::string& accountType, double balance){
    accounts.emplace_back(accountName, accountType, balance);    
}

const std::vector<std::tuple<std::string, std::string, double>>& InitialAccountSetup::getAccounts() const {
    return accounts;
}

double InitialAccountSetup::getTotalBalance() const {
    double total=0.0;
    for (const auto& account:accounts){
        total += std::get<2>(account);
    }
    return total;
}
