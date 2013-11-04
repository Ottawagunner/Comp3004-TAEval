#include "Database.h"

Database* construct(int size, std::string path, std::string* fileList){
	

	return new Database(size, path, fileList);
}

int main(){

	std::string fileList[4];
	fileList[0] = "Admin.db";
	fileList[1] = "Instructor.db";
	fileList[2] = "TA.db";
	fileList[3] = "Course.db";

	std::string path = "./Storage/";

	Database* db = construct(4, path, fileList);

	std::string instructor = "Glynda Goodwitch";
	std::string** returnValue;
	returnValue = db->query(1, &instructor);

	std::cout << "idk: " << returnValue[0][0] << std::endl;

	int temp, size;
	std::string tempString;
	tempString = returnValue[0][0];
	std::stringstream (tempString) >> size;

	for (int i = 1; i < size+1; i++){
		tempString = returnValue[0][i];
		std::stringstream (tempString) >> temp;
		for (int k = 0; k < temp; k++){
			std::cout << returnValue[i][k] << std::endl;
		}
	}

	std::string** list;
	list = new std::string*[3];
	std::string listA[3] = {"2","1","1"};
	std::string listB[1] = {"Course/MNSTR101.db"};
	std::string listC[1] = {"TA/Weiss.db"};
	list[0] = listA;
	list[1] = listB;
	list[2] = listC;

	std::string newInst = "Takumi Fujiwara";
	std::string newPath = "Instructor/Takumi.db";

	db->insert(1, &newInst, *&list, &newPath);

	delete(db);

	return 0;
}

