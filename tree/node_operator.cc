#include "node_operator.h"

namespace io {
    Node NodeOperator::operator[](std::string key){
        std::cerr << "Operator[](string) not implemented for this type!\n";
        return Node(0);
    }
    Node NodeOperator::operator[](unsigned int i){
        std::cerr << "Operator[](int) not implemented for this type!\n";
        return Node(0);
    }
    void NodeOperator::set(std::string value){
        std::cerr << "Function set not implemented for this type!\n";
    }
    std::string NodeOperator::get(){
        std::cerr << "Function get not implemented for this type!\n";
        return "Error";
    }
    
    void NodeOperator::push_back(std::string key, Value *value){
        std::cerr << "Function push_back not implemented for this type!\n";
    }
    void NodeOperator::push_back(Field *field){
        std::cerr << "Function push_back not implemented for this type!\n";
    }
    void NodeOperator::push_back(Value *value){
        std::cerr << "Function push_back not implemented for this type!\n";
    }
    
    
    ItemOperator::ItemOperator(Item *item) : item(item) {}
    void ItemOperator::set(std::string value){
        item->_value = value;
    }
    std::string ItemOperator::get(){
        return item->_value;
    }
    
    
    ObjectOperator::ObjectOperator(Object *object) : object(object) {}
    Node ObjectOperator::operator[](std::string key){
        return Node((*object)[key]);
    }
    void ObjectOperator::push_back(std::string key, Value *value){
        object->push_back(key, value);
    }
    void ObjectOperator::push_back(Field *field){
        object->push_back(field->key, field->value);
    }
    
    
    ListOperator::ListOperator(List *list) : list(list) {}
    Node ListOperator::operator[](unsigned int i){
        return Node((*list)[i]);
    }
    void ListOperator::push_back(Value *value){
        list->push_back(value);
    }
    
}
