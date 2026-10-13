#include <cstring>
#include <iostream>
#include <limits>

constexpr int cCommandCount{5};
constexpr int cCommandSize{20};
constexpr int cNotFound{-1};

void Deposit(int& balance) {
  int k{};
  std::cin >> k;
  if (k <= 0) {
    std::cout << "error\n";
    return;
  }
  balance += k;
}

void Withdraw(int& balance) {
  int k{};
  std::cin >> k;
  if (k <= 0 || k > balance) {
    std::cout << "error\n";
    return;
  }
  balance -= k;
}

void Balance(int& balance) {
  std::cout << balance << '\n';
}

void Reset(int& balance) {
  balance = 0;
}

void Inc(int& balance) {
  ++balance;
}

int main() {
  const char* command_names[cCommandCount]{
      "deposit", "withdraw", "balance", "reset", "inc"};
  void (*operations[cCommandCount])(int&){
      Deposit, Withdraw, Balance, Reset, Inc};

  int balance{};
  char command[cCommandSize]{};

  while (std::cin >> command) {
    if (std::strcmp(command, "stop") == 0) {
      break;
    }

    int command_index{cNotFound};

    for (int i{}; i < cCommandCount; ++i) {
      if (std::strcmp(command, command_names[i]) == 0) {
        command_index = i;
        break;
      }
    }

    if (command_index == cNotFound) {
      std::cout << "error\n";
    } else {
      operations[command_index](balance);
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}