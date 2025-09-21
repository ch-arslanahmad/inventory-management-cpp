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

