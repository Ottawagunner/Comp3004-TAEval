#include "Database.h"
#include <fstream>
#include <string>
#include <iostream>//DEBUG

#define UNABLE_TO_WRITE_FILE 1


Database::Database(int arg1, std::string arg2, std::string* arr) : numOfTrees(arg1), fileIO(arg2){
	if(numOfTrees > 0){
		arrayOfFiles = arr;
		arrayOfTrees = new BinaryTree<Pair>[numOfTrees];

		for(int i = 0; i < numOfTrees; i++)
			treeInit(i);
	}
}

Database::~Database(){
	for(int i = 0; i < numOfTrees; i++) 
		updateTreeFile(i);
	delete[] arrayOfTrees; 
}

char Database::find(int treeNum, std::string* keyPtr, std::string** dataArray){

	Pair data(*keyPtr);

	if(arrayOfTrees[treeNum].find(&data))
		return DATA_NOT_FOUND;

	std::string fileValue = data.getFile();
	fileIO.readFile(&fileValue, dataArray);

	return 0;
}

char Database::add(int treeNum, std::string* keyPtr, std::string* filenamePtr, std::string** dataArray){
	
	Pair data(*keyPtr, *filenamePtr);

	if(fileIO.writeFile(filenamePtr, dataArray))
		return UNABLE_TO_WRITE_FILE;

	arrayOfTrees[treeNum].add(&data);

    updateTreeFile(treeNum);

	return 0;
}

char Database::edit(int treeNum, std::string* keyPtr, std::string** dataArray){

	Pair data(*keyPtr);

	if(arrayOfTrees[treeNum].find(&data))
		return DATA_NOT_FOUND; //Thus the appropriate file cannot be edited

    for(int i = 0; i < 5; i++){std::cout << "(*dataArray)[" << i << "] " << (*dataArray)[i] << std::endl;}

	std::string fileValue = data.getFile();
    std::cout << "fileVAlue " << fileValue << std::endl;
	fileIO.overwriteFile(&fileValue, dataArray);

	return 0;
}

char Database::remove(int treeNum, std::string* keyPtr){

	Pair data(*keyPtr);

	if(arrayOfTrees[treeNum].find(&data))
		return DATA_NOT_FOUND;//Nothing to delete

	std::string fileValue = data.getFile();
	arrayOfTrees[treeNum].remove(&data);
	fileIO.removeFile(&fileValue);

    updateTreeFile(treeNum);

	return 0;
}


void Database::treeInit(int index){

	std::ifstream myFile( (fileIO.getPath() + arrayOfFiles[index]).c_str() );
	Pair newDataPoint;

	std::string key,file;

	key = "rabbit";

	while(!myFile.eof()){
		if(!getline(myFile, key))
			break;
		if(!getline(myFile, file))
			break;

		newDataPoint = Pair(key, file);
		//std::cout << "newDataPoint.getKey(): " << newDataPoint.getKey() << std::endl;
		//std::cout << "newDataPoint.getFile(): " << newDataPoint.getFile() << std::endl;
		arrayOfTrees[index].add(&newDataPoint);
	}

	myFile.close();
}

void Database::updateTreeFile(int index){

	std::ofstream myFile( (fileIO.getPath() + arrayOfFiles[index]).c_str() );

	myFile << arrayOfTrees[index];

	myFile.close();
}
