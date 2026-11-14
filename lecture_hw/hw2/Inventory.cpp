#include "Inventory.h"

double InventoryItem::dailyEnergy() const {
    return 0.0;
}

bool InventoryItem::suitableForNovice(int) const {
    return false;
}

std::ostream& operator<<(std::ostream& out, const InventoryItem& item) {
    return out << item.describe();
}

bool operator<(const InventoryItem& a, const InventoryItem& b) {
    return a.inventoryId() < b.inventoryId();
}

bool operator==(const InventoryItem& a, const InventoryItem& b) {
    return a.inventoryId() == b.inventoryId();
}