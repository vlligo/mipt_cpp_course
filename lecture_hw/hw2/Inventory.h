#ifndef MIPT_CPP_INVENTORY_H
#define MIPT_CPP_INVENTORY_H

#include <ostream>
#include <string>

class InventoryItem {
public:
    virtual ~InventoryItem() = default;

    virtual const std::string& inventoryId() const = 0;
    virtual const std::string& name() const = 0;
    virtual std::string describe() const = 0;

    virtual double energyConsumption() const;
    virtual bool suitableForNovice(int threshold) const;
};

std::ostream& operator<<(std::ostream& out, const InventoryItem& item);
bool operator<(const InventoryItem& a, const InventoryItem& b);
bool operator==(const InventoryItem& a, const InventoryItem& b);


#endif // MIPT_CPP_INVENTORY_H
