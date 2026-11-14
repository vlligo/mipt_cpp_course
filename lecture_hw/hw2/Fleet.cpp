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

void Fleet::checkUniqueId(const std::string& id) const {
    for (std::size_t i = 0; i < items_.size(); ++i) {
        if (items_[i]->inventoryId() == id) {
            throw InvalidCommand("item or vehicle with this ID already exists");
        }
    }
}

std::size_t Fleet::size() const {
    return items_.size();
}
