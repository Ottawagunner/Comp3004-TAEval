/*
	Binary Tree-Map, Utilizing a (Key, Value) Pairing
	to allow for more complex data to be stored


	Author: Draymire
	Date: 25/10/13 18:25


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
	void addLeftChild(KEY*, VALUE*, Node*);
	void addRightChild(KEY*, VALUE*, Node*);
	void fixDepth(Node*);

	void incrementSize();
	void decrementSize();
	void setSize(int);

	Node root;
	int numberOfNodes;
};



template <class KEY, class VALUE>
BinaryTree<KEY,VALUE>::BinaryTree() {
//
//     Function : Constructor
//
// Input Params : None
//
//Output Params : None
//
//  Description : Initializes the BinaryTree
//	
	setSize(0);
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
//     Function : Destructor
//
// Input Params : None
//
//Output Params : None
//
//  Description : Destroys the BinaryTree
//
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::add(KEY* addKey, VALUE* addValue){
//
//     Function : add
//
// Input Params : The key and value to be added
//
//Output Params : None
//
//  Description : Finds the location to add the New Node
//					And then adds it.
//
	if (isEmpty()){
		root.key = addKey;
		root.value = addValue;
	} else {
		Node* iterNode = &root;
		while (iterNode != LEAF){
			if (addKey <= iterNode->key){
				if (iterNode->leftChild == LEAF){
					addLeftChild(addKey, addValue, iterNode);
					iterNode = LEAF;
				} else {
					iterNode = iterNode->leftChild;
				}
			} else {
				if (iterNode->rightChild == LEAF){
					addRightChild(addKey, addValue, iterNode);
					iterNode = LEAF;
				} else {
					iterNode = iterNode->rightChild;
				}
			}
		}
	}
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::addLeftChild(KEY* addKey, VALUE* addValue, Node* parentNode){
//
//     Function : addLeftChild
//
// Input Params : The key and value to be added along with 
//					The parent to add it too.
//
//Output Params : None
//
//  Description : Adds a new node to the BinaryTree at
//					The chosen location.
//
	Node* tempNode = new Node();
	tempNode->parent = parentNode;
	tempNode->key = addKey;
	tempNode->data = addValue;
	tempNode->leftChild = LEAF;
	tempNode->rightChild = LEAF;
	parentNode->leftChild = tempNode;
	fixDepth(tempNode);
	incrementSize();
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::addRightChild(KEY* addKey, VALUE* addValue, Node* parentNode){
//
//     Function : addRightChild
//
// Input Params : The key and value to be added along with 
//					The parent to add it too.
//
//Output Params : None
//
//  Description : Adds a new node to the BinaryTree at
//					The chosen location.
//
	Node* tempNode = new Node();
	tempNode->parent = parentNode;
	tempNode->key = addKey;
	tempNode->data = addValue;
	tempNode->leftChild = LEAF;
	tempNode->rightChild = LEAF;
	parentNode->rightChild = tempNode;
	fixDepth(tempNode);
	incrementSize();
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::fixDepth(Node* leafNode){
//
//     Function : fixDepth
//
// Input Params : The Node to start at
//
//Output Params : Node
//
//  Description : Checks Depth Values and fixes incorrect ones
//
	Node* currNode = leafNode->parent;
	Node* prevNode = leafNode;
	while (currNode != ROOT){
		if (currNode->depth < (prevNode->depth + 1)){
			currNode->depth = (prevNode->depth + 1);
		}
		prevNode = currNode;
		currNode = currNode->parent;
	}	
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::remove(KEY*){
//
//     Function : remove
//
// Input Params : The key to find and remove
//
//Output Params : None
//
//  Description : Finds and removes a specific Entry
//
// Comment: Maybe have a return value rather then node 
// 			to help indicate success or failure.
	std::cout << "KEY based removal" << std::endl;
}

template <class KEY, class VALUE>
bool BinaryTree<KEY,VALUE>::isEmpty() const{
//
//     Function : isEmpty
//
// Input Params : None
//
//Output Params : True if Empty, False if not
//
//  Description : Check if the Tree is empty or not.
//
	if (!size()){
		std::cout << "empty" << std::endl;
	} else {
		std::cout << "got something" << std::endl;
	}
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
void BinaryTree<KEY,VALUE>::setSize(int input){
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
	numberOfNodes = input;
}
//WARNING::TEMPORARY FUNCTION
template <class KEY, class VALUE>
typename BinaryTree<KEY,VALUE>::Node BinaryTree<KEY,VALUE>::getRoot() const{
	return root;
}



///////////////////////NODE Functions

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::Node::setData(VALUE* input){
//
//     Function : setData
//
// Input Params : Pointer to the Data
//
//Output Params : None
//
//  Description : sets the nodes data value to the input
//

	data = input;
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::Node::setKey(KEY* input){
//
//     Function : setKey
//
// Input Params : Pointer to the Key
//
//Output Params : None
//
//  Description : Sets the nodes key to the input
//
	key = input;
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::Node::setParent(Node* input){
//
//     Function : setParent
//
// Input Params : Pointer to a node
//
//Output Params : None
//
//  Description : Sets the Parent Node to the input
//
	parent = input;
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::Node::setLeftChild(Node* input){
//
//     Function : setLeftChild
//
// Input Params : Pointer to a node
//
//Output Params : None
//
//  Description : Sets the Left Child Node to the input 
//
	leftChild = input;
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::Node::setRightChild(Node* input){
//
//     Function : setRightChild
//
// Input Params : Pointer to a node
//
//Output Params : None
//
//  Description : Sets the Right Child Node to the input
//
	rightChild = input;
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::Node::setDepth(int input){
//
//     Function : setDepth
//
// Input Params : value the depth should be
//
//Output Params : None
//
//  Description : Sets the depth of the node to the input
//
	depth = input;
}

template <class KEY, class VALUE>
VALUE* BinaryTree<KEY,VALUE>::Node::getData() const{
//
//     Function : getData 
//
// Input Params : None
//
//Output Params : Returns a Pointer to the data.
//
	return data;
}

template <class KEY, class VALUE>
KEY* BinaryTree<KEY,VALUE>::Node::getKey() const{
//
//     Function : getKey
//
// Input Params : None
//
//Output Params : Returns a Pointer to the data
//
	return key;
}

template <class KEY, class VALUE>
typename BinaryTree<KEY,VALUE>::Node* BinaryTree<KEY,VALUE>::Node::getParent() const{
//
//     Function : getParent
//
// Input Params : None
//
//Output Params : Returns a Pointer to the Parent Node
//
	return parent;
}

template <class KEY, class VALUE>
typename BinaryTree<KEY,VALUE>::Node* BinaryTree<KEY,VALUE>::Node::getLeftChild() const{
//
//     Function : getLeftChild
//
// Input Params : None
//
//Output Params : Returns a Pointer to the Left Child Node
//
	return leftChild;
}

template <class KEY, class VALUE>
typename BinaryTree<KEY,VALUE>::Node* BinaryTree<KEY,VALUE>::Node::getRightChild() const{
//
//     Function : getRightChild
//
// Input Params : None
//
//Output Params : Returns a Pointer to the Right Child Node
//
	return rightChild;
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
	return depth;
}



//WARNING: TEMPORARY FUNCTION
int main()
{
	BinaryTree<int, int> test;

	test.isEmpty();// << std::endl;

	return 0;
}


#endif