#include <iostream>
#include <string>

#include "tree/node.h"
#include "parser/input_file.h"

int main() {

    /** Create a root node containing the AST */
    io::Root root;

    std::string filename("conf.txt");

    bool result = io::read_input(filename, root);
    if (result) {
        std::cout << root << "\n";
    }

    return 0;
}
