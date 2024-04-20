#pragma once
#include "sandpile.h"

#include <iostream>

void matrix::add_a_line_at_the_top() {
    node* e = new node(0);
    e->down = start;
    start->up = e;
    start = e;
    last = start;
    while (last->down->right != nullptr) {
        node *el = new node(0);
        el->left = last;
        last->right = el;
        el->down = last->down->right;
        last->down->right->up = el;
        last = el;
    }
    length++;
}

void matrix::add_a_line_at_the_bottom() {
    last = start;
    while (last->down != nullptr) last = last->down;
    node* e = new node(0);
    e->up = last;
    last->down = e;
    last = e;
    while (last->up->right != nullptr) {
        node* el = new node(0);
        el->left = last;
        last->right = el;
        el->up = last->up->right;
        last->up->right->down = el;
        last = el;
    }
    length++;
}

void matrix::add_a_column_to_the_left() {
    node* e = new node(0);
    e->right = start;
    start->left = e;
    start = e;
    last = start;
    while (last->right->down != nullptr) {
        node *el = new node(0);
        el->up = last;
        last->down = el;
        el->right = last->right->down;
        last->right->down->left = el;
        last = el;
    }
    width++;
}

void matrix::add_a_column_to_the_right() {
    last = start;
    while (last->right != nullptr) last = last->right;
    node* e = new node(0);
    e->left = last;
    last->right = e;
    last = e;
    while (last->left->down != nullptr) {
        node* el = new node(0);
        el->up = last;
        last->down = el;
        el->left = last->left->down;
        last->left->down->right = el;
        last = el;
    }
    width++;
}

void matrix::renewal() {
    std::unordered_set<node*> mountains_of_sand_update;
    for (auto x : mountains_of_sand) {
        mountains_of_sand_update.insert(x);
    }

    for (auto mountain : mountains_of_sand_update) {
        node *element = mountain;

        element->key -= 4;
        if (element->key < 4) mountains_of_sand.erase(element);

        if (element->left == nullptr) add_a_column_to_the_left();
        element->left->key++;
        if (element->left->key >= 4) mountains_of_sand.insert(element->left);

        if (element->right == nullptr) add_a_column_to_the_right();
        element->right->key++;
        if (element->right->key >= 4) mountains_of_sand.insert(element->right);

        if (element->up == nullptr) add_a_line_at_the_top();
        element->up->key++;
        if (element->up->key >= 4) mountains_of_sand.insert(element->up);

        if (element->down == nullptr) add_a_line_at_the_bottom();
        element->down->key++;
        if (element->down->key >= 4) mountains_of_sand.insert(element->down);
    }
}

matrix::~matrix() {
    node* line = start;
    node* el = line;
    while (el->right != nullptr) {
        el = el->right;
        delete el->left;
    }
    delete el;
    while (line->down != nullptr) {
        line = line->down;
        delete line->up;
        el = start_i;
        while (el->right != nullptr) {
            el = el->right;
            delete el->left;
        }
        delete el;
    }
    delete line;
}
