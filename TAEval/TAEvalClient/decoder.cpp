#include "decoder.h"

decoder::decoder(){}

void decoder::decode(char delimiter, std::string command, std::string** out) // message, output string array
{
    short firstPos = command.find_first_of(delimiter, 0); // gets the position of the first delimiter
    std::string firstP = command.substr(0,firstPos); // gets the string up to that delimiter
    int numberOfSegments = atoi(firstP.c_str()) +1; // turns it into an int and adds 1
    std::cout<<"Number of segments: "<<numberOfSegments<<std::endl;
    std::cout<<"Command: "<<command<<std::endl;
    short pos[numberOfSegments]; // allocates enough space to hold the position of all the delimiters

    std::string* output = new std::string[numberOfSegments+1]; // Creates new array of string to contain the new message

    for(int i=0; i<numberOfSegments;i++)
        output[i] = "";

    for(short i = 0; i < numberOfSegments; i++) // Goes through numberOfSegments of delimiters and records their position in the string
    {
        pos[i] = 0;
        if(i == 0) continue;
        else
        {
            if(pos[i-1]+1 >= command.length())
            {
                pos[i] = -1;
                break;
            }
            pos[i] = command.find_first_of(delimiter, pos[i-1]+1);
        }
    }

    for(short i = 0; i < numberOfSegments; i++) // Assigns every segment of the command to the message array
    {
        if(i == 0)
            output[i] = command.substr(pos[i],pos[i+1]-pos[i]);
        else if(i+1 > numberOfSegments)
            output[i] = command.substr(pos[i]+1,-1);
        else
            output[i] = command.substr(pos[i]+1,pos[i+1]-pos[i]-1);
         //std::cout<<((output[i]).c_str())<<std::endl;
    }
    *out = output;
}
