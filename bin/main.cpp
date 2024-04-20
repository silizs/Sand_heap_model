#include <lib/sandpile/sandpile.h>
#include <lib/picture/picture.h>

#include <iostream>
#include <vector>
#include <cstring>

std::vector<uint64_t> read_a_file(const char* file_name, uint16_t& width, uint16_t& length) {
    std::freopen(file_name, "r", stdin);

    uint16_t x;
    uint16_t y;
    uint64_t sand;
    std::vector<uint64_t> array(length*width, 0);
    while (std::cin >> x) {
        std::cin >> y;
        std::cin >> sand;
        array[y*width + x] = sand;
    }

    return array;
}

void picture_saved(matrix& field, const std::string& path_to_the_picture, uint64_t n) {
    node* line = field.start;
    node* el = line;
    int ii = 0, jj = 0;

    picture p(field.length, field.width);

    color white(255, 255, 255);
    color black(0, 0, 0);
    color green(0, 168, 107);
    color darkviolet(148, 0, 211);
    color yellow(254, 254, 34);

    while (line != nullptr) {
        el = line;
        jj = 0;
        while (el != nullptr) {
            if (el->key == 0) {
                p.set_color(white , ii, jj);
            } else if (el->key == 1) {
                p.set_color(green , ii, jj);
            } else if (el->key == 2) {
                p.set_color(darkviolet , ii, jj);
            } else if (el->key == 3) {
                p.set_color(yellow , ii, jj);
            } else {
                p.set_color(black , ii, jj);
            }
            el = el->right;
            jj++;
        }
        line = line->down;
        ii++;
    }

    p.print(path_to_the_picture + std::string("picture_number_") + std::to_string(n) + std::string(".bmp"));
}


void processing(matrix& field, uint64_t& max_iter, uint64_t& freq, const std::string& path_to_the_picture) {
    uint64_t iteration_number = 0;
    while (iteration_number < max_iter && not(field.mountains_of_sand.empty())) {
        field.renewal();
        if (iteration_number % freq == 0) {
            uint64_t n = iteration_number / freq;
            picture_saved(field, path_to_the_picture, n);
        }
        iteration_number++;
    }

}

int main(int argc, char* argv[]) {
    if (argc == 1) std::cerr << "No input found";

    else {
        uint16_t length;
        uint16_t width;
        uint64_t max_iter = 1844674073709551615;
        uint64_t freq;
        char* file_name;
        std::string path_to_the_picture;

        for (int i = 1; i < argc; i += 2) {
            if (!strcmp(argv[i], "-l") || !strcmp(argv[i], "--length")) {
                length = atoi(argv[i + 1]);
            } else if (!strcmp(argv[i], "-w") || !strcmp(argv[i], "--width")) {
                width = atoi(argv[i + 1]);
            } else if (!strcmp(argv[i], "-i") || !strcmp(argv[i], "--input")) {
                file_name = argv[i + 1];
            } else if (!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")) {
                if (argv[i + 1][strlen(argv[i + 1]) - 1] == '\\') {
                    path_to_the_picture = argv[i + 1];
                } else {
                    path_to_the_picture = argv[i + 1] + std::string("\\");
                }
            } else if (!strcmp(argv[i], "-m") || !strcmp(argv[i], "--max-iter")) {
                max_iter = atoi(argv[i + 1]);
            } else if (!strcmp(argv[i], "-f") || !strcmp(argv[i], "--freq")) {
                freq = atoi(argv[i + 1]);
            }
        }

        std::vector<uint64_t> array = read_a_file(file_name, width, length);

        matrix field(length, width, array);

        processing(field, max_iter, freq, path_to_the_picture);

        field.~matrix();

        return 0;
    }
}
