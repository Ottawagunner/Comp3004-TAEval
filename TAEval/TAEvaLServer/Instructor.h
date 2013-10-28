#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H
#include "User.h"
class Instructor:User{
public:
    Instructor(std::string u,std::string n,std::string e);
    void save();
    void write();
    short createTask();
    short editTask();
    short deleteTask();
    short viewTask();
    short viewTAs();
    short viewCourses();
    short writeReview();
};


#endif // INSTRUCTOR_H
