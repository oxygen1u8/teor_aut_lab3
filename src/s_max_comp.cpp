#include "classes.h"
#include <algorithm>

static uint32_t get_cover(std::vector<int32_t> a, std::vector<int32_t> b)
{
    auto max_size = (b.size() >= a.size()) ? b.size() : a.size();
    auto new_a = (b.size() >= a.size()) ? b : a;
    auto new_b = (b.size() >= a.size()) ? a : b;

    uint32_t count = 0;

    for (uint32_t i = 0; i < max_size; i++) {
        for (uint32_t j = 0; j < new_b.size(); j++) {
            if (new_a[i] == new_b[j]) {
                count += 1;
            }
        }
    }

    return count;
}

static std::vector<std::vector<int32_t>> third_step(std::vector<std::vector<int32_t>> &max_classes,
    std::vector<int32_t> sec)
{
    std::vector<std::vector<int32_t>> tmp_classes;
    for (uint32_t i = 0; i < max_classes.size(); i++) {
        std::vector<int32_t> tmp = max_classes[i];
        tmp_classes.push_back(std::vector<int32_t>());
        for (uint32_t j = 0; j < tmp.size(); j++) {
            for (uint32_t k = 0; k < sec.size(); k++) {
                if (tmp[j] == sec[k]) {
                    tmp_classes[i].push_back(tmp[j]);
                }
            }
        }
    }
    return tmp_classes;
}

static void fourth_step(std::vector<std::vector<int32_t>> &third,
    uint32_t state)
{
    for (uint32_t i = 0; i < third.size(); i++) {
        third[i].push_back(state);
        std::sort(third[i].begin(), third[i].end());
    }
}

static uint32_t fith_step(std::vector<std::vector<int32_t>> &max_classes,
    std::vector<std::vector<int32_t>> &fourth)
{
    for (uint32_t i = 0; i < fourth.size(); i++) {
        max_classes.push_back(fourth[i]);
    }

    return fourth.size();
}

static bool check_on_sub(std::vector<int32_t> a, std::vector<int32_t> b)
{
    bool result = true;
    uint32_t min_size = 0;
    uint32_t count = 0;

    if (a.size() >= b.size()) {
        return false;
    }

    min_size = a.size();

    for (uint32_t i = 0; i < b.size(); i++) {
        for (uint32_t j = 0; j < min_size; j++) {
            if (a[j] == b[i]) {
                count += 1;
            }
            if (count == min_size) {
                return true;
            }
        }
    }

    if (count == min_size) {
        return true;
    }

    return false;
}

static void sixth_step(std::vector<std::vector<int32_t>> &max_classes,
    uint32_t add_size)
{
    std::vector<int32_t> tmp, tmp2;

a1:
    uint32_t curr_size = max_classes.size();
    for (uint32_t i = 0; i < curr_size; i++) {
        tmp = max_classes[i];
        tmp2 = max_classes[curr_size - 1 - i];

        if (check_on_sub(tmp, tmp2)) {
            max_classes.erase(max_classes.begin() + i);
            goto a1;
        }
    }
}

s_max_comp::s_max_comp(f_comp_table &_f_comp_table)
{
    int32_t **f_table = _f_comp_table.get_table();
    uint32_t state_count = _f_comp_table.get_table_size();
    this->states = _f_comp_table.get_states();
    this->outputs = _f_comp_table.get_outputs();
    this->new_states = std::vector<std::vector<int32_t>>(this->states.size());
    this->new_outputs = std::vector<std::vector<int32_t>>(this->outputs.size());

    // for (uint32_t i = 0; i < state_count; i++) {
    //     for (uint32_t j = 0; j < state_count; j++) {
    //         printf("%2d ", f_table[i][j]);
    //     }
    //     printf("\r\n");
    // }

    this->max_classes.push_back(std::vector<int32_t>(1, state_count));
    // this->max_classes[0].push_back(state_count);

    std::vector<int32_t> tmp;
    std::vector<int32_t> tmp2;

    for (uint32_t i = 1; i < state_count; i++) {
        for (uint32_t j = state_count - i; j < state_count; j++) {
            if (f_table[j][state_count - 1 - i] > 0) {
                tmp.push_back(j + 1);
            }
        }
        auto third = third_step(this->max_classes, tmp);
        fourth_step(third, state_count - i);
        uint32_t add_size = fith_step(this->max_classes, third);
        sixth_step(this->max_classes, add_size);
        tmp.clear();
    }
    
    for (uint32_t i = 0; i < this->new_states.size(); i++) {
        for (uint32_t j = 0; j < this->max_classes.size(); j++) {
            this->new_states[i].push_back(0);
            this->new_outputs[i].push_back(0);
        }
    }

    (void) 0;
}

void s_max_comp::sort()
{
    for (uint32_t i = 0; i < this->max_classes.size(); i++) {
        auto tmp = this->max_classes[i];
        for (uint32_t j = i; j < this->max_classes.size() - 1; j++) {
            auto real_j = j + 1;
            auto tmp2 = this->max_classes[real_j];
            auto min_size = (tmp.size() <= tmp2.size()) ? tmp.size() : tmp2.size();
            for (uint32_t k = 0; k < min_size; k++) {
                if (tmp[k] > tmp2[k]) {
                    this->max_classes[i] = tmp2;
                    this->max_classes[real_j] = tmp;
                    tmp = this->max_classes[i];
                    break;
                }
            }
        }
    }
}

void s_max_comp::make_state_table()
{
    uint32_t max_cover = 0;
    uint32_t max_index = 0;
    std::vector<uint32_t> max_covers;

    for (uint32_t i = 0; i < this->max_classes.size(); i++) {
        std::vector<int32_t> tmp;
        for (uint32_t j = 0; j < this->states.size(); j++) {
            for (uint32_t k = 0; k < this->max_classes[i].size(); k++) {
                auto tmp_index = this->max_classes[i][k];
                tmp.push_back(this->states[j][tmp_index - 1]);
            }
            for (uint32_t k = 0; k < this->max_classes.size(); k++) {
                auto tmp_max = get_cover(tmp, this->max_classes[k]);
                max_covers.push_back(tmp_max);

                if (tmp_max > max_cover) {
                    max_cover = tmp_max;
                    max_index = k;
                }

            }

            // if (max_cover == max_covers[i]) {
            //     max_index = i;
            // }

            this->new_states[j][i] = max_index + 1;
            max_cover = 0;
            max_index = 0;
            max_covers.clear();
            tmp.clear();
        }
    }
}

void s_max_comp::make_output_table()
{
    std::vector<int32_t> outputs;
    for (uint32_t i = 0; i < this->max_classes.size(); i++) {
        auto tmp = this->max_classes[i];
        for (uint32_t k = 0; k < this->outputs.size(); k++) {
            for (uint32_t j = 0; j < tmp.size(); j++) {
                auto index = tmp[j] - 1;
                outputs.push_back(this->outputs[k][index]);
            }
            std::sort(outputs.begin(), outputs.end(), std::greater());
            this->new_outputs[k][i] = outputs[0];
            outputs.clear();
        }
    }

    (void) outputs;
}

void s_max_comp::print()
{
    for (uint32_t i = 0; i < this->max_classes.size(); i++) {
        for (uint32_t j = 0; j < this->max_classes[i].size(); j++) {
            printf("s%d", this->max_classes[i][j]);
        }

        printf(" -> s%d\r\n", i + 1);
    }

    printf("fs min:\r\n");
    for (uint32_t i = 0; i < this->new_states.size(); i++) {
        for (uint32_t j = 0; j < this->new_states[i].size(); j++) {
            printf("%2d ", this->new_states[i][j]);
        }
        printf("\r\n");
    }

    printf("\r\nfy min:\r\n");
    for (uint32_t i = 0; i < this->new_outputs.size(); i++) {
        for (uint32_t j = 0; j < this->new_outputs[i].size(); j++) {
            printf("%2d ", this->new_outputs[i][j]);
        }
        printf("\r\n");
    }
}
