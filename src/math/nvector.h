#ifndef NVECTOR_H
#define NVECTOR_H

#include <vector>
#include <iostream>
#include <string>

namespace io {
    class Node;
}

namespace math {
    class NVector {
        public:
            NVector(unsigned int length, double init=0.0);
            NVector(const std::vector<double> &init);
            NVector(const io::Node &n);
            NVector(const NVector &n);
            ~NVector();

            NVector &operator=(const NVector &n);
            NVector &operator+=(const NVector &n);
            NVector &operator-=(const NVector &n);
            NVector &operator*=(const NVector &n);
            NVector &operator/=(const NVector &n);

            double abs2();
            double abs();
            NVector normalize();

            io::Node toAST() const;
            void fromAST(const io::Node &n);
            std::string str();

            unsigned int length() const;
            void length(unsigned int i, double init=0.0);
            NVector mkNew(unsigned int from, unsigned int upto);
            double &operator[](unsigned int i);
            double  operator[](unsigned int i) const;

            friend double dot(const NVector &lhs, const NVector &rhs);

        protected:
            NVector();
            unsigned int _length;
            double *_data;

    };

    double dot(const NVector &lhs, const NVector &rhs);

    NVector operator+(NVector lhs, const NVector &rhs);
    NVector operator-(NVector lhs, const NVector &rhs);
    NVector operator*(NVector lhs, const NVector &rhs);
    NVector operator/(NVector lhs, const NVector &rhs);
}
std::ostream & operator<< (std::ostream &out, const math::NVector &n);

#endif
