#ifndef BASICS_H_INCLUDED
#define BASICS_H_INCLUDED

#include <string>
#include <sstream>


inline std::string toString(double val)
{
    std::ostringstream oss;
    oss << val;
    return oss.str();
}

inline double toDouble(std::string in)
{
    double out;
    std::istringstream iss;
    iss.str(in);
    iss >> out;
    return out;
}

inline unsigned long puis(unsigned long a, unsigned long b)
{
    unsigned long out(1);
    for(unsigned int i = 0 ; i < b ; i++) {
        out = out * a;
    }
    return out;
}

#endif // BASICS_H_INCLUDED
