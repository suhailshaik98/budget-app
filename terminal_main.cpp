#include <iostream>
#include <limits> // for std::numeric_limits
#include "IncomeBaseline.h"  // Include your class header


void printIncomeBaseline(const IncomeBaseline& baseline)
{
    std::cout<<"Income Baseline:\n";
    std::cout<<"Savings: "<< baseline.getSavings() << "\n";
    std::cout<<"Checkings: "<< baseline.getCheckings() << "\n";
    std::cout<<"Total: "<< baseline.getTotal() << "\n";
}

int main()
{
    IncomeBaseline baseline;
    char choice;

        double savings,checkings;
        std::cout<<"Enter amount for savings Amount: $";
     while (!(std::cin >> savings)){
        std::cin.clear(); // clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore invalid input
        std::cout<<"Invalid input. Please enter a number:";
    };

    std::cout<<"Enter amount in Checkings Amount: $";
    while (!(std::cin>>checkings)){
        std::cin.clear(); // clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore invalid input
        std::cout<<"Invalid input. Please enter a number:";
    }
    baseline.setSavings(savings);
    baseline.setCheckings(checkings);
    printIncomeBaseline(baseline);

    return 0;
}