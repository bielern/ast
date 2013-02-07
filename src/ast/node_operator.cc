#include "node_operator.h"

namespace io {
    /*************************
     * OPERATORS
     *************************/
    Node NodeOperator::operator[](std::string key){
        std::cerr << "Operator[](string) not implemented for this type!\n";
        return Node(0);
    }
    Node NodeOperator::operator()(std::string key, std::string seperator){
        std::cerr << "Operator()(key, seperator) not implemented for this type!\n";
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
    
    Node::iterator NodeOperator::begin() const {
        std::cerr << "Function begin not implemented for this type!\n";
        return NodeIterator();
    }
    Node::iterator NodeOperator::end() const {
        std::cerr << "Function end not implemented for this type!\n";
        return NodeIterator();
    }
    unsigned int NodeOperator::size() const {
        std::cerr << "Function size not implemented for this type!\n";
        return 0;
    }

    std::string NodeOperator::str(int i) const{
        return std::string("Not implemented");
    }

    /* ItemOperator */
    
    ItemOperator::ItemOperator(Item *item) : item(item) {}
    void ItemOperator::set(std::string value){
        item->_value = value;
    }
    std::string ItemOperator::get(){
        return item->_value;
    }
    Node::iterator ItemOperator::begin() const {
        Node::iterator ni(item);
        ni._begin();
        return ni;
    }
    Node::iterator ItemOperator::end() const { 
        Node::iterator ni(item);
        ni._end();
        return ni;
    }
    unsigned int ItemOperator::size() const {
        return 1;
    }
    
    std::string ItemOperator::str(int i) const{
        std::stringstream ss;
        if (item->_string)
            ss << '"';
        ss << item->_value;
        if (item->_string)
            ss << '"';
        return ss.str();
    }

    /* ObjectOperator */
    
    ObjectOperator::ObjectOperator(Object *object) : object(object) {}
    Node ObjectOperator::operator[](std::string key){
        return Node((*object)[key]);
    }
    Node ObjectOperator::operator()(std::string key, std::string seperator){
        size_t pos = key.find(seperator);
        if (pos == key.length() - seperator.length()){
            return Node((*object)[key.substr(0, pos)]);
        }
        if (pos == key.npos){
            return Node((*object)[key]);
        } else {
            return (*this)[key.substr(0, pos)]
                (key.substr(pos + seperator.length()), seperator);
        }
    }
    void ObjectOperator::push_back(std::string key, Value *value){
        object->push_back(key, value);
    }
    void ObjectOperator::push_back(Field *field){
        object->push_back(field->key, field->value);
    }
    Node::iterator ObjectOperator::begin() const {
        Node::iterator ni(object);
        ni._begin();
        return ni;
    }
    Node::iterator ObjectOperator::end() const { 
        Node::iterator ni(object);
        ni._end();
        return ni;
    }
    unsigned int ObjectOperator::size() const {
        return object->_fields.size();
    }

    std::string ObjectOperator::str(int i) const{
        std::stringstream ss;
        ss << "{";
        if (size() > 0){
            ss << std::endl;
            Node::iterator it = begin(),
                to = end();
            for (; it != to; ++it){
                for (int j = 0; j < i; j++){
                    ss << " ";
                }
                ss << it.key() << " = " << it.str(i+1) << std::endl;
            }
            for (int j = 1; j < i; j++){
                ss << " ";
            }
        }
        ss << "}";
        return ss.str();
    }
    
    /* ListOperator */
    
    ListOperator::ListOperator(List *list) : list(list) {}
    Node ListOperator::operator[](unsigned int i){
        return Node((*list)[i]);
    }
    void ListOperator::push_back(Value *value){
        list->push_back(value);
    }
    Node::iterator ListOperator::begin() const {
        Node::iterator ni(list);
        ni._begin();
        return ni;
    }
    Node::iterator ListOperator::end() const { 
        Node::iterator ni(list);
        ni._end();
        return ni;
    }
    unsigned int ListOperator::size() const {
        return list->_list.size();
    }

    std::string ListOperator::str(int i) const{
        std::stringstream ss;
        ss << "[";
        if (size() > 0){
            Node::iterator it = begin(),
                to = end();
            if (list->_listType == ITEM){
                ss << " ";
                for (; it != to; ++it){
                    ss << it << " ";
                }
            } else {
                ss <<  std::endl;
                for (; it != to; ++it){
                    for (int j = 0; j < i; j++){
                        ss << " ";
                    }
                    ss <<  it.str(i+1) << std::endl;
                }
                for (int j = 1; j < i; j++){
                    ss << " ";
                }
            }
        }
        ss << "]";
        return ss.str();
    }

    /*************************
     * ITERATORS
     *************************/
    NIOperator::NIOperator(NodeType type) :
        type(type)
    {
    }
    void NIOperator::next(){
        std::cerr << "Iterator not implemented for this type!\n";
    }
    void NIOperator::_begin(){
        std::cerr << "Iterator not implemented for this type!\n";
    }
    void NIOperator::_end(){
        std::cerr << "Iterator not implemented for this type!\n";
    }
    Value * NIOperator::value(){
        std::cerr << "Iterator not implemented for this type!\n";
        return 0;
    }
    std::string NIOperator::key(){
        std::cerr << "Key not implemented for this type!\n";
        return std::string("Key not implemented for this type");
    }
    bool NIOperator::eq(NIOperator *ni){
        std::cerr << "Equality not implemented for this type!\n";
        return false;
    }
    bool NIOperator::at_end(){
        std::cerr << "at_end not implemented for this type!\n";
        return false;
    }

    /* ObjectIterator */

    ObjectIterator::ObjectIterator(Object *object) :
        NIOperator(io::OBJECT),
        object(object),
        it (0)
    {}
    void ObjectIterator::_begin(){
        it = object->_fields.begin();
    }
    void ObjectIterator::_end(){
        it = object->_fields.end();
    }
    void ObjectIterator::next(){
        it++;
    }
    Value * ObjectIterator::value(){
        return it->second;
    }
    std::string ObjectIterator::key(){
        return it->first;
    }
    bool ObjectIterator::eq(NIOperator *ni){
        if (this->type == ni->type) {
            return it == static_cast<ObjectIterator *>(ni)->it;
        }
        else {
            std::cerr << "Comparing two Iterators of different type!\n";
            return false;
        }
    }
    bool ObjectIterator::at_end(){
        return it == object->_fields.end();
    }

    /* ListIterator */

    ListIterator::ListIterator(List *list) :
        NIOperator(io::LIST),
        list(list),
        it (0)
    {}
    void ListIterator::_begin(){
        it = list->_list.begin();
    }
    void ListIterator::_end(){
        it = list->_list.end();
    }
    void ListIterator::next(){
        it++;
    }
    Value * ListIterator::value(){
        return *it;
    }
    bool ListIterator::eq(NIOperator *ni){
        // Dangerous!
        return it == static_cast<ListIterator *>(ni)->it;
    }
    bool ListIterator::at_end(){
        return it == list->_list.end();
    }

    /* ItemIterator */
    
    ItemIterator::ItemIterator(Item *item) :
        NIOperator(io::ITEM),
        item(item),
        _at_end(false)
    {}
    void ItemIterator::next(){
        _at_end = true;
    }
    void ItemIterator::_begin(){
    }
    void ItemIterator::_end(){
        _at_end = true;
    }
    Value * ItemIterator::value(){
        return item;
    }
    bool ItemIterator::at_end(){
        return _at_end;
    }
    bool ItemIterator::eq(NIOperator *ni){
        if (this->type == ni->type) {
            return _at_end == static_cast<ItemIterator *>(ni)->_at_end;
        }
        else {
            std::cerr << "Comparing two Iterators of different type!\n";
            return false;
        }
    }
}
