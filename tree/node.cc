
#include <sstream>

#include "ast.h"
#include "node.h"
#include "node_operator.h"

namespace io {

    Node::Node (Value *value) : value(value) {
        switch(value->_type) {
            case item: {
                           Item *item = static_cast<Item *>(value);
                           nodeOperator = new ItemOperator(item);
                           break;
                       }
            case list: {
                           List *list = static_cast<List *>(value);
                           nodeOperator = new ListOperator(list);
                           break;
                       }
            case object: {
                           Object *object = static_cast<Object *>(value);
                           nodeOperator = new ObjectOperator(object);
                           break;
                         }
        }
    }
    Node Node::operator[](std::string key){
        return (*nodeOperator)[key];
    }
    Node Node::operator[](unsigned int i){
        return (*nodeOperator)[i];
    }
    
    void Node::push_back(std::string key, Value *value){
        nodeOperator->push_back(key, value);
    }
    void Node::push_back(Field *field){
        nodeOperator->push_back(field);
    }
    void Node::push_back(Value *value){
        nodeOperator->push_back(value);
    }

    void Node::_set(std::string &value){
        nodeOperator->set(value);
    }
    std::string Node::_get(){
        return nodeOperator->get();
    }
    
    void Node::del(){
        delete value;
    }
}
