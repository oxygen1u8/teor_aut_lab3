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

    this->row_count = states.size();
    this->column_count = states[0].size();

    table = new std::vector<s_couple> *[column_count];
    for (uint32_t i = 0; i < column_count; i++) {
        table[i] = new std::vector<s_couple> [column_count];
    }

    int32_t sort_data[2];
    int32_t tmp;

    int32_t state1, state2;

    bool is_comp = true;
    for (uint32_t i = 0; i < column_count; i++) {
        for (uint32_t j = i; j < column_count - 1; j++) {
            uint32_t real_j = j + 1;
            for (uint32_t k = 0; k < row_count; k++) {
                if (states[k][i] > 0 && states[k][real_j] > 0) {
                    for (uint32_t a = 0; a < row_count; a++) {
                        if (outputs[a][i] > 0 && outputs[a][real_j] > 0
                            && outputs[a][i] != outputs[a][real_j]) {
                            is_comp = false;
                            break;
                        }
                    }
                    sort_data[0] = states[k][i];
                    sort_data[1] = states[k][real_j];

                    if (sort_data[0] > sort_data[1]) {
                        tmp = sort_data[1];
                        sort_data[1] = sort_data[0];
                        sort_data[0] = tmp;
                    }

                    std::vector<s_couple> temp_vector = table[i][real_j];
                    
                    bool is_exist = false;
                    if (temp_vector.size() > 0) {
                        for (uint32_t i = 0; i < temp_vector.size(); i++) {
                            if (temp_vector[i].get_state1() == sort_data[0]
                                && temp_vector[i].get_state2() == sort_data[1]) {
                                is_exist = true;
                                break;
                            }
                        }
                    }

                    if (!is_exist) {
                        table[i][real_j].push_back(s_couple(sort_data[0],
                            sort_data[1], is_comp));
                    }
                    is_comp = true;
                }
            }
        }
    }
}

std::vector<s_couple> **pre_comp_table::get_pre_table()
{
    return this->table;
}

std::vector<std::vector<int32_t>> pre_comp_table::get_states()
{
    return this->states;
}

std::vector<std::vector<int32_t>> pre_comp_table::get_outputs()
{
    return this->outputs;
}

pre_comp_table::~pre_comp_table()
{
    if (this->table != nullptr) {
        for (uint32_t i = 0; i < column_count; i++) {
            delete [] this->table[i];
        }
        this->table = nullptr;
    }
}
