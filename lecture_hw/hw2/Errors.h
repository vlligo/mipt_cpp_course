#ifndef MIPT_CPP_ERRORS_H
#define MIPT_CPP_ERRORS_H

#include <stdexcept>

class FleetError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class InvalidCommand : public FleetError {
public:
    using FleetError::FleetError;
};

class InspectionRejected : public FleetError {
public:
    using FleetError::FleetError;
};

#endif // MIPT_CPP_ERRORS_H
