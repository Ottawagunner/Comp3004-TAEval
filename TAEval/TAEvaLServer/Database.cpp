/*

Database that utilizes my Binary Tree as the storage mechanism

Author: Draymire
Data: 30/10/13

NOTE:: Remember to search out and correct WARNING content.

WARNING:: filename probably should be dereference everywhere, as should most other string variables. Check it over.  

DESIGN_DECISION: THIS DATABASE MAKES NO GUARANTEE THAT REFERENCES TO DATA WILL BE REMOVED
				WHEN THE ACTUAL DATA IS. 
				This decision was made in a speed/memory use trade favouring the extra speed 
				regardless of how small it might be.  
				If the user of the Database is worried about using the extra space storing 
				references to deleted data then they may chain together several commands to 
				find and remove the references on their own terms. 


ERROR CODES: 
CODE :         NAME           :           DESCRIPTION 
0    : NONE                   :   There were no Errors, Everything is running Smoothly.
0    : SUCCESS                :   There were no Errors, Everything is running Smoothly.
1    : KEY_NOT_FOUND          :   Could not find the given Key.
2    : KEY_ALREADY_IN_USE     :   The Key provided is already in use. The Databases backend does not support duplicate Keys. 
3    : FILE_NOT_FOUND         :   Could not locate the given File.
4    : FAILED_FILE_DELETION   :   Could not delete the specified file. Could be caused as a result of multiple reasons. The most likely being it not existing in the first place.
5    : FAILED_TO_RENAME_FILE  :   Could not rename the specified file. The name might still be in use or the file might not exist.
6    : UNABLE_TO_CREATE_FILE  :   Failed to create a new file. See ofstream for possible reasons
7    : CORRUPT_FILE           :   The file you are reading is corrupt. Usually caused by a crash while writing the file.
8    : FILE_ALREADY_EXISTS    :   The file you are trying to create already exists and therefore could not be created. 
255  : ARRAY_OUT_OF_BOUNDS    :   You are probably trying to access a tree that doesn't exist.
*/

#include "Database.h"



// Input Params: size = the number of trees
//				path = the storage pathname
//				setupList = list of files used in tree population
Database::Database(int size = 0, std::string path = "", std::string* setupList = NULL){
	pathname = path;
	numberOfTrees = size;
	if (size != 0)
		arrayOfTrees = &((new typename BinaryTree<std::string,std::string>::BinaryTree())[size]);	

	for (int i = 0;i<size;i++){
		//Should probably do something with this so that the program won't go forward with a corrupt database.
		populateTree(i, &setupList[i]);
	}
}

Database::~Database(){
	delete[] arrayOfTrees;
}

////////Public Functions

char Database::query(int treeNumber, std::string* key, std::string** returnValue){
//
// Input Params : treeNumber -> The Number of the Tree you wish to access. 
//					key		-> The key to search the Tree with
//
//Output Params : returnValue -> The data obtained via the query.
//
//  Description : Requests data from the Trees. Utilizes the provieded TreeNumber to know
//					Which Tree to Search and uses the key to find any stored information.
//
//      Returns : 0 if there were no errors
//					Otherwise can return:
//						ARRAY_OUT_OF_BOUNDS
//						any Error Code produced by findFile()
//						any Error Code produced by readFile()
//

	char error = ARRAY_OUT_OF_BOUNDS;
	std::string filename;

	if (treeNumber < numberOfTrees) //Make sure the treeNumber actually exists.
		if ( (error = findFile(treeNumber, key, &filename)) == NONE)
			return readFile(&filename, returnValue);
	
	return error;
}

char Database::insert(int treeNumber, std::string* key, std::string** data){
//
// Input Params : treeNumber -> The Number of the Tree you wish to access. 
//					key		-> The key to be associated with the data
//					data 	-> The Data to insert
//
//Output Params : None
//
//  Description : Adds the provided (key,data) pair to the specifed Tree.
//					Also builds a file, by calling buildFile(), for permanent storage
//					 of the provided data
//	
//      Returns : 0 if there were no errors
//					Otherwise can return:
//						ARRAY_OUT_OF_BOUNDS
//						any Error Code produced by findFile() other than
//							KEY_NOT_FOUND or NONE 
//							NONE results in KEY_ALREADY_IN_USE being returned
//						any Error Code produced buildFile()
//						any Error Code produced by insertFile()
//						any Error Code produced by updateTreeFile()
//
	char error = ARRAY_OUT_OF_BOUNDS;
	std::string filename;

	if (treeNumber < numberOfTrees)
		if ( (error = findFile(treeNumber, key, &filename)) == KEY_NOT_FOUND)
			if ( (error = buildFile(data, &filename)) == NONE)
				return insertFile(treeNumber, key, &filename);
		else if (error == NONE)
			return KEY_ALREADY_IN_USE;

	return error;
}

char Database::removeEntry(int treeNumber, std::string* key){
//
// Input Params : treeNumber -> The Number of the Tree you wish to access. 
//					key		-> The key to find and remove
//
//Output Params : None
//
//  Description : Removes the specifed Node from the specifed tree
//					and deletes the associated file by calling removeFile()
//
//      Returns : 0 if there were no errors
//					Otherwise can return:
//						ARRAY_OUT_OF_BOUNDS
//						any Error Code produced by removeFile()
//						any Error Code produced by updateTreeFile()
//
	std::string filename;

	if (treeNumber < numberOfTrees)
		return removeFile(treeNumber, key);

	updateTreeFile(treeNumber);

	return ARRAY_OUT_OF_BOUNDS;
}

char Database::update(){//WARNING
//
// Input Params :
//
//Output Params :
//
//  Description :
//
//      Returns :
//	

	std::cout << "I don't know what i'm doing here" << std::endl;
}

/////////Private Helper Functions

char Database::buildFile(std::string** data, std::string* filename){
//
// Input Params : data -> The data to populate the file with
//					filename -> The name to be used for the new file
//
//Output Params : None
//
//  Description : Using the given data it creates a file which will 'permanently' 
//					Store the data.
//	
//      Returns : 0 if there were no errors
//					Otherwise can return:
//						FILE_ALREADY_EXISTS	
//						CORRUPT_FILE
//

	int size, ss;

	std::ofstream theFile ((*filename).c_str());

	if (!theFile.is_open())
		return FILE_ALREADY_EXISTS;

	int* arraySizes;

	try{
		//create integer array from data[0]
		size = std::stoi(data[0][0]);
		arraySizes = new int[size];

		theFile << data[0][0];

		for (int i = 1; i <= size; i++){
			ss = std::stoi(data[0][i]);
			(arraySizes[i-1]) = ss;
			theFile << data[0][i];
		}
	} catch (std::exception const & e){
		return CORRUPT_FILE;
	}

	for (int i= 0; i < size; i++){
		for (int k = 0; k < arraySizes[i]; k++){
			theFile << data[i+1][k] << std::endl;
		}
	}

	theFile.close();

	return SUCCESS;

// FILE SETUP:
//	[[array of integer values specifying size of itself, and number of other values to expect.],[values 1],...,[Values n]]
}

char Database::readFile(std::string* filename, std::string** data){
//
// Input Params : filename -> The name of the to read.
//
//Output Params : data -> Storage for the data in the file
//
//  Description : Reads in the Data from the File so that it can be utilized.
//
//      Returns : 0 if there were no errors
//					Otherwise can return:
//						FILE_NOT_FOUND
//						CORRUPT_FILE
//	
// Comments: Allocates several arrays with calls to new. Therefore useage of readFile must be balanced with proper destruction
//			of the data pointer.
//
	int size, temp;
	std::string buffer;

	// filename probably should have path prepended to it.
	std::ifstream theFile ((*filename).c_str());

	if (!theFile.is_open())
		return FILE_NOT_FOUND;


	//Read in the number of arrays needed
	if(!getline(theFile, buffer))
		return CORRUPT_FILE;

	try{
		//Change the buffer into an int
		size = std::stoi(buffer);

		int* arraySizes[size+1];
		(*arraySizes[0]) = size;

		data = new std::string*[size+1];
		data[0] = new std::string[size+1];
		data[0][0] = buffer;

		for (int i = 1; i <= size; i++){
			if(!getline(theFile, buffer))
				return CORRUPT_FILE;	

			temp = std::stoi(buffer);
			(*arraySizes[i]) = temp;
			data[0][i] = buffer;
			data[i] = new std::string[temp];
		}

		for (int i = 1; i <= size; i++){
			for (int k = 0; k < (*arraySizes[i]); k++){
				if (!getline(theFile, buffer))
					return CORRUPT_FILE;

				data[i][k] = buffer;
			}
		}

	} catch (std::exception const & e){
		return CORRUPT_FILE;
	}

	theFile.close();

	return SUCCESS;

}

char Database::removeFile(int treeNumber, std::string* key){
//
// Input Params : treeNumber -> The Number of the Tree you wish to access. 
//					key		-> The key to find and remove
//
//Output Params : None
//
//  Description : Searches out and removes the specified Node from
//					the specifed tree. Also removes the associated file.
//
//      Returns : 0 if there were no errors
//					Otherwise can return:
//						FILE_NOT_FOUND
//						FAILED_FILE_DELETION
//
	std::string filename;

	if (findFile(treeNumber, key, &filename))
		return FILE_NOT_FOUND;

	arrayOfTrees[treeNumber].remove(key);//WARNING

	updateTreeFile(treeNumber);

	if (remove((filename).c_str()))
		return FAILED_FILE_DELETION;
}

char Database::updateTreeFile(int treeNumber){
//
// Input Params : treeNumber -> the tree to update
//
//Output Params : None
//
//  Description : updates the .db file associated with the tree
//
//      Returns : 0 if there were no errors
//					Otherwise can return:
//						FAILED_FILE_DELETION
//						FAILED_TO_RENAME_FILE
//

	std::ofstream myFile (((treeFiles[treeNumber])+".TEMP").c_str());

	myFile << arrayOfTrees[treeNumber];

	myFile.close();

	if (remove((treeFiles[treeNumber]).c_str()))
		return FAILED_FILE_DELETION;

	if (rename((treeFiles[treeNumber]+".TEMP").c_str(), (treeFiles[treeNumber]).c_str()))
		return FAILED_TO_RENAME_FILE;

	return SUCCESS;

//COMMENT:: I'll have to repurpose my print function for this. 

}

char Database::insertFile(int treeNumber, std::string* key, std::string* filename){
//
// Input Params : treeNumber -> the tree to insert into
//					key -> the key part of the (key, value) pairing
//					filename -> the value part of the (key, value) pairing
//
//Output Params : None
//
//  Description : Adds a (key, value) node to the specified tree
//
//      Returns : 0 if there were no errors
//					Otherwise can return:
//						any Error Code produced by updateTreeFile()
//

	arrayOfTrees[treeNumber].add(key, filename);

	return updateTreeFile(treeNumber);

}

char Database::editFile(std::string* filename, std::string** dataList){//WARNING
//
// Input Params : filename -> the name of the file to edit
//					dataList -> The data that is to replace the old data
//
//Output Params : None
//
//  Description : Creates a temporary file which contains the updated data provided
//					Then replaces the old file with the temporary one.
//
//      Returns : 0 if there were no errors
//					Otherwise can return:
//						UNABLE_TO_CREATE_FILE
//						FAILED_FILE_DELETION
//						FAILED_TO_RENAME_FILE
//
	std::ofstream tempFile (((*filename)+".TEMP").c_str());
	if(!tempFile.is_open())
		return UNABLE_TO_CREATE_FILE;
	
	              /* Might need to dereference dataList[k]*/
				/* Might just call buildFile() instead. Kinda makes more sense*/
	//WARNING REWRITE
	for (int k = 0; (*dataList[k]) != DELIMETER_STRING; k++){
		for (int i = 0; (dataList[k][i]) != DELIMETER_STRING; i++){
			tempFile << dataList[k][i] << std::endl;
		}
		tempFile << DELIMETER_STRING << std::endl;
	}
	tempFile << DELIMETER_STRING << std::endl;

	tempFile.close();

	if (remove((*filename).c_str()))
		return FAILED_FILE_DELETION;

	if (rename(((*filename)+".TEMP").c_str(), (*filename).c_str()))
		return FAILED_TO_RENAME_FILE;

	return SUCCESS;
}

char Database::populateTree(int treeNumber, std::string* filename){
//
// Input Params : treeNumber -> Access number for the tree you wish to populate.
//					filename -> the name of the file to use for population
//
//Output Params : None
//
//  Description : initializes the Trees to state they were at during last runtime
//					by reading in the appropriate .db files.
//
//      Returns : 0 if there were no errors
//					Otherwise can return:
//						CORRUPT_FILE
//	

	std::ifstream theFile ((*filename).c_str());

	if (!theFile.is_open())
		return CORRUPT_FILE;

	std::string buffer;
	std::string* key;
	std::string* value;

	while(getline(theFile, buffer)){
		key = new std::string(buffer);
		getline(theFile, buffer);
		value = new std::string(buffer);

		arrayOfTrees[treeNumber].add(key,value);
	}

	return SUCCESS;
}

int main(){
	return 0;
}