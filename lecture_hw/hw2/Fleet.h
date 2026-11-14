#ifndef MIPT_CPP_FLEET_H
#define MIPT_CPP_FLEET_H

#include <cstddef>
#include <memory>
#include <string>
#include <ostream>

#include "Inventory.h"
#include "Registry.h"
#include "Transport.h"

class Fleet {
public:
    void addTransport(std::unique_ptr<Transport> vehicle);
    void addItem(std::unique_ptr<InventoryItem> item);
    void printList(std::ostream& out) const;
    double totalDailyEnergy() const;
    void printNovice(std::ostream& out, int threshold = 6) const;
    void focus(const std::string& id);
    void showFocus(std::ostream& out) const;
    void remove(const std::string& id);
    void printMaxEnergy(std::ostream& out) const;
    std::size_t size() const;

private:
    void checkUniqueId(const std::string& id) const;
    std::size_t findIndex(const std::string& id) const;
    Registry<std::shared_ptr<InventoryItem>> items_;
    std::weak_ptr<InventoryItem> focused_;
};

#endif // MIPT_CPP_FLEET_H
