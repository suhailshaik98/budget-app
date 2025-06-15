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

void InitialAccountSetup::addCategory(const std::string& categoryName, double budget, const std::vector<BudgetItem>& budgetItems) {
    categories.emplace_back(categoryName, budget, budgetItems);
}

const std::vector<Category>& InitialAccountSetup::getCategories() const {
    return categories;
}

double InitialAccountSetup::getTotalBudget() const {
    double total = 0.0;
    for (const auto& category : categories) {
        total += category.total_budget;
    }
    return total;
}

void InitialAccountSetup::saveToDatabase(DatabaseModule& db) {
    for (const auto& account : accounts) {
        std::cout << "Inserting account: " << std::get<0>(account) << ", Type: " << std::get<1>(account) 
                  << ", Balance: " << std::get<2>(account) << std::endl;
        db.insertAccount(userId, std::get<0>(account), std::get<1>(account), std::get<2>(account));
    }

    for (const auto& category : categories) {
        std::cout << "Inserting category: " << category.name << " with budget: " << category.total_budget << std::endl;
        for (const auto& item : category.budgetItems) {
            std::cout << "  Budget Item: " << item.first << ", Amount: " << item.second << std::endl;
        }
        db.insertCategory(userId, category.name, category.total_budget, category.budgetItems);
    }
}