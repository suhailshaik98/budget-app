#include "Category_Manager.h"
#include <iostream>
#include <stdexcept>
#include <vector>

Category_Manager::Category_Manager(int userId, const std::string& categoryName, double budget, const std::vector<std::pair<std::string, double>>& budgetItems)
    : userId(userId), categoryName(categoryName), budget(budget), budgetItems(budgetItems) {
}
void Category_Manager::addCategory(DatabaseModule& db) {
    if (categoryName.empty()) {
        throw std::invalid_argument("Category name cannot be empty.");
    }
    // db.insertCategory(userId, categoryName, budget, budgetItems);
}
void Category_Manager::updateCategory(DatabaseModule& db, int categoryId, const std::string& newCategoryName, double newBudget, const std::vector<std::pair<std::string, double>>& newBudgetItems) {
    if (newCategoryName.empty()) {
        throw std::invalid_argument("New category name cannot be empty.");
    }
    // db.insertCategory(userId, newCategoryName, newBudget, newBudgetItems);
}
void Category_Manager::deleteCategory(DatabaseModule& db, int categoryId) {
    // Assuming DatabaseModule has a method to delete a category by ID
    // db.deleteCategory(categoryId);
}
std::vector<std::string> Category_Manager::getCategories(DatabaseModule& db) {
    return db.getOnlyCategories(userId);
}
std::vector<std::pair<std::string, double>> Category_Manager::getBudgetItems(DatabaseModule& db, int categoryId) {
    // return db.getBudgetItemsforUser(userId);
}
std::vector<std::tuple<std::string,std::string, double, int>> Category_Manager::getBudgetItemsforUser(DatabaseModule& db, int userId) {
    return db.getBudgetItemsforUser(userId);
}

