#ifndef EXPENSEMANAGER_HPP
#define EXPENSEMANAGER_HPP

#include "Expense.hpp"

#include <vector>


class ExpenseManager {
    private:
    //Variables
        std::vector<Expense> expenses;

    //Functions
        std::string getCategoryName(int i);
        void getExpenses();
        std::string saveTime(std::time_t seconds);
        std::time_t loadTime(std::string seconds);

    public:
        ExpenseManager();
        void addExpense();
        void viewExpenses();
        void monthlySummary();
        void deleteExpense();
        void saveExpenses();
        
};
#endif