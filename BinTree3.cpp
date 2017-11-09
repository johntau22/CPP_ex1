#include <iostream>

class Node
{
public:
	Node()
		:_val(0), _leftChild(nullptr), _rightChild(nullptr) {};
	Node(int v)
		:_val(v), _leftChild(nullptr), _rightChild(nullptr) {};
	~Node();

	int _val;
	Node* _parent;
	Node* _leftChild;
	Node* _rightChild;
};

Node::~Node()
{
	if (_parent->_leftChild == this)
		_parent->_leftChild = nullptr;
	else if (_parent->_rightChild == this)
		_parent->_rightChild = nullptr;
}

class BinTree
{
public:
	BinTree()
		:_root(nullptr) {};
	~BinTree() { deleteTree(); }
	bool isEmpty() const { return _root == nullptr; }
	void insert(int);
	void remove(int);
	void deleteTree();
	void deleteSubTree(Node*);
	Node* findClosestValueNode(int) const;

	void print_inorder() const;
	void print_preorder() const;
	void print_postorder() const;
	void inorder(Node* p) const;
	void preorder(Node* p) const;
	void postorder(Node* p) const;

private:
	void remove(int, Node*);
	Node* findInsertPos(int) const;
	Node* findLeftmostLeaf() const;
	Node* findLeftmostLeaf(Node*) const;
	Node* findClosestValueNode(int, Node*) const;

	Node* _root;
};

void BinTree::deleteTree()
{	
	if (_root == nullptr)
		return;

	Node* curr = _root;
	while (curr->_leftChild != nullptr || curr->_rightChild != nullptr)
	{
		delete findLeftmostLeaf(curr);
	}

	delete _root;
	_root = nullptr;
}

void BinTree::deleteSubTree(Node* n)
{
	if (n == nullptr)
		return;

	if (n == _root)
	{
		std::cout << "DeleteSubTree: function can't delete root. Use deleteTree() for full tree deletion." << std::endl;
		return;
	}	

	Node* curr = n;
	while (curr->_leftChild != nullptr || curr->_rightChild != nullptr)
	{
		delete findLeftmostLeaf(curr);
	}

	delete n;
	n = nullptr;
}

// helper function for tree deletion
Node* BinTree::findLeftmostLeaf(Node* n) const
{
	if (n == nullptr)
		return n;

	Node* curr = n;
	while (curr->_leftChild != nullptr || curr->_rightChild != nullptr)
	{
		if (curr->_leftChild != nullptr)
			curr = curr->_leftChild;
		else if (curr->_rightChild != nullptr)
			curr = curr->_rightChild;
	}
	return curr;
}

Node* BinTree::findLeftmostLeaf() const
{
	return findLeftmostLeaf(_root);
}

void BinTree::insert(int val)
{
	if (isEmpty())
	{
		Node* newNode = new Node(val);
		_root = newNode;
		_root->_parent = _root; // root is himself's parent
	}
	else if (findClosestValueNode(val)->_val == val)
	{
		std::cout << "Node with value " << val << " already exists." << std::endl;
		return;
	}
	else
	{
		Node* parent = findInsertPos(val);
		Node* newNode = new Node(val);
		newNode->_parent = parent;
		if (newNode->_val < parent->_val)
			parent->_leftChild = newNode;
		else
			parent->_rightChild = newNode;
	}
}

void BinTree::remove(int val, Node* n)
{
	if (isEmpty()) std::cout << "Tree is empty." << std::endl;

	Node* curr = findClosestValueNode(val);
	Node* parent = curr->_parent;
	if (curr->_val == val)
	{
		// leaf node
		if (curr->_leftChild == nullptr && curr->_rightChild == nullptr)
		{
			if (curr != _root)
			{
				if (curr == parent->_leftChild)
					parent->_leftChild = nullptr;
				else if (curr == parent->_rightChild)
					parent->_rightChild = nullptr;
			}

			delete curr;
			curr = nullptr;
		}

		// only left child
		else if (curr->_leftChild != nullptr && curr->_rightChild == nullptr)
		{
			if (curr == _root)
			{
				_root = curr->_leftChild;
			}
			else
			{
				curr->_leftChild->_parent = parent;
				if (curr == parent->_leftChild)
					parent->_leftChild = curr->_leftChild;
				else
					parent->_rightChild = curr->_leftChild;
			}

			delete curr;
			curr = nullptr;
		}

		// only right child
		else if (curr->_leftChild == nullptr && curr->_rightChild != nullptr)
		{
			if (curr == _root)
			{
				_root = curr->_rightChild;
			}
			else
			{
				curr->_rightChild->_parent = parent;
				if (curr == parent->_leftChild)
					parent->_leftChild = curr->_rightChild;
				else
					parent->_rightChild = curr->_rightChild;
			}

			delete curr;
			curr = nullptr;
		}

		// 2 children
		else if (curr->_leftChild != nullptr && curr->_rightChild != nullptr)
		{
			// search right sub-tree for closest value to the removed one
			Node* minNode = findClosestValueNode(val, curr->_rightChild);
			int min_val = minNode->_val;
			remove(minNode->_val, curr);
			curr->_val = min_val;
		}
	}
	else
		std::cout << " Data not found! " << std::endl;
}

void BinTree::remove(int val)
{
	remove(val, _root);
}

Node* BinTree::findInsertPos(int val) const
{
	Node* curr = _root;
	Node* parent = _root->_parent;
	while (curr != nullptr)
	{
		parent = curr;
		if (val < curr->_val)
			curr = curr->_leftChild;
		else
			curr = curr->_rightChild;
	}

	return parent;
}

Node* BinTree::findClosestValueNode(int val, Node* n) const
{
	if (isEmpty())
	{
		std::cout << "Tree is empty." << std::endl;
		return nullptr;
	}

	int min_diff = abs(n->_val - val);
	Node* closestValueNode = n;
	Node* curr = n;
	Node* parent = n->_parent;
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

	if (abs(parent->_val - val) < min_diff && parent->_val > 0)
	{
		min_diff = abs(parent->_val - val);
		closestValueNode = parent;
	}

	return closestValueNode;
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
	TestTree.insert(5);
	TestTree.insert(6);
	TestTree.insert(9);
	TestTree.insert(13);

	TestTree.print_preorder();
	puts("");
	TestTree.remove(8);
	TestTree.remove(2);
	TestTree.print_preorder();
	puts("");

	//TestTree.deleteTree(TestTree.findClosestValueNode(3));
	//TestTree.deleteTree(TestTree.findClosestValueNode(0));
	TestTree.deleteSubTree(TestTree.findClosestValueNode(3));
	TestTree.deleteSubTree(TestTree.findClosestValueNode(5));
	//delete TestTree._root;
	//TestTree._root = nullptr;
	TestTree.deleteTree();
	
	return 0;
}
