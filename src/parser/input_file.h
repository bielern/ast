#ifndef INPUT_FILE_H
#define INPUT_FILE_H

#include <string>

namespace io {

    struct Node;

    enum InputFormat {
        J
    };
    bool read_input(std::string filename, Node &root, InputFormat inputFormat=J);
}
#endif
