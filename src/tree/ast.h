#ifndef AST_H
#define AST_H

#include <vector>
#include <map>
#include <string>

namespace io {

    enum NodeType {
        item,
        object,
        list
    };
    
    struct Value {
        Value(NodeType t);
        virtual ~Value();
        NodeType _type;
    };
    
    struct Field {
        Field(std::string key, Value *value);
        std::string key;
        Value *value;
    };
    
    struct Item : public Value {
        Item(std::string value, bool _string=false);

        // Members
        std::string _value;
        bool _string;
    };
    
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

