#include "classes.h"

#include <string>
#include <vector>
#include <cstring>

static std::vector<int32_t> parse_string(std::string &str)
{
    uint32_t index = 0;
    char buff[1024];
    std::vector<int32_t> out;
    memset(buff, 0, sizeof(buff));

    for (uint32_t i = 0; i < str.length() + 1; i++, index++) {
        if (i > 0 && str[i - 1] == ' ') {
            index = 0;
            memset(buff, 0, sizeof(buff));
        }
        if (i == str.length()) {
            if (buff[0] == '-') {
                out.push_back(-1);
            } else {
                out.push_back(atoi(buff));
            }
            break;
        }
        if (str[i] != ' ') {
            buff[index] = str[i];
        } else {
            if (buff[0] == '-') {
                out.push_back(-1);
            } else {
                out.push_back(atoi(buff));
            }
        }
    }

    return out;
}

pre_comp_table::pre_comp_table(std::ifstream &state_file, std::ifstream &output_file)
{
    std::string str;
    std::vector<std::vector<int32_t>> states;
    std::vector<std::vector<int32_t>> outputs;

    while (!state_file.eof()) {
        std::getline(state_file, str);
        if (str.length() > 0) {
            states.push_back(parse_string(str));
        }
    }

    while (!output_file.eof()) {
        std::getline(output_file, str);
        if (str.length() > 0) {
            outputs.push_back(parse_string(str));
        }
    }

    std::vector<s_couple> couples;
    std::vector<std::vector<s_couple>> pre_table;

    uint32_t row_count = states.size();
    uint32_t column_count = states[0].size();
    
    for (uint32_t i = 0; i < column_count - 1; i++) {
        for (uint32_t j = i + 1; j < column_count; j++) {
            for (uint32_t k = 0; k < row_count; k++) {
                if (states[k][i] > 0 && states[k][j] > 0) {
                    bool comp = true;
                    if ((outputs[k][i] > 0 && outputs[k][j] > 0) &&
                        (outputs[k][i] != outputs[k][j])) {
                        comp = false;
                    }
                    uint32_t state1, state2;
                    if (states[k][i] > states[k][j]) {
                        state1 = states[k][j];
                        state2 = states[k][i];
                    } else {
                        state1 = states[k][i];
                        state2 = states[k][j];
                    }
                    s_couple tmp(state1, state2, comp);
                    couples.push_back(tmp);
                }
            }
        }
    }

    std::cout << "Hello, world!\n";
}
