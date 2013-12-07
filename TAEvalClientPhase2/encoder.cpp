#include "encoder.h"


encoder::encoder(){}

std::string encoder::encode(short messageLength, std::string lockStatus, std::string message)
{
    std::stringstream mL;
    mL << messageLength;
    return ""+mL.str()+"~"+lockStatus+"~"+message;
}

std::string encoder::encode(short listLength, std::string* list)
{
    std::string encodedList = "";
    for(int i=0; i<listLength; i++)
    {
        encodedList+=list[i];
        if(i+1 < listLength)
            encodedList+="~";
    }
}

std::string encoder::encode(std::string original, std::string toAdd)
{
    return original+"~"+toAdd;
}

std::string encoder::encode(short numberOfTildas, std::string toAdd)
{
    std::stringstream mL;
    mL << numberOfTildas;
    return ""+mL.str()+"~"+toAdd;
}

