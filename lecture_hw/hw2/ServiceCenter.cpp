#include <cctype>
#include <string>

#include "ServiceCenter.h"
#include "Errors.h"
#include "Transport.h"

void ServiceCenter::inspect(const Transport& vehicle) {
    std::string vehicle_name = vehicle.name();
    for (auto&i : vehicle_name) {
        i = static_cast<char>(std::tolower(i));
    }
    if (vehicle_name.find("broken") != std::string::npos) {
        throw InspectionRejected("Broken vehicle, inspection rejected");
    }
}
