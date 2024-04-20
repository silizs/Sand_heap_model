#include <iostream>
#include <vector>

struct color {
    uint8_t r, g, b;

    color();
    color(uint8_t r, uint8_t g, uint8_t b);
    ~color();
};

struct picture {
    uint16_t length;
    uint16_t width;
    std::vector<color> colors;

    picture(uint16_t length, uint16_t width);
    ~picture();

    color get_color(int x, int y) const;
    void set_color(const color& cl, int x, int y);

    void print(const std::string& path) const;

};
