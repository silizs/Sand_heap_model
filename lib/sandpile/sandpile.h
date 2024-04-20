#include <iostream>
#include <vector>
#include <unordered_set>

struct node {
    uint64_t key;
    node* right;
    node* left;
    node* up;
    node* down;
    node(uint64_t x) : right(nullptr), left(nullptr), up(nullptr), down(nullptr), key(x)
    {
    }
};

struct matrix {
    uint16_t length;
    uint16_t width;
    node* start = nullptr;
    node* last = nullptr;
    node* start_i = nullptr;
    std::unordered_set<node*> mountains_of_sand;

    matrix(uint16_t& length, uint16_t& width, std::vector<uint64_t>& array) : length(length), width(width) {
        for (uint16_t i = 0; i < length; ++i) {
            for (uint16_t j = 0; j < width; ++j) {
                node* el = new node(array[i * width + j]);
                if (el->key >= 4) mountains_of_sand.insert(el);
                if (i == 0) {
                    if (j == 0) {
                        start = el;
                        start_i = el;
                    } else {
                        el->left = last;
                        last->right = el;
                    }
                } else {
                    if (j == 0) {
                        el->up = start_i;
                        start_i->down = el;
                        start_i = el;
                    } else {
                        el->left = last;
                        last->right = el;
                        el->left->up->right->down = el;
                        el->up = el->left->up->right;
                    }
                }

                last = el;
            }
        }
    }

    void add_a_line_at_the_top();
    void add_a_line_at_the_bottom();
    void add_a_column_to_the_left();
    void add_a_column_to_the_right();

    void renewal();

    ~matrix();
};
