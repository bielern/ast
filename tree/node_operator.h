#ifndef NODE_OPERATOR_H
#define NODE_OPERATOR_H

#include <iostream>
#include <string>

#include "node.h"

namespace io {

    struct NodeOperator {
        virtual Node operator[](std::string key);
        virtual Node operator[](unsigned int i);
        virtual void set(std::string value);
        virtual std::string get();
    
        virtual void push_back(std::string key, Value *value);
        virtual void push_back(Field *field);
        virtual void push_back(Value *value);
    };
    
    struct ItemOperator : public NodeOperator {
        ItemOperator(Item *item);
        Item *item;
        void set(std::string value);
        std::string get();
    };
    
    struct ObjectOperator : public NodeOperator {
        ObjectOperator(Object *object);
        Object *object;
        Node operator[](std::string key);
        void push_back(std::string key, Value *value);
        void push_back(Field *field);
    };
    
    struct ListOperator : public NodeOperator {
        ListOperator(List *list);
        List *list;
        Node operator[](unsigned int i);
        void push_back(Value *value);
    };
}
#endif
