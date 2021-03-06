
#include <sstream>

#include "ast.h"
#include "node.h"
#include "node_operator.h"

namespace io {

    /***************************
     * NODE
     ***************************/
    Node::Node (Value *value) : 
        nodeOperator(0),
        value(value) {
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
            if (nodeOperator)
                delete nodeOperator;
            switch(value->_type) {
                case ITEM: {
                               Item *item = static_cast<Item *>(value);
                               nodeOperator = new ItemOperator(item);
                               break;
                           }
                case LIST: {
                               List *list = static_cast<List *>(value);
                               nodeOperator = new ListOperator(list);
                               break;
                           }
                case OBJECT: {
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
    Node Node::operator[](std::string key) const{
        return (*nodeOperator)[key];
    }
    Node Node::operator()(std::string key, std::string seperator){
        return (*nodeOperator)(key, seperator);
    }
    Node Node::operator[](unsigned int i) const{
        return (*nodeOperator)[i];
    }
    
    void Node::push_back(std::string key, Value *value){
        nodeOperator->push_back(key, value);
    }
    void Node::push_back(std::string key, const Node &node){
        nodeOperator->push_back(key, node.value);
    }
    void Node::push_back(Field *field){
        nodeOperator->push_back(field);
    }
    void Node::push_back(Value *value){
        nodeOperator->push_back(value);
    }
    void Node::push_back(const Node &node){
        nodeOperator->push_back(node.value);
    }
    math::NVector Node::getNVector(std::string key, const math::NVector &fallBack) const{
        if (contains(key)){
            std::vector<double> result;
            result = getVector(key, result);
            return math::NVector(result);
        } else {
            return fallBack;
        }
    }
    void Node::addNVector(std::string key, const math::NVector &vector){
        push_back(key, vector.toAST());
    }

    Node::iterator Node::begin() const{
        return nodeOperator->begin();
    }
    Node::iterator Node::end() const{
        return nodeOperator->end();
    }
    unsigned int Node::size() const{
        return nodeOperator->size();
    }
    bool Node::contains(std::string key) const{
      return nodeOperator->contains(key);
    }

    void Node::_set(std::string &value){
        nodeOperator->set(value);
    }
    std::string Node::_get() const {
        return nodeOperator->get();
    }
    
    void Node::del(){
        if (value)
            delete value;
    }

    std::string Node::str(int i) const {
        return nodeOperator->str(i);
    }

    /***************************
     * NODE ITERATOR
     ***************************/

    NodeIterator::NodeIterator() : 
        Node(0),
        niOperator(0)
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
    NodeIterator::~NodeIterator() {
       if (niOperator)
          delete niOperator;
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


    Root::Root(Value *value) :
        Node(value)
    {}
    Root::Root(const Node &n) :
        Node(n.value)
    {}
    Root::Root() :
        Node(0)
    {}
    Root::~Root() {
        del();
    }

    Node _mkItem(std::string value, bool as_string){
      Item *i = new Item(value, as_string);
      return Node(i);
    }
    Node mkList(){
      List *l = new List();
      return Node(l);
    }
    Node mkObject(){
      Object *o = new Object();
      return Node(o);
    }
}

/*************************
 * Out put stream
 ************************/
std::ostream & operator<< (std::ostream &out, const io::Node &node){
    out << node.str(1);
    return out;
}
