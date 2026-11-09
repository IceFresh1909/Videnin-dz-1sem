#pragma once

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Counter.hpp"
#include "Errors.hpp"
#include "Inventory.hpp"

class ServiceCenter {
 public:
  void Inspect(const InventoryItem& item) const {
    std::string name{item.Name()};
    for (char& symbol : name) {
      symbol = static_cast<char>(std::tolower(static_cast<unsigned char>(symbol)));
    }
    if (name.find("broken") != std::string::npos) {
      throw InspectionError("inspection rejected");
    }
  }
};

class Fleet {
 private:
  std::vector<std::shared_ptr<InventoryItem>> items_;
  std::weak_ptr<InventoryItem> focus_;
  ServiceCenter service_;
  int novice_score_{cDefaultNoviceScore};

  void AddItem(std::unique_ptr<InventoryItem> candidate, bool needs_inspection) {
    for (const auto& item : items_) {
      if (*item == *candidate) {
        throw InputError("duplicate id");
      }
    }

    if (needs_inspection) {
      service_.Inspect(*candidate);
    }

    // До техосмотра объект принадлежит unique_ptr, затем — shared_ptr в парке.
    items_.push_back(std::shared_ptr<InventoryItem>(std::move(candidate)));
  }

 public:
  void AddTransport(std::unique_ptr<InventoryItem> item) {
    AddItem(std::move(item), true);
  }

  void AddThing(std::unique_ptr<InventoryItem> item) {
    AddItem(std::move(item), false);
  }

  void PrintList(std::ostream& out) const {
    auto sorted{items_};
    std::sort(sorted.begin(), sorted.end(), [](const auto& left, const auto& right) {
      return *left < *right;
    });

    for (const auto& item : sorted) {
      out << *item << '\n';
    }
  }

  void PrintNovice(std::ostream& out) const {
    for (const auto& item : items_) {
      if (item->ForNovice(novice_score_)) {
        out << *item << '\n';
      }
    }
  }

  double TotalEnergy() const {
    Counter<double> energy;
    for (const auto& item : items_) {
      energy.Add(item->DailyEnergy());
    }
    return energy.Get();
  }

  int CountNovice() const {
    Counter<int> count;
    for (const auto& item : items_) {
      if (item->ForNovice(novice_score_)) {
        count.Add(1);
      }
    }
    return count.Get();
  }

  void PrintReport(std::ostream& out) const {
    out << "count: " << items_.size() << '\n';
    out << "energy: " << std::fixed << std::setprecision(1) << TotalEnergy() << '\n';
  }

  void SetNoviceScore(int score) {
    if (score < 1 || score > cMaxScore) {
      throw InputError("invalid score");
    }
    novice_score_ = score;
  }

  void Focus(const std::string& id) {
    for (const auto& item : items_) {
      if (item->InventoryId() == id) {
        focus_ = item;
        return;
      }
    }
    throw InputError("unknown id");
  }

  void ShowFocus(std::ostream& out) const {
    auto item{focus_.lock()};
    if (item) {
      out << *item << '\n';
    } else {
      out << "removed\n";
    }
  }

  void Remove(const std::string& id) {
    auto it{std::find_if(items_.begin(), items_.end(), [&id](const auto& item) {
      return item->InventoryId() == id;
    })};
    if (it == items_.end()) {
      throw InputError("unknown id");
    }
    items_.erase(it);
  }
};
