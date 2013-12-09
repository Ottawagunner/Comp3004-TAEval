#include "DatabaseInterface.h"

#include <sstream>
#include <string>
#include <iostream> //DEBUG

//////////Define the Request Types
#define LOGIN				"LOGIN"

#define VIEW_TA 			"VIEW-TA"//Done

#define VIEW_TASK 			"VIEW-TASK"//Done
#define CREATE_TASK			"CREATE-TASK"
#define EDIT_TASK			"EDIT-TASK"
#define DELETE_TASK			"DELETE-TASK"

#define VIEW_TASK_INFO		"VIEW-TASK-INFO"//Done
#define VIEW_EVAL_INFO 		"VIEW-EVAL-INFO"//Done
#define CREATE_EVALUATION	"CREATE-EVAL"
#define EDIT_EVALUATION		"EDIT-EVAL"

///////////Define the User Types 
#define INSTRUCTOR_TYPE "i"
#define TA_TYPE			"t"

///////////Define Place Holder Data
#define RATING_PLACEHOLDER	"-1"
#define REVIEW_PLACEHOLDER 	"No Written Review"


DatabaseInterface::DatabaseInterface(int arg1, std::string arg2, std::string* arg3) : db(arg1, arg2, arg3){
}

DatabaseInterface::~DatabaseInterface(){
	//delete[] db;
};

char DatabaseInterface::handleRequest(std::string** requestArr, std::string** returnArr){

	*returnArr = NULL;
	
	std::string* baseArr = new std::string[3];
	std::string* dataArr;

	adaptRequest(requestArr, &baseArr, &dataArr);

	//handle the request

    if(baseArr[2] == LOGIN){
		if(!loginRequest(&(baseArr[1]), &(baseArr[0]), returnArr)){
			*returnArr = new std::string[3];
			(*returnArr)[0] = ("1");
			(*returnArr)[1] = ("1");
			(*returnArr)[2] = ("FAILURE");
		}

	}else if(baseArr[2] == CREATE_EVALUATION || baseArr[2] == CREATE_TASK){
		if(!createRequest( &(baseArr[1]), &(baseArr[0]), &(baseArr[2]), &dataArr )){
			*returnArr = new std::string[3]; 
			(*returnArr)[0] = ("1");
			(*returnArr)[1] = ("1");
			(*returnArr)[2] = ("FAILURE");
		}

	}else if(baseArr[2] == EDIT_EVALUATION || baseArr[2] == EDIT_TASK){
		if(!editRequest( &(baseArr[1]), &dataArr)){
			*returnArr = new std::string[3]; 
			(*returnArr)[0] = ("1");
			(*returnArr)[1] = ("1");
			(*returnArr)[2] = ("FAILURE");
		}

	}else if(baseArr[2] == DELETE_TASK){
		if(!removeRequest(&(baseArr[0]), &(dataArr)[1])){
			*returnArr = new std::string[3]; 
			(*returnArr)[0] = ("1");
			(*returnArr)[1] = ("1");
			(*returnArr)[2] = ("FAILURE");
		}

	}else{
		if(!viewRequest( &(baseArr[1]), &(baseArr[0]), &(baseArr[2]), &(dataArr)[1], returnArr)){
			*returnArr = new std::string[3]; 
			(*returnArr)[0] = ("1");
			(*returnArr)[1] = ("1");
			(*returnArr)[2] = ("FAILURE");
		}
	}

	

	//Cleanup
	delete[] baseArr;
	if(dataArr != NULL)
		delete[] dataArr;

	return 0;
}

bool DatabaseInterface::loginRequest(std::string* userType, std::string* userName, std::string** dataArr){
    std::cout << "I like to eat rabbits" << std::endl;
	if(*userType == INSTRUCTOR_TYPE){
        if(db.find(0, userName, dataArr)) return false;
        else return true;
	}
	if(*userType == TA_TYPE){
        if(db.find(1, userName, dataArr)) return false;
        else return true;
	}
}

bool DatabaseInterface::createRequest(std::string* userType, std::string* userName, std::string* requestType, std::string** dataArr){

	if(*requestType == CREATE_TASK){

		if(*userType == INSTRUCTOR_TYPE){

			std::string* arr;
			if(db.find(1, userName, &arr))
				return false;

			int num;
			int sum;
			std::stringstream( arr[1] ) >> num;

			sum = num + 2;

			std::string* newArr = new std::string[sum+1];

			newArr[0] = arr[0];

			std::stringstream convert;
			convert << (num+1);

			newArr[1] = convert.str();

			for(int i = 0; i < num; i++){
				newArr[i+2] = arr[i+2];
			}

			newArr[sum] = (*dataArr)[2];

			db.edit(1, userName, &newArr);

			delete[] arr;
			delete[] newArr;

			arr = new std::string[7];

			arr[0] = "1";
			arr[1] = "5";
			arr[5] = RATING_PLACEHOLDER;
			arr[6] = REVIEW_PLACEHOLDER;

			for(int i = 0; i < 3; i++){
				arr[2+i] = (*dataArr)[1+i];
			}

			std::string key = (*dataArr)[2];
			std::string filename = "Task/"+(*dataArr)[2]+".txt";

			db.add(3, &key, &filename, &arr);

			delete[] arr;
		}

	} else if(*requestType == CREATE_EVALUATION){

		std::string* arr;
		std::string key = (*dataArr)[3];
		if(db.find(3, &key, &arr))
			return false;

		arr[5] = (*dataArr)[1];
		arr[6] = (*dataArr)[2];

		db.edit(3, &key, &arr);

		delete[] arr;
	}
	return true;
}

bool DatabaseInterface::editRequest(std::string* userType, std::string** dataArr){

	std::string key = (*dataArr)[1];
	std::string* arr;
	if(db.find(3, &key, &arr))
		return false;
	arr[4] = (*dataArr)[2];
	db.edit(3, &key, &arr);

	delete[] arr;
	return true;
}

bool DatabaseInterface::viewRequest(std::string* userType, std::string* userName, std::string* requestType, std::string* id, std::string** dataArr){
	if(*requestType == VIEW_TA)
		return viewTaRequest(userType, id, dataArr);
	else if(*requestType == VIEW_TASK)
		return viewTaskRequest(userType, userName, id, dataArr);
	else if(*requestType == VIEW_TASK_INFO)
		return viewTaskInfoRequest(id, dataArr);
	else if(*requestType == VIEW_EVAL_INFO)
		return viewEvalInfoRequest(id, dataArr);
}

bool DatabaseInterface::removeRequest(std::string* taKey, std::string* taskKey){

	std::string* arr;
	if(db.find(1, taKey, &arr))
		return false;

	int num;
	std::stringstream(arr[1]) >> num;

	num-=1;

	std::string* newArr = new std::string[num+2];

	int count = 0;

	for(int i = 0; i < (num+1); i++){
		if( *taskKey != arr[i+2]){
			newArr[2+count] == arr[i+2];
			count+=1;
		}
	}

	newArr[0] = "1";

	delete[] arr;

	std::stringstream convert;
	convert << num;
	newArr[1] = convert.str();

	db.edit(1, taKey, &newArr);

	delete[] newArr;

	db.remove(3, taskKey);
	return true;
}



void DatabaseInterface::adaptRequest(std::string** requestArr, std::string** baseArr, std::string** dataArr){
	int requestArrSize;
	int additionalInfoSize;

	int lenOfArr;

	(*baseArr)[0] = (*requestArr)[1];
	(*baseArr)[1] = (*requestArr)[2];
	(*baseArr)[2] = (*requestArr)[3];

	std::string buffer = (*requestArr)[0];

	std::stringstream(buffer) >> requestArrSize;

	lenOfArr = requestArrSize - 3;

	if(requestArrSize > 3){
		
		(*dataArr) = new std::string[lenOfArr+1];

		std::stringstream convert;
		convert << lenOfArr;
		(*dataArr)[0] = convert.str();

		for(int i = 0; i < lenOfArr; i++){
			(*dataArr)[1+i] = (*requestArr)[4+i];
		}
	} else {
		(*dataArr) = NULL;
	}
}

bool DatabaseInterface::viewTaRequest(std::string* userType, std::string* id, std::string** dataArr){
	if(*userType == INSTRUCTOR_TYPE){
		if(db.find(2, id, dataArr))
			return false;
	}
	return true;
}

bool DatabaseInterface::viewTaskRequest(std::string* userType, std::string* userName, std::string* id, std::string** dataArr){
	if(*userType == INSTRUCTOR_TYPE){

		std::string* arr;
		if(db.find(1, id, &arr))
			return false;

		int lenOfArr;
		std::stringstream(arr[1]) >> lenOfArr;

		*dataArr = new std::string[lenOfArr];

		std::string* tempArr;

		int count = 1;
		for(int i = 0; i < lenOfArr; i++){
 			if(db.find(3, &(arr[2+i]), &tempArr))
 				return false;
			if(tempArr[2] == *userName){
				(*dataArr)[count] = arr[2+i];
				count+=1;
			}
			delete[] tempArr;
		}

		std::stringstream convert;
		convert << (count-1);
		(*dataArr)[0] = convert.str();

		delete[] arr;		
	} 
	return true;
}

bool DatabaseInterface::viewTaskInfoRequest(std::string* id, std::string** dataArr){
	std::string* arr;
	if(db.find(3, id, &arr))
		return false;

	(*dataArr) = new std::string[4];
	(*dataArr)[0] = "1";
	(*dataArr)[1] = "2";
	(*dataArr)[2] = arr[3];
	(*dataArr)[3] = arr[4];

	delete[] arr;
	return true;
}

bool DatabaseInterface::viewEvalInfoRequest(std::string* id, std::string** dataArr){
	std::string* arr;
	if(db.find(3, id, &arr))
		return false;

	(*dataArr) = new std::string[4];
	(*dataArr)[0] = "1";
	(*dataArr)[1] = "2";
	(*dataArr)[2] = arr[5];
	(*dataArr)[3] = arr[6];

	delete[] arr;
	return true;
}
