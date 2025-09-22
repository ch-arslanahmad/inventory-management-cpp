#include <iostream>
#include <vector>
#include <iomanip>
#include "display.h";
using std::cin;
using std::cout;

std::string options[5] = {"Search Product", "Add Product", "Remove Product", "Update Product", "See Inventory"};

int main()
{

    while (true)
    {

        int choice = MenuHandler(options, 5);

        switch (choice)
        {
        case 0:
            return 0;
        case 1:
            search();
        case 2:
            // add_item();
            break;
        case 3:
            // remove_item();
            break;
        case 4:
            // update_item();
            break;
        case 5:
            // show();
            break;
        default:
            cout << "The input is invalid. Choose 1-6.\n";
            break;
        }
    }
}
}
