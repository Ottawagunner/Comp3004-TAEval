#ifndef TASK_H
#define TASK_H
#include <evaluation.h>
#include <string>

class task
{
public:
    task();
    Evaluation givenEvaluation;
    std::string Discripion;
    bool Completed;
};

#endif // TASK_H
