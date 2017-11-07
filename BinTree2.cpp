#include <iostream>

class Node
{
public:
	Node()
		:_val(0), _leftChild(nullptr), _rightChild (nullptr) {};
	Node(int val)
		:_val(val), _leftChild(nullptr), _rightChild(nullptr) {};
	~Node()
	{	
		if (_leftChild != nullptr)
			delete _leftChild;
		if (_rightChild != nullptr)
			delete _rightChild;
	}
	int _val;
	Node* _leftChild;
	Node* _rightChild;
};

class BinTree
{
public:
	BinTree()
		:_root(nullptr) {};
	~BinTree() { deleteTree(); }
	bool isEmpty() const { return _root == nullptr; }
	void insert(int);
	void remove(int);
	void remove(int, Node*);
	void deleteTree();
	Node* findClosestValueNode(int) const;
	Node* findClosestValueNode(int, Node*) const;

	void print_inorder() const;
	void inorder(Node* p) const;
	void print_preorder() const;
	void preorder(Node* p) const;
	void print_postorder() const;
	void postorder(Node* p) const;

private:
	Node* _root;
};

void BinTree::deleteTree()
{
	delete _root;
}

void BinTree::insert(int val)
{
	Node* newNode = new Node(val);

	if (isEmpty())
		_root = newNode;
	else if (findClosestValueNode(val)->_val == val)
	{
		std::cout << "Node with value " << val << " already exists." << std::endl;
		return;
	}
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
	Node* parent = n; // used later in removing process
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
	else if ((curr->_leftChild == nullptr && curr->_rightChild != nullptr) || (curr->_leftChild != nullptr && curr->_rightChild == nullptr))
	{
		if (curr->_leftChild != nullptr)
		{
			if (curr == parent->_leftChild)
				parent->_leftChild = curr->_leftChild;
			else
				parent->_rightChild = curr->_leftChild;
		}
		else if (curr->_rightChild != nullptr)
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
		// search right sub-tree for closest value to the removed one
		Node* minNode = findClosestValueNode(val, curr->_rightChild);
		curr->_val = minNode->_val;
		remove(minNode->_val, curr->_rightChild);
	}
}

void BinTree::remove(int val)
{
	remove(val, _root);
}

Node* BinTree::findClosestValueNode(int val, Node* n) const
{
	if (isEmpty())
	{
		std::cout << "Tree is empty." << std::endl;
		return nullptr;
	}

	Node* curr = n;
	Node* parent = n;
	while (curr != nullptr)
	{
		parent = curr;
		if (val < curr->_val)
			curr = curr->_leftChild;
		else if (val > curr->_val)
			curr = curr->_rightChild;
		else
			return curr; // exact match
	}
	
	return parent; // closest
}

Node* BinTree::findClosestValueNode(int val) const
{
	return findClosestValueNode(val, _root);
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
try {
	BinTree TestTree;
	TestTree.insert(2);
	TestTree.insert(3);
	TestTree.insert(5);
	TestTree.insert(16);
	TestTree.insert(0);
	TestTree.insert(8);
	TestTree.insert(7);
	TestTree.insert(11);
	TestTree.insert(5);
	TestTree.insert(6);
	TestTree.insert(9);
	TestTree.insert(13);

	TestTree.print_preorder();
	puts("");
	TestTree.remove(8);
	TestTree.print_preorder();
	puts("");
	
	TestTree.deleteTree();

	return 0;
}
catch (char *e)
{
	std::cout << "Error" << std::endl;
}
