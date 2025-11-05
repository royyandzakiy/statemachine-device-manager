#ifndef BSTATES_H
#define BSTATES_H

namespace BStates {
    enum State {
        OFF,
        STANDBY,
        ACTIVE,
        MAINTENANCE
    };
    
    inline const char* stateToString(State state) {
        switch(state) {
            case OFF: return "OFF";
            case STANDBY: return "STANDBY";
            case ACTIVE: return "ACTIVE";
            case MAINTENANCE: return "MAINTENANCE";
            default: return "UNKNOWN";
        }
    }
}

#endif