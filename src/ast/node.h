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
    
    class Node;
    /**
     * Create a List packed in a List
     */
    Node mkList();
    /**
     * Create an object packed in a Object
     */
    Node mkObject();

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
        /////////////////////////////////////////
        // Iterator stuff
        typedef NodeIterator iterator;
        iterator begin() const;
        iterator end() const;
        unsigned int size() const;
    
        /////////////////////////////////////////
        // Constructors
        Node (Value *value);
        Node(); 
        virtual ~Node();
        void _init();
        void operator=(Value *value);
        void operator=(Node &other);
        /////////////////////////////////////////
        // For Object
        /**
         * Acces value with key
         */
        Node operator[](std::string key) const;
        /**
         * Access value with path, where key are seperated by seperator
         */
        Node operator()(std::string key, std::string seperator);
        /**
         * Add key value pair to object.
         */
        void push_back(std::string key, Value *value);
        /**
         * Add a key value (wrapped in a Node) pair to object.
         */
        void push_back(std::string key, const Node &node);
        /**
         * Add key value pair in form of a field to object.
         */
        void push_back(Field *field);
        /**
         * Easy adding function.
         */
        template<typename T>
        void add(std::string key, const T value, bool asString=false){
          push_back(key, mkItem(value, asString));
        }
        template<typename T>
        void addList(std::string key, const T &list, bool asString=false){
          push_back(key, mkList());
          int num = list.size();
          for (int i = 0; i < num; i++){
            (*this)[key].push_back(mkItem(list[i], asString));
          }
        }
        /**
         * Test if Object contains field with key
         */
        bool contains(std::string key) const;
        /**
         * Getter with fall back variant
         */
        template<typename T>
        T get(std::string key, T fallBack) const {
          if (contains(key)){
            return (*this)[key].get<T>();
          } else {
            return fallBack;
          }
        }
        /**
         * Return the node at key as a std::vector
         */
        template<typename T>
        T asList(std::string key, const T &fallBack) const {
          if (contains(key)){
            T result;
            int num = (*this)[key].size();
            for (int i = 0; i < num; i++){
              result.push_back((*this)[key][i].get<typename T::value_type>());
            }
            return result;
          } else {
            return fallBack;
          }
        }

        /////////////////////////////////////////
        // For List
        /**
         * Access value with index i
         */
        Node operator[](unsigned int i) const;
        /**
         * Add a value
         */
        void push_back(Value *value);
        /**
         * Add a value wrapped in a Node
         */
        void push_back(const Node &node);

        /////////////////////////////////////////
        // For Item
        /**
         * Set the value
         */
        template<typename T>
        void set(T value){
            std::stringstream ss;
            ss << value;
            _set(ss.str());
        }
        /**
         * Get the value
         */
        template<typename T>
        T get() const {
            std::stringstream ss(_get());
            T value;
            ss >> value;
            return value;
        }
        void _set(std::string &value);
        std::string _get() const;
    
        // delete ast
        void del();

        // For output
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
        Root(const Node &n);
        Root();
        ~Root();
    };

    // Some Node Factories
    Node _mkItem(std::string value, bool as_string);
    /**
     * Create an item packed in a node
     */
    template<typename T>
    Node mkItem(T value, bool as_string = false) {
      std::stringstream ss;
      ss << value;
      return _mkItem(ss.str(), as_string);
    }
}
/** 
 * Outputs the AST in the "J"-Format.
 */
std::ostream & operator<< (std::ostream &out, const io::Node &node);
#endif
