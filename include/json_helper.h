#ifndef JSON_HELPERS_H
#define JSON_HELPERS_H

#include "crow.h"
#include "accounts.h"

crow::json::wvalue transactionToJson(const Transaction& tx);

#endif