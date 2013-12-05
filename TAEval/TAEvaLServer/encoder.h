#ifndef ENCODER_H
#define ENCODER_H
#include <string>
#include <sstream>

class encoder{

public:
    encoder();
    std::string encode(short, std::string, std::string);
    std::string encode(short, std::string *);
    std::string encode(std::string, std::string);
    std::string encode(short, std::string);
};

#endif // ENCODER_H
