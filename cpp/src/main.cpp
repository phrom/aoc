#include <iostream>

int x;

auto f() -> int&
{
    return x;
}

auto main() -> int
{
    std::cout << "hello world!\n";
    return 0;
}
