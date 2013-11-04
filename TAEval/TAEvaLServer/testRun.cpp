#include "Database.h"

int main(){

	std::string fileList[4];
	fileList[0] = "Admin.db";
	fileList[1] = "Instructor.db";
	fileList[2] = "TA.db";
	fileList[3] = "Course.db";

	std::string path = "./Storage/";
	Database db = Database(4,path, fileList);

	std::string** returnValue;
	std::string Glynda = "Glynda Goodwitch";
	char error = db.query(1, &Glynda, returnValue);
	std::cout << "ERROR: "<< error << std::endl;
	//if (error)

	int temp, temp2;
	std::stringstream (returnValue[0][0]) >> temp;
	std::cout << "[["<<returnValue[0][0]<<", "<<returnValue[0][1]<<"] "<<std::endl;
	for(int i = 1; i <= temp; i++){
		std::stringstream (returnValue[0][i]) >> temp2;
		std::cout << ", [";
		for (int k = 0; k < temp2; k++){
			std::cout << returnValue[i][k] << ", ";
		}
		std::cout << "]" << std::endl;
	}
	std::cout << "]" << std::endl;
	//delete(db);



	return 0;
};