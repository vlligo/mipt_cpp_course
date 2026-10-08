#include <iostream>
#include <functional>

static std::function<int(int)> addLog(const std::function<int(int)>& fun) {
    return [fun](const int x) {
        std::cout << "Argument: " << x << std::endl;
        const int result = fun(x);
        std::cout << "Result: " << result << std::endl;
        return result;
    };
}

int main() {
    auto square = [](const int x) {return x * x;};
    auto logged_square = addLog(square);
    logged_square(2);
    return 0;
}