#pragma once

#include <iostream>
#include "Product.h" // model class : Product
#include "input.h"
using std::cout;

int MenuHandler(const std::vector<std::string> &options)
{
    int n = options.size();
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << ". " << options[i] << "\n"; // Remove 'count', use i+1
    }

    while (true)
    {
        int a = input<int>("Enter your choice: ");
        if (a >= 0 && a <= n)
        { // menu starts at 0
            return a;
        }
        else
        {

            cout << "Invalid choice (0-" << options.size() << "). ";
        }
    }
}

void displayItemDetails(Product item)
{
    printf("***---%s---***\n", item.getName().c_str());
    printf("***---Price: %f---***\n", item.getPrice());
    printf("***---Quantity: %d---***\n", item.getQuantity());
}

void displayAllItems(std::vector<Product> items)
{
    int i = 1;
    for (Product item : items)
    {
        printf("Item#%d\n", i);
        displayItemDetails(item);
        i++;
    }
}
