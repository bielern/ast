
#include <sstream>

#include "ast.h"
#include "node.h"
#include "node_operator.h"

namespace io {

    Node::Node (Value *value) : value(value) {
        _init();
    }
    Node::Node(){
        std::cerr << "Error: Node without value!\n";
    }
    Node::~Node() {
        if (nodeOperator)
            delete nodeOperator;
    }
    void Node::_init(){
        if (value){
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
    }
    void Node::operator=(Node &other){
        value = other.value;
        if (nodeOperator){
            delete nodeOperator;
        }
        _init();
    }
    void Node::operator=(Value *value){
        this->value = value;
        _init();
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

    Node::iterator Node::begin(){
        return nodeOperator->begin();
    }
    Node::iterator Node::end(){
        return nodeOperator->end();
    }
    unsigned int Node::size(){
        return nodeOperator->size();
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

    std::string Node::str(int i) const {
        return nodeOperator->str(i);
    }

    /***************************
     * NODE ITERATOR
     ***************************/

    NodeIterator::NodeIterator() : 
        Node(0)
    {}
    NodeIterator::NodeIterator(Object *object) : 
        Node(object)
    {
        niOperator = new ObjectIterator(object);
    }
    NodeIterator::NodeIterator(List *list) : 
        Node(list)
    {
        niOperator = new ListIterator(list);
    }
    NodeIterator::NodeIterator(Item *item) : 
        Node(item)
    {
        niOperator = new ItemIterator(item);
    }

    NodeIterator& NodeIterator::operator++() {
        niOperator->next();
        if (! niOperator->at_end())
            value = niOperator->value();
            _init();
        return *this;
    }
    bool NodeIterator::operator==(NodeIterator &ni) {
        return niOperator->eq(ni.niOperator);
    }
    bool NodeIterator::operator!=(NodeIterator &ni) {
        return !niOperator->eq(ni.niOperator);
    }

    std::string NodeIterator::key(){
        return niOperator->key();
    }
    void NodeIterator::_begin(){
        niOperator->_begin();
        if (! niOperator->at_end())
            value = niOperator->value();
            _init();
    }
    void NodeIterator::_end(){
        niOperator->_end();
    }
}

/*************************
 * Out put stream
 ************************/
std::ostream & operator<< (std::ostream &out, const io::Node &node){
    out << node.str(1);
    return out;
}
