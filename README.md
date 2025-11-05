# State Machine Device Manager

## Overview

A C++ implementation of a type-safe state machine management system using template-based device managers without inheritance. This project demonstrates a modern C++ approach to managing heterogeneous devices with different state machines while maintaining compile-time safety and performance.

## Architectural Pattern

### Template-Based State Management

The system employs a specialized template pattern where each device type maintains its own state machine with device-specific states and transitions. The key architectural components are:

- **Device-Specific State Machines**: Each device (`ADevice`, `BDevice`) defines its own state enum and transition rules
- **Template Device Managers**: Generic manager template with specializations for each device type
- **Zero-Inheritance Design**: Uses templates and composition instead of class hierarchies
- **Compile-Time Polymorphism**: Type safety ensured through template specialization

### Core Components

#### State Machines
- Defined using enum-based states for simplicity and performance
- Transition tables with conditional logic
- Self-contained validation rules

#### Device Managers
- **Generic Template**: `DeviceManager<DeviceType>` for common operations
- **Specialized Implementations**: Device-specific managers with type-safe operations
- **Centralized Logic**: Complex operation sequences handled at manager level

## Project Structure

```
src/
├── devices/
│   ├── ADevice.h/cpp          # Device A with IDLE/RUNNING/ERROR states
│   └── BDevice.h/cpp          # Device B with OFF/STANDBY/ACTIVE/MAINTENANCE states
├── states/
│   ├── AStates.h              # Device A state definitions
│   └── BStates.h              # Device B state definitions
├── statemachine/
│   └── StateMachine.h         # Generic state machine template
├── devicemanager/
│   └── DeviceManager.h        # Template device manager with specializations
└── main.cpp                   # Demonstration application
```

## Building the Project

### Prerequisites

- CMake 3.20 or higher
- C++23 compatible compiler (GCC 11+, Clang 12+, MSVC 2019+)
- VCPKG (optional, for dependency management)

### Build Instructions

```bash
# Configure the project
cmake -B build -S .

# Build the project
cmake --build build

# Run the executable
./build/app_manager
```

### Windows-Specific Setup

The project includes Windows-specific configuration in `cmake/setup-windows.cmake` for enhanced compatibility when building on Windows platforms.

## Usage Example

```cpp
#include "devices/ADevice.h"
#include "devices/BDevice.h"
#include "devicemanager/DeviceManager.h"

int main() {
    // Create devices
    ADevice a_device;
    BDevice b_device;
    
    // Create specialized device managers
    DeviceManager<ADevice> a_manager;
    DeviceManager<BDevice> b_manager;
    
    // Add devices to managers
    a_manager.addDevice(&a_device);
    b_manager.addDevice(&b_device);
    
    // Perform device-specific operations
    a_manager.startAll();           // Transitions ADevices to RUNNING state
    b_manager.powerOnAll();         // Transitions BDevices to STANDBY state
    b_manager.activateAll();        // Transitions BDevices to ACTIVE state
    
    // Display current status
    a_manager.displayAllStatus();
    b_manager.displayAllStatus();
    
    return 0;
}
```

## Key Features

### State Transition Management
- Each device defines valid state transitions with conditional logic
- Transition requests are validated against device-specific rules
- Failed transitions are logged and handled gracefully

### Device Manager Specializations
- **ADevice Manager**: `startAll()`, `stopAll()`, `reportErrorToAll()`, `recoverFromError()`
- **BDevice Manager**: `powerOnAll()`, `powerOffAll()`, `activateAll()`, `putAllInMaintenance()`

### Error Handling
- Conditional state transitions (e.g., cannot recover from CRITICAL errors)
- Maintenance mode restrictions (e.g., HARDWARE_FAILURE prevents recovery)
- Comprehensive status reporting

## Design Benefits

1. **Type Safety**: Compile-time checking prevents invalid device operations
2. **Performance**: No virtual function overhead, template-based dispatch
3. **Extensibility**: New device types can be added with minimal code changes
4. **Maintainability**: Device-specific logic isolated in specialized managers
5. **Testability**: Each component can be tested independently

## Extending the System

To add a new device type:

1. Define device-specific states in `states/CStates.h`
2. Implement the device class following `ADevice`/`BDevice` pattern
3. Create a manager specialization in `DeviceManager.h`
4. Add device-specific operations in the specialized manager

## License

This project is provided as a reference implementation for educational purposes.