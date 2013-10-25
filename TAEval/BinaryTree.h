/*
	Binary Tree-Map, Utilizing a (Key, Value) Pairing
	to allow for more complex data to be stored


	Author: Draymire
	Date: 24/10/13 23:13


	NOTE: remember to rename to BinaryTree.h as contains 
	header specific data. Will lose marks and is bad form 
	to keep it as a .cpp

	NOTE: Search WARNING to find TEMPORARY DEBUGGING 
		functions and data. Remove for final product.
*/


#define ROOT  NULL
#define LEAF  NULL
#define EMPTY NULL


#ifndef BinaryTree_H
#define BinaryTree_H

#include <iostream>
#include <string>




template <class KEY, class VALUE>
class BinaryTree
{

	//template <class E> //for overloading later

	class Node
	{
		friend class BinaryTree;

	public:
		void setData(VALUE*);
		void setKey(KEY*);
		void setParent(Node*);
		void setLeftChild(Node*);
		void setRightChild(Node*);
		void setDepth(int);

		VALUE* getData() const;
		KEY* getKey() const;
		Node* getParent() const;
		Node* getLeftChild() const;
		Node* getRightChild() const;
		int getDepth() const;

	private:
		Node* parent;
		Node* leftChild;
		Node* rightChild;
		
		int depth;

		VALUE* data;
		KEY* key;

	};

public:
	BinaryTree();

	~BinaryTree();

	void add(KEY*, VALUE*);
	void remove(KEY*);

	bool isEmpty() const;

	int size() const;

	Node getRoot() const;//WARNING::TEMPORARY DEBUGGING

private:
	void incrementSize();
	void decrementSize();
	void setSize(int);

	Node root;
	int numberOfNodes;
};



template <class KEY, class VALUE>
BinaryTree<KEY,VALUE>::BinaryTree() {
//
//     Function : 
//
// Input Params : 
//
//Output Params : 
//
//  Description : 
//	
	//setSize(0);
	root.parent = ROOT;
	root.leftChild = LEAF;
	root.rightChild = LEAF;
	root.data = EMPTY;
	root.key = EMPTY;
	root.depth = 0;
}

template <class KEY, class VALUE>
BinaryTree<KEY,VALUE>::~BinaryTree(){
//
//     Function : 
//
// Input Params : 
//
//Output Params : 
//
//  Description : 
//
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::add(KEY*, VALUE*){
//
//     Function : 
//
// Input Params : 
//
//Output Params : 
//
//  Description : 
//
	std::cout << "IMPLEMENT BINARY TREE ADDITION" << std::endl;
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::remove(KEY*){
//
//     Function : 
//
// Input Params : 
//
//Output Params : 
//
//  Description : 
//
	std::cout << "KEY based removal" << std::endl;
}

template <class KEY, class VALUE>
bool BinaryTree<KEY,VALUE>::isEmpty() const{
//
//     Function : 
//
// Input Params : 
//
//Output Params : 
//
//  Description : 
//
	std::cout << "Is this a waste of space" << std::endl;
}

template <class KEY, class VALUE>
int BinaryTree<KEY,VALUE>::size() const{
//
//     Function : Size
//
// Input Params : None
//
//Output Params : Integer return value
//
//  Description : Returns the number of nodes currently in the tree
//
	return numberOfNodes;
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::incrementSize(){
//
//     Function : incrementSize
//
// Input Params : None
//
//Output Params : None
//
//  Description : Private Helper Function
//					Increases the Node Number count
//
	numberOfNodes+=1;
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::decrementSize(){
//
//     Function : decrementSize
//
// Input Params : None
//
//Output Params : None
//
//  Description : Private Helper Function
//					Decreases the Node Number Count
//
	numberOfNodes-=1;
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::setSize(int changeValue){
//
//     Function : setSize
//
// Input Params : The Value you wish Size to become
//
//Output Params : None
//
//  Description : Private Helper Function
//					Changes the Node Number Count to the 
//					Desired Value
//
//Comment: Contemplate passing a reference rather then 
//			an actual value.
	numberOfNodes = changeValue;
}
//WARNING::TEMPORARY FUNCTION
template <class KEY, class VALUE>
typename BinaryTree<KEY,VALUE>::Node BinaryTree<KEY,VALUE>::getRoot() const{
	return root;
}



///////////////////////NODE Functions

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::Node::setData(VALUE*){
//
//     Function : 
//
// Input Params : 
//
//Output Params : 
//
//  Description : 
//
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::Node::setKey(KEY*){
//
//     Function : 
//
// Input Params : 
//
//Output Params : 
//
//  Description : 
//
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::Node::setParent(Node*){
//
//     Function : 
//
// Input Params : 
//
//Output Params : 
//
//  Description : 
//
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::Node::setLeftChild(Node*){
//
//     Function : 
//
// Input Params : 
//
//Output Params : 
//
//  Description : 
//
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::Node::setRightChild(Node*){
//
//     Function : 
//
// Input Params : 
//
//Output Params : 
//
//  Description : 
//
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::Node::setDepth(int){
//
//     Function : 
//
// Input Params : 
//
//Output Params : 
//
//  Description : 
//
}

template <class KEY, class VALUE>
VALUE* BinaryTree<KEY,VALUE>::Node::getData() const{
//
//     Function : 
//
// Input Params : 
//
//Output Params : 
//
//  Description : 
//
}

template <class KEY, class VALUE>
KEY* BinaryTree<KEY,VALUE>::Node::getKey() const{
//
//     Function : 
//
// Input Params : 
//
//Output Params : 
//
//  Description : 
//
}

template <class KEY, class VALUE>
typename BinaryTree<KEY,VALUE>::Node* BinaryTree<KEY,VALUE>::Node::getParent() const{
//
//     Function : 
//
// Input Params : 
//
//Output Params : 
//
//  Description : 
//
}

template <class KEY, class VALUE>
typename BinaryTree<KEY,VALUE>::Node* BinaryTree<KEY,VALUE>::Node::getLeftChild() const{
//
//     Function : 
//
// Input Params : 
//
//Output Params : 
//
//  Description : 
//
}

template <class KEY, class VALUE>
typename BinaryTree<KEY,VALUE>::Node* BinaryTree<KEY,VALUE>::Node::getRightChild() const{
//
//     Function : 
//
// Input Params : 
//
//Output Params : 
//
//  Description : 
//
}

template <class KEY, class VALUE>
int BinaryTree<KEY,VALUE>::Node::getDepth() const{
//
//     Function : getDepth
//
// Input Params : None
//
//Output Params : Returns the Depth
//
//  Description : A controlled method of accessing the Depth 
//					Variable
//
	return depth;
}

int main()
{
	BinaryTree<int, int> test;

	std::cout << test.getRoot().getDepth() << std::endl;

	return 0;
}


#endif