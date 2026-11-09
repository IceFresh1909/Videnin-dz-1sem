#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "Errors.hpp"
#include "Fleet.hpp"
#include "Inventory.hpp"

void CheckEnd(std::istringstream& input) {
  std::string extra;
  if (input >> extra) {
    throw InputError("extra arguments");
  }
}

void AddCommand(std::istringstream& input, Fleet& fleet) {
  std::string type;
  std::string id;
  std::string name;
  if (!(input >> type >> id >> name)) {
    throw InputError("invalid add command");
  }

  if (type == "scooter" || type == "ebike") {
    double energy{};
    int score{};
    if (!(input >> energy >> score)) {
      throw InputError("invalid add command");
    }
    CheckEnd(input);
    if (type == "scooter") {
      fleet.AddTransport(std::make_unique<ElectricScooter>(id, name, energy, score));
    } else {
      fleet.AddTransport(std::make_unique<ElectricBike>(id, name, energy, score));
    }
  } else if (type == "bike" || type == "cargo") {
    int score{};
    if (!(input >> score)) {
      throw InputError("invalid add command");
    }
    CheckEnd(input);
    if (type == "bike") {
      fleet.AddTransport(std::make_unique<Bike>(id, name, score));
    } else {
      fleet.AddTransport(std::make_unique<CargoBike>(id, name, score));
    }
  } else if (type == "helmet") {
    CheckEnd(input);
    fleet.AddThing(std::make_unique<Helmet>(id, name));
  } else if (type == "dock") {
    double energy{};
    if (!(input >> energy)) {
      throw InputError("invalid add command");
    }
    CheckEnd(input);
    fleet.AddThing(std::make_unique<Dock>(id, name, energy));
  } else {
    throw InputError("unknown item type");
  }
}

bool ProcessCommand(const std::string& line, Fleet& fleet) {
  std::istringstream input(line);
  std::string command;
  if (!(input >> command)) {
    return true;
  }

  if (command == "quit") {
    CheckEnd(input);
    return false;
  }

  if (command == "add") {
    AddCommand(input, fleet);
  } else if (command == "list") {
    CheckEnd(input);
    fleet.PrintList(std::cout);
  } else if (command == "energy") {
    CheckEnd(input);
    std::cout << std::fixed << std::setprecision(1) << fleet.TotalEnergy() << '\n';
  } else if (command == "novice") {
    CheckEnd(input);
    fleet.PrintNovice(std::cout);
  } else if (command == "count_novice") {
    CheckEnd(input);
    std::cout << fleet.CountNovice() << '\n';
  } else if (command == "report") {
    CheckEnd(input);
    fleet.PrintReport(std::cout);
  } else if (command == "focus" || command == "remove") {
    std::string id;
    if (!(input >> id)) {
      throw InputError("missing id");
    }
    CheckEnd(input);
    if (command == "focus") {
      fleet.Focus(id);
    } else {
      fleet.Remove(id);
    }
  } else if (command == "show_focus") {
    CheckEnd(input);
    fleet.ShowFocus(std::cout);
  } else if (command == "set_novice") {
    int score{};
    if (!(input >> score)) {
      throw InputError("invalid score");
    }
    CheckEnd(input);
    fleet.SetNoviceScore(score);
  } else {
    throw InputError("unknown command");
  }
  return true;
}

int main() {
  Fleet fleet;
  std::string line;

  while (std::getline(std::cin, line)) {
    try {
      if (!ProcessCommand(line, fleet)) {
        break;
      }
    } catch (const FleetError& error) {
      std::cout << "error: " << error.what() << '\n';
    }
  }
}
