#include <iostream>
#include <string>

#include "ast/node.h"
#include "parser/input_file.h"
#include "math/nvector.h"

int main() {

    /** Create a root node containing the AST */
    io::Root root;

    std::string filename("conf.txt");

    bool result = io::read_input(filename, root);
    if (result) {
        root.push_back("mytest", io::mkList());

        math::NVector add(4, 1.0);
        io::Node nvec = root["vec"];
        math::NVector vec(nvec);
        math::NVector result = add + vec;
        //math::NVector result = vec;
        std::cout << root << "\n";
        std::cout << "// subobj.newkey = " << root("subobj.newkey", ".") << std::endl;
        //io::Root r = result.toAST();
        //io::Root r = vec.toAST();
        //std::cout << "// add 1: " << r << std::endl;
        std::cout << "// add 1: " << result << std::endl;
    }


    return 0;
}
