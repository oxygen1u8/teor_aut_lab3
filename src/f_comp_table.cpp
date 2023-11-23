#include "classes.h"

static void get_ncomp_states(std::vector<s_couple> **table, int32_t **f_table,
    int32_t state1, int32_t state2, uint32_t state_count)
{
    f_table[state1][state2] = -1;

    std::vector<s_couple> tmp;
    uint32_t real_j;

    for (uint32_t i = 0; i < state_count; i++) {
        for (uint32_t j = i; j < state_count - 1; j++) {
            real_j = j + 1;
            tmp = table[i][real_j];
            if (tmp.size() > 0) {
                for (uint32_t k = 0; k < tmp.size(); k++) {
                    if ((state1 + 1) == tmp[k].get_state1()
                        && (state2 + 1) == tmp[k].get_state2()) {
                        get_ncomp_states(table, f_table, i,
                            real_j, state_count);
                    }
                }
            }
        }
    }
}

f_comp_table::f_comp_table(pre_comp_table &_pre_comp_table)
{
    this->pre_table = _pre_comp_table.get_pre_table();
    this->states = _pre_comp_table.get_states();
    this->outputs = _pre_comp_table.get_outputs();

    uint32_t state_count = this->states[0].size();

    this->f_table = new int32_t*[state_count];
    for (uint32_t i = 0; i < state_count; i++) {
        this->f_table[i] = new int32_t[state_count];
    }

    for (uint32_t i = 0; i < state_count; i++) {
        for (uint32_t j = 0; j < state_count; j++) {
            this->f_table[i][j] = 1;
        }
    }

    bool is_comp = true;
    std::vector<s_couple> tmp;
    for (uint32_t i = 0; i < state_count; i++) {
        for (uint32_t j = 0; j < state_count; j++) {
            tmp = this->pre_table[i][j];
            for (uint32_t k = 0; k < tmp.size(); k++) {
                if (!tmp[k].get_comp()) {
                    get_ncomp_states(this->pre_table, this->f_table,
                        i, j, state_count);
                }
            }
        }
    }

    for (uint32_t i = 0; i < state_count; i++) {
        for (uint32_t j = 0; j < i; j++) {
            f_table[i][j] = f_table[j][i];
        }
    }

    for (uint32_t i = 0; i < state_count; i++) {
        for (uint32_t j = 0; j < state_count; j++) {
            if (i <= j)
                f_table[i][j] = 0;
        }
    }
}

int32_t** f_comp_table::get_table()
{
    return this->f_table;
}

uint32_t f_comp_table::get_table_size()
{
    return this->states.at(0).size();
}

std::vector<std::vector<int32_t>> f_comp_table::get_states()
{
    return this->states;
}

std::vector<std::vector<int32_t>> f_comp_table::get_outputs()
{
    return this->outputs;
}
