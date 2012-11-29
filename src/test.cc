#include <iostream>
#include <string>

#include "tree/node.h"
#include "parser/input_file.h"

int main() {

    io::Root root;

    std::string filename("conf.txt");

    bool result = io::read_input(filename, root);
    if (result) {
        std::cout << root << "\n";
    }
    //root.del();

    return 0;
}
