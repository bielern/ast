#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "ast.h"

namespace io {
    std::string typeNames[] = {
        "Item",
        "Object",
        "List"
    };
    
    Value::Value(NodeType t) : _type(t) {}

    Field::Field(std::string key, Value *value) :
        key(key),
        value(value)
    {}
    
    Item::Item(std::string value) : Value(item), _value(value) {}
    
    List::List() : Value(list) {}
    List::~List(){
        std::vector<Value *>::iterator it = _list.begin(),
            to = _list.end();
        for (; it != to; it++){
            delete *it;
        }
    }
    void List::push_back(Value *value){
        if (_list.size() == 0){
           _listType = value->_type;
           _list.push_back(value);
        } else if (value->_type == _listType){
            _list.push_back(value);
        } else {
            std::cerr << "ERROR: Trying to put a " 
                      << typeNames[value->_type]
                      << " into a list of "
                      << typeNames[_listType]
                      << "!\n";
        }
    }
    Value * List::operator[](unsigned int i){
        return _list[i];
    }
    
    Object::Object() : Value(object) {}
    Object::~Object(){
        std::map<std::string, Value *>::iterator it = _fields.begin(),
            to = _fields.end();
        for (; it != to; it++){
            delete it->second;
        }
    }
    
    void Object::push_back(std::string key, Value *value){
        _fields[key] = value;
    }
    void Object::push_back(Field &field){
        _fields[field.key] = field.value;
    }
    Value * Object::operator[](std::string key){
        return _fields[key];
    }
}
