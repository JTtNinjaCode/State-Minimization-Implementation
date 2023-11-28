#ifndef KISS_FILE_INFO_H
#define KISS_FILE_INFO_H

#include <string>
#include <iostream>
#include <vector>

#include "StateLink.h"

struct KissFileInfo {
    unsigned int input_count;
    unsigned int output_count;
    unsigned int state_link_count;
    unsigned int state_count;
    std::string start_state;
    std::vector<StateLink> state_links;

    friend std::istream& operator>>(std::istream& in, KissFileInfo& kiss_file_info);
    friend std::ostream& operator<<(std::ostream& out, const KissFileInfo& kiss_file_info);
};

#endif