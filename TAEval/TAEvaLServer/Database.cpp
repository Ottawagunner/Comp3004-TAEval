/*

Database that utilizes my Binary Tree as the storage mechanism

Author: Draymire
Data: 1/11/13

I think we need something to do

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
//				path = the storage storagePath
//				setupList = list of files used in tree population
Database::Database(int arg1, std::string arg2, std::string* list) : numberOfTrees(arg1), storagePath(arg2){
	treeFiles = list;
	arrayOfTrees = new BinaryTree<std::string, std::string>*[numberOfTrees];	

	for (int i = 0; i < numberOfTrees; i++){
        arrayOfTrees[i] = new BinaryTree<std::string, std::string>;
		populateTree(i, &treeFiles[i]);
	}
}

Database::~Database(){
	//delete[] arrayOfTrees;

    //for (int i = numberOfTrees-1; i > 0; i--){
    //    delete arrayOfTrees[i];
//    }
    delete[] (arrayOfTrees);
}

////////Public Functions

std::string** Database::query(int treeNumber, std::string* key){/////
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

    if (treeNumber > numberOfTrees)
        return NULL;

    std::string filename;
    if (arrayOfTrees[treeNumber]->find(*&key, &filename))
        return NULL;
    return readFile(&filename);

}


char Database::insert(int treeNumber, std::string* key, std::string** data, std::string* filename){/////
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
   if (treeNumber > numberOfTrees)
        return ARRAY_OUT_OF_BOUNDS;

    std::string randomString;

    if (!arrayOfTrees[treeNumber]->find(key, &randomString))
        return KEY_ALREADY_IN_USE;

    arrayOfTrees[treeNumber]->add(*&key, *&filename);

    if (buildFile(filename, *&data))
        return UNABLE_TO_CREATE_FILE;

    return updateTreeFile(treeNumber);
}

char Database::removeEntry(int treeNumber, std::string* key){/////
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
	char error = ARRAY_OUT_OF_BOUNDS;

	if (treeNumber < numberOfTrees){
		error = removeFile(treeNumber, *&key);
		if (error == NONE)
			return updateTreeFile(treeNumber);
	}

	return error;
}

char Database::edit(int treeNumber, std::string* key, std::string** data){/////
//
// Input Params :
//
//Output Params :
//
//  Description :
//
//      Returns :
//	

    if (treeNumber > numberOfTrees)
        return ARRAY_OUT_OF_BOUNDS;

    arrayOfTrees[treeNumber]->remove(*&key);

    arrayOfTrees[treeNumber]->add(*&key, *&data);

    return SUCCESS;
}

/////////Private Helper Functions

char Database::buildFile(std::string* filename, std::string** data){/////
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

    std::ofstream theFile ((storagePath+(*filename)).c_str());

    if (!theFile.is_open()){
        theFile.close();
        return FILE_ALREADY_EXISTS;
    }

    int* arraySizes;

    try{
        //create integer array from data[0]
        std::stringstream (data[0][0]) >> size;//size = std::stoi(data[0][0]);
        arraySizes = new int[size];

        theFile << data[0][0] << std::endl;

        for (int i = 1; i <= size; i++){
                std::stringstream (data[0][i]) >> ss;// = std::stoi(data[0][i]);
                (arraySizes[i-1]) = ss;
                theFile << data[0][i] << std::endl;
        }
    } catch (std::exception const & e){
        theFile.close();
        return CORRUPT_FILE;
    }

    for (int i= 0; i < size; i++){
        for (int k = 0; k < arraySizes[i]; k++){
            theFile << data[i+1][k] << std::endl;
        }
    }

    theFile.close();

    delete[] arraySizes;
    delete[] data;

    return SUCCESS;


// FILE SETUP:
//	[[array of integer values specifying size of itself, and number of other values to expect.],[values 1],...,[Values n]]
}

std::string** Database::readFile(std::string* filename){/////
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

    std::string** returnValue;
    std::ifstream theFile ((storagePath+(*filename)).c_str());

    if (!theFile.is_open())
        return NULL;

    std::string buffer;
    int tempValue, size;
    //Get the number of arrays to expect.
    if (!getline(theFile, buffer))
        return NULL;

    std::stringstream (buffer) >> size;

    int* arraySizes[size+1];
    returnValue = new std::string*;
    *returnValue = (new std::string[size+1]);
    //returnValue = new std::string*[size+1];
    returnValue[0] = new std::string[size+1];

    arraySizes[0] = &size;
    returnValue[0][0] = *(new std::string(buffer));
    //returnValue[0][0] = buffer;


    //find the size of the following arrays and create the placeholder
    for (int i = 1; i < size+1; i++){
        if (!getline(theFile, buffer))
            return NULL;

        std::stringstream (buffer) >> tempValue;
        arraySizes[i] = &tempValue;
        returnValue[i] = new std::string[tempValue];
        returnValue[0][i] = *(new std::string(buffer));
        //returnValue[0][i] = buffer;
    }

    //Populate the arrays
    for (int i = 1; i < size+1; i++){
        for (int k = 0; k < *arraySizes[i]; k++){
            if (!getline(theFile, buffer))
                return NULL;

            returnValue[i][k] = *(new std::string(buffer));
            //returnValue[i][k] = buffer;
        }
    }

    theFile.close();

    return returnValue;





}

char Database::removeFile(int treeNumber, std::string* key){/////
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
		return cleanUp(FILE_NOT_FOUND, &filename);


	arrayOfTrees[treeNumber]->remove(*&key);


	updateTreeFile(treeNumber);

	if (remove((storagePath+filename).c_str()))
		return cleanUp(FAILED_FILE_DELETION, &filename);

	return cleanUp(SUCCESS, &filename);
}

char Database::findFile(int treeNumber, std::string* key, std::string* filename){/////
//
// Input Params : treeNumber -> The tree to search in
//					key -> The key used to find a file
//
//Output Params : filename -> The name of the file requested
//
//  Description :
//
//      Returns : 0 if there were no errors
//
	if (arrayOfTrees[treeNumber]->find(key, filename) != NONE)
		return KEY_NOT_FOUND;


	return SUCCESS;
}

char Database::updateTreeFile(int treeNumber){/////
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

	std::ofstream myFile (((storagePath+treeFiles[treeNumber])+".TEMP").c_str());

    myFile << *(arrayOfTrees[treeNumber]);

	myFile.close();

	if (remove((storagePath+treeFiles[treeNumber]).c_str()))
		return FAILED_FILE_DELETION;

	if (rename((storagePath+treeFiles[treeNumber]+".TEMP").c_str(), (storagePath+treeFiles[treeNumber]).c_str()))
		return FAILED_TO_RENAME_FILE;

	return SUCCESS;

//COMMENT:: I'll have to repurpose my print function for this. 

}


	
char Database::populateTree(int treeNumber, std::string* filename){/////
//
// Input Params : treeNumber -> Access number for the tree you wish to populate.
//                                        filename -> the name of the file to use for population
//
//Output Params : None
//
// Description : initializes the Trees to state they were at during last runtime
//                                        by reading in the appropriate .db files.
//
// Returns : 0 if there were no errors
//                                        Otherwise can return:
//                                                CORRUPT_FILE
//        
        std::ifstream theFile ((storagePath+(*filename)).c_str());

        if (!theFile.is_open()){
                return CORRUPT_FILE;
        }

        std::string buffer;
        std::string* key;
        std::string* value;

        while(getline(theFile, buffer)){
                key = new std::string(buffer);
                getline(theFile, buffer);
                value = new std::string(buffer);
                arrayOfTrees[treeNumber]->add(key,value);
        }

        return SUCCESS;
}

char Database::cleanUp(char errorCode, std::string* filename){/////
	//delete(filename);
	return errorCode;
}

//int main(){
//	return 0;
//}
