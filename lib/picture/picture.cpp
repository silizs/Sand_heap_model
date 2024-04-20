#pragma once
#include "picture.h"

#include <iostream>
#include <fstream>
#include <cstring>

const uint8_t FILE_HEADER_SIZE = 14;
const uint8_t INFORMATION_HEADER_SIZE = 40;

color::color()
        : r(0), g(0), b(0) {
}

color::color(uint8_t r, uint8_t g, uint8_t b)
    :  r(r), g(g), b(b) {
}

color::~color()
{
}

picture::picture(uint16_t length, uint16_t width)
    : length(length), width(width), colors(std::vector<color> (width * length)) {
}

picture::~picture()
{
}

color picture::get_color(int x, int y) const {
    return colors[y * width + x];
}

void picture::set_color(const color& cl, int x, int y) {
    colors[y * width + x].r = cl.r;
    colors[y * width + x].g = cl.g;
    colors[y * width + x].b = cl.b;
}

void picture::print(const std::string& path) const{
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if (!f.is_open()) {
        std::cerr << "File could not be opened\n";
        return;
    }

    unsigned char bmp_pad[3] = { 0, 0, 0 };
    const uint32_t padding_amount = ((4 - (width * 3) % 4) % 4);

    const uint8_t file_size = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + width * length * 3 + padding_amount * width;

    unsigned char file_header[FILE_HEADER_SIZE];
    std::memset(file_header, 0, FILE_HEADER_SIZE);

    file_header[0] = 'B';
    file_header[1] = 'M';

    file_header[2] = file_size;
    file_header[3] = file_size >> 8;
    file_header[4] = file_size >> 16;
    file_header[5] = file_size >> 24;

    unsigned char information_header[INFORMATION_HEADER_SIZE];
    std::memset(information_header, 0, INFORMATION_HEADER_SIZE);

    information_header[0] = INFORMATION_HEADER_SIZE;

    information_header[4] = width;
    information_header[5] = width >> 8;
    information_header[6] = width >> 16;
    information_header[7] = width >> 24;

    information_header[8] = length;
    information_header[9] = length >> 8;
    information_header[10] = length >> 16;
    information_header[11] = length >> 24;

    information_header[12] = 1;

    information_header[14] = 24;

    f.write(reinterpret_cast<char*>(file_header), FILE_HEADER_SIZE);
    f.write(reinterpret_cast<char*>(information_header), INFORMATION_HEADER_SIZE);

    for (uint16_t y = 0; y < length; y++) {
        for (uint16_t x = 0; x < width; x++) {
            unsigned char r = static_cast<unsigned char>(get_color(x, y).r);
            unsigned char g = static_cast<unsigned char>(get_color(x, y).g);
            unsigned char b = static_cast<unsigned char>(get_color(x, y).b);

            unsigned char color[] = {b, g, r};

            f.write(reinterpret_cast<char *>(color), 3);
        }
        f.write(reinterpret_cast<char *>(bmp_pad), padding_amount);
    }
    f.close();
}
