#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H
#include "User.h"
#include "Database.h"
#include <cstdlib>
class Instructor:User{
public:
    Instructor(Database *database);
    void manageReq(std::string, std::string, std::string*);
    void search(std::string, std::string[]);
private:
    Database* d;
    short createTask(std::string, std::string *);
    short editTask(std::string, std::string *);
    short deleteTask(std::string, std::string *);
    short viewTask(std::string, std::string *);
    short viewTAs(std::string, std::string *);
    short viewCourses(std::string, std::string *);
    short writeReview(std::string, std::string *);
    std::string reqType[10];
};


#endif // INSTRUCTOR_H
