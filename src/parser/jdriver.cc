#include <fstream>
#include <sstream>

#include "jdriver.h"
#include "jscanner.h"

#include "../ast/node.h"

namespace io {

    JDriver::JDriver(class Node& root)
        : trace_scanning(false),
          trace_parsing(false),
          root(root)
    {
    }
    
    bool JDriver::parse_stream(std::istream& in, const std::string& sname)
    {
        streamname = sname;
    
        JScanner scanner(&in);
        scanner.set_debug(trace_scanning);
        this->lexer = &scanner;
    
        JParser parser(*this);
        parser.set_debug_level(trace_parsing);
        return (parser.parse() == 0);
    }
    
    bool JDriver::parse_file(const std::string &filename)
    {
        std::ifstream in(filename.c_str());
        if (!in.good()) return false;
        return parse_stream(in, filename);
    }
    
    bool JDriver::parse_string(const std::string &input, const std::string& sname)
    {
        std::istringstream iss(input);
        return parse_stream(iss, sname);
    }
    
    void JDriver::error(const class location& l,
    		   const std::string& m)
    {
        std::cerr << l << ": " << m << std::endl;
    }
    
    void JDriver::error(const std::string& m)
    {
        std::cerr << m << std::endl;
    }

} // namespace io

