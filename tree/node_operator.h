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

        virtual Node::iterator begin();
        virtual Node::iterator end();
        virtual unsigned int size();
    };
    
    struct ItemOperator : public NodeOperator {
        ItemOperator(Item *item);
        void set(std::string value);
        std::string get();
        // Member
        Item *item;
    };
    
    struct ObjectOperator : public NodeOperator {
        ObjectOperator(Object *object);
        Node operator[](std::string key);
        void push_back(std::string key, Value *value);
        void push_back(Field *field);
        Node::iterator begin();
        Node::iterator end();
        // Member
        Object *object;
    };
    
    struct ListOperator : public NodeOperator {
        ListOperator(List *list);
        Node operator[](unsigned int i);
        void push_back(Value *value);
        // Member
        List *list;
    };

    /**** ITERATORS  *********/

    struct NIOperator {
        NIOperator(NodeType type);
        virtual Value *next();
        virtual Value * _begin();
        virtual void _end();
        virtual bool at_end();
        virtual bool eq(NIOperator *ni);
        virtual std::string key();
        // Member
        NodeType type;
    };

    struct ObjectIterator : public NIOperator {
        ObjectIterator(Object *object);
        Value *next();
        Value *_begin();
        void _end();
        bool at_end();
        bool eq(NIOperator *ni);
        std::string key();
        // Member
        Object *object;
        Object::ObjectContainer::iterator it;
    };

    struct ListIterator : public NIOperator {
        ListIterator(List *list);
        Value *next();
        Value *_begin();
        void _end();
        bool at_end();
        bool eq(NIOperator *ni);
        // Member
        List *list;
        List::ListContainer::iterator it;
    };

    struct ItemIterator : public NIOperator {
        ItemIterator(Item *item);
        Value *next();
        Value *_begin();
        void _end();
        bool at_end();
        bool eq(NIOperator *ni);
        // Member
        Item *item;
        bool _at_end;
    };
}
#endif
