#include <iostream>
#include <fstream>
#include <string>

#include "tree/node.h"
#include "parser/driver.h"

int main() {

    io::Object obj_root;
    io::Node root(&obj_root);
    io::Driver driver(root);

    std::string filename("conf.txt");

    std::fstream infile(filename.c_str());
    if (!infile.good()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return 0;
    }

    bool result = driver.parse_stream(infile, filename);
    if (result) {
        std::map<std::string, io::Value *> &fields = obj_root._fields;
        std::map<std::string, io::Value *>::iterator it = fields.begin(),
            to = fields.end();
        for (; it != to; it++) {
            io::Node node(it->second);
            std::cout << it->first << " = " 
                      << node._get() << "\n";
        }
    }

    return 0;
}
