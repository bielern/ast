#include <sstream>
#include <cmath>
#include <assert.h>
#include "nvector.h"
#include "../ast/node.h"

namespace math {
    // Constructors
    NVector::NVector(unsigned int length, double init){
        _length = length;
        _data = new double[_length];
        for (unsigned int i = 0; i < length; i++){
            _data[i] = init;
        }
    }
    NVector::NVector(const std::vector<double> &init){
        _length = init.size();
        _data = new double[_length];
        for (unsigned int i = 0; i < _length; i++){
            _data[i] = init[i];
        }
    }
    NVector::NVector(const io::Node &n){
        _length = n.size();
        _data = new double[_length];
        io::NodeIterator it = n.begin(),
            to = n.end();
        for (unsigned int i = 0; it != to; ++i, ++it){
            _data[i] = it.get<double>();
        }
    }
    NVector::NVector(const NVector &n){
        _length = n._length;
        _data = new double[_length];
        for (unsigned int i = 0; i < _length; i++){
            _data[i] = n._data[i];
        }
    }
    NVector::NVector() : 
        _length(0),
        _data(0)
    {}
    NVector::~NVector(){
        delete[] _data;
    }
    NVector &
    NVector::operator=(const NVector &n){
        if (_data)
            delete[] _data;
        _length = n._length;
        _data = new double[_length];
        for (unsigned int i = 0; i < _length; i++){
            _data[i] = n._data[i];
        }
        return *this;
    }

    // Mathematical Operations
    NVector &
    NVector::operator+=(const NVector &n){
        assert(_length == n._length);
        for (unsigned int i = 0; i < _length; i++){
            _data[i] += n[i];
        }
        return *this;
    }
    NVector &
    NVector::operator-=(const NVector &n){
        assert(_length == n._length);
        for (unsigned int i = 0; i < _length; i++){
            _data[i] -= n[i];
        }
        return *this;
    }
    NVector &
    NVector::operator*=(const NVector &n){
        assert(_length == n._length);
        for (unsigned int i = 0; i < _length; i++){
            _data[i] *= n[i];
        }
        return *this;
    }
    NVector &
    NVector::operator/=(const NVector &n){
        assert(_length == n._length);
        for (unsigned int i = 0; i < _length; i++){
            _data[i] /= n[i];
        }
        return *this;
    }


    double 
    NVector::abs2(){
        return dot(*this, *this);
    }

    double 
    NVector::abs(){
        return sqrt(abs2());
    }

    NVector 
    NVector::normalize(){
        double len = abs();
        if (len == 0.0){
            return NVector(_length);
        } else {
            return *this / NVector(_length, 1.0 / len);
        }
    }

    io::Node 
    NVector::toAST() const{
        io::Node n = io::mkList();
        for (unsigned int i = 0; i < _length; i++){
            n.push_back(io::mkItem(_data[i]));
        }
        return n;
    }

    void 
    NVector::fromAST(const io::Node &n){
        *this = NVector(n);
    }

    std::string
    NVector::str(){
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }


    unsigned int 
    NVector::length() const{
        return _length;
    }

    void 
    NVector::length(unsigned int i, double init){
        if (_data){
            delete[] _data;
        }
        *this = NVector(i, init);
    }

    NVector 
    NVector::mkNew(unsigned int from, unsigned int upto){
        unsigned int limit = upto < _length ? upto : _length;
        unsigned int start = from < limit ? from : limit;
        NVector result;
        result._length = limit - start;
        result._data = new double[result._length];
        for (unsigned int i = 0; i < result._length; i++){
            result._data[i] = _data[i + start];
        }
        return result;
    }

    double &
    NVector::operator[](unsigned int i){
        return _data[i];
    }
    double
    NVector::operator[](unsigned int i) const {
        return _data[i];
    }

    // ================== Free functions ==================
    double
    dot(const NVector &lhs, const NVector &rhs){
        double dp = 0.0;
        for (unsigned int i = 0; i < lhs.length(); i++){
            dp = lhs[i] * rhs[i];
        }
        return dp;
    }

    NVector operator+(NVector lhs, const NVector &rhs){
        return lhs += rhs;
    }
    NVector operator-(NVector lhs, const NVector &rhs){
        return lhs -= rhs;
    }
    NVector operator*(NVector lhs, const NVector &rhs){
        return lhs *= rhs;
    }
    NVector operator/(NVector lhs, const NVector &rhs){
        return lhs /= rhs;
    }
}

std::ostream & 
operator<< (std::ostream &out, const math::NVector &n){
    io::Root root = n.toAST();
    out << root;
    return out;
}
