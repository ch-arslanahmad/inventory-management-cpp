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

// Specialization for strings (handles spaces)
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
