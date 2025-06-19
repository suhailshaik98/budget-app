#pragma once


#include <string>

struct Account {
    int account_id;
    std::string account_name;
    double balance;
    std::string account_type; // e.g., "Savings", "Checking"
};