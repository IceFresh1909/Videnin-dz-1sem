#include <iomanip>
#include <iostream>

double GetAverage(const int* a, int n) {
  double sum{};
  for (int i{}; i < n; ++i) {
    sum += a[i];
  }
  return sum / n;
}

int GetMinMax(const int* a, int n, int& maximum) {
  int minimum{a[0]};
  maximum = a[0];
  for (int i{1}; i < n; ++i) {
    if (a[i] < minimum) {
      minimum = a[i];
    }
    if (a[i] > maximum) {
      maximum = a[i];
    }
  }
  return minimum;
}

int GetNegativeCount(const int* a, int n) {
  int count{};
  for (int i{}; i < n; ++i) {
    if (a[i] < 0) {
      ++count;
    }
  }
  return count;
}

int main() {
  int n{};
  std::cin >> n;
  int* a{new int[n]};
  for (int i{}; i < n; ++i) {
    std::cin >> a[i];
  }
  int maximum{};
  int minimum{GetMinMax(a, n, maximum)};
  std::cout << std::fixed << std::setprecision(1) << GetAverage(a, n) << '\n';
  std::cout << minimum << ' ' << maximum << '\n';
  std::cout << GetNegativeCount(a, n) << '\n';
  delete[] a;
}