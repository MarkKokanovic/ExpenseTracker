#include <iostream>

#include <ctime>
#include <chrono>
#include <iomanip>

#include "ExpenseManager.hpp"

using namespace std;

int main(){
    // Expense tester("Burger", Categories::Food, 12);
    // cout << 
    // tester.getCategory() << endl <<
    // tester.getAmount() << endl <<
    // tester.getDescription() << endl;
    // tester.printTimestamp();

    int input = 0;

    ExpenseManager manager;

    while (input != 5) {

        cout << "Welcome to your Expense Manager!" << endl << "What would you like to do?" << endl << 
        "1. Add an Expense" << endl <<
        "2. View Expenses" << endl <<
        "3. View Monthly Summary" << endl <<
        "4. Delete an Expense" << endl <<
        "5. Exit" << endl;

        std::string action;
        std::getline(std::cin, action);
        input = std::stoi(action);

        if (input > 0 and input < 6) {
            switch (input) {
                case 1:
                    manager.addExpense();
                    break;

                case 2:
                    manager.viewExpenses();
                    break;

                case 3:
                    manager.monthlySummary();
                    break;

                case 4:
                    manager.deleteExpense();
                    break;

                case 5:
                    manager.saveExpenses();
                    break;

                default:
                    break;
            }
        }
    }

    return 0;
}