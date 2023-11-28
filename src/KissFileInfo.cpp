#include "KissFileInfo.h"
#include <sstream>

std::istream& operator>>(std::istream& in, KissFileInfo& kiss_file_info) {
    while(true){
        std::string temp;
        std::getline(in, temp);
        std::stringstream line(temp);
        std::string token;
        line >> token;
        if (token == ".start_kiss"){
        } else if (token == ".i"){
            std::string value;
            line >> value;
            kiss_file_info.input_count = std::stoi(value);
        } else if (token == ".o") {
            std::string value;
            line >> value;
            kiss_file_info.output_count = std::stoi(value);
        } else if (token == ".p") {
            std::string value;
            line >> value;
            kiss_file_info.state_link_count = std::stoi(value);
        } else if (token == ".s") {
            std::string value;
            line >> value;
            kiss_file_info.state_count = std::stoi(value);
        } else if (token == ".r") {
            std::string value;
            line >> value;
            kiss_file_info.start_state = value;
        } else if (token == ".end_kiss"){
            return in;
        } else {
            StateLink state_link;
            std::stringstream line(temp);
            line >> state_link;
            kiss_file_info.state_links.push_back(state_link);
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const KissFileInfo& kiss_file_info) {
    out << ".start_kiss" << '\n';
    out << ".i " << kiss_file_info.input_count << '\n';
    out << ".o " << kiss_file_info.output_count << '\n';
    out << ".p " << kiss_file_info.state_link_count << '\n';
    out << ".s " << kiss_file_info.state_count <<'\n';
    out << ".r " << kiss_file_info.start_state <<'\n';
    for (size_t i = 0; i < kiss_file_info.state_link_count; i++)
    {
        out << kiss_file_info.state_links[i] << '\n';
    }
    out << ".end_kiss";
    return out;
}