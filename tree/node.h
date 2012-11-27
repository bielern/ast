#ifndef NODE_H
#define NODE_H

#include <sstream>
#include <string>

#include "ast.h"

namespace io {
    struct NodeOperator;
    
    struct Node {
        Node (Value *value);
        Node operator[](std::string key);
        Node operator[](unsigned int i);
        template<typename T>
        void set(T value){
            std::stringstream ss;
            ss << value;
            _set(ss.str());
        }
        template<typename T>
        T get(){
            std::stringstream ss(_get());
            T value;
            ss >> value;
            return value;
        }
        void _set(std::string &value);
        std::string _get();
    
        void push_back(std::string key, Value *value);
        void push_back(Field *field);
        void push_back(Value *value);
    
        void del();
    
        NodeOperator *nodeOperator;
        Value *value;
    };
    
    
}
#endif
