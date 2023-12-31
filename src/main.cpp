#include <iostream>
#include <fstream>
#include "classes.h"

#define STATE_TABLE_FILE  "f_table.txt"
#define OUTPUT_TABLE_FILE "g_table.txt"

int main()
{
    std::ifstream state_file(STATE_TABLE_FILE);
    std::ifstream output_file(OUTPUT_TABLE_FILE);

    pre_comp_table _pre_comp_table(state_file, output_file);
    f_comp_table _f_comp_table(_pre_comp_table);
    s_max_comp _s_max_comp(_f_comp_table);

    _s_max_comp.sort();
    _s_max_comp.make_state_table();
    _s_max_comp.make_output_table();

    _s_max_comp.print();

    return 0;
}
