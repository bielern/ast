/**
 * This is the interface for reading in and out files
 */
#ifndef INPUT_FILE_H
#define INPUT_FILE_H

#include <string>

namespace io {

    struct Node;

    /**
     * Known Input Formats
     */
    enum InputFormat {
        J       /* JSON-like format */
    };
    /**
     * Read in an input file
     */
    bool read_input(std::string filename, Node &root, InputFormat inputFormat=J);
}
#endif
