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

    // Constructor 2
    Product(std::string name)
    {
        this->name = name;
    }

    // GETTERS

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

    // SETTERS

    void setItem(std::string name, double price, int quantity)
    {
        this->name = name;
        this->price = price;
        this->quantity = quantity;
    }

    void setName(std::string name)
    {
        this->name = name;
    }

    void setPrice(double price)
    {
        this->price = price;
    }

    void setName(int quantity)
    {
        this->quantity = quantity;
    }
};