#ifndef ADEVICE_H
#define ADEVICE_H

#include "../states/AStates.h"
#include "../statemachine/StateMachine.h"
#include <string>
#include <functional>

class ADevice {
private:
    StateMachine<AStates::State> state_machine_;
    std::string error_message_;
    
public:
    ADevice();
    
    // Direct state machine access for DeviceManager
    bool requestTransition(AStates::State new_state);
    AStates::State getCurrentState() const { return state_machine_.getCurrentState(); }
    std::string getCurrentStateName() const;
    
    // State data access
    const std::string& getErrorMessage() const { return error_message_; }
    void setErrorMessage(const std::string& message) { error_message_ = message; }
    
    void displayStatus() const;
    
private:
    void setupTransitions();
};

#endif