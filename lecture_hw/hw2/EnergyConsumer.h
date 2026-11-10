#ifndef MIPT_CPP_ENERGYCONSUMER_H
#define MIPT_CPP_ENERGYCONSUMER_H

class EnergyConsumer {
public:
    virtual ~EnergyConsumer() = default;

    virtual double dailyEnergy() const = 0;
};


#endif // MIPT_CPP_ENERGYCONSUMER_H
