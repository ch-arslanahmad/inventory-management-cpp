#include <iostream>
#include "Product.h"; // model class : Product
#include "input.h"    // for input
using std::cout;

int MenuHandler(std::string options[], int n)
{
    int i = 1;
    for (int i = 0; i < n; i++)
    {
        cout << i << ". " << options[i];
    }
    int n;
    // get int input
    int a = input<int>("Enter your value: ");
    return a;
}

void displayItemDetails(Product item)
{
    printf("***---%d---***\n", item.getName());
    printf("***---Price: %d---***\n", item.getPrice());
    printf("***---Quantity: %d---***\n", item.getQuantity());
}

void displayAllItems(std::vector<Product> items)
{
    int i = 1;
    for (Product item : items)
    {
        printf("Item#%d", i);
        displayItemDetails(item);
        i++;
    }
}
