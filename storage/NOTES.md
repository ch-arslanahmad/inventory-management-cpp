
# NOTES

I am currently using SQLite as a DB.

- Had to install dependencies or libraries or header files for it.

- So installed sqlite3 (CLI version) & libsqlite3 (for core stuff)

```bash
sudo apt install libsqlite3-dev sqlite3
```

But its too verbose, hence an easy solution, i found was `sqlite_modern_cpp`, its syntax is quite easy and clear.

Now for logging,

```bash
sudo apt install libspdlog-dev
```

I have now been introduced to template based (generic) functions.

In C++, the input taken is `std::cout` and is quite verbose and different, and without validation, hence it is necessary to build a generic function that takes an input like python so feels easier to use.

## What is a Template Function?

A template lets you write a function once and use it with different data types.

`template <typename T> → T` is a placeholder for the type (e.g., int, double, float).

- Compiler replaces `T` with the type you use when calling the function.

The compiler decides the actual type when the function is called.

For my example,

```cpp
// this can take any datatype
template <typename T>
T input(const std::string& prompt) {
    T value;
}
```

For one data-type specifically like string,

```cpp

template <>
std::string input<std::string>() { ... }

```

> [!Note]
> Special version of the input <T> template, but only for T = std::string
