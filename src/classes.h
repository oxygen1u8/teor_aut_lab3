#ifndef CLASSES_H
#define CLASSES_H

#include <vector>
#include <iostream>
#include <fstream>

class s_couple {
    private:
        int32_t state1;
        int32_t state2;
        bool is_comp;
    public:
        s_couple();
        s_couple(int32_t state1, int32_t state2, bool is_comp);
        void set_states(int32_t state1, int32_t state2);
        void set_comp(bool is_comp);
        std::vector<int32_t> get_states();
        bool get_comp();
};

class comp_table {
    private:
    protected:
        std::vector<s_couple> table;
    public:
};

class pre_comp_table : public comp_table {
    private:
        
    public:
        pre_comp_table(std::ifstream &, std::ifstream &);
};

#endif
