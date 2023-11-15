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

    return 0;
}
