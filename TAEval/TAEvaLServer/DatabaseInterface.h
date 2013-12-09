#ifndef DATABASE_INTERFACE
#define DATABASE_INTERFACE

#include <string>
#include <iostream>

#include "Database.h"

class DatabaseInterface {

public:
	DatabaseInterface(int, std::string, std::string*);
	~DatabaseInterface();

	char handleRequest(std::string**, std::string**);

private:
	Database db;

	void adaptRequest(std::string** ,/*Return Variables*/std::string**, std::string**);

	bool loginRequest(std::string*, std::string*, std::string**);
	bool createRequest(std::string*, std::string*, std::string*, std::string**);
	bool editRequest(std::string*, std::string**);
	bool removeRequest(std::string*, std::string*);

	bool viewRequest(std::string*, std::string*, std::string*, std::string*, std::string**);
	bool viewTaRequest(std::string*, std::string*, std::string**);
	bool viewTaskRequest(std::string*, std::string*, std::string*, std::string**);
	bool viewTaskInfoRequest(std::string*, std::string**);
	bool viewEvalInfoRequest(std::string*, std::string**);


};

#endif
//DATABASE_INTERFACE