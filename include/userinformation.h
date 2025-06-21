#ifndef USER_INFORMATION_H
#define USER_INFORMATION_H

#include <string>
#include <vector>
#include "Accounts_Manager.h"
#include "Category_Manager.h"
#include "Transaction_Manager.h"



class UserInformation {
public:
    UserInformation(int userId);
    // Add account

    // Getters
    const std::vector<Account>& getAccounts() const;
    const std::vector<CategoryInfo>& getCategories() const;
    const std::vector<Transaction>& getAllTransactions(DatabaseModule& db) const;
    const std::vector<Transaction>& getTimedTransactions(DatabaseModule& db) const;

private:
    std::vector<Account> accounts_;
    std::vector<CategoryInfo> categories_;
    std::vector<Transaction> transactions_;
};

#endif // USER_INFORMATION_H