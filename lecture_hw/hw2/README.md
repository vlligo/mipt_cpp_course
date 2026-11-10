# FizKat

## Build and Run

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
- `EnergyConsumer` (abstract)
  - `DockStation`
  - `ElectricBicycle`
  - `ElectricScooter`


## Smart Pointers

## Exceptions
`FleetError` is a base class for all custom errors in this application. It derives from `std::runtime_error`.
1. `InvalidCommand` is an error indicating user entered an invalid command
2. `InspectionRejected` is an error indicating a failed inspection

## Templates

## Custom Features

## AI Usage
