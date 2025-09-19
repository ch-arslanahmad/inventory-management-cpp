#include <iostream>
#include <vector>
#include <iomanip>
using std::cin;
using std::cout;

int main()
{

    while (true)
    {
        int choice;
        cout << "\n1. Search Product\n2. Add Product\n3. Remove Product\n4. Update Product\n5. See Inventory\n6. Exit\n\tChoose(1-6): ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please enter a number between 1 and 6.\n";
        }

        else
        {
            switch (choice)
            {
            case 1:
                // search();
                break;
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
            case 6:
                return 0;
            default:
                cout << "The input is invalid. Choose 1-6.\n";
                break;
            }
        }
    }
}
