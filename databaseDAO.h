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
    try
    {

        auto db = createConnection();
        if (!db)
            return false;

        bool hasItems = false;
        *db << "SELECT COUNT(*) FROM " + tableName >> [&](int count)
        {
            hasItems = (count > 0);
        };
        return hasItems;
    }
    catch (const sqlite::errors::error &e)
    {
        // If an exception is thrown, the code inside this block will run
        std::cerr << "Database error (tableExists): " << e.what() << std::endl;
        return false;
    }
}

// ? does item exist in table
bool itemsExist(const std::string &tableName = "inventory")
{
    try
    {
        if (!tableExists(tableName))
        {
            createStructure();
            return false;
        }

        auto db = createConnection();
        if (!db)
            return false;

        bool hasItems = false;
        *db << "SELECT COUNT(*) FROM " + tableName >> [&](int count)
        {
            hasItems = (count > 0);
        };
        return hasItems;
    }
    catch (const sqlite::errors::error &e)
    {
        std::cerr << "Database error (itemsExist): " << e.what() << std::endl;
        return false;
    }
}
// item exists (by input)
bool itemExists(const std::string &name)
{
    try
    {
        auto db = createConnection();
        if (!db)
            return false;

        // so when it returns 1 or 0 (nothing more)
        bool exists = false;
        *db << "SELECT EXISTS(SELECT 1 FROM inventory WHERE name = ? LIMIT 1);"
            << name >>
            exists;

        return exists == 1; // true if one
    }
    catch (const sqlite::errors::error &e)
    {
        // If an exception is thrown, the code inside this block will run
        std::cerr << "Database error (itemExist): " << e.what() << std::endl;
        return false;
    }
}

bool addItem(Product item)
{
    try
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
    catch (const sqlite::errors::error &e)
    {
        // If an exception is thrown, the code inside this block will run
        std::cerr << "Database error (addItem): " << e.what() << std::endl;
        return false;
    }
}

bool removeItem(const std::string &name)
{
    try
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
    catch (const sqlite::errors::error &e)
    {
        // If an exception is thrown, the code inside this block will run
        std::cerr << "Database error (removeItem): " << e.what() << std::endl;
        return false;
    }
}

std::optional<Product> fetchItemDetails(const std::string &name)
{
    try
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
    catch (const sqlite::errors::error &e)
    {
        // If an exception is thrown, the code inside this block will run
        std::cerr << "Database error (fetchItemDetails): " << e.what() << std::endl;
        return std::nullopt;
    }
}

std::vector<Product> fetchAllItems()
{
    try
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
    catch (const sqlite::errors::error &e)
    {
        // If an exception is thrown, the code inside this block will run
        std::cerr << "Database error (tableExists): " << e.what() << std::endl;
        return {};
    }
}

// UPDATE: whole item - price, quant from name
bool updateItem(Product item)
{
    try
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
    catch (const sqlite::errors::error &e)
    {
        // If an exception is thrown, the code inside this block will run
        std::cerr << "Database error (tableExists): " << e.what() << std::endl;
        return false;
    }
}

// UPDATE: item - quantity from name
bool updateItem(std::string &name, int &quantity)
{
    try
    {
        if (!itemExists(name))
        {
            cout << "Item does not exists.";
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
    catch (const sqlite::errors::error &e)
    {
        // If an exception is thrown, the code inside this block will run
        std::cerr << "Database error (updateItem): " << e.what() << std::endl;
        return false;
    }
}

// UPDATE: item - price from name
bool updateItem(std::string &name, double &price)
{
    try
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
    catch (const sqlite::errors::error &e)
    {
        // If an exception is thrown, the code inside this block will run
        std::cerr << "Database error (updateItem[price]): " << e.what() << std::endl;
        return false;
    }
}
