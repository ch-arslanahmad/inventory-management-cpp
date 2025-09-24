#include <iostream>
#include <vector>
#include <iomanip>
#include "display.h"
#include "input.h"
#include "databaseDAO.h"
using std::cin;
using std::cout;

bool updateMenu()
{
    std::vector<std::string> options = {"Update Whole Item", "Update Item Price", "Update Item Quantity"};

    while (true)
    {
        int choice = MenuHandler(options);

        switch (choice)
        {
        case 0:
        {
            cout << "Exiting Update Options";
            cout << ".";
            cout << ".";
            cout << ".\n";
            return false;
        }
        case 1:
        {

            if (auto item = input_item())
            {
                updateItem(*item); // deference the wrapper (get Product item)
            }
            else
            {
                break;
            }
            break;
        }
        case 2:
        {

            std::string name = input<std::string>("Enter Name: ");
            double price = input<double>("Enter Price: ");
            if (updateItem(name, price))
            {
                return true;
            }
            break;
        }
        case 3:
        {
            std::string name = input<std::string>("Enter Name: ");
            int quantity = input<int>("Enter Quantity: ");
            if (updateItem(name, quantity))
            {
                return true;
            }
            break;
        }
        default:
            break;
        }
    }
}

int main()
{
    std::vector<std::string> options = {"Search Product", "Add Product", "Remove Product", "Update Product", "See Inventory"};

    if (!itemsExist())
    {
        // Remove by index (0-based)
        options.erase(options.begin() + 0); // Remove 1st element
        options.erase(options.begin() + 2); // Remove 3rd element (after first removal)
        options.erase(options.begin() + 3); // Remove 4th element
    }

    while (true)
    {
        int choice = MenuHandler(options);
        switch (choice)
        {
        case 0:
        { // exit
            cout << "Exiting Inventory Program";
            cout << ".";
            cout << ".";
            cout << ".";
            return 0;
        }
        case 1:
        { // search
            std::string name = input<std::string>("Enter Item (to search): ");
            fetchItemDetails(name);
            break;
        }
        case 2:
        { // add

            if (auto item = input_item())
            {
                addItem(*item); // Dereference the optional (if only Product)
            }
            else
            {
                break;
            }
            break;
        }
        case 3: // remove
        {
            std::string name = input<std::string>("Enter Item (to remove): ");
            removeItem(name);
            break;
        }
        case 4:
        { // update
            updateMenu();
            break;
        }
        case 5:
        { // show();
            break;
        }
        default:
            cout << "The input is invalid. Choose 1-6.\n";
            break;
        }
    }
}
