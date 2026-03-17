#include <iostream>

#include "Expense.hpp"

Expense::Expense(std::string desc, Categories ctgry, double amt) 
: description(desc), category(ctgry), amount(amt) {
    setTimestamp();
}

Expense::Expense(std::string desc, Categories ctgry, double amt, std::time_t time) 
: description(desc), category(ctgry), amount(amt), timestamp(time) {}

void Expense::setDescription(std::string desc){
    description = desc;
}

std::string Expense::getDescription(){
    return description;
}

void Expense::setCategory(int categ){
    category = static_cast<Categories>(categ);
}

Categories Expense::getCategoryValue(){
    return category;
}

std::string Expense::getCategory(){
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

void Expense::setAmount(double amt){
    amount = amt;
}

double Expense::getAmount(){
    return amount;
}

void Expense::setTimestamp() {
    auto now = std::chrono::system_clock::now();
    timestamp = std::chrono::system_clock::to_time_t(now);
}

std::time_t Expense::getTimestamp(){
    return timestamp;
}

void Expense::printTimestamp(){
    std::cout << std::put_time(std::localtime(&timestamp), "%F") << "\n";
}