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
		:_root(nullptr) {};
	~BinTree() { deleteTree(_root); }
	bool isEmpty() const { return _root == nullptr; }
	void insert(int);
	void remove(int);
	void remove(int, Node*);
	void deleteTree(Node*);
	Node* findClosestValueNode(int) const;
	Node* findMinValueNode(Node*) const;

	void print_inorder() const;
	void inorder(Node* p) const;
	void print_preorder() const;
	void preorder(Node* p) const;
	void print_postorder() const;
	void postorder(Node* p) const;

private:
	Node* _root;
};

void BinTree::deleteTree(Node* n)
{
	deleteTree(n->_leftChild);
	deleteTree(n->_rightChild);
	delete n;
}

void BinTree::insert(int val)
{
	if (findClosestValueNode(val)->_val == val)
	{
		std::cout << "Node with value " << val << "already exists." << std::endl;
		return;
	}

	Node* newNode = new Node;
	newNode->_val = val;
	newNode->_leftChild = nullptr;
	newNode->_rightChild = nullptr;
	if (isEmpty()) _root = newNode;
	else
	{
		Node* curr = _root;
		Node* parent = nullptr;
		while (curr != nullptr)
		{
			parent = curr;
			if (newNode->_val < curr->_val)
				curr = curr->_leftChild;
			else
				curr = curr->_rightChild;
		}
		if (newNode->_val < parent->_val)
			parent->_leftChild = newNode;
		else
			parent->_rightChild = newNode;
	}
	Node* curr = _root;
}

void BinTree::remove(int val, Node* n)
{
	if (isEmpty()) std::cout << "Tree is empty." << std::endl;
	
	bool search_res = true;
	Node* curr = n;
	Node* parent = nullptr; // needed for removing process
	while (curr != nullptr)
	{
		if (curr->_val == val)
		{
			search_res = true;
			break;
		}
		else
		{
			parent = curr;
			if (val < curr->_val)
				curr = curr->_leftChild;
			else
				curr = curr->_rightChild;
		}
	}

	if (!search_res)
	{
		std::cout << " Data not found! " << std::endl;
		return;
	}

	// removing leaf node
	if (curr->_leftChild == nullptr && curr->_rightChild == nullptr)
	{
		if (curr == parent->_leftChild)
			parent->_leftChild = nullptr;
		else
			parent->_rightChild = nullptr;

		delete curr;
	}

	// removing node with 1 child
	else if (curr->_leftChild != nullptr || curr->_rightChild != nullptr)
	{
		if (curr->_leftChild != nullptr)
		{
			if (curr == parent->_leftChild)
				parent->_leftChild = curr->_leftChild;
			else
				parent->_rightChild = curr->_leftChild;
		}
		else
		{
			if (curr == parent->_leftChild)
				parent->_leftChild = curr->_rightChild;
			else
				parent->_rightChild = curr->_rightChild;
		}
		delete curr;
	}

	// removing node with 2 children
	else if (curr->_leftChild != nullptr && curr->_rightChild != nullptr)
	{
		// search sub-trees for a node with min value and construct new node with this value
		Node* minLeft = findMinValueNode(curr->_leftChild);
		Node* minRight = findMinValueNode(curr->_rightChild);
		Node* minNode = (minLeft < minRight) ? minLeft : minRight;
		Node* newNode = new Node;
		newNode->_val = minNode->_val;
		newNode->_leftChild = curr->_leftChild; // transfer children from node under removal to the new one
		newNode->_rightChild = curr->_rightChild;

		if (curr == parent->_leftChild)
		{
			parent->_leftChild = newNode;
		}
		else if (curr == parent->_rightChild)
		{
			parent->_rightChild = newNode;
		}

		remove(minNode->_val, curr);
		delete curr;
	}
}

void BinTree::remove(int val)
{
	remove(val, _root);
}


Node* BinTree::findClosestValueNode(int val) const
{
	if (isEmpty())
	{
		std::cout << "Tree is empty." << std::endl;
		return nullptr;
	}

	Node* curr = _root;
	Node* parent;
	while (curr->_val != val)
	{
		if (val < curr->_leftChild->_val)
			curr = curr->_leftChild;
		else
			curr = curr->_rightChild;
	}
	
	return curr; // either closest or exact match
}

Node* BinTree::findMinValueNode(Node* n) const
{
	Node* curr = n;
	while (curr->_leftChild != nullptr);
	{
		curr = curr->_leftChild;
	}
	return curr;
}


void BinTree::print_inorder() const
{
	inorder(_root);
}

void BinTree::inorder(Node* p) const
{
	if (p != nullptr)
	{
		if (p->_leftChild) inorder(p->_leftChild);
		std::cout << " " << p->_val << " ";
		if (p->_rightChild) inorder(p->_rightChild);
	}
	else return;
}

void BinTree::print_preorder() const
{
	preorder(_root);
}

void BinTree::preorder(Node* p) const
{
	if (p != nullptr)
	{
		std::cout << " " << p->_val << " ";
		if (p->_leftChild) preorder(p->_leftChild);
		if (p->_rightChild) preorder(p->_rightChild);
	}
	else return;
}

void BinTree::print_postorder() const
{
	postorder(_root);
}

void BinTree::postorder(Node* p) const
{
	if (p != nullptr)
	{
		if (p->_leftChild) postorder(p->_leftChild);
		if (p->_rightChild) postorder(p->_rightChild);
		std::cout << " " << p->_val << " ";
	}
	else return;
}



int main()
{
	BinTree TestTree;
	TestTree.insert(2);
	TestTree.insert(3);
	TestTree.insert(5);
	TestTree.insert(16);
	TestTree.insert(0);
	TestTree.insert(8);
	TestTree.insert(7);
	TestTree.insert(11);
	TestTree.insert(6);
	TestTree.insert(9);
	TestTree.insert(13);

	TestTree.remove(0);

	TestTree.print_inorder();
	puts("");
	TestTree.print_preorder();
	puts("");
	TestTree.print_postorder();
	puts("");

	return 0;
}
