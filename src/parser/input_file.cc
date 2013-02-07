#include <fstream>
#include <iostream>

#include "input_file.h"
#include "../ast/node.h"
#include "jdriver.h"

namespace io {
    bool read_input(std::string filename, Node &root, InputFormat inputFormat){
        switch (inputFormat) {
            case J : {
                        io::JDriver driver(root);

                        std::fstream infile(filename.c_str());
                        if (!infile.good()) {
                            std::cerr << "Could not open file: " << filename << std::endl;
                            return 0;
                        }

                        bool result = driver.parse_stream(infile, filename);
                        return result;
                     }
            default: {
                         std::cerr << "ERROR: Unknown Input Format!\n";
                         return false;
                     }
        }
    }
}
