/*

Filename: DatabaseFileIO.h
Author: Draymire
Last Modified: 19/11/13 02:35
Description: File I/O Class for my database

*/


#ifndef DATABASE_IO
#define DATABASE_IO

#include <string>

class DatabaseFileIO {
public:
	DatabaseFileIO(std::string);
	~DatabaseFileIO();
	char readFile(std::string*, std::string**);
	char writeFile(std::string*, std::string**);
	char removeFile(std::string*);
	char overwriteFile(std::string*, std::string**);

	std::string getPath() const;
private:
	std::string directoryPath;
	void cleanup(std::ifstream*, int** = NULL, std::string** = NULL);
};

#endif
//DATABASE_IO