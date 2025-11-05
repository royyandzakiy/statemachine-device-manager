#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <iostream>
#include <vector>
#include <functional>

// Generic DeviceManager template
template<typename DeviceType>
class DeviceManager {
private:
    std::vector<DeviceType*> devices_;
    
public:
    void addDevice(DeviceType* device) {
        devices_.push_back(device);
    }
    
    // Generic transition operation - logic is passed in via function
    void operateOnAll(std::function<void(DeviceType&)> operation) {
        for (auto* device : devices_) {
            operation(*device);
        }
    }
    
    void displayAllStatus() {
        std::cout << "=== Device Status ===" << std::endl;
        operateOnAll([](DeviceType& device) {
            device.displayStatus();
        });
    }
};

// Specialized operations for ADevice
template<>
class DeviceManager<ADevice> {
private:
    std::vector<ADevice*> devices_;
    
public:
    void addDevice(ADevice* device) {
        devices_.push_back(device);
    }
    
    // ADevice-specific operations
    void startAll() {
        std::cout << "Starting all ADevices..." << std::endl;
        for (auto* device : devices_) {
            device->requestTransition(AStates::RUNNING);
        }
    }
    
    void stopAll() {
        std::cout << "Stopping all ADevices..." << std::endl;
        for (auto* device : devices_) {
            device->requestTransition(AStates::IDLE);
        }
    }
    
    void reportErrorToAll(const std::string& message) {
        std::cout << "Reporting error to all ADevices: " << message << std::endl;
        for (auto* device : devices_) {
            device->setErrorMessage(message);
            device->requestTransition(AStates::ERROR);
        }
    }
    
    void recoverFromError() {
        std::cout << "Attempting to recover all ADevices from error..." << std::endl;
        for (auto* device : devices_) {
            device->requestTransition(AStates::IDLE);
        }
    }
    
    void displayAllStatus() {
        std::cout << "=== ADevice Status ===" << std::endl;
        for (auto* device : devices_) {
            device->displayStatus();
        }
    }
};

// Specialized operations for BDevice
template<>
class DeviceManager<BDevice> {
private:
    std::vector<BDevice*> devices_;
    
public:
    void addDevice(BDevice* device) {
        devices_.push_back(device);
    }
    
    // BDevice-specific operations
    void powerOnAll() {
        std::cout << "Powering on all BDevices..." << std::endl;
        for (auto* device : devices_) {
            device->requestTransition(BStates::STANDBY);
        }
    }
    
    void powerOffAll() {
        std::cout << "Powering off all BDevices..." << std::endl;
        for (auto* device : devices_) {
            device->requestTransition(BStates::OFF);
        }
    }
    
    void activateAll() {
        std::cout << "Activating all BDevices..." << std::endl;
        for (auto* device : devices_) {
            device->requestTransition(BStates::ACTIVE);
        }
    }
    
    void putAllInMaintenance(const std::string& reason) {
        std::cout << "Putting all BDevices in maintenance: " << reason << std::endl;
        for (auto* device : devices_) {
            device->setMaintenanceReason(reason);
            device->requestTransition(BStates::MAINTENANCE);
        }
    }
    
    void recoverFromMaintenance() {
        std::cout << "Attempting to recover all BDevices from maintenance..." << std::endl;
        for (auto* device : devices_) {
            device->requestTransition(BStates::STANDBY);
        }
    }
    
    void displayAllStatus() {
        std::cout << "=== BDevice Status ===" << std::endl;
        for (auto* device : devices_) {
            device->displayStatus();
        }
    }
};

#endif