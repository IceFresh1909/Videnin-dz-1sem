#include <cstring>
#include <iostream>

constexpr int cRows{5};
constexpr int cColumns{10};
constexpr int cCommandSize{20};
constexpr int cWordSize{11};

bool IsInside(int x, int y) {
  return x >= 0 && x < cColumns && y >= 0 && y < cRows;
}

void Clear(char board[cRows][cColumns]) {
  for (int y{}; y < cRows; ++y) {
    for (int x{}; x < cColumns; ++x) {
      board[y][x] = ' ';
    }
  }
}

bool Put(char board[cRows][cColumns], int x, int y, char symbol) {
  if (!IsInside(x, y)) {
    return false;
  }
  board[y][x] = symbol;
  return true;
}

bool Text(char board[cRows][cColumns], int x, int y, const char* word) {
  int length{static_cast<int>(std::strlen(word))};

  if (!IsInside(x, y) || x + length > cColumns) {
    return false;
  }

  for (int i{}; i < length; ++i) {
    Put(board, x + i, y, word[i]);
  }
  return true;
}

void Print(const char board[cRows][cColumns]) {
  for (int y{}; y < cRows; ++y) {
    for (int x{}; x < cColumns; ++x) {
      std::cout << board[y][x];
    }
    std::cout << '\n';
  }
}

int main() {
  char board[cRows][cColumns]{};
  Clear(board);

  char command[cCommandSize]{};

  while (std::cin >> command) {
    if (std::strcmp(command, "quit") == 0) {
      break;
    }

    if (std::strcmp(command, "clear") == 0) {
      Clear(board);
    } else if (std::strcmp(command, "put") == 0) {
      int x{};
      int y{};
      char symbol{};
      std::cin >> x >> y >> symbol;

      if (!Put(board, x, y, symbol)) {
        std::cout << "error\n";
      }
    } else if (std::strcmp(command, "text") == 0) {
      int x{};
      int y{};
      char word[cWordSize]{};
      std::cin >> x >> y >> word;

      if (!Text(board, x, y, word)) {
        std::cout << "error\n";
      }
    } else if (std::strcmp(command, "print") == 0) {
      Print(board);
    } else {
      std::cout << "error\n";
    }
  }
}