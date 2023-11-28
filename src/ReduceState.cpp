#include "ReduceState.h"
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <type_traits>

using State = std::string;
using StatePair = std::pair<State, State>;
using Index = std::pair<int, int>;
using Input = std::string;

struct ImplicantElement {
    StatePair state_pair;
    std::vector<std::pair<Input, StatePair>> input_next_states;
    bool is_same = false;
};

auto state_link_equal = [] (const StateLink &a, const StateLink &b) {
    return a.output == b.output;
};

using Results = std::list<StateLink>;

struct StatePairHash {
    std::size_t operator()(const StatePair &c) const {
        return std::hash<std::string>()(c.first) ^ std::hash<std::string>()(c.second);
    }
};

std::unordered_map<StatePair, Index, StatePairHash> search_table;

void deleteRecord(const ImplicantElement &implicant_element, std::map<State, std::pair<Results, bool>> &table, State &init_state) {
    const State &delete_state = implicant_element.state_pair.first;
    const State &target_state = implicant_element.state_pair.second;
    for (auto &record : table) {
        bool &is_record_valid = record.second.second;
        if (is_record_valid == false) {
            continue;
        } else if (record.first == delete_state) {
            if (delete_state == init_state)
                init_state = target_state;
            is_record_valid = false;
            continue;
        } else {
            auto &links = record.second.first;
            for (auto &link : links) {
                if (link.next_state == delete_state) {
                    link.next_state = target_state;
                }
            }
        }
    }
}

void reduceState(KissFileInfo &kiss_file_info) {
    auto &links = kiss_file_info.state_links;
    std::map<State, std::pair<Results, bool>> result_table;

    for (auto link :links) {
        State state_name = link.present_state;
        result_table.insert(std::pair<State, std::pair<Results, bool>>(state_name, {Results{}, true}));
        auto result_iter = result_table.find(state_name);
        result_iter->second.first.push_back(link);
    }
    std::vector<std::vector<ImplicantElement>> implicant_table(kiss_file_info.state_count);
    for (auto &v: implicant_table) {
        v.resize(kiss_file_info.state_count);
    }

    // build implicant table
    int i = 0;
    for (auto &record_1: result_table) {
        int j = 0;
        for (auto &record_2: result_table) {
            bool is_same = std::equal(record_1.second.first.begin(), record_1.second.first.end(), record_2.second.first.begin(), state_link_equal) << '\n';
            auto &implicant_element = implicant_table[i][j];
            implicant_element.state_pair = {record_1.first, record_2.first};
            implicant_element.is_same = is_same;
            implicant_element.input_next_states.resize(record_1.second.first.size());
            [] (auto begin_1, auto end_1, auto begin_2, auto out_iter) {
                while (begin_1 != end_1) {
                    out_iter->first = begin_1->input;
                    out_iter->second = {begin_1->next_state, begin_2->next_state};
                    begin_1++;
                    begin_2++;
                    out_iter++;
                }
            } (record_1.second.first.begin(), record_1.second.first.end(), record_2.second.first.begin(), implicant_element.input_next_states.begin());
            search_table.insert({{record_1.first, record_2.first}, {i, j}});
            j++;
        }
        i++;
    }

    bool have_revise;
    do {
        have_revise = false;
        for (size_t i = 0; i < kiss_file_info.state_count; i++)
        {
            for (size_t j = 0; j < kiss_file_info.state_count; j++)
            {
                auto &implicant_element = implicant_table[i][j];
                for (auto &record : implicant_element.input_next_states) {
                    auto index_i = search_table[record.second].first, index_j = search_table[record.second].second;
                    if (implicant_table[index_i][index_j].is_same == false && implicant_element.is_same == true) {
                        implicant_element.is_same = false;
                        have_revise = true;
                    }
                }
            }
        }
    } while(have_revise);

    State &init_state = kiss_file_info.start_state;
    for (size_t i = 1; i < kiss_file_info.state_count; i++)
    {
        for (size_t j = 0; j < i; j++)
        {
            auto &implicant_element = implicant_table[i][j];
            if (implicant_element.is_same) {
                deleteRecord(implicant_element, result_table, init_state);
            }
        }
    }
    unsigned int counter = 0;
    links.clear();
    for (auto &record : result_table)
    {
        if (record.second.second) {
            for (auto &result: record.second.first) {
                links.push_back(result);
            }
            counter++;
        }
    }
    kiss_file_info.state_count = counter;
    kiss_file_info.state_link_count = links.size();
}