#include <iostream>
#include "storage/lib/sqlite_modern_cpp.h" // importing sqlite db
#include "Product.h"
#include <string>
using std::cin;
using std::cout;

std::optional<sqlite::database> createConnection()
{
    try
    {
        return sqlite::database("storage/inventory.sql"); // opens or creates "inventory.db"
    }
    catch (std::exception &e)
    {
        std::cerr << "DB connection failed" << "\n";
        return std::nullopt; // to indicate that optional wrapper object does not have value
    }
}

bool createStructure()
{
    std::optional<sqlite::database> db = createConnection();
    if (!db)
    {
        cout << "Error Establishing (DB) Connection.";
        return false;
    }
    else
    {
        std::string create_structure_query = "CREATE TABLE IF NOT EXISTS inventory(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, price INTEGER, quantity FLOAT )";
        *db << create_structure_query; // as 'db' is optional and to get the actual from optional (wrapper), dereference operator is needed
        std::cout << "Successfully made structure.";
        return true;
    }
}

Product input_item()
{
    std::string name;
    double price;
    int quantity;

    std::cout << "Enter Name: ";
    std::getline(std::cin >> std::ws, name);

    std::cout << "Cost: ";
    std::cin >> price;
    std::cout << "Quantity: ";
    std::cin >> quantity;

    if (name == "0" && price == 0)
    {
        std::cout << "Aborting Add Operation\n";
        return Product("", 0, 0); // sentinel Product
    }

    std::cout << "The Item has been added.\n";
    return Product(name, price, quantity);
}

/* const std::string &name
Unlike languages like Java or Python do not have pass-by reference which allows the either to do by reference or by value.
By reference allows no duplication of variable hence used.
As the input is also from user which requires no meddling hence const, so no changing.
*/
bool itemExists(const std::string &name)
{
    auto db = createConnection();
    if (!db)
        return false;

    // so when it returns 1 or 0 (nothing more)
    int exists = 0;
    *db << "SELECT EXISTS(SELECT 1 FROM inventory WHERE name = ? LIMIT 1);"
        << name >>
        exists;

    return exists == 1; // true if one
}

bool addItem(Product item)
{
    if (itemExists(item.getName()))
    {
        cout << "Item already exists.";
        return false;
    }
    std::optional<sqlite::database> db = createConnection();
    if (!db)
    {
        std::cout << "Error Establishing (DB) Connection.";
        return false;
    }
    else
    {
        *db << "INSERT INTO inventory(name,price,quantity) VALUES((?),(?),(?))" << item.getName() << item.getPrice() << item.getQuantity(); // as 'db' is optional and to get the actual from optional (wrapper), dereference operator is needed
        std::cout << "Successfully added item.";
        return true;
    }
}
