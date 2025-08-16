#include "json_helper.h"

crow::json::wvalue transactionToJson(const Transaction& tx){
    crow::json::wvalue json_tx;
    json_tx["id"]=tx.transaction_id;
    json_tx["account_name"]=tx.account;
    json_tx["amount"] = tx.amount;
    json_tx["budget_item_name"] = tx.budget_item;
    json_tx["description"] = tx.description;
    json_tx["transaction_date"]=tx.date;
    json_tx["account_type"]=tx.account_type;
    return json_tx;

}