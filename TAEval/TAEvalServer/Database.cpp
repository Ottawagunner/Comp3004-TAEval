#include "Database.h"

Database::Database(){
    //permission = UNLOCKED;
    adminTree = *(new typename BinaryTree<std::string, std::string>::BinaryTree());
    instructorTree = *(new typename BinaryTree<std::string, std::string>::BinaryTree());
    taTree = *(new typename BinaryTree<std::string, std::string>::BinaryTree());
    courseTree = *(new typename BinaryTree<std::string, std::string>::BinaryTree());
    taskTree = *(new typename BinaryTree<std::string, std::string>::BinaryTree());
}
