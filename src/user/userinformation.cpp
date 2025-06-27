#include "userinformation.h"
#include <iostream>
UserInformation::UserInformation(int userId) {
    this->userId = userId;
    // Constructor implementation
}

// UserInformation::~UserInformation() {
//     // Destructor implementation
// }

// // Assuming userinformation.h declares these methods and members:

const std::vector<Transaction> UserInformation::getTimedTransactions(const std::string& start_date,const std::string& end_date,DatabaseModule& db) const {
    Transaction_Manager tm(userId);
    std::vector<Transaction> result =  tm.getTimedTransactions(start_date,end_date,db);
    std::cout << "In userinformation successuflly result" << std::endl;  // This flushes automatically
    return result;

}

// const std::vector<Transaction>& getTransactions(){
    
// }