#include <cstring>
#include <iostream>

constexpr int cCommandCount{5};
constexpr int cCommandSize{20};

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
  const char* commands[cCommandCount]{
      "deposit", "withdraw", "balance", "reset", "inc"};

  void (*operations[cCommandCount])(int&){
      Deposit, Withdraw, Balance, Reset, Inc};

  int balance{};
  char command[cCommandSize]{};

  while (std::cin >> command) {
    if (std::strcmp(command, "stop") == 0) {
      break;
    }

    int command_index{-1};

    for (int i{}; i < cCommandCount; ++i) {
      if (std::strcmp(command, commands[i]) == 0) {
        command_index = i;
        break;
      }
    }

    if (command_index == -1) {
      std::cout << "error\n";
    } else {
      operations[command_index](balance);
    }
  }
}