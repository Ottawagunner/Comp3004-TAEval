#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H
#include "User.h"
#include "Database.h"
class Instructor:User{
public:
    Instructor(std::string u,std::string n,std::string e, Database *database);
    short createTask();
    short editTask();
    short deleteTask();
    short viewTask();
    short viewTAs();
    short viewCourses();
    short writeReview();
private:
    Database* d;
    void search(std::string, std::string[]);
};


#endif // INSTRUCTOR_H
