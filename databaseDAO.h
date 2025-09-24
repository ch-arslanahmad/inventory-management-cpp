#pragma once

#include <list> // for lsits
#include "Database.h"
#include <string>
#include <vector>

/* const std::string &name
Unlike languages like Java or Python do not have pass-by reference which allows the either to do by reference or by value.
By reference allows no duplication of variable hence used.
As the input is also from user which requires no meddling hence const, so no changing.
*/

/* Using Lambda Function:
        [&](std::string n, double p, int q)
    {
        result = Product{n, p, q};
    };

In which [&] is used to capture all the output while the next are variables in question (after output), which were then stored in the object of Product Class

*/

// does table exist
bool tableExists(const std::string &tableName)
{
    
    auto db = createConnection();
    if (!db)
        return false;

    bool exists = false;
    *db << "SELECT COUNT(*) FROM sqlite_master WHERE type='table' AND name=?"
        << tableName >>
        [&](int count)
    {
        exists = (count > 0);
    };
    return exists;
}

// ? does item exist in table
bool itemsExist(const std::string &tableName = "inventory")
{
    if (!tableExists(tableName))
    {
        createStructure(); // create strucutre;
    }

    // Validating the tableName to prevent SQL injection
    if (tableName != "inventory" && tableName != "another_valid_table")
    {
        return false; // Or throw an exception
    }

    auto db = createConnection();
    if (!db)
        return false;

    bool hasItems = false;
    *db << "SELECT COUNT(*) FROM " << tableName >> [&](int count)
    {
        hasItems = (count > 0);
    };
    return hasItems;
}

// item exists (by input)
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
        std::cout << "Error Establishing (DB-add) Connection.";
        return false;
    }
    else
    {
        *db << "INSERT INTO inventory(name,price,quantity) VALUES((?),(?),(?))" << item.getName() << item.getPrice() << item.getQuantity(); // as 'db' is optional and to get the actual from optional (wrapper), dereference operator is needed
        std::cout << "Successfully added item.";
        return true;
    }
}

bool removeItem(const std::string &name)
{
    if (itemExists(name))
    {
        cout << "Item already exists.";
        return false;
    }

    std::optional<sqlite::database> db = createConnection();
    if (!db)
    {
        std::cout << "Error Establishing (DB-remove) Connection.";
        return false;
    }
    else
    {
        *db << "DELETE FROM inventory WHERE name = ?" << name; // as 'db' is optional and to get the actual from optional (wrapper), dereference operator is needed
        std::cout << "Successfully added item.";
        return true;
    }
}

std::optional<Product> fetchItemDetails(const std::string &name)
{
    if (!itemExists(name))
    {
        cout << "Item does not exist.\n";
        return std::nullopt;
    }

    std::optional<sqlite::database> db = createConnection();
    if (!db)
    {
        std::cout << "Error Establishing (DB-fetch) Connection.\n";
        return std::nullopt;
    }

    std::optional<Product> result;

    *db << "SELECT name, price, quantity FROM inventory WHERE name=?"
        << name >>
        [&](std::string n, double p, int q)
    {
        result = Product{n, p, q};
    };

    return result;
}

std::vector<Product> fetchAllItems()
{
    // create connection
    std::optional<sqlite::database> db = createConnection();
    if (!db)
    {
        std::cout << "Error Establishing (DB-fetch) Connection.\n";
        return {}; // empty vector
    }

    // fetch all items
    std::vector<Product> inventory;
    *db << "SELECT name, price, quantity FROM inventory" >> [&](std::string n, double p, int q)
    {
        inventory.emplace_back(n, p, q);
    };
    // return
    return inventory;
}

// UPDATE: whole item - price, quant from name
bool updateItem(Product item)
{
    if (itemExists(item.getName()))
    {
        cout << "Item already exists.";
        return false;
    }

    std::optional<sqlite::database> db = createConnection();
    if (!db)
    {
        std::cout << "Error Establishing (DB-updateName) Connection.";
        return false;
    }

    *db << "UPDATE inventory SET name = ?, price=?, quantity=? WHERE name=?" << item.getPrice() << item.getQuantity() << item.getName(); // as 'db' is optional and to get the actual from optional (wrapper), dereference operator is needed

    std::cout << "Successfully updated item.";
    return true;
}

// UPDATE: item - quantity from name
bool updateItem(std::string &name, int &quantity)
{
    if (itemExists(name))
    {
        cout << "Item already exists.";
        return false;
    }

    std::optional<sqlite::database> db = createConnection();
    if (!db)
    {
        std::cout << "Error Establishing (DB-updateName) Connection.";
        return false;
    }

    *db << "UPDATE inventory SET quantity=? WHERE name=?" << quantity << name; // as 'db' is optional and to get the actual from optional (wrapper), dereference operator is needed

    std::cout << "Successfully updated item.";
    return true;
}

// UPDATE: item - price from name
bool updateItem(std::string &name, double &price)
{
    if (itemExists(name))
    {
        cout << "Item already exists.";
        return false;
    }

    std::optional<sqlite::database> db = createConnection();
    if (!db)
    {
        std::cout << "Error Establishing (DB-updateName) Connection.";
        return false;
    }

    *db << "UPDATE inventory SET price=? WHERE name=?" << price << name; // as 'db' is optional and to get the actual from optional (wrapper), dereference operator is needed

    std::cout << "Successfully updated item.";
    return true;
}
