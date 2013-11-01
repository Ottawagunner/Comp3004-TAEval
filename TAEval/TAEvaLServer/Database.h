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
#include <fstream>>
#include <stdio.h>
#include "BinaryTree.h"



class Database{

public:
	Database(int /*Number of Trees*/,std::string /*Path to Storage*/, std::string* /*Tree File Names*/);
	~Database();

	char query(int /*Tree Number*/,std::string /*Key*/, std::string* /*Return Value*/);
	char insert(int /*Tree Number*/, std::string /*Key*/, std::string* /*Filename*/);
	char remove(int /*Tree Number*/, std::string /*Key*/);
	char update();//variables to be determined

private:

	BinaryTree<std::string,std::string>* arrayOfTrees;
	std::string pathname;
	int numberOfTrees;
	std::string* treeFiles;

	char insertFile(int /*Tree Number*/, std::string /*Key*/, std::string /*Data*/);
	char findFile(int /*Tree Number*/, std::string /*Key*/, std::string /*Return Filename*/);

	char removeFile(std::string* /*Filename*/);
	char buildFile(std::string* /*Data*/, std::string* /*Return Filename*/);
	char readFile(std::string /*Filename*/);
	char editFile(std::string* /*filename*/, std::string* /*Data List*/);//variables to be determined.

	char populateTree(int /*Tree*/, std::string* /*Filename*/); 
};

#endif