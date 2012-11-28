#include <fstream>
#include <sstream>

#include "driver.h"
#include "scanner.h"

#include "../tree/node.h"

namespace io {

    Driver::Driver(class Node& root)
        : trace_scanning(false),
          trace_parsing(false),
          root(root)
    {
    }
    
    bool Driver::parse_stream(std::istream& in, const std::string& sname)
    {
        streamname = sname;
    
        Scanner scanner(&in);
        scanner.set_debug(trace_scanning);
        this->lexer = &scanner;
    
        JParser parser(*this);
        parser.set_debug_level(trace_parsing);
        return (parser.parse() == 0);
    }
    
    bool Driver::parse_file(const std::string &filename)
    {
        std::ifstream in(filename.c_str());
        if (!in.good()) return false;
        return parse_stream(in, filename);
    }
    
    bool Driver::parse_string(const std::string &input, const std::string& sname)
    {
        std::istringstream iss(input);
        return parse_stream(iss, sname);
    }
    
    void Driver::error(const class location& l,
    		   const std::string& m)
    {
        std::cerr << l << ": " << m << std::endl;
    }
    
    void Driver::error(const std::string& m)
    {
        std::cerr << m << std::endl;
    }

} // namespace io
