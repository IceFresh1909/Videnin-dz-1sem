#include <iostream>

int main() {
  // В трехмерном кубе хранятся целые числа.
  // Нужно найти их сумму, а затем сохранить несколько выбранных результатов:
  // либо отдельные ячейки куба, либо общую сумму.
  // int*** нужен для хранения трехмерного куба.
  // void* нужен, чтобы в одном массиве хранить адреса значений разных типов:
  // ячейка имеет тип int, а общая сумма — long long.

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

  int count{};
  std::cin >> count;

  void** results{new void*[count]};
  int* types{new int[count]};

  for (int i{}; i < count; ++i) {
    std::cin >> types[i];

    if (types[i] == 1) {
      int x{};
      int y{};
      int z{};
      std::cin >> x >> y >> z;

      if (x < 0 || x >= n || y < 0 || y >= n || z < 0 || z >= n) {
        results[i] = nullptr;
      } else {
        results[i] = &cube[x][y][z];
      }
    } else if (types[i] == 2) {
      results[i] = &sum;
    } else {
      results[i] = nullptr;
    }
  }

  for (int i{}; i < count; ++i) {
    if (results[i] == nullptr) {
      std::cout << "error\n";
    } else if (types[i] == 1) {
      std::cout << *static_cast<int*>(results[i]) << '\n';
    } else {
      std::cout << *static_cast<long long*>(results[i]) << '\n';
    }
  }

  delete[] results;
  delete[] types;

  for (int i{}; i < n; ++i) {
    for (int j{}; j < n; ++j) {
      delete[] cube[i][j];
    }

    delete[] cube[i];
  }

  delete[] cube;
}