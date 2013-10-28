#ifndef DATABASE_H
#define DATABASE_H
#include "BinaryTree.h"
#include <string>

enum LOCK {UNLOCKED, WRITE_LOCKED, READ_WRITE_LOCKED};

class Database{
public:
    Database();
    LOCK permission;
private:
    BinaryTree<std::string, std::string> adminTree;
    BinaryTree<std::string, std::string> instructorTree;
    BinaryTree<std::string, std::string> taTree;
    BinaryTree<std::string, std::string> courseTree;
    BinaryTree<std::string, std::string> taskTree;
};


#endif // DATABASE_H
