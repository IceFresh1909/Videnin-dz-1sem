#pragma once

// Один и тот же счётчик работает для int (количество) и double (энергия).
template <typename T>
class Counter {
 private:
  T value_{};

 public:
  void Add(T amount) { value_ += amount; }
  T Get() const { return value_; }
};
