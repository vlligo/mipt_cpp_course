# FizKat
A console program for rental fleet managing 
## Build and Run
```bash
g++ -std=c++14 main.cpp Inventory.cpp Things.cpp \
 Transport.cpp ServiceCenter.cpp Fleet.cpp -o fizkat
./fizkat
```
## Class Hierarchy
- `std::runtime_error`
    - `FleetError`
        - `InvalidCommand`
        - `InspectionRejected`
- `InventoryItem` (abstract)
  - `Helmet`
  - `DockStation`
  - `Transport`
    - `Bicycle`
    - `ElectricBicycle`
    - `ElectricScooter`
    - `ElectricSkateboard`
- `EnergyConsumer` (abstract)
  - `DockStation`
  - `ElectricBicycle`
  - `ElectricScooter`
  - `ElectricSkateboard`
- `ServiceCenter`
- `Registry`
- `Fleet`

These classes have multiple inheritance: `DockStation`, `ElectricBicycle`, `ElectricScooter`, `ElectricSkateboard`

## Smart Pointers
- `unique_ptr` owns new vehicles before and during the inspection
- `shared_ptr` owns accepted entries in the fleet registry
- `weak_ptr` refers to the selected showcase entry. After removing the entry showcase prints `expired`

## Exceptions
`FleetError` is a base class for all custom errors in this application. It derives from `std::runtime_error`.
1. `InvalidCommand` is an error indicating user entered an invalid command
2. `InspectionRejected` is an error indicating a failed inspection

## Templates
`Registry<T>` stores entries in a vector for `Fleet` to use `Registry<std::shared_ptr<InventoryItem>>`

## Custom Features
- `ElectricSkateboard` is added as an additional vehicle type.
- `max_energy` is a new command added. It prints an items with the highest daily energy consumption
- `operator==` compares entries by their id

## AI Usage
Statement parsing. For example, on page 2 under "Функции приложения" item 3 they explicitly want a command to print both in stock items and daily energy consumption. Note, that in the command table there is no such a command required. It would have been quite hard to find without a chatbot.
Also, AI was used for code review, but not code generating.
