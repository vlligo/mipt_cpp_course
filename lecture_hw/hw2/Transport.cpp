#include "Transport.h"

#include <utility>
#include "Errors.h"

Transport::Transport(std::string  id, std::string  name, const int score)
    : id_(std::move(id)), name_(std::move(name)), score_(score) {
    if (id_.empty()) {
        throw InvalidCommand("empty ID");
    }
    if (score_ < 1 || score_ > 10) {
        throw InvalidCommand("score out of bounds");
    }
}

const std::string& Transport::inventoryId() const {
    return id_;
}

const std::string& Transport::name() const {
    return name_;
}

int Transport::score() const {
    return score_;
}

Bicycle::Bicycle(const std::string& id, const std::string& name, int score)
    : Transport(id, name, score) {
}

std::string Bicycle::describe() const {
    return inventoryId() + " " + name();
}

ElectricScooter::ElectricScooter(const std::string& id,
                                 const std::string& name, const double energy, const int score)
    : Transport(id, name, score), energy_(energy) {
    if (energy_ < 0) {
        throw InvalidCommand("negative energy");
    }
}

std::string ElectricScooter::describe() const {
    return inventoryId() + " " + name();
}

double ElectricScooter::dailyEnergy() const {
    return energy_;
}

ElectricBicycle::ElectricBicycle(const std::string& id,
                                 const std::string& name, const double energy, const int score)
    : Transport(id, name, score), energy_(energy) {
    if (energy_ < 0) {
        throw InvalidCommand("negative energy");
    }
}

std::string ElectricBicycle::describe() const {
    return inventoryId() + " " + name();
}

double ElectricBicycle::dailyEnergy() const {
    return energy_;
}
