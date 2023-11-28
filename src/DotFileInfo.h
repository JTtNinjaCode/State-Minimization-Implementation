#ifndef DOT_FILE_INFO_H
#define DOT_FILE_INFO_H

#include <string>
#include <iostream>
#include <set>

#include "StateLink.h"
#include "KissFileInfo.h"

class DotFileInfo {
public:
    DotFileInfo(const KissFileInfo &kiss_file_info) :
    start_state(kiss_file_info.start_state),
    state_links(kiss_file_info.state_links)
    {
        for(auto state_link: state_links) {
            state_names.insert(state_link.next_state);
            state_names.insert(state_link.present_state);
        }
    }
private:
    std::string start_state;
    std::set<std::string> state_names;
    std::vector<StateLink> state_links;

    friend std::ostream& operator<<(std::ostream& out, const DotFileInfo& dot_file_info);
};
#endif