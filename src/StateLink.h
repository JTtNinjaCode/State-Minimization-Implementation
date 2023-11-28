#ifndef STATE_H
#define STATE_H

#include <string>
#include <iostream>

struct StateLink {
    std::string present_state;
    std::string input;
    std::string output;
    std::string next_state;

    friend std::istream& operator>>(std::istream& in, StateLink& state_link);
    friend std::ostream& operator<<(std::ostream& out, const StateLink& state_link);
};
#endif