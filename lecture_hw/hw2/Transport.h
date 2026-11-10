#ifndef MIPT_CPP_TRANSPORT_H
#define MIPT_CPP_TRANSPORT_H

#include <string>
#include "Inventory.h"
#include "EnergyConsumer.h"

class Transport : public InventoryItem {
public:
    const std::string& inventoryId() const override;
    const std::string& name() const override;
    int score() const;

protected:
    Transport(std::string  id, std::string  name, int score);

private:
    std::string id_;
    std::string name_;
    int score_;
};

class Bicycle : public Transport {
public:
    Bicycle(const std::string& id, const std::string& name, int score);

    std::string describe() const override;
};

class ElectricScooter : public Transport, public EnergyConsumer {
public:
    ElectricScooter(const std::string& id, const std::string& name,
                    double energy, int score);

    std::string describe() const override;
    double dailyEnergy() const override;

private:
    double energy_;
};

class ElectricBicycle : public Transport, public EnergyConsumer {
public:
    ElectricBicycle(const std::string& id, const std::string& name,
                    double energy, int score);

    std::string describe() const override;
    double dailyEnergy() const override;

private:
    double energy_;
};

#endif // MIPT_CPP_TRANSPORT_H
