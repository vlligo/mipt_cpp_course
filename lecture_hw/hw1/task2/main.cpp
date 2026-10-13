#include <cstring>
#include <iostream>
#include <utility>

void deposit(int& current_amount) {
  int deposit_amount = 0;
  if (!(std::cin >> deposit_amount)) {
    std::cout << "error" << std::endl;
    return;
  }
  if (deposit_amount <= 0) {
    std::cout << "error" << std::endl;
    return;
  }
  current_amount += deposit_amount;
}

void withdraw(int& current_amount) {
  int withdraw_amount = 0;
  if (!(std::cin >> withdraw_amount)) {
    std::cout << "error" << std::endl;
    return;
  }
  if (withdraw_amount <= 0 || withdraw_amount > current_amount) {
    std::cout << "error" << std::endl;
    return;
  }
  current_amount -= withdraw_amount;
}

void balance(int& current_amount) {
  std::cout << current_amount << std::endl;
}

void reset(int& current_amount) {
  current_amount = 0;
}

void inc(int& current_amount) {
  ++current_amount;
}

int main() {
  const std::pair<const char*, void (*)(int&)> command_list[] = {
    {"deposit", &deposit},
    {"withdraw", &withdraw},
    {"balance", &balance},
    {"reset", &reset},
    {"inc", &inc},
};
  char command[32];
  int current_amount = 0;
  while (std::cin >> command) {
    if (std::strcmp(command, "stop") == 0) {
      break;
    }
    bool command_exists = false;
    for (const auto& entry : command_list) {
      if (std::strcmp(entry.first, command) == 0) {
        entry.second(current_amount);
        command_exists = true;
        break;
      }
    }
    if (!command_exists) {
      std::cout << "error" << std::endl;
    }
  }
  return 0;
}