#include <iostream>
#include "devices/ADevice.h"
#include "devices/BDevice.h"
#include "devicemanager/DeviceManager.h"

int main() {
    // Create devices
    ADevice a1, a2, a3;
    BDevice b1, b2;
    
    // Create device managers
    DeviceManager<ADevice> a_manager;
    DeviceManager<BDevice> b_manager;
    
    // Add devices to managers
    a_manager.addDevice(&a1);
    a_manager.addDevice(&a2);
    a_manager.addDevice(&a3);
    
    b_manager.addDevice(&b1);
    b_manager.addDevice(&b2);
    
    std::cout << "=== Initial State ===" << std::endl;
    a_manager.displayAllStatus();
    b_manager.displayAllStatus();
    
    std::cout << "\n=== Operating ADevices ===" << std::endl;
    a_manager.startAll();
    a_manager.displayAllStatus();
    
    std::cout << "\n=== Operating BDevices ===" << std::endl;
    b_manager.powerOnAll();
    b_manager.activateAll();
    b_manager.displayAllStatus();
    
    std::cout << "\n=== Error Scenarios ===" << std::endl;
    a_manager.reportErrorToAll("ROUTINE_ERROR");
    a_manager.displayAllStatus();
    
    std::cout << "\n=== Recovery from Routine Error ===" << std::endl;
    a_manager.recoverFromError();
    a_manager.displayAllStatus();
    
    std::cout << "\n=== Critical Error Scenario ===" << std::endl;
    a_manager.reportErrorToAll("CRITICAL");
    a_manager.displayAllStatus();
    
    std::cout << "\n=== Attempt Recovery from Critical (Should Fail) ===" << std::endl;
    a_manager.recoverFromError();
    a_manager.displayAllStatus();
    
    std::cout << "\n=== Maintenance Scenarios ===" << std::endl;
    b_manager.putAllInMaintenance("ROUTINE_CHECK");
    b_manager.displayAllStatus();
    
    std::cout << "\n=== Recovery from Routine Maintenance ===" << std::endl;
    b_manager.recoverFromMaintenance();
    b_manager.displayAllStatus();
    
    std::cout << "\n=== Critical Maintenance Scenario ===" << std::endl;
    b_manager.putAllInMaintenance("HARDWARE_FAILURE");
    b_manager.displayAllStatus();
    
    std::cout << "\n=== Attempt Recovery from Critical Maintenance (Should Fail) ===" << std::endl;
    b_manager.recoverFromMaintenance();
    b_manager.displayAllStatus();
    
    std::cout << "\n=== Final State ===" << std::endl;
    a_manager.displayAllStatus();
    b_manager.displayAllStatus();
    
    return 0;
}