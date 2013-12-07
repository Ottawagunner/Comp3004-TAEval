#ifndef DECODER_H
#define DECODER_H
#include <cstdlib>
#include <iostream>

class decoder
{
public:
    decoder();
    void decode(char, std::string, std::string**); // arg: delimiter character,message, return string array
};
#endif // DECODER_H
