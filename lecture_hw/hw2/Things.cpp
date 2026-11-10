#include "Things.h"
#include "Errors.h"
#include <utility>


Helmet::Helmet(std::string  id, std::string  name)
    : id_(std::move(id)), name_(std::move(name)) {
    if (id_.empty()) {
        throw InvalidCommand("empty ID");
    }
}

const std::string& Helmet::inventoryId() const {
    return id_;
}

const std::string& Helmet::name() const {
    return name_;
}

std::string Helmet::describe() const {
    return id_ + " " + name_;
}

DockStation::DockStation(std::string  id, std::string  name, const double energy)
    : id_(std::move(id)), name_(std::move(name)), energy_(energy) {
    if (id_.empty()) {
        throw InvalidCommand("empty ID");
    }

    if (energy_ < 0) {
        throw InvalidCommand("negative energy");
    }
}

const std::string& DockStation::inventoryId() const {
    return id_;
}

const std::string& DockStation::name() const {
    return name_;
}

std::string DockStation::describe() const {
    return id_ + " " + name_;
}

double DockStation::dailyEnergy() const {
    return energy_;
}
