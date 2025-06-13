// This is called an include guard to prevent more than once, which can cause errors.
#ifndef INCOMEBaseline_H // Start of the guard
#define INCOMEBaseline_H // End of the guard

class IncomeBaseline
{
    private:
    // These are private data members. They store the user's savings and checkings.
    // Being 'private' means they cannot be accessed directly from outside the class.
        double savings;
        double checkings;
    public:
    // This is a constructor. It will be used to create an object of this class.
    // We provide default values in case nothing is passed
    IncomeBaseline(double savingsAmount=0.0, double checkingsAmount=0.0);
    void setSavings(double amount);
    void setCheckings(double amount);
    double getSavings() const;
    double getCheckings() const;
    double getTotal() const;
};

#endif // End of the include guard