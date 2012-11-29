/**
 * @file node.h
 * This file contains the interface to access the AST definied in ast.h.
 *
 * Only include this file, if you have to deal with ASTs.
 */
#ifndef NODE_H
#define NODE_H

#include <sstream>
#include <iostream>
#include <string>

namespace io {
    // from node_operator.h
    struct NodeOperator;
    struct NodeIterator;

    // from ast.h
    struct Value;
    struct Item;
    struct List;
    struct Object;
    struct Field;
    
    /**
     * @class Node
     * The Node class provides an interface to access the nodes
     * of an AST as defined in ast.h. 
     *
     * Node doesn't delete the AST, when it goes out of scope. See Root for 
     * a class, which addresses that.
     * The actual implementation of the Node is performed via the NodeOperator
     * class and its deerived classes (Strategy Pattern).
     */
    struct Node {
        Node (Value *value);
        Node(); 
        virtual ~Node();
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

    // === ITERATOR ===
    struct NIOperator;

    /**
     * @class NodeIterator
     * The NodeIterator class allows you to iterate over the childs
     * of a Node, while providing you the same interface.
     *
     * The actual implementation of the NodeIterator is performed via the 
     * NIOperator class and its deerived classes (Strategy Pattern).
     */
    struct NodeIterator : public Node {
        NodeIterator();
        NodeIterator(Object *object);
        NodeIterator(List *list);
        NodeIterator(Item *item);
        ~NodeIterator();

        NodeIterator &operator++();
        bool operator==(NodeIterator &ni);
        bool operator!=(NodeIterator &ni);
        std::string key();
        // "private" functions
        void _begin();
        void _end();

        // Memeber
        NIOperator *niOperator;
    };

    /**
     * @class Root
     * The Root class is almost the same as the Node class,
     * except that it deletes the AST, once it goes out of scope.
     */
    struct Root : public Node {
        Root(Value * value);
        Root();
        ~Root();
    };

}
/** 
 * Outputs the AST in the "J"-Format.
 */
std::ostream & operator<< (std::ostream &out, const io::Node &node);
#endif
