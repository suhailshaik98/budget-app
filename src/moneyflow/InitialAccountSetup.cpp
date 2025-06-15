#include "InitialAccountSetup.h"
#include <sstream>  // Make sure this header is included at the top of your file
#include <iostream>

InitialAccountSetup::InitialAccountSetup(int userId):userId(userId) {}
void InitialAccountSetup::addAccount(const std::string& accountName, const std::string& accountType, double balance){
    std::cout << "Adding account: " << accountName << ", Type: " << accountType << ", Balance: " << balance << std::endl;
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

void InitialAccountSetup::addCategory(const std::string& categoryName, double budget) {
    categories.emplace_back(categoryName, budget);
}

const std::vector<std::pair<std::string, double>>& InitialAccountSetup::getCategories() const {
    return categories;
}

double InitialAccountSetup::getTotalBudget() const {
    double total = 0.0;
    for (const auto& category : categories) {
        total += category.second;
    }
    return total;
}

void InitialAccountSetup::saveToDatabase(DatabaseModule& db) {
    for (const auto& account : accounts) {
        db.insertAccount(userId, std::get<0>(account), std::get<1>(account), std::get<2>(account));
    }

    for (const auto& category : categories) {
        db.insertCategory(userId, category.first, category.second);
    }
}