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
        void set_comp(bool is_comp);
        int32_t get_state1();
        int32_t get_state2();
        bool get_comp();
};

class comp_table {
    private:
    protected:
    public:
};

class pre_comp_table : public comp_table {
    private:
        uint32_t row_count = 0;
        uint32_t column_count = 0;

        std::vector<std::vector<int32_t>> states;
        std::vector<std::vector<int32_t>> outputs;

        std::vector<s_couple> **table = nullptr;
    public:
        pre_comp_table(std::ifstream &, std::ifstream &);
        std::vector<s_couple> **get_pre_table();
        std::vector<std::vector<int32_t>> get_states();
        std::vector<std::vector<int32_t>> get_outputs();
        ~pre_comp_table();
};

class f_comp_table : public comp_table {
    private:
        int32_t **f_table;
        std::vector<std::vector<int32_t>> states;
        std::vector<std::vector<int32_t>> outputs;
        std::vector<s_couple> **pre_table = nullptr;
    public:
        f_comp_table(pre_comp_table &_pre_comp_table);
        int32_t **get_table();
        uint32_t get_table_size();
        std::vector<std::vector<int32_t>> get_states();
        std::vector<std::vector<int32_t>> get_outputs();

};

class s_max_comp {
    private:
        std::vector<std::vector<int32_t>> states;
        std::vector<std::vector<int32_t>> outputs;
        std::vector<std::vector<int32_t>> max_classes;
        std::vector<std::vector<int32_t>> new_states;
        std::vector<std::vector<int32_t>> new_outputs;
    public:
        s_max_comp(f_comp_table &);
        void sort();
        void make_state_table();
        void make_output_table();
        void print();
};

#endif
