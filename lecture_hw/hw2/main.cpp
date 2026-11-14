#include <iostream>
#include <iomanip>
#include <memory>
#include <string>

#include "Errors.h"
#include "Fleet.h"
#include "Things.h"
#include "Transport.h"

static void add(std::istringstream& input, Fleet& fleet) {
    std::string type, id, name;
    if (!(input >> type >> id >> name)) {
        throw InvalidCommand("invalid arguments");
    }
    if (type == "helmet") {
        fleet.addItem(std::make_unique<Helmet>(id, name));
        return;
    }
    double energy = 0;
    if (type != "bike" && !(input >> energy)) {
        throw InvalidCommand("no double energy provided");
    }
    if (type == "dock") {
        fleet.addItem(std::make_unique<DockStation>(id, name, energy));
        return;
    }
    int score;
    if (!(input >> score)) {
        throw InvalidCommand("no integer score provided");
    }
    if (type == "bike") {
        fleet.addTransport(std::make_unique<Bicycle>(id, name, score));
        return;
    }
    if (type == "scooter") {
        fleet.addTransport(std::make_unique<ElectricScooter>(id, name, energy, score));
        return;
    }
    if (type == "ebike") {
        fleet.addTransport(std::make_unique<ElectricBicycle>(id, name, energy, score));
        return;
    }
    if (type == "eskateboard") {
        fleet.addTransport(std::make_unique<ElectricSkateboard>(id, name, energy, score));
        return;
    }
    throw InvalidCommand("unknown item");
}

int main() {
    Fleet fleet;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream input(line);
        std::string command;
        if (!(input >> command)) {
            continue;
        }
        try {
            if (command == "add") {
                add(input, fleet);
                continue;
            }
            if (command == "focus" || command == "remove") {
                std::string id;
                if (!(input >> id)) {
                    throw InvalidCommand("no id provided");
                }
                if (command == "focus") {
                    fleet.focus(id);
                } else {
                    fleet.remove(id);
                }
                continue;
            }
            if (command == "energy" || command == "stats") {
                std::ostringstream report;
                if (command == "stats") {
                    report << fleet.size() << ' ';
                }
                report << std::fixed << std::setprecision(1)
                       << fleet.totalDailyEnergy();
                std::cout << report.str() << '\n';
            } else if (command == "max_energy") {
                fleet.printMaxEnergy(std::cout);
            } else if (command == "novice") {
                fleet.printNovice(std::cout);
            } else if (command == "list") {
                fleet.printList(std::cout);
            } else if (command == "show_focus") {
                fleet.showFocus(std::cout);
            } else if (command == "quit") {
                break;
            } else {
                throw InvalidCommand("unrecognized command: " + command);
            }
        } catch (const FleetError& error) {
            std::cout << "error: " << error.what() << '\n';
        }
    }
    return 0;
}