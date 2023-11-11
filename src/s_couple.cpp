#include "classes.h"

s_couple::s_couple()
{
    this->state1 = 0;
    this->state2 = 0;
    this->is_comp = 0;
}

s_couple::s_couple(int32_t state1, int32_t state2, bool is_comp)
{
    this->state1 = state1;
    this->state2 = state2;

    this->is_comp = is_comp;   
}

void s_couple::set_states(int32_t state1, int32_t state2)
{
    this->state1 = state1;
    this->state2 = state2;
}

void s_couple::set_comp(bool is_comp)
{
    this->is_comp = is_comp;
}

std::vector<int32_t> s_couple::get_states()
{
    std::vector<int32_t> states;

    states.push_back(state1);
    states.push_back(state2);

    return states;
}

bool s_couple::get_comp()
{
    return this->is_comp;
}
