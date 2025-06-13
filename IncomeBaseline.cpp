#include "IncomeBaseline.h"


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
