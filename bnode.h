#ifndef BNode_H
#define BNode_H

#include <iostream>
#include <cassert>

template <class T>
struct BNode {
public:
	T data;
	BNode<T>* pLeft;
	BNode<T>* pRight;
	BNode<T>* pParent;

	BNode() : pLeft(NULL), pRight(NULL), pParent(NULL), data() {}

	// non-default. Initialize data as we create the node
	BNode(const T& data) : pLeft(NULL), pRight(NULL), pParent(NULL), data(data) {}
};

template<class T>
void addLeft(BNode<T>* pNode, const T& t)
{
	try 
	{
		BNode<T>* pAdd = new BNode<T>(t);
		pAdd->pParent = pNode;
		pNode->pLeft = pAdd;
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a node";
	}
}

template<class T>
void addLeft(BNode<T>* pNode, BNode<T>* pAdd)
{
	try
	{
		if (pAdd != NULL)
			pAdd->pParent = pNode;
		pNode->pLeft = pAdd;
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a node";
	}
}

template<class T>
void addRight(BNode<T>* pNode, const T& t)
{
	try
	{
		BNode<T>* pAdd = new BNode<T>(t);
		pAdd->pParent = pNode;
		pNode->pRight = pAdd;
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a node";
	}
}

template<class T>
void addRight(BNode<T>* pNode, BNode<T>* pAdd)
{
	try
	{
		if (pAdd != NULL)
			pAdd->pParent = pNode;
		pNode->pRight = pAdd;
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a node";
	}
}

template<class T>
int sizeBTree(const BNode<T>* node)
{
	if (node == NULL)
	{
		return 0;
	}
	else
	{
		return sizeBTree(node->pLeft) + 1 + sizeBTree(node->pRight);
	}
}

template<class T>
void deleteBTree(BNode<T>* & node)
{
	if (node == NULL)
	{
		return;
	}
	
	deleteBTree(node->pLeft);
	deleteBTree(node->pRight);
	delete node;
}

template<class T>
BNode<T>* copyBTree(const BNode<T>* source)
{
	if (source == NULL)
	{
		return NULL;
	}
	BNode<T>* destination = new BNode<T>(source->data);

	destination->pLeft = copyBTree(source->pLeft);
	if (destination->pLeft != NULL)
	{
		destination->pLeft->pParent = destination;
	}

	destination->pRight = copyBTree(source->pRight);
	if (destination->pRight != NULL)
	{
		destination->pRight->pParent = destination;
	}
	
	return destination;
}

template <class T>
std::ostream& operator << (std::ostream& out, const BNode <T>* pHead)
{
	// paranoia
	if (pHead == NULL)
		return out;

	if (pHead->pLeft)
		return (out << " " << pHead->pLeft);
	
	out << " " << pHead->data;
	
	if (pHead->pRight)
		return (out << " " << pHead->pRight);
}


#endif // BNode_H
