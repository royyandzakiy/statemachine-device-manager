#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <unordered_map>
#include <functional>
#include <string>
#include <iostream>

template<typename StateType>
class StateMachine {
private:
    StateType current_state_;
    std::unordered_map<std::string, std::function<bool(StateType)>> transitions_;
    
public:
    StateMachine(StateType initial_state) : current_state_(initial_state) {}
    
    bool transitionTo(StateType new_state) {
        std::string transition_key = std::to_string(current_state_) + "->" + std::to_string(new_state);
        
        if (transitions_.count(transition_key) && transitions_.at(transition_key)(current_state_)) {
            std::cout << "Transition: " << std::to_string(current_state_) 
                      << " -> " << std::to_string(new_state) << std::endl;
            current_state_ = new_state;
            return true;
        }
        
        std::cout << "Transition denied: " << std::to_string(current_state_) 
                  << " -> " << std::to_string(new_state) << std::endl;
        return false;
    }
    
    StateType getCurrentState() const { return current_state_; }
    
    void addTransition(StateType from, StateType to, 
                      std::function<bool(StateType)> condition = [](auto){ return true; }) {
        std::string key = std::to_string(from) + "->" + std::to_string(to);
        transitions_[key] = condition;
    }
};

#endif