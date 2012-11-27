#ifndef NODE_H
#define NODE_H

#include <sstream>
#include <iostream>
#include <string>

#include "ast.h"

namespace io {
    struct NodeOperator;
    struct NodeIterator;
    
    struct Node {
        Node (Value *value);
        Node(); // TODO: error, catch somehow
        ~Node();
        void _init();
        void operator=(Value *value);
        void operator=(Node &other);
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

        typedef NodeIterator iterator;
        iterator begin();
        iterator end();
        unsigned int size();
    
        void del();

        std::string str(int i) const;
    
        // Memeber
        NodeOperator *nodeOperator;
        Value *value;
    };

    struct NIOperator;
    struct NodeIterator : public Node {
        NodeIterator();
        NodeIterator(Object *object);
        NodeIterator(List *list);
        NodeIterator(Item *item);
        NodeIterator &operator++();
        bool operator==(NodeIterator &ni);
        bool operator!=(NodeIterator &ni);
        std::string key();
        void _begin();
        void _end();
        // Memeber
        NIOperator *niOperator;
    };

}
std::ostream & operator<< (std::ostream &out, const io::Node &node);
#endif
