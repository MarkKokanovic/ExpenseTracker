#include <iostream>
#include <fstream>
#include <sstream>

#include "ExpenseManager.hpp"

ExpenseManager::ExpenseManager(){
    getExpenses();
}

void ExpenseManager::addExpense(){
    std::string categ;
    Categories category = Categories::Other;
    std::string amt;
    double amount = 0.0;
    std::string description;

    std::cout << std::endl << "Please enter a category for your expense." << std::endl;
    std::cout << "1. Food 2.Transport 3. Entertainment  4.Clothing  5.Subscription  6.Other" << std::endl;

    if (std::getline(std::cin, categ)) {
        try {
            // Convert the string to a double
            category = static_cast<Categories>(std::stoi(categ) - 1);
        } catch (const std::exception& e) {
            std::cerr << "Error: Invalid input or number out of range: " << e.what() << std::endl;
        }
    }

    std::cout << std::endl << "Please enter an amount for your expense." << std::endl;
    if (std::getline(std::cin, amt)) {
        try {
            // Convert the string to a double
            amount = std::stod(amt);
        } catch (const std::exception& e) {
            std::cerr << "Error: Invalid input or number out of range: " << e.what() << std::endl;
        }
    }
    
    std::cout << std::endl << "Please enter a description for your expense." << std::endl;
    std::getline(std::cin, description);

    Expense newExpense(description, category, amount);
    expenses.push_back(newExpense);
}

void ExpenseManager::viewExpenses(){
    int i = 1;
    for (auto expense : expenses){
        std::cout << "-------------------" << std::endl;
        std::cout << "Transaction #" << i << std::endl;
        std::cout << "-------------------" << std::endl;
        std::cout << "     | " << expense.getDescription() << " |" << std::endl;
        
        std::cout << "Date: ";
        expense.printTimestamp();

        std::cout << 
        "Category: " << expense.getCategory() << std::endl <<
        "Amount: $" << std::fixed << std::setprecision(2) << expense.getAmount() << std::endl;
        i++;
    }

    std::cout << std::endl;
}

void ExpenseManager::monthlySummary(){
    std::vector<double> totals;
    std::vector<int> count;
    int numCategories = 6; //Number of categories in enum class Categories

    for (int i = 0; i < numCategories ; i++){
        totals.push_back(0);
        count.push_back(0);
    }

    for (auto expense : expenses) {
        switch (expense.getCategoryValue()){
            case Categories::Food:
                totals[0] += expense.getAmount();
                count[0] += 1;
                break;
            case Categories::Transport:
                totals[1] += expense.getAmount();
                count[1] += 1;
                break;
            case Categories::Entertainment:
                totals[2] += expense.getAmount();
                count[2] += 1;
                break;
            case Categories::Clothing:
                totals[3] += expense.getAmount();
                count[3] += 1;
                break;
            case Categories::Subscription:
                totals[4] += expense.getAmount();
                count[4] += 1;
                break;
            case Categories::Other:
                totals[5] += expense.getAmount();
                count[5] += 1;
                break;
            default:
                break;
        }
    }

    std::cout << std::endl << "  Your monthly expenses  " << std::endl;
    std::cout <<              "-------------------------" << std::endl;
    for (int x = 0; x < (int)totals.size(); x++){
        if (count[x] == 0) {
            count[x] = 1;
        }
        std::cout << " " << x + 1 << ". " << getCategoryName(x) << std::endl <<
        " Total - $" << totals[x] <<  "  Average - $" << totals[x]/count[x] << std::endl;
    }
    std::cout << std::endl;

}

std::string ExpenseManager::getCategoryName(int i){
    Categories category = static_cast<Categories>(i);
    switch(category){
        case Categories::Food:
            return "Food";

        case Categories::Transport:
            return "Transport";

        case Categories::Entertainment:
            return "Entertainment";

        case Categories::Clothing:
            return "Clothing";

        case Categories::Subscription:
            return "Subscription";

        case Categories::Other:
            return "Other";
        
        default:
            return "Not Found";
    }
}

void ExpenseManager::deleteExpense(){
    int i = 1;
    for (auto expense : expenses) {
        std::cout << "| Transaction #" << i << "| " << expense.getDescription() << std::endl;
        i++;
    }

    bool valid = false;
    std::string input;
    int num;

    std::cout << "Which expense would you like to delete?" << std::endl;
     while (!valid){
        std::getline(std::cin, input);
        num = std::stoi(input);
        if (num < 0 or num > (int)expenses.size()){
            std::cout << "That is not an available task." << std::endl;
        } else {
            expenses.erase(expenses.begin() + num - 1);
            std::cout << "Expense deleted." << std::endl;
            valid = true;
        }
    }
}

void ExpenseManager::saveExpenses(){

    std::ofstream outFile;
    outFile.open("expenses.txt");

    for (Expense expense : expenses){
        outFile << expense.getDescription() << "|" << expense.getAmount() << "|" 
        << static_cast<int>(expense.getCategoryValue()) << "|" << saveTime(expense.getTimestamp()) << std::endl;
    }
}

void ExpenseManager::getExpenses(){
    std::ifstream inFile;
    inFile.open("expenses.txt");

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream linestream(line);
        std::string cell;
        std::vector<std::string> expense;

        // Process the line by the custom delimiter (e.g., comma ',')
        while (std::getline(linestream, cell, '|')) {
            expense.push_back(cell);
        }

        std::string desc = expense[0];
        double amt = std::stod(expense[1]);
        Categories ctgry = static_cast<Categories>(std::stoi(expense[2]));
        std::time_t time = loadTime(expense[3]);

        Expense newExpense(desc, ctgry, amt, time);

        expenses.push_back(newExpense);
    }
}

std::string ExpenseManager::saveTime(std::time_t seconds){
    return std::to_string(seconds);
}

std::time_t ExpenseManager::loadTime(std::string seconds){
    long long value;
    std::stringstream ss(seconds);

    ss >> value;

    // 1. Create a duration object
    std::chrono::seconds duration(value);

    // 2. Create a time_point representing the epoch + the duration
    std::chrono::system_clock::time_point time_point = std::chrono::system_clock::from_time_t(0) + duration;
    // Alternatively, for C++20:
    // auto time_point_cxx20 = std::chrono::system_clock::from_time_t(0) + std::chrono::sys_seconds(std::chrono::seconds(seconds_since_epoch_ll));

    // 3. Convert the time_point to time_t
    std::time_t raw_time = std::chrono::system_clock::to_time_t(time_point);

    return raw_time;
}