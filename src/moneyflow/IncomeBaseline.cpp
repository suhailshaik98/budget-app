#include "IncomeBaseline.h"
#include <sstream>  // Make sure this header is included at the top of your file


IncomeBaseline::IncomeBaseline(double savingsAmount, double checkingsAmount)
    : savings(savingsAmount), checkings(checkingsAmount)
    {}
    void IncomeBaseline::setSavings(double amount) {
        savings=amount;
    }
    void IncomeBaseline::setCheckings(double amount) {
        checkings=amount;
    }
    double IncomeBaseline::getSavings() const {
        return savings;
    }
    double IncomeBaseline::getCheckings() const {
        return checkings;
    }
    double IncomeBaseline::getTotal() const {
        return savings + checkings;
    }
