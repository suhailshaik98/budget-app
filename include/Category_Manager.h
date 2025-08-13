#ifndef CATEGORY_MANAGER_H
#define CATEGORY_MANAGER_H

#include <string>
#include <vector>
#include <utility>
#include "database_module.h"  // Database interaction layer

class Category_Manager {
public:
    Category_Manager(int userId,
                     const std::string& categoryName,
                    //  DatabaseModule& db,
                     double budget = 0.0,
                     const std::vector<std::pair<std::string, double>>& budgetItems = {});

    // Add a new category and its associated budget items
    void addCategory(DatabaseModule& db);

    // Update category name/budget and replace its budget items
    void updateCategory(DatabaseModule& db,
                        int categoryId,
                        const std::string& newCategoryName,
                        double newBudget,
                        const std::vector<std::pair<std::string, double>>& newBudgetItems);

    // Delete the category and its associated budget items
    void deleteCategory(DatabaseModule& db, int categoryId);

    // Get all categories for the user, formatted as strings
    std::vector<std::string> getCategories(DatabaseModule& db);

    // Get all budget items for a given category ID
    std::vector<std::pair<std::string, double>> getBudgetItems(DatabaseModule& db, int categoryId);

    std::vector<std::tuple<std::string,std::string ,double,int>> getBudgetItemsforUser(DatabaseModule& db, int userId);

private:
    int userId;
    std::string categoryName;
    double budget;
    // DatabaseModule& db;
    std::vector<std::pair<std::string, double>> budgetItems;
};

#endif // CATEGORY_MANAGER_H
