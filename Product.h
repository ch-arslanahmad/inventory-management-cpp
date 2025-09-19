#pragma once
#include <string>

class Product
{
    std::string name;
    double price;
    int quantity;

public:
    Product(std::string name, double price, int quantity) // constructor
    {
        this->name = name;
        this->price = price;
        this->quantity = quantity;
    }

    std::string getName()
    {
        return name;
    }
    double getPrice()
    {
        return price;
    }
    int getQuantity()
    {
        return quantity;
    }
};