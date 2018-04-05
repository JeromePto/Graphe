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

#endif // BASICS_H_INCLUDED
