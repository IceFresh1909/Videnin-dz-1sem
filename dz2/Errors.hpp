#pragma once

#include <stdexcept>
#include <string>

class FleetError : public std::runtime_error {
 public:
  explicit FleetError(const std::string& message) : std::runtime_error(message) {}
};

class InspectionError : public FleetError {
 public:
  explicit InspectionError(const std::string& message) : FleetError(message) {}
};

class InputError : public FleetError {
 public:
  explicit InputError(const std::string& message) : FleetError(message) {}
};
