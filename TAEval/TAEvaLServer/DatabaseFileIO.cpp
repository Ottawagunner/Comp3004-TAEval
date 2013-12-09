/*

Filename: DatabaseFileIO.cpp
Author: Draymire
Last Modified: 19/11/13 02:35
Description: File I/O Class for my database

Memory Leaks:
	None unless you don't manually delete the returned array

Comment:
	Remember to delete DEBUG LINES
*/

#include "DatabaseFileIO.h"
#include <fstream>
#include <sstream>
#include <iostream>


#define SUCCESS 0
#define FILE_DOES_NOT_EXIST 1
#define CORRUPT_FILE 2
#define UNABLE_TO_CREATE_FILE 3


DatabaseFileIO::DatabaseFileIO(std::string arg1) : directoryPath(arg1){}
DatabaseFileIO::~DatabaseFileIO(){}

void DatabaseFileIO::cleanup(std::ifstream* myFilePtr, int** lenArr, std::string** dataArray){
	myFilePtr->close();
	if (lenArr != NULL)
		delete[] *lenArr;
	if (dataArray != NULL){
		delete[] *dataArray;
		*dataArray = NULL;
	}
}


char DatabaseFileIO::readFile(std::string* filenamePtr, std::string** dataArray){
	std::ifstream myFile((directoryPath + *filenamePtr).c_str());

	int sizeOfArray = 1; //to be used for dataArray's size
	int* lenOfArray; //array of sub array lengths
	int numOfArray; //indicates number of sub arrays

	std::string buffer;//buffer for getline
	
	if (!myFile){
		cleanup(&myFile);
		return FILE_DOES_NOT_EXIST;
	}

	if (!getline(myFile, buffer)){
		cleanup(&myFile);
		return CORRUPT_FILE;
	}

	std::stringstream(buffer) >> numOfArray;
	sizeOfArray += numOfArray;

	//Determin Length of sub Arrays
	lenOfArray = new int[numOfArray];
	for (int i = 0; i < numOfArray; i++){
		if (!getline(myFile, buffer)){
			cleanup(&myFile, &lenOfArray);
			return CORRUPT_FILE;	
		}

		std::stringstream(buffer) >> lenOfArray[i];
		sizeOfArray += lenOfArray[i];
	}

	//Build the Array using the newly acquired size
	*dataArray = new std::string[sizeOfArray];

	std::stringstream convert;
	convert << numOfArray;
	buffer = convert.str();
	(*dataArray)[0] = buffer;

	//Clean the stringstream
	convert.str(std::string());
	convert.clear();

	int iterPos = numOfArray+1;

	for(int i = 0; i < numOfArray; i++){
		
		convert << lenOfArray[i];
		buffer = convert.str();
		(*dataArray)[i+1] = buffer;
	
		//Clean the stringstream
		convert.str(std::string());
		convert.clear();

		for(int k = 0; k < lenOfArray[i]; k++){
			if (!getline(myFile, buffer)){
				cleanup(&myFile, &lenOfArray, dataArray);
				return CORRUPT_FILE;
			}
			(*dataArray)[iterPos+k] = buffer;
		}
		iterPos+=lenOfArray[i];
	}

	//Clean up before return.
	cleanup(&myFile, &lenOfArray);

	return SUCCESS;

}

char DatabaseFileIO::writeFile(std::string* filenamePtr, std::string** dataArray){

	std::ofstream myFile((directoryPath + *filenamePtr).c_str());

	if (!myFile)
		return UNABLE_TO_CREATE_FILE;

	int size, num, temp;

	size = 1;

	std::stringstream((*dataArray)[0]) >> num;
	size += num;

	for (int i = 0; i < num; i++){
		std::stringstream((*dataArray)[i+1]) >> temp;
		size+=temp;
	}

	for (int i = 0; i < size; i++){
		myFile << (*dataArray)[i] << std::endl;
	}
	return SUCCESS;
}

char DatabaseFileIO::removeFile(std::string* filenamePtr){

	return remove((directoryPath + *filenamePtr).c_str());

}

char DatabaseFileIO::overwriteFile(std::string* filenamePtr, std::string** dataArray){

	std::string tempFilename = (*filenamePtr)+"TEMP";

	char error;

	error = writeFile(&tempFilename, dataArray);

	if(error) return error;

	error = removeFile(filenamePtr);

	if(error) return error;
	
	error = rename(((directoryPath + tempFilename).c_str()),((directoryPath + *filenamePtr).c_str()));

	if(error) return error;
	else return SUCCESS;
}

std::string DatabaseFileIO::getPath() const{
	return directoryPath;
}