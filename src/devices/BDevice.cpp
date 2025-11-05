#include "BDevice.h"
#include <iostream>

BDevice::BDevice() : state_machine_(BStates::OFF), maintenance_reason_("") {
    setupTransitions();
}

void BDevice::setupTransitions() {
    state_machine_.addTransition(BStates::OFF, BStates::STANDBY);
    state_machine_.addTransition(BStates::STANDBY, BStates::OFF);
    state_machine_.addTransition(BStates::STANDBY, BStates::ACTIVE);
    state_machine_.addTransition(BStates::ACTIVE, BStates::STANDBY);
    state_machine_.addTransition(BStates::ACTIVE, BStates::MAINTENANCE);
    state_machine_.addTransition(BStates::STANDBY, BStates::MAINTENANCE);
    
    state_machine_.addTransition(BStates::MAINTENANCE, BStates::STANDBY, 
        [this](BStates::State) -> bool {
            return maintenance_reason_ != "HARDWARE_FAILURE";
        });
}

bool BDevice::requestTransition(BStates::State new_state) {
    return state_machine_.transitionTo(new_state);
}

std::string BDevice::getCurrentStateName() const {
    return BStates::stateToString(state_machine_.getCurrentState());
}

void BDevice::displayStatus() const {
    std::cout << "BDevice: State = " << getCurrentStateName();
    if (state_machine_.getCurrentState() == BStates::MAINTENANCE) {
        std::cout << " (" << maintenance_reason_ << ")";
    }
    std::cout << std::endl;
}