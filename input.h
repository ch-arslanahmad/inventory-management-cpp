#include <iostream>
#include <limits>
using std::cin;
using std::cout;

/* ---CREATING TEMPLATE INPUT METHODS for intiuitive built-in error handling methods--*/

// For numeric types (int, double, float, etc.)
template <typename T>
T input(std::string message)
{
    T value;
    while (true)
    {
        std::cout << message;
        if (!(std::cin >> value))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. " << message;
            continue.
        }
        else
        {
            return value;
        }
    }
}

// Specialization template function for strings
template <>
std::string input<std::string>(std::string message)
{
    std::string value;
    std::cout << message;
    std::getline(std::cin >> std::ws, value); // Skip whitespace and read full line

    if (!value.empty())
    {
        return value;
    }
    return value;
    std::cout << "Input cannot be empty. " << message;
}

Product input_item()
{
    std::string name;
    double price;
    int quantity;
    name = input<std::string>("Enter Name: ");
    price = input<double>("Price: ");
    quantity = input<int>("Quantity: ");
    if (name == "0" && price == 0)
    {
        std::cout << "Aborting Operation\n";
        return Product("", 0, 0); // sentinel (default) details
    }
    return Product(name, price, quantity);
}