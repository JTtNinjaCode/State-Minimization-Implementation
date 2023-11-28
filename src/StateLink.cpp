#include "StateLink.h"

std::istream& operator>>(std::istream& in, StateLink& state_link) {
    std::string temp;
    in >> temp;
    state_link.input = temp;
    in >> temp;
    state_link.present_state = temp;
    in >> temp;
    state_link.next_state = temp;
    in >> temp;
    state_link.output = temp;
    return in;
}
std::ostream& operator<<(std::ostream& out, const StateLink& state_link) {
    out << state_link.input << ' ' << state_link.present_state << ' ' << state_link.next_state << ' ' << state_link.output;
    return out;
}