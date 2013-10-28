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
	template <class KEY_E, class VALUE_E>
	friend std::ostream& operator<<(std::ostream&, BinaryTree<KEY_E,VALUE_E> const&);

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

	VALUE* find(KEY*);

	Node getRoot() const;//WARNING::TEMPORARY DEBUGGING

private:
	void addLeftChild(KEY*, VALUE*, Node*);
	void addRightChild(KEY*, VALUE*, Node*);
	void fixDepth(Node*);

	void remove(Node*);
	Node* findNode(KEY*);

	void incrementSize();
	void decrementSize();
	void setSize(int);

	void balance();
	void balance(Node*);
	bool isBalanced() const;
	void ReorganizePatternOne(Node*);
	void ReorganizePatternTwo(Node*);
	void ReorganizePatternThree(Node*);
	void ReorganizePatternFour(Node*);

	Node* root;
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
	root = new Node();
	root->parent = ROOT;
	root->leftChild = LEAF;
	root->rightChild = LEAF;
	root->data = EMPTY;
	root->key = EMPTY;
	root->depth = 0;
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
		root->key = addKey;
		root->data = addValue;
		incrementSize();
	} else {
		Node* iterNode = root;
		while (iterNode != LEAF){
			if (*addKey <= *(iterNode->key)){
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
		balance();
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
	while (currNode != ROOT){
		if ((currNode->rightChild != LEAF) && currNode->depth < (currNode->rightChild->depth + 1)){
			currNode->depth = (currNode->rightChild->depth + 1);
		}
		if ((currNode->leftChild != LEAF) && currNode->depth < (currNode->leftChild->depth + 1)){
			currNode->depth = (currNode->leftChild->depth + 1);
		}
		currNode = currNode->parent;
	}	
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::remove(KEY* locatorKey){
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

	remove(findNode(locatorKey));
	decrementSize();
	balance();
}

template <class KEY, class VALUE>
VALUE* BinaryTree<KEY,VALUE>::find(KEY* locatorKey){
//
//     Function : find
//
// Input Params : The key to search with
//
//Output Params : The data the key is associated with
//
//  Description : Locates the first occurence of a given key
//
	return findNode(locatorKey)->data;
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
		return true;
	} else {
		return false;
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

/////////////////////Private Helper Functions

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::remove(Node* theNode){
//
//     Function : remove
//
// Input Params : The node to remove
//
//Output Params : None
//
//  Description : Finds and removes a specific Entry
//
// Comment: Maybe have a return value rather then node 
// 			to help indicate success or failure.
	Node* tempNode = new Node();
	if (size() == 1){
		delete(theNode);
		root = new Node();
	} else if (theNode->rightChild != LEAF){
	
		if (theNode->rightChild->leftChild != LEAF){//NOTE: WORKS
			//Replicate theNode
			tempNode->parent = theNode->parent;
			tempNode->leftChild = theNode->leftChild;
			tempNode->rightChild = theNode->rightChild;
			tempNode->depth = theNode->depth;
			tempNode->key = theNode->key;
			tempNode->data = theNode->data;

			//Change What theNode knows about
			theNode->parent = tempNode->rightChild;
			theNode->leftChild = tempNode->rightChild->leftChild->leftChild;
			theNode->rightChild = tempNode->rightChild->leftChild->rightChild;

			//Change where the parent points
			if (tempNode->parent->leftChild == theNode){
				tempNode->parent->leftChild = tempNode;
			} else if (tempNode->parent->rightChild == theNode){
				tempNode->parent->rightChild = tempNode;
			}

			//Change the parent of the Children to tempNode
			if (tempNode->leftChild != LEAF)
				tempNode->leftChild->parent = tempNode;
			if (tempNode->rightChild != LEAF)
				tempNode->rightChild->parent = tempNode;

			//Give tempNode the appropriate Data
			tempNode->key = tempNode->rightChild->leftChild->key;
			tempNode->data = tempNode->rightChild->leftChild->data;

			//Set the parent of theNodes new Children
			if (theNode->leftChild != LEAF){
				theNode->leftChild->parent = theNode;
			} 
			if (theNode->rightChild != LEAF){
				theNode->rightChild->parent = theNode;
			}

			delete(tempNode->rightChild->leftChild);

			tempNode->rightChild->leftChild = theNode;

			remove(theNode);
		} else {

			if (theNode->leftChild != LEAF){
				theNode->leftChild->parent = theNode->rightChild;
				theNode->rightChild->leftChild = theNode->leftChild;
				if (theNode->rightChild->rightChild != LEAF){
					if ((theNode->rightChild->leftChild->depth + 1) > (theNode->rightChild->rightChild->depth + 1)){
						theNode->rightChild->depth = (theNode->rightChild->leftChild->depth + 1);
					} else {
						theNode->rightChild->depth = (theNode->rightChild->rightChild->depth + 1);
					} 
				} else {
					theNode->rightChild->depth = (theNode->rightChild->leftChild->depth + 1);
				}	
			}

			theNode->rightChild->parent = theNode->parent;
			if (theNode->parent != ROOT){
				if (theNode->parent->leftChild == theNode){
					theNode->parent->leftChild = theNode->rightChild;
				} else {
					theNode->parent->rightChild = theNode->rightChild;
				}
			}

			fixDepth(theNode->rightChild);

			delete(theNode);

		}
	} else if(theNode->leftChild != LEAF){//Change
		if (theNode->leftChild->rightChild != LEAF){
			//Replicate theNode
			tempNode->parent = theNode->parent;
			tempNode->leftChild = theNode->leftChild;
			tempNode->rightChild = theNode->rightChild;
			tempNode->depth = theNode->depth;
			tempNode->key = theNode->key;
			tempNode->data = theNode->data;

			//Change What theNode knows about
			theNode->parent = tempNode->leftChild;
			theNode->leftChild = tempNode->leftChild->rightChild->leftChild;
			theNode->rightChild = tempNode->leftChild->rightChild->rightChild;

			//Change where the parent points
			if (tempNode->parent->leftChild == theNode){
				tempNode->parent->leftChild = tempNode;
			} else if (tempNode->parent->rightChild == theNode){
				tempNode->parent->rightChild = tempNode;
			}

			//Change the parent of the Children to tempNode
			if (tempNode->leftChild != LEAF)
				tempNode->leftChild->parent = tempNode;
			if (tempNode->rightChild != LEAF)
				tempNode->rightChild->parent = tempNode;

			//Give tempNode the appropriate Data
			tempNode->key = tempNode->leftChild->rightChild->key;
			tempNode->data = tempNode->leftChild->rightChild->data;

			//Set the parent of theNodes new Children
			if (theNode->leftChild != LEAF){
				theNode->leftChild->parent = theNode;
			} 
			if (theNode->rightChild != LEAF){
				theNode->rightChild->parent = theNode;
			}

			delete(tempNode->leftChild->rightChild);

			tempNode->leftChild->rightChild = theNode;

			remove(theNode);
		} else {

			theNode->leftChild->parent = theNode->parent;
			if (theNode->parent != ROOT){
				if (theNode->parent->leftChild == theNode){
					theNode->parent->leftChild = theNode->leftChild;
				} else {
					theNode->parent->rightChild = theNode->leftChild;
				}
			} else {
				root = theNode->leftChild;
			}
			fixDepth(theNode->leftChild);
			delete(theNode);
		}
	} else {
		if(theNode->parent->leftChild == theNode){
			theNode->parent->leftChild = LEAF;
			delete(theNode);
		} else{
			theNode->parent->rightChild = LEAF;
			delete(theNode);
		}
	}
}

template <class KEY, class VALUE>
typename BinaryTree<KEY,VALUE>::Node* BinaryTree<KEY,VALUE>::findNode(KEY* locatorKey){
//
//     Function : findNode
//
// Input Params : They key to use as a locator
//
//Output Params : The node corresponding to said key
//
//  Description : Finds the first Node which has the input key
//	
	Node* currNode = root;
	while (currNode != LEAF){
		if (*(currNode->key) > *(locatorKey)){
			currNode = currNode->leftChild;
		} else if (*(currNode->key) < *(locatorKey)){
			currNode = currNode->rightChild;
		} else {
			return currNode;
		}
	}

	//Found none. Return NULL
	return EMPTY;
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


//////Balance

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::balance(){
//
//     Function : balance
//
// Input Params : None
//
//Output Params : None
//
//  Description : Private Helper Function
//					Optimizes the Tree
//
	if (!isBalanced()){
		balance(root);
	}
}

template <class KEY, class VALUE>
bool BinaryTree<KEY,VALUE>::isBalanced() const{
//
//     Function : isBalanced
//
// Input Params : None
//
//Output Params : True if Balanced, False if not
//
//  Description : Private Helper Function
//					Checks to see if the Tree is balanced and Optimal
//
	int leftDepth, rightDepth, middleDepth;
	if (root->leftChild != LEAF)
		leftDepth = root->leftChild->depth;
	 else
		leftDepth = 0;

	if (root->rightChild != LEAF)
		rightDepth = root->rightChild->depth;
	else
		rightDepth = 0;

	middleDepth = root->depth;

	// (1<<middleDepth) is a left Shift being applied to one to calulate the 
	// Minimum number of nodes for that depth to exist assuming optimal distribution.
	if (numberOfNodes >= (1<<middleDepth) && (leftDepth == rightDepth))
		return true;
	else 
		return false;
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::balance(Node* theNode){
//
//     Function : balance
//
// Input Params : Node to start the balancing act at
//
//Output Params : None
//
//  Description : Private Helper Function
//					Actually Does the Optimization through recursive calls
//
	if (theNode->leftChild != LEAF && theNode->rightChild != LEAF){
		if (theNode->leftChild->depth == theNode->rightChild->depth){
			balance(theNode->leftChild);
			balance(theNode->rightChild);
		}
	} else if (theNode->leftChild != LEAF){
		if (theNode->leftChild->leftChild != LEAF || theNode->leftChild->rightChild != LEAF){
			if (theNode->leftChild->leftChild != LEAF && (theNode->leftChild->leftChild->leftChild != LEAF && theNode->leftChild->leftChild->rightChild != LEAF)){
				ReorganizePatternOne(theNode);
				if (theNode->parent != ROOT) balance(theNode->parent);
			} else if (theNode->leftChild->rightChild != LEAF && (theNode->leftChild->rightChild->leftChild != LEAF && theNode->leftChild->rightChild->rightChild != LEAF)){
				ReorganizePatternTwo(theNode);
				if (theNode->parent != ROOT) balance(theNode->parent);
			}
		}
	} else if (theNode->rightChild != LEAF){
		if (theNode->rightChild->leftChild != LEAF || theNode->rightChild->rightChild != LEAF){
			if (theNode->rightChild->leftChild != LEAF && (theNode->rightChild->leftChild->leftChild != LEAF && theNode->rightChild->leftChild->rightChild != LEAF)){
				ReorganizePatternFour(theNode);
				if (theNode->parent != ROOT) balance(theNode->parent);
			} else if (theNode->rightChild->rightChild != LEAF && (theNode->rightChild->rightChild->leftChild != LEAF && theNode->rightChild->rightChild->rightChild != LEAF)){
				ReorganizePatternThree(theNode);
				if (theNode->parent != ROOT) balance(theNode->parent);
			}
		}
	}
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::ReorganizePatternOne(Node* theNode){
	//Reorganize Pattern 1
	// Given a Tree with the Order (50,25,10,5,15,30,55) which has 4 levels
	// This rearranges it into (25,10,5,15,50,30,55) which has 3 levels
	// Order is chosen traveling left down the tree and picking
	// Nodes the first time you come across them. 
	Node* tempNode = theNode->leftChild;
	tempNode->parent = theNode->parent;

	//Relink the 'root' parent/child relationship
	if (theNode->parent != ROOT && theNode->parent->leftChild == theNode){
		theNode->parent->leftChild = tempNode;
	} else if (theNode->parent != ROOT){
		theNode->parent->rightChild = tempNode;
	}

	//Relink the leftChild parent/child relationship
	theNode->leftChild = tempNode->rightChild;
	tempNode->rightChild->parent = theNode;

	//Relink the rightChild parent/child relationship
	theNode->parent = tempNode;
	tempNode->rightChild = theNode;

	if (theNode->rightChild != LEAF){
		fixDepth(theNode->rightChild);
	} else {
		theNode->depth = 0;
		fixDepth(theNode);
	}
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::ReorganizePatternTwo(Node* theNode){
	//Reorganize Pattern 2
	//Given a Tree with the Order (50,25,10,40,30,45,55) which has 4 levels
	//This rearranges it into (40,25,10,30,50,45,55) which has 3 levels
	//Order is chosen the same as in Pattern 1
	Node* tempNode = theNode->leftChild->rightChild;
	tempNode->parent = theNode->parent;
	
	if (theNode->parent != ROOT){
		if (theNode->parent->leftChild == theNode){
			theNode->parent->leftChild = tempNode;
		} else {
			theNode->parent->rightChild = tempNode;
		}
	}

	theNode->leftChild->parent = tempNode;
	theNode->leftChild->rightChild = tempNode->leftChild;

	if (tempNode->leftChild != LEAF){
		tempNode->leftChild->parent = theNode->leftChild;
	}

	tempNode->leftChild = theNode->leftChild;
	theNode->parent = tempNode;
	theNode->leftChild = tempNode->rightChild;
	tempNode->rightChild->parent = theNode;
	tempNode->rightChild = theNode;

	if (theNode->rightChild != LEAF) fixDepth(theNode->rightChild);
	else if (theNode->leftChild != LEAF) fixDepth(theNode->leftChild);
	else{
		theNode->depth = 0;
		fixDepth(theNode);
	}
	
	if (tempNode->leftChild->leftChild != LEAF) fixDepth(tempNode->leftChild->leftChild);
	else if (tempNode->leftChild->rightChild != LEAF) fixDepth(tempNode->rightChild->leftChild);
	else{
		tempNode->leftChild->depth = 0;
		fixDepth(tempNode->leftChild);
	}		
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::ReorganizePatternThree(Node* theNode){
	//Reorganize Pattern 3
	//Given a Tree with the Order (50,25,75,60,100,80,125) which has 4 levels
	//This rearranges it into (75,50,25,60,100,80,125) which has 3 levels
	//Order is chosen the same as in Pattern 1
	Node* tempNode = theNode->rightChild;
	tempNode->parent = theNode->parent;

	if (theNode->parent != ROOT && theNode->parent->leftChild == theNode){
		theNode->parent->leftChild = tempNode;
	} else if (theNode->parent != ROOT){
		theNode->parent->rightChild = tempNode;
	}

	theNode->rightChild = tempNode->leftChild;
	tempNode->leftChild->parent = theNode;

	theNode->parent = tempNode;
	tempNode->leftChild = theNode;

	if (theNode->leftChild != LEAF){
		fixDepth(theNode->leftChild);
	} else {
		theNode->depth = 0;
		fixDepth(theNode);
	}
}

template <class KEY, class VALUE>
void BinaryTree<KEY,VALUE>::ReorganizePatternFour(Node* theNode){
	//Reorganize Pattern 4
	//Given a Tree with the Order (50,25,100,75,60,80,125) which has 4 levels
	//This rearranges it into (75,50,25,60,100,80,125) which has 3 levels
	//Order is chosen the same as in Pattern 1	
	Node* tempNode = theNode->rightChild->leftChild;
	tempNode->parent = theNode->parent;
	
	if (theNode->parent != ROOT){
		if (theNode->parent->leftChild == theNode){
			theNode->parent->leftChild = tempNode;
		} else {
			theNode->parent->rightChild = tempNode;
		}
	}

	theNode->rightChild->parent = tempNode;
	theNode->rightChild->leftChild = tempNode->leftChild;
	tempNode->leftChild->parent = theNode->rightChild;
	tempNode->leftChild = theNode->rightChild;
	theNode->parent = tempNode;
	theNode->rightChild = tempNode->rightChild;
	tempNode->rightChild->parent = theNode;
	tempNode->rightChild = theNode;

	if (theNode->rightChild != LEAF) fixDepth(theNode->rightChild);
	else if (theNode->leftChild != LEAF) fixDepth(theNode->leftChild);
	else{
		theNode->depth = 0;
		fixDepth(theNode);
	}
	
	if (tempNode->leftChild->leftChild != LEAF) fixDepth(tempNode->leftChild->leftChild);
	else if (tempNode->leftChild->rightChild != LEAF) fixDepth(tempNode->rightChild->leftChild);
	else{
		tempNode->leftChild->depth = 0;
		fixDepth(tempNode->leftChild);
	}
}


//WARNING::TEMPORARY FUNCTION
template <class KEY, class VALUE>
typename BinaryTree<KEY,VALUE>::Node BinaryTree<KEY,VALUE>::getRoot() const{
	return *root;
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

//////////////Overloaded Functions

template <class KEY, class VALUE>
std::ostream& operator<<(std::ostream& out, BinaryTree<KEY,VALUE> const& rhs){
	if ( !(rhs.isEmpty()) ){
		typename BinaryTree<KEY,VALUE>::Node *tempNode;
		typename BinaryTree<KEY,VALUE>::Node* backupNode;
		tempNode = (rhs.root);
		int count = 0;
		out << "(";
		do{
			out << *(tempNode->getData()) << ", ";
			count+=1;
			if (tempNode->getLeftChild() != LEAF){
				tempNode = tempNode->getLeftChild();
			} else if (tempNode->getRightChild() != LEAF){
				tempNode = tempNode->getRightChild();
			} else {
				backupNode = tempNode;
				do {
					if(tempNode->getParent() != ROOT && tempNode->getParent()->getRightChild() != LEAF){
						backupNode = tempNode;
						tempNode = tempNode->getParent();
					} else if (tempNode->getParent() == ROOT){
						backupNode = rhs.root;
					} else {
						tempNode = tempNode->getParent();
						backupNode = tempNode->getRightChild();
					}
				} while (tempNode->getRightChild() == backupNode);
				if (tempNode->getRightChild() != LEAF)
					tempNode = tempNode->getRightChild();
			}
		} while (count != rhs.size());
		out <<")";
		return out;
	}
	out <<"( EMPTY )";
	return out;

}

#endif