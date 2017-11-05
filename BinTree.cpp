#include <iostream>

struct Node
{
	int _val;
	Node* _parent;
	Node* _leftChild;
	Node* _rightChild;
};

class BinTree
{
public:
	BinTree()
		:root(NULL) {};
	bool isEmpty() const { return root == NULL; }
	void insert(int);
	void remove(int);

private:
	Node* root;
};

void BinTree::insert(int a)
{
	Node* newNode = new Node;
	newNode->_val = a;
	newNode->_leftChild = NULL;
	newNode->_rightChild = NULL;
	if (isEmpty())
		root = newNode;
	else
	{
		Node* curr = root;
		while (curr->_leftChild != NULL && curr->_rightChild != NULL)
		{
			curr = curr->_leftChild;
		}
		if (curr->_leftChild == NULL)
			curr->_leftChild = newNode;
		else
			curr->_rightChild = newNode;
	}
	Node* curr = root;
}

int main()
{
	;
}
