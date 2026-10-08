#include <iostream>
#include <functional>
#include <utility>

class Keyboard {
    std::function<void(const char x)> action;
    public:
    explicit Keyboard(std::function<void(const char x)> action) : action(std::move(action)) {}

    void setAction(std::function<void(const char x)> action_) {
        action = std::move(action_);
    }

    void keyPress(const char x) const {
        action(x);
    }
};

int main() {
    Keyboard keyboard([](const char x) {std::cout << x << std::endl; });
    keyboard.keyPress('a');
    keyboard.setAction([](const char x) {std::cout << "Pressed key: " << x << std::endl; });
    keyboard.keyPress('a');
    return 0;
}