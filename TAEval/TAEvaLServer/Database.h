/*

Database that utilizes my Binary Tree as the storage mechanism

Author: Draymire
Data: 30/10/13

*/

#ifndef DRAYMIRE_DATABASE
#define DRAYMIRE_DATABASE

//		Error Name         Error Code

#define NONE                  0
#define SUCCESS               0
#define KEY_NOT_FOUND         1
#define KEY_ALREADY_IN_USE    2
#define FILE_NOT_FOUND        3
#define FAILED_FILE_DELETION  4
#define FAILED_TO_RENAME_FILE 5
#define UNABLE_TO_CREATE_FILE 6
#define CORRUPT_FILE          7
#define FILE_ALREADY_EXISTS   8
#define ARRAY_OUT_OF_BOUNDS   255


//Useful string
#define DELIMETER_STRING "Put something here i guess"

#include <iostream>
#include <fstream>
#include <sstream>
#include "BinaryTree.h"



class Database{

public:
	Database(int, std::string, std::string*);
	~Database();

	std::string** query(int/*Tree Number*/, std::string* /*Search Key*/);// std::string** /*Return Data*/);
	char insert(int, std::string*, std::string**, std::string*);
	
	char removeEntry(int /*Tree Number*/, std::string* /*Key*/);
	char edit(int, std::string*, std::string**);//variables to be determined

private:

	int numberOfTrees;
	std::string storagePath;

	BinaryTree<std::string, std::string>** arrayOfTrees;
	std::string* treeFiles;

	char findFile(int /*Tree Number*/, std::string* /*Key*/, std::string* /*Return Filename*/);

	char removeFile(int /*Tree Number*/, std::string* /*Filename*/);
	char buildFile(std::string*, std::string**);

	char populateTree(int, std::string*);

	std::string** readFile(std::string*);


	char updateTreeFile(int /*Tree Number*/);

	char cleanUp(char, std::string*);
};

#endif
