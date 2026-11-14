#include <utility>
#include <vector>
#include <algorithm>

#include "Fleet.h"
#include "Errors.h"
#include "ServiceCenter.h"

void Fleet::addTransport(std::unique_ptr<Transport> vehicle) {
    if (!vehicle) {
        throw InvalidCommand("empty vehicle");
    }
    checkUniqueId(vehicle->inventoryId());
    ServiceCenter::inspect(*vehicle);
    items_.add(std::shared_ptr<InventoryItem>(std::move(vehicle)));
}

void Fleet::addItem(std::unique_ptr<InventoryItem> item) {
    if (!item) {
        throw InvalidCommand("empty item");
    }
    checkUniqueId(item->inventoryId());
    items_.add(std::shared_ptr<InventoryItem>(std::move(item)));
}

void Fleet::printList(std::ostream& out) const {
    std::vector<const InventoryItem*> sorted;
    sorted.reserve(items_.size());
    for (std::size_t i = 0; i < items_.size(); ++i) {
        sorted.push_back(items_[i].get());
    }
    std::sort(sorted.begin(), sorted.end(), [](const InventoryItem* a, const InventoryItem* b) {
        return *a < *b;
    });
    for (const InventoryItem* item : sorted) {
        out << *item << '\n';
    }
}

double Fleet::totalDailyEnergy() const {
    double total = 0;
    for (std::size_t i = 0; i < items_.size(); ++i) {
        total += items_[i]->dailyEnergy();
    }
    return total;
}

void Fleet::printNovice(std::ostream& out, const int threshold) const {
    for (std::size_t i = 0; i < items_.size(); ++i) {
        if (items_[i]->suitableForNovice(threshold)) {
            out << *items_[i] << '\n';
        }
    }
}

void Fleet::focus(const std::string& id) {
    const std::size_t index = findIndex(id);
    if (index == items_.size()) {
        throw InvalidCommand("invalid id");
    }
    focused_ = items_[index];
}

void Fleet::showFocus(std::ostream& out) const {
    const auto item = focused_.lock();
    if (item) {
        out << *item << '\n';
    } else {
        out << "expired\n";
    }
}

void Fleet::remove(const std::string& id) {
    const std::size_t index = findIndex(id);
    if (index == items_.size()) {
        throw InvalidCommand("invalid id");
    }
    items_.erase(index);
}

void Fleet::printMaxEnergy(std::ostream& out) const {
    if (items_.size() == 0) {
        out << "empty\n";
        return;
    }
    std::size_t ans = 0;
    for (std::size_t i = 1; i < items_.size(); ++i) {
        if (items_[i]->dailyEnergy() > items_[ans]->dailyEnergy()) {
            ans = i;
        }
    }
    out << *items_[ans] << ' ' << items_[ans]->dailyEnergy() << '\n';
}

void Fleet::checkUniqueId(const std::string& id) const {
    for (std::size_t i = 0; i < items_.size(); ++i) {
        if (items_[i]->inventoryId() == id) {
            throw InvalidCommand("item or vehicle with this ID already exists");
        }
    }
}

std::size_t Fleet::findIndex(const std::string& id) const {
    for (std::size_t i = 0; i < items_.size(); ++i) {
        if (items_[i]->inventoryId() == id) {
            return i;
        }
    }
    return items_.size();
}

std::size_t Fleet::size() const {
    return items_.size();
}
