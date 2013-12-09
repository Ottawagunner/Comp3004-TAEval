#ifndef DRAYMIRE_DATABASE_LOGIC
#define DRAYMIRE_DATABASE_LOGIC

#include "Pair.h"
#include "BinaryTree.h"
#include "DatabaseFileIO.h"

class Database {

public:

	Database(int, std::string, std::string*);
	~Database();

	char find(int, std::string*, std::string**);
	char add(int, std::string*, std::string*, std::string**);
	char edit(int, std::string*, std::string**);
	char remove(int, std::string*);

private:

	void treeInit(int);
	void updateTreeFile(int);

	BinaryTree<Pair>* arrayOfTrees;
	int numOfTrees;
	std::string* arrayOfFiles;
	DatabaseFileIO fileIO;

};


#endif
//DRAYMIRE_DATABASE_LOGIC