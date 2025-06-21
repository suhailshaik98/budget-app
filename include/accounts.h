#pragma once


#include <string>

struct Account {
    int account_id;
    std::string account_name;
    double balance;
    std::string account_type; // e.g., "Savings", "Checking"
};

// Structure to store category information
struct CategoryInfo {
    std::string category_name;
    std::string description;
};

// Structure to store transaction information
struct Transaction {
    double amount;
    int transaction_id;
    int account_id;
    std::string date;
    std::string budget_item;
    std::string description;
    std::string account;
};