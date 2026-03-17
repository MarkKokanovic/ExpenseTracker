#ifndef EXPENSE_HPP
#define EXPENSE_HPP

#include "Categories.hpp"

#include <string>

#include <ctime>
#include <chrono>
#include <iomanip>

class Expense {
    private:
        std::string description;
        Categories category;
        double amount;
        std::time_t timestamp;

    public:
        //Constructor
        Expense(std::string desc, Categories ctgry, double amt);
        Expense(std::string desc, Categories ctgry, double amt, std::time_t time);

        //Setters and Getters
        void setDescription(std::string desc);
        std::string getDescription();

        void setCategory(int categ);
        Categories getCategoryValue();          //Return Categories Enum
        std::string getCategory();              //Returns Category as string

        void setAmount(double amt);
        double getAmount(); 
        
        void setTimestamp();
        std::time_t getTimestamp();             //Return timestamp in time format
        void printTimestamp();                   //Prints time in Day Month Year
};
#endif