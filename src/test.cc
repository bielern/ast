#include <iostream>
#include <string>

#include "ast/node.h"
#include "parser/input_file.h"

int main() {

    /** Create a root node containing the AST */
    io::Root root;

    std::string filename("conf.txt");

    bool result = io::read_input(filename, root);
    if (result) {
        root.push_back("mytest", io::mkList());
        std::cout << root << "\n";
        std::cout << "// subobj.newkey = " << root("subobj.newkey", ".") << std::endl;
    }


    return 0;
}
