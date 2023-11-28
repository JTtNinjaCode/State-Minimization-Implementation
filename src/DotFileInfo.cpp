#include "DotFileInfo.h"

std::ostream& operator<<(std::ostream& out, const DotFileInfo& dot_file_info) {

    out << "digraph STG {\n";
    out << "\trankdir=LR;\n";
    out << "\n";
    out << "\tINIT [shape=point]\n";
    for (auto &name: dot_file_info.state_names) {
        out << '\t' << name << " [label=\"" << name << "\"]\n";
    }
    out << "\n";
    out << "\tINIT -> " << dot_file_info.start_state << '\n';
    for (auto &state_link: dot_file_info.state_links) {
        out << '\t' << state_link.present_state << " -> " << state_link.next_state << " [label=\"" << state_link.input << '/' << state_link.output<< "\"];\n";
    }
    out << '}';
    return out;
}