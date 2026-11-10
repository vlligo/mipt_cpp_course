#ifndef MIPT_CPP_THINGS_H
#define MIPT_CPP_THINGS_H

#include <string>

#include "EnergyConsumer.h"
#include "Inventory.h"

class Helmet : public InventoryItem {
public:
    Helmet(std::string  id, std::string  name);

    const std::string& inventoryId() const override;
    const std::string& name() const override;
    std::string describe() const override;

private:
    std::string id_;
    std::string name_;
};

class DockStation : public InventoryItem, public EnergyConsumer {
public:
    DockStation(std::string  id, std::string  name,
                double energy);

    const std::string& inventoryId() const override;
    const std::string& name() const override;
    std::string describe() const override;
    double dailyEnergy() const override;

private:
    std::string id_;
    std::string name_;
    double energy_;
};

#endif // MIPT_CPP_THINGS_H
