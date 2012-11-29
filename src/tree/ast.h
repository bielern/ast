/**
 * @file ast.h
 *
 * Defines the Abstract Syntax Tree (AST).
 *
 * There are simple Leafs (Item), lists (List) and
 * dictionaries (Object).
 *
 * You shouldn't need to include this file, except if you implement
 * a parser or generator
 */
#ifndef AST_H
#define AST_H

#include <vector>
#include <map>
#include <string>

namespace io {

    /**
     * The different types of nodes
     */
    enum NodeType {
        ITEM,
        OBJECT,
        LIST
    };
    
    /**
     * Basic Type
     */
    struct Value {
        Value(NodeType t);
        virtual ~Value();
        NodeType _type;
    };
    
    /** 
     * An Object contains fiels. Though not in this form.
     */
    struct Field {
        Field(std::string key, Value *value);
        std::string key;
        Value *value;
    };
    
    /**
     * The leaf of the AST
     */
    struct Item : public Value {
        Item(std::string value, bool _string=false);

        // Members
        std::string _value;
        bool _string;
    };
    
    /**
     * List node of the AST
     */
    struct List : public Value {
        List();
        ~List();

        void push_back(Value *value);
        Value *operator[](unsigned int i);

        // Members
        typedef std::vector<Value *> ListContainer;
        ListContainer _list;
        NodeType _listType;
    };
    
    /**
     * Object (or dictionary) node of the AST
     */
    struct Object : public Value {
        Object();
        ~Object();
    
        void push_back(std::string key, Value *value);
        void push_back(Field &field);
        Value *operator[](std::string key);
        
        // Members
        typedef std::map<std::string, Value*> ObjectContainer;
        ObjectContainer _fields;
    };
}
#endif

