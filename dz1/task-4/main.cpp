// В трехмерном кубе, разбитом на единичные квадратики,
// стоят целые числа. Нужно найти их сумму.
// int*** нужен, чтобы обращаться к элементам куба по трем координатам.
// void* нужен, потому что выбранный результат может быть двух типов:
// общей суммой long long или одной ячейкой int.


#include <iostream>

int main() {
 int n{};
  std::cin >> n;
  int*** cube{new int**[n]};
  for (int i{}; i < n; ++i) {
    cube[i] = new int*[n];
    for (int j{}; j < n; ++j) {
      cube[i][j] = new int[n];
    }
  }
  long long sum{};
  for (int i{}; i < n; ++i) {
    for (int j{}; j < n; ++j) {
      for (int k{}; k < n; ++k) {
        std::cin >> cube[i][j][k];
        sum += cube[i][j][k];
      }
    }
  }
  int type{};
  std::cin >> type;
  void* result{nullptr};
  if (type == 1) {
    result = &sum;
    std::cout << *static_cast<long long*>(result) << '\n';
  } else if (type == 2) {
    int x{};
    int y{};
    int z{};
    std::cin >> x >> y >> z;
    if (x < 0 || x >= n || y < 0 || y >= n || z < 0 || z >= n) {
      std::cout << "error\n";
    } else {
      result = &cube[x][y][z];
      std::cout << *static_cast<int*>(result) << '\n';
    }
  } else {
    std::cout << "error\n";
  }
  for (int i{}; i < n; ++i) {
    for (int j{}; j < n; ++j) {
      delete[] cube[i][j];
    }
    delete[] cube[i];
  }
  delete[] cube;
}