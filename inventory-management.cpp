#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct product {
    string name;
    double price;
    int quantity;
};

vector<product> inventory;

void search() {
    if (inventory.empty()) {
        cout << "Inventory is empty.\n";
        return;
    }

    else {

        string searchName;
        cout << "Search (product name): ";
        getline(cin >> ws, searchName); // Use getline to allow spaces in product names
        bool found = false;

        for (int i = 0; i < inventory.size(); i++) {
            if (searchName == inventory[i].name) {
                cout << "The search: " << searchName << " is in index " << i <<" & position "<< i + 1 << ".\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "No entries found. Try again. (Sentence Case Only)\n";
        }
    }
}

void add_item() {
    product newItem;
    cout << "Enter Name: ";
    getline(cin >> ws, newItem.name); // Use getline to allow spaces in product names
    cout << "Cost: ";
    cin >> newItem.price;
    cout << "Quantity: ";
    cin >> newItem.quantity;
    inventory.push_back(newItem);
    cout << "The Item has been added.\n";
}


void remove_item() {
    if (inventory.empty()) {
        cout << "There are no products available currently.\n";
        return;
    }

    else {
    cout << "Note: Removal of item depends upon human counting, hence starts from 1.\n";
    int idx;

    cout << "Remove Element# ";
    cin >> idx;
    if (idx < 1 || idx > inventory.size()) {
        cout << "Invalid index.\n";
        return;
    }

    else {
        inventory.erase(inventory.begin() + (idx - 1));
        cout << "The Item has been removed.\n";
    }
}
}
void update_item() {
    if (inventory.empty()) {
        cout << "There are no products available currently.\n";
        return;
    }

    int idx;
    cout << "Update Element# ";
    cin >> idx;
    if (idx < 1 || idx > static_cast<int>(inventory.size())) {
        cout << "That index does not exist.\n";
        return;
    }

    cout << "Updated Name: ";
    cin >> inventory[idx - 1].name;
    cout << "Updated Cost: ";
    cin >> inventory[idx - 1].price;
    cout << "Updated Quantity: ";
    cin >> inventory[idx - 1].quantity;
    cout << "The Item#" << idx << " has been updated.\n";
}

void show() {
    if (inventory.empty()) {
        cout << "There is no product to show.\n";
        return;
    }

    cout << left << setw(15) << "Name" << setw(10) << "Cost (PKR)" << setw(10) << "Quantity\n";
    cout << setfill('-') << setw(35) << "" << "\n" << setfill(' ');

    for (int i = 0; i < inventory.size(); i++) {
        cout << left << setw(15) << inventory[i].name
             << setw(10) << inventory[i].price
             << setw(10) << inventory[i].quantity << "\n";
    }
}

int main() {
    // sample data for testing
    inventory.push_back({"Pencil", 10, 300});
    inventory.push_back({"Rubber", 5, 500});

    while (true) {
        int choice;
        cout << "\n1. Search Product\n2. Add Product\n3. Remove Product\n4. Update Product\n5. See Inventory\n6. Exit\n\tChoose(1-6): ";
        cin >> choice;

        if(cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please enter a number between 1 and 6.\n";
        }

        else {
        switch (choice) {
            case 1:
                search();
                break;
            case 2:
                add_item();
                break;
            case 3:
                remove_item();
                break;
            case 4:
                update_item();
                break;
            case 5:
                show();
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
