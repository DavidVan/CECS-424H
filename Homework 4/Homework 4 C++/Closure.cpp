#include <iostream>
#include <functional>
#include <algorithm>

#include "Closure.h"

std::function<int(int, int)> GetRegularClosure();
std::function<int(int, int)> GetCustomClosure();

int main() {
    std::function<int(int, int)> func = GetRegularClosure();
    std::cout << func(10, 20) << std::endl;

    std::function<int(int, int)> closure = GetCustomClosure();
    std::cout << closure(10, 20) << std::endl;
}

std::function<int(int, int)> GetRegularClosure() {
    int x = 10, y = 20;

    auto f = [x, y](int a, int b) {
        return (x + y) * (a + b);
    };
    return f;
}

std::function<int(int, int)> GetCustomClosure() {
    int x = 10, y = 20;
    return Closure(x, y);
}