#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <utility>

#include "Errors.hpp"

inline constexpr int cMaxScore{10};
inline constexpr int cCargoScore{8};
inline constexpr int cDefaultNoviceScore{6};

class InventoryItem {
 protected:
  std::string id_;
  std::string name_;

 public:
  InventoryItem(std::string id, std::string name)
      : id_(std::move(id)), name_(std::move(name)) {
    if (id_.empty() || name_.empty()) {
      throw InputError("empty id or name");
    }
  }

  virtual ~InventoryItem() = default;

  virtual const std::string& InventoryId() const = 0;
  virtual const std::string& Name() const = 0;
  virtual void Describe(std::ostream& out) const = 0;

  virtual double DailyEnergy() const { return 0.0; }
  virtual bool ForNovice(int) const { return false; }
};

inline std::ostream& operator<<(std::ostream& out, const InventoryItem& item) {
  item.Describe(out);
  return out;
}

inline bool operator<(const InventoryItem& left, const InventoryItem& right) {
  return left.InventoryId() < right.InventoryId();
}

inline bool operator==(const InventoryItem& left, const InventoryItem& right) {
  return left.InventoryId() == right.InventoryId();
}

class EnergyConsumer {
 public:
  virtual ~EnergyConsumer() = default;
  virtual double DailyEnergy() const = 0;
};

inline void CheckEnergy(double energy) {
  if (!std::isfinite(energy) || energy < 0) {
    throw InputError("invalid energy");
  }
}

class Transport : public InventoryItem {
 protected:
  int score_{};

 public:
  Transport(std::string id, std::string name, int score)
      : InventoryItem(std::move(id), std::move(name)), score_(score) {
    if (score_ < 1 || score_ > cMaxScore) {
      throw InputError("invalid score");
    }
  }

  const std::string& InventoryId() const override { return id_; }
  const std::string& Name() const override { return name_; }

  void Describe(std::ostream& out) const override {
    out << InventoryId() << ' ' << Name();
  }

  bool ForNovice(int minimum_score) const override {
    return score_ >= minimum_score;
  }
};

class ElectricScooter : public Transport, public EnergyConsumer {
 private:
  double energy_{};

 public:
  ElectricScooter(std::string id, std::string name, double energy, int score)
      : Transport(std::move(id), std::move(name), score), energy_(energy) {
    CheckEnergy(energy_);
  }

  double DailyEnergy() const override { return energy_; }
};

class Bike : public Transport {
 public:
  using Transport::Transport;
};

class ElectricBike : public Transport, public EnergyConsumer {
 private:
  double energy_{};

 public:
  ElectricBike(std::string id, std::string name, double energy, int score)
      : Transport(std::move(id), std::move(name), score), energy_(energy) {
    CheckEnergy(energy_);
  }

  double DailyEnergy() const override { return energy_; }
};

// Дополнительный вид транспорта: грузовой велосипед сложнее для новичка.
class CargoBike : public Bike {
 public:
  using Bike::Bike;

  bool ForNovice(int minimum_score) const override {
    return Bike::ForNovice(minimum_score) && score_ >= cCargoScore;
  }
};

class Thing : public InventoryItem {
 public:
  Thing(std::string id, std::string name)
      : InventoryItem(std::move(id), std::move(name)) {}

  const std::string& InventoryId() const override { return id_; }
  const std::string& Name() const override { return name_; }

  void Describe(std::ostream& out) const override {
    out << InventoryId() << ' ' << Name();
  }
};

class Helmet : public Thing {
 public:
  using Thing::Thing;
};

class Dock : public Thing, public EnergyConsumer {
 private:
  double energy_{};

 public:
  Dock(std::string id, std::string name, double energy)
      : Thing(std::move(id), std::move(name)), energy_(energy) {
    CheckEnergy(energy_);
  }

  double DailyEnergy() const override { return energy_; }
};
