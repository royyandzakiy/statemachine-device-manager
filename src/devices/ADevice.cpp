#include "ADevice.h"
#include <iostream>

ADevice::ADevice() : state_machine_(AStates::IDLE), error_message_("") {
    setupTransitions();
}

void ADevice::setupTransitions() {
    state_machine_.addTransition(AStates::IDLE, AStates::RUNNING);
    state_machine_.addTransition(AStates::RUNNING, AStates::IDLE);
    state_machine_.addTransition(AStates::RUNNING, AStates::ERROR);
    state_machine_.addTransition(AStates::IDLE, AStates::ERROR);
    
    state_machine_.addTransition(AStates::ERROR, AStates::IDLE, 
        [this](AStates::State) -> bool {
            return error_message_ != "CRITICAL";
        });
}

bool ADevice::requestTransition(AStates::State new_state) {
    return state_machine_.transitionTo(new_state);
}

std::string ADevice::getCurrentStateName() const {
    return AStates::stateToString(state_machine_.getCurrentState());
}

void ADevice::displayStatus() const {
    std::cout << "ADevice: State = " << getCurrentStateName();
    if (state_machine_.getCurrentState() == AStates::ERROR) {
        std::cout << " (" << error_message_ << ")";
    }
    std::cout << std::endl;
}