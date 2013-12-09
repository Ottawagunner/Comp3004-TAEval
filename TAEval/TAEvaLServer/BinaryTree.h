#ifndef DRAYMIRE_BINARYTREE
#define DRAYMIRE_BINARYTREE

#include <string>
#include <iostream>

#define TREE_EMPTY 1
#define DATA_NOT_FOUND 2

template <class T>
class BinaryTree {

	template <class E>
	friend std::ostream& operator<<(std::ostream&, BinaryTree<E> const &);

	class Node{

		friend class BinaryTree;

	public:
		Node();
		Node(T* , int = 0);
		~Node();

	private:
		Node* parentPtr;
		Node* leftChildPtr;
		Node* rightChildPtr;
		T data;
		int depth;
	};


public:
	BinaryTree();
	~BinaryTree();

	Node* rootPtr;

	char add(T*);
	char remove(T*);
	char find(T*) const;

	bool isEmpty() const;

	int getSize() const;

private:
	int size;

	void reorangePatternOne(Node*);
	void reorangePatternTwo(Node*);
	void reorangePatternThree(Node*);
	void reorangePatternFour(Node*);

	void balanceCheck(Node*);
	void balance(Node*);

	char remove(Node*);

	void removePatternOne(Node*);
	void removePatternTwo(Node*);
	void removePatternThree(Node*);
	void removePatternFour(Node*);

	bool depthCheck(Node*);
	void depthFix(Node*);

	void destruct(Node*);
	char destructNode(Node*);

	void outputStream(Node*, std::ostream*) const;
};


////////// Node Functions
template<class T>
BinaryTree<T>::Node::Node(){}

template<class T>
BinaryTree<T>::Node::Node(T* arg1, int arg2) : data(*arg1), depth(arg2){
	parentPtr = NULL;
	leftChildPtr = NULL;
	rightChildPtr = NULL;
}

template<class T>
BinaryTree<T>::Node::~Node(){}


////////// BinaryTree Functions
template<class T>
BinaryTree<T>::BinaryTree(){
	rootPtr = NULL;
	size = 0;
}

template<class T>
BinaryTree<T>::~BinaryTree(){
	destruct(rootPtr);
}

template<class T>
char BinaryTree<T>::add(T* newData){
	size++;
	if(rootPtr == NULL)
		rootPtr = new Node(newData);
	else{
		Node* tempNode = rootPtr;
		while(tempNode != NULL){
			if( *newData < tempNode->data){
				if(tempNode->leftChildPtr == NULL){//Memory free might be needed
					Node* newNode = new Node(newData);
					newNode->parentPtr = tempNode;
					tempNode->leftChildPtr = newNode;
					balanceCheck(newNode);
					tempNode = NULL;
				} else {
					tempNode = tempNode->leftChildPtr;
				}
			} else {
				if(tempNode->rightChildPtr == NULL){//Memory free might be needed.
					Node* newNode = new Node(newData);
					newNode->parentPtr = tempNode;
					tempNode->rightChildPtr = newNode;
					balanceCheck(newNode);
					tempNode = NULL;
				} else{
					tempNode = tempNode->rightChildPtr;
				}
			}
		}//end of while loop
	}//end of if statement

	return 0;
}

template<class T>
char BinaryTree<T>::remove(T* oldDataPtr){
	if (rootPtr == NULL)
		return 0;

	Node* tempNode = rootPtr;

	while(tempNode != NULL){
		if((*oldDataPtr) < tempNode->data){
			tempNode = tempNode->leftChildPtr;
		} else if((*oldDataPtr) == tempNode->data) {
			return remove(tempNode);
		} else {
			tempNode = tempNode->rightChildPtr;
		}
	}

	return 0;
}

template<class T>
char BinaryTree<T>::remove(Node* nodePtr){

	//Base Case, Tree Size of 1
	if(getSize() == 1)
		return destructNode(rootPtr);

	int leftDepth, rightDepth;
	
	while(nodePtr != NULL){
		//Base Case, Children are NULL
		if(nodePtr->leftChildPtr == NULL && nodePtr->rightChildPtr == NULL)
			return destructNode(nodePtr);

		//Logic
		leftDepth = (-1);
		rightDepth = (-1);

		if(nodePtr->leftChildPtr != NULL)
			leftDepth = nodePtr->leftChildPtr->depth;
		if(nodePtr->rightChildPtr != NULL)
			rightDepth = nodePtr->rightChildPtr->depth;

		if(leftDepth < rightDepth){//Use the right side
		
			if(nodePtr->rightChildPtr->leftChildPtr != NULL)
				removePatternFour(nodePtr);
			else 
				removePatternThree(nodePtr);

		} else if (leftDepth > rightDepth){//Use the left side
		
			if(nodePtr->leftChildPtr->rightChildPtr != NULL)
				removePatternTwo(nodePtr);
			else
				removePatternOne(nodePtr);

		} else {//Uhhh i guess it doesn't matter which side you use.

			if(nodePtr->leftChildPtr != NULL){
				if(nodePtr->leftChildPtr->rightChildPtr != NULL)
					removePatternTwo(nodePtr);
				else 
					removePatternOne(nodePtr);

			} else if (nodePtr->rightChildPtr != NULL){
				if(nodePtr->rightChildPtr->leftChildPtr != NULL)
					removePatternFour(nodePtr);
				else 
					removePatternThree(nodePtr);
			}
		}
	}

	return 1;
}

template<class T>
char BinaryTree<T>::find(T* dataPtr) const{
	if(isEmpty())
		return TREE_EMPTY;

	Node* tempNode = rootPtr;
	while(tempNode != NULL){
		if(*dataPtr < tempNode->data){
			if(tempNode->leftChildPtr == NULL)
				return DATA_NOT_FOUND;
			else
				tempNode = tempNode->leftChildPtr;
		} else{
			if(*dataPtr == tempNode->data){
				(*dataPtr) = T(tempNode->data);
				return 0;
			}
			else{
				if(tempNode->rightChildPtr == NULL)
					return DATA_NOT_FOUND;
				else
					tempNode = tempNode->rightChildPtr;
			}
		}
	}
}

template<class T>
bool BinaryTree<T>::isEmpty() const { return (!getSize());}

template<class T>
int BinaryTree<T>::getSize() const { return size;} 

template<class T>
void BinaryTree<T>::balanceCheck(Node* nodePtr){
	if(depthCheck(nodePtr)){
		if (getSize() > 2 && (getSize() > (1<<(rootPtr->depth -1))) ){
			balance(nodePtr->parentPtr->parentPtr);
		}
	}
		
}

template<class T>
void BinaryTree<T>::balance(Node* nodePtr){
	int leftDepth, rightDepth;
	leftDepth = -1;
	rightDepth = -1;
	int difference;


	if (nodePtr->leftChildPtr != NULL)
		leftDepth = nodePtr->leftChildPtr->depth;
	if (nodePtr->rightChildPtr != NULL)
		rightDepth = nodePtr->rightChildPtr->depth;

	difference = leftDepth - rightDepth;
	if (difference < 0)
		difference*=(-1);

	if (difference > 1){
		if (nodePtr->leftChildPtr != NULL){
			if (nodePtr->leftChildPtr->rightChildPtr != NULL)
				reorangePatternTwo(nodePtr);
			else if(nodePtr->leftChildPtr->leftChildPtr != NULL)
				reorangePatternOne(nodePtr);
			else if (nodePtr->rightChildPtr != NULL){
				if (nodePtr->rightChildPtr->leftChildPtr != NULL)
					reorangePatternFour(nodePtr);
				else if(nodePtr->rightChildPtr->rightChildPtr != NULL) 
					reorangePatternThree(nodePtr);
			}
		} else if (nodePtr->rightChildPtr != NULL){
			if (nodePtr->rightChildPtr->leftChildPtr != NULL)
				reorangePatternFour(nodePtr);
			else if(nodePtr->rightChildPtr->rightChildPtr != NULL)
				reorangePatternThree(nodePtr);
		}
	} else if (nodePtr->parentPtr != NULL){
		balance(nodePtr->parentPtr);
	}
}

template<class T>
void BinaryTree<T>::reorangePatternOne(Node* nodePtr){
	//Given a tree of form {A,B,E,F,G,D,C} = {50,25,10,5,15,30,55}
	//Apply Pattern One to acquire
	// a tree of form {B,E,F,G,A,D,C} = {25,10,5,15,50,30,55}

	//Store B 
	Node* storedNodePtr = nodePtr->leftChildPtr;
	
	//Attach D to A left
	nodePtr->leftChildPtr = storedNodePtr->rightChildPtr;
	if (storedNodePtr->rightChildPtr != NULL)
		storedNodePtr->rightChildPtr->parentPtr = nodePtr;

	//Change parents
	storedNodePtr->parentPtr = nodePtr->parentPtr;
	if(nodePtr->parentPtr != NULL){//Change the sub-root parent
		if(nodePtr->parentPtr->leftChildPtr == nodePtr)
			nodePtr->parentPtr->leftChildPtr = storedNodePtr;
		else if(nodePtr->parentPtr->rightChildPtr == nodePtr)
			nodePtr->parentPtr->rightChildPtr = storedNodePtr;
	} else {
		rootPtr = storedNodePtr;//Make B Root
	}

	//Attach A to B right
	storedNodePtr->rightChildPtr = nodePtr;
	nodePtr->parentPtr = storedNodePtr;

	depthFix(storedNodePtr->leftChildPtr);
	depthFix(storedNodePtr->rightChildPtr);
	depthCheck(storedNodePtr);
}

template<class T>
void BinaryTree<T>::reorangePatternTwo(Node* nodePtr){
	//Given a tree of form {A,B,D,E,F,G,C} = {50,25,10,40,30,45,55}
	//Apply pattern two to acquire
	// a tree of form {E,B,D,F,A,G,C} = {40,25,10,30,50,45,55}

	//Store B
	Node* storedNodePtr = nodePtr->leftChildPtr;

	//G to A left
	nodePtr->leftChildPtr = storedNodePtr->rightChildPtr->rightChildPtr;
	if(storedNodePtr->rightChildPtr->rightChildPtr != NULL){
		storedNodePtr->rightChildPtr->rightChildPtr->parentPtr = nodePtr;
	}

	//A to E right first half
	storedNodePtr->rightChildPtr->rightChildPtr = nodePtr;

	//Set Root/Parent Association
	storedNodePtr->rightChildPtr->parentPtr = nodePtr->parentPtr;
	if(nodePtr->parentPtr != NULL){
		if(nodePtr->parentPtr->leftChildPtr == nodePtr)
			nodePtr->parentPtr->leftChildPtr = storedNodePtr->rightChildPtr;
		else if(nodePtr->parentPtr->rightChildPtr == nodePtr)
			nodePtr->parentPtr->rightChildPtr = storedNodePtr->rightChildPtr;
	} else {//Make E Root
		rootPtr = storedNodePtr->rightChildPtr;
	}

	//A to E right second half
	nodePtr->parentPtr = storedNodePtr->rightChildPtr;

	//F to B right
	storedNodePtr->rightChildPtr = nodePtr->parentPtr->leftChildPtr;
	if(nodePtr->parentPtr->leftChildPtr != NULL)
		nodePtr->parentPtr->leftChildPtr->parentPtr = storedNodePtr;

	//B to E right
	nodePtr->parentPtr->leftChildPtr = storedNodePtr;
	storedNodePtr->parentPtr = nodePtr->parentPtr;

	depthFix(storedNodePtr);
	depthFix(nodePtr);
	depthCheck(nodePtr->parentPtr);
}

template<class T>
void BinaryTree<T>::reorangePatternThree(Node* nodePtr){
	//Given a tree of form {A,B,C,D,E,F,G} = {50,25,75,60,100,80,125}
	//Apply Pattern Three to acquire
	// a tree of form {C,A,B,D,E,F,G} = {75,50,25,60,100,80,125}

	//Store C 
	Node* storedNodePtr = nodePtr->rightChildPtr;
	
	//Attach D to A right
	nodePtr->rightChildPtr = storedNodePtr->leftChildPtr;
	if (storedNodePtr->leftChildPtr != NULL)
		storedNodePtr->leftChildPtr->parentPtr = nodePtr;

	//Change parents
	storedNodePtr->parentPtr = nodePtr->parentPtr;
	if(nodePtr->parentPtr != NULL){//Change the sub-root parent
		if(nodePtr->parentPtr->leftChildPtr == nodePtr)
			nodePtr->parentPtr->leftChildPtr = storedNodePtr;
		else if(nodePtr->parentPtr->rightChildPtr == nodePtr)
			nodePtr->parentPtr->rightChildPtr = storedNodePtr;
	} else {
		rootPtr = storedNodePtr;//Make C Root
	}

	//Attach A to C left
	storedNodePtr->leftChildPtr = nodePtr;
	nodePtr->parentPtr = storedNodePtr;

	depthFix(storedNodePtr->leftChildPtr);
	depthFix(storedNodePtr->rightChildPtr);
	depthCheck(storedNodePtr);
}

template<class T>
void BinaryTree<T>::reorangePatternFour(Node* nodePtr){//WARNING
	//Given a tree of form {A,B,C,D,E,F,G} = {50,25,100,75,60,80,125}
	//Apply pattern two to acquire
	// a tree of form {D,A,B,E,C,F,G} = {75,50,25,60,100,80,125}

	//Store C
	Node* storedNodePtr = nodePtr->rightChildPtr;

	//E to A right
	nodePtr->rightChildPtr = storedNodePtr->leftChildPtr->leftChildPtr;
	if (storedNodePtr->leftChildPtr->leftChildPtr != NULL)
		storedNodePtr->leftChildPtr->leftChildPtr->parentPtr = nodePtr;

	//A to D left first half
	storedNodePtr->leftChildPtr->leftChildPtr = nodePtr;

	//Set Root/Parent Association
	storedNodePtr->leftChildPtr->parentPtr = nodePtr->parentPtr;
	if(nodePtr->parentPtr != NULL){
		if(nodePtr->parentPtr->leftChildPtr == nodePtr)
			nodePtr->parentPtr->leftChildPtr = storedNodePtr->leftChildPtr;
		else if(nodePtr->parentPtr->rightChildPtr == nodePtr)
			nodePtr->parentPtr->rightChildPtr = storedNodePtr->leftChildPtr;
	} else {//Make D Root
		rootPtr = storedNodePtr->leftChildPtr;
	}

	//A to D left second half
	nodePtr->parentPtr = storedNodePtr->leftChildPtr;

	//F to C left
	storedNodePtr->leftChildPtr = nodePtr->parentPtr->rightChildPtr;
	if(nodePtr->parentPtr->rightChildPtr != NULL)
		nodePtr->parentPtr->rightChildPtr->parentPtr = storedNodePtr;

	//C to D right
	nodePtr->parentPtr->rightChildPtr = storedNodePtr;
	storedNodePtr->parentPtr = nodePtr->parentPtr;

	depthFix(storedNodePtr);
	depthFix(nodePtr);
	depthCheck(nodePtr->parentPtr);
}



template<class T>
bool BinaryTree<T>::depthCheck(Node* nodePtr){
	Node* tempNode = nodePtr;
	int oldRootDepth;
	if(rootPtr != NULL)
		oldRootDepth = rootPtr->depth;
	else 
		oldRootDepth = (-1);

	while(tempNode != NULL){
		depthFix(tempNode);
		tempNode = tempNode->parentPtr;
	}

	if(rootPtr != NULL && oldRootDepth != rootPtr->depth)
		return true;
	else
		return false;
}

template<class T>
void BinaryTree<T>::depthFix(Node* nodePtr){
	if(nodePtr != NULL){
		nodePtr->depth = 0;
		if(nodePtr->leftChildPtr != NULL){
			if(nodePtr->depth <= nodePtr->leftChildPtr->depth)
				nodePtr->depth = (nodePtr->leftChildPtr->depth + 1);
		}
		if(nodePtr->rightChildPtr != NULL){
			if(nodePtr->depth <= nodePtr->rightChildPtr->depth)
				nodePtr->depth = (nodePtr->rightChildPtr->depth + 1);
		}
	}
}



template<class T>
void BinaryTree<T>::removePatternOne(Node* nodePtr){
	//Left
	//Store C
	Node* storedNodePtr = nodePtr->rightChildPtr;
	//Store B
	Node* swapNodePtr = nodePtr->leftChildPtr;

	//Attach E to A right
	nodePtr->rightChildPtr = swapNodePtr->rightChildPtr;
	if(swapNodePtr->rightChildPtr != NULL)
		swapNodePtr->rightChildPtr->parentPtr = nodePtr;

	//Attach C to B right
	swapNodePtr->rightChildPtr = storedNodePtr;
	if(storedNodePtr != NULL)
		storedNodePtr->parentPtr = swapNodePtr;

	//Attach D to A left
	nodePtr->leftChildPtr = swapNodePtr->leftChildPtr;
	if(swapNodePtr->leftChildPtr != NULL)
		swapNodePtr->leftChildPtr->parentPtr = nodePtr;

	//Root/Parent Association
	swapNodePtr->parentPtr = nodePtr->parentPtr;
	if(nodePtr->parentPtr != NULL){
		if(nodePtr->parentPtr->leftChildPtr == nodePtr)
			nodePtr->parentPtr->leftChildPtr = swapNodePtr;
		else
			nodePtr->parentPtr->rightChildPtr = swapNodePtr;
	} else {
		rootPtr = swapNodePtr;
	}

	//Attach A to B left
	swapNodePtr->leftChildPtr = nodePtr;
	nodePtr->parentPtr = swapNodePtr;
}

template<class T>
void BinaryTree<T>::removePatternTwo(Node* nodePtr){
	//Left Right
	//Store C
	Node* storedNodePtr = nodePtr->rightChildPtr;
	//Store D as swap
	Node* swapNodePtr = nodePtr->leftChildPtr->rightChildPtr;

	//Attach F to A right
	nodePtr->rightChildPtr = swapNodePtr->rightChildPtr;
	if(swapNodePtr->rightChildPtr != NULL)
		swapNodePtr->rightChildPtr->parentPtr = nodePtr;

	//Attach C to D right
	swapNodePtr->rightChildPtr = storedNodePtr;
	if(storedNodePtr != NULL)
		storedNodePtr->parentPtr = swapNodePtr;

	//Store B
	storedNodePtr = nodePtr->leftChildPtr;

	//Attach E to A left
	nodePtr->leftChildPtr = swapNodePtr->leftChildPtr;
	if(swapNodePtr->leftChildPtr != NULL)
		swapNodePtr->leftChildPtr->parentPtr = nodePtr;

	//Attach B to D left
	swapNodePtr->leftChildPtr = storedNodePtr;
	if(storedNodePtr != NULL)
		storedNodePtr->parentPtr = swapNodePtr;

	//Root/Parent Association
	swapNodePtr->parentPtr = nodePtr->parentPtr;
	if(nodePtr->parentPtr != NULL){
		if(nodePtr->parentPtr->leftChildPtr == nodePtr)
			nodePtr->parentPtr->leftChildPtr = swapNodePtr;
		else 
			nodePtr->parentPtr->rightChildPtr = swapNodePtr;
	} else {
		rootPtr = swapNodePtr;
	}

	//Attach A to B right
	storedNodePtr->rightChildPtr = nodePtr;
	nodePtr->parentPtr = storedNodePtr;
}

template<class T>
void BinaryTree<T>::removePatternThree(Node* nodePtr){
	//Right
	//Store D
	Node* storedNodePtr = nodePtr->rightChildPtr->leftChildPtr;
	//Store C
	Node* swapNodePtr = nodePtr->rightChildPtr;

	//Attach B to C left
	swapNodePtr->leftChildPtr = nodePtr->leftChildPtr;
	if(nodePtr->leftChildPtr != NULL)
		nodePtr->leftChildPtr->parentPtr = swapNodePtr;

	//Attach D to A left
	nodePtr->leftChildPtr = storedNodePtr;
	if(storedNodePtr != NULL)
		storedNodePtr->parentPtr = nodePtr;

	//Attach E to A right
	nodePtr->rightChildPtr = swapNodePtr->rightChildPtr;
	if(swapNodePtr->rightChildPtr != NULL)
		swapNodePtr->rightChildPtr->parentPtr = nodePtr;

	//Root/Parent Association
	swapNodePtr->parentPtr = nodePtr->parentPtr;
	if(nodePtr->parentPtr != NULL){
		if(nodePtr->parentPtr->leftChildPtr == nodePtr)
			nodePtr->parentPtr->leftChildPtr = swapNodePtr;
		else
			nodePtr->parentPtr->rightChildPtr = swapNodePtr;
	} else{
		rootPtr = swapNodePtr;
	}

	//Attach A to C right
	swapNodePtr->rightChildPtr = nodePtr;
	nodePtr->parentPtr = swapNodePtr;
}

template<class T>
void BinaryTree<T>::removePatternFour(Node* nodePtr){
	//Right Left
	Node* storedNodePtr = nodePtr->leftChildPtr;//Store D
	Node* swapNodePtr = nodePtr->rightChildPtr->leftChildPtr;//Store C

	//Attach E to A left
	nodePtr->leftChildPtr = swapNodePtr->leftChildPtr;
	if(swapNodePtr->leftChildPtr != NULL)
		swapNodePtr->leftChildPtr->parentPtr = nodePtr;

	//Attach D to C left
	swapNodePtr->leftChildPtr = storedNodePtr;
	if(storedNodePtr != NULL)
		storedNodePtr->parentPtr = swapNodePtr;

	//Store B
	storedNodePtr = nodePtr->rightChildPtr;

	//Attach F to A right
	nodePtr->rightChildPtr = swapNodePtr->rightChildPtr;
	if(swapNodePtr->rightChildPtr != NULL)
		swapNodePtr->rightChildPtr->parentPtr = nodePtr;

	//Attach B to C right
	swapNodePtr->rightChildPtr = storedNodePtr;
	storedNodePtr->parentPtr = swapNodePtr;

	//Attach A to B left part one
	storedNodePtr->leftChildPtr = nodePtr;

	//Root/Parent Association
	swapNodePtr->parentPtr = nodePtr->parentPtr;
	if(nodePtr->parentPtr != NULL){
		if(nodePtr->parentPtr->leftChildPtr == nodePtr)
			nodePtr->parentPtr->leftChildPtr = swapNodePtr;
		else
			nodePtr->parentPtr->rightChildPtr = swapNodePtr;
	} else {//Make C root
		rootPtr = swapNodePtr;
	}

	//Attach A to B left part two
	nodePtr->parentPtr = storedNodePtr;
}

template<class T>
void BinaryTree<T>::destruct(Node* theNode){
	if (theNode != NULL){
		if (theNode->leftChildPtr != NULL)
			destruct(theNode->leftChildPtr);
		if (theNode->rightChildPtr != NULL)
			destruct(theNode->rightChildPtr);
		delete theNode;
	}
}

template<class T>
char BinaryTree<T>::destructNode(Node* nodePtr){
	Node* tempNode = nodePtr->parentPtr;

	if(tempNode != NULL){
		if(tempNode->leftChildPtr == nodePtr)
			tempNode->leftChildPtr = NULL;
		else if (tempNode->rightChildPtr == nodePtr)
			tempNode->rightChildPtr = NULL;
	}

	delete nodePtr;
	size--;

	if(tempNode != NULL)
		depthCheck(tempNode);
	return 0;
}

template<class T>
void BinaryTree<T>::outputStream(Node* theNode, std::ostream* out) const{
	*(out) << theNode->data;
	if(theNode->leftChildPtr != NULL)
		outputStream(theNode->leftChildPtr, out);
	if (theNode->rightChildPtr != NULL)
		outputStream(theNode->rightChildPtr, out);
}

template<class T>
std::ostream& operator<<(std::ostream& out, BinaryTree<T> const & rhs){
	out << "";
	if(rhs.isEmpty())
		return out;
	rhs.outputStream(rhs.rootPtr, &out);
	return out;
}

#endif
//DRAYMIRE_BINARYTREE
