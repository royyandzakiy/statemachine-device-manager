#ifndef ASTATES_H
#define ASTATES_H

namespace AStates {
    enum State {
        IDLE,
        RUNNING, 
        ERROR
    };
    
    inline const char* stateToString(State state) {
        switch(state) {
            case IDLE: return "IDLE";
            case RUNNING: return "RUNNING";
            case ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }
}

#endif