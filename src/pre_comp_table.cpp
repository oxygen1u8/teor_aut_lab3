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

    // for (uint32_t i = 0; i < states.size(); i++) {
    //     for (uint32_t j = 0; j < states[i].size(); j++) {
    //         std::cout << states[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << std::endl;

    // for (uint32_t i = 0; i < outputs.size(); i++) {
    //     for (uint32_t j = 0; j < outputs[i].size(); j++) {
    //         std::cout << outputs[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    uint32_t row_count = states.size();
    uint32_t column_count = states[0].size();

    
}
