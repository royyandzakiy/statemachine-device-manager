#ifndef BDEVICE_H
#define BDEVICE_H

#include "../states/BStates.h"
#include "../statemachine/StateMachine.h"
#include <string>
#include <functional>

class BDevice {
private:
    StateMachine<BStates::State> state_machine_;
    std::string maintenance_reason_;
    
public:
    BDevice();
    
    // Direct state machine access for DeviceManager
    bool requestTransition(BStates::State new_state);
    BStates::State getCurrentState() const { return state_machine_.getCurrentState(); }
    std::string getCurrentStateName() const;
    
    // State data access
    const std::string& getMaintenanceReason() const { return maintenance_reason_; }
    void setMaintenanceReason(const std::string& reason) { maintenance_reason_ = reason; }
    
    void displayStatus() const;
    
private:
    void setupTransitions();
};

#endif