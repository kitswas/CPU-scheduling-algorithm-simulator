#include "rbtree.hpp"
#include "process.hpp"

template class RBTree<std::unique_ptr<Process>>;

template <typename T>
RBTree<T>::RBTree(int (*comparator)(const T &a, const T &b))
{
	this->compare = comparator;
	this->elements = 0;

	this->nil = std::make_shared<Node>();
	this->nil->left = nullptr;
	this->nil->right = nullptr;
	this->nil->parent = nullptr;
	this->nil->isRed = false;

	this->root = this->nil;
}

template <typename T>
RBTree<T>::~RBTree()
{
}

/**
 * @brief Left rotate the tree at the given node
 *
 * @details
 *
 *    x             y
 *   / \           / \
 *  a   y   ->    x   c
 *     / \       / \
 *    b   c     a   b
 * @tparam T
 * @param node
 */
template <typename T>
void RBTree<T>::leftRotate(std::shared_ptr<Node> node)
{
	std::shared_ptr<Node> right = node->right;
	if (node == nullptr || right == nullptr)
		return;
	node->right = right->left;
	if (right->left != this->nil)
		right->left->parent = node;
	right->left = node;
	right->parent = node->parent;
	if (node->parent == this->nil)
	{
		this->root = right;
	}
	else if (node == node->parent->left)
	{
		node->parent->left = right;
	}
	else
	{
		node->parent->right = right;
	}
	node->parent = right;
}

/**
 * @brief Right rotate the tree at the given node
 *
 * @details
 *
 *     x             y
 *    / \           / \
 *   y   c   ->    a   x
 *  / \               / \
 * a   b             b   c
 * @tparam T
 * @param node
 */
template <typename T>
void RBTree<T>::rightRotate(std::shared_ptr<Node> node)
{
	std::shared_ptr<Node> left = node->left;
	if (node == nullptr || left == nullptr)
		return;
	node->left = left->right;
	if (left->right != this->nil)
		left->right->parent = node;
	left->right = node;
	left->parent = node->parent;
	if (node->parent == this->nil)
	{
		this->root = left;
	}
	else if (node == node->parent->left)
	{
		node->parent->left = left;
	}
	else
	{
		node->parent->right = left;
	}
	node->parent = left;
}

/**
 * @brief Insert a new node into the tree
 *
 * @details
 *
 * @tparam T
 * @param data
 */
template <typename T>
void RBTree<T>::insert(T &data)
{
	std::shared_ptr<Node> node = std::make_shared<Node>(std::move(data), this->nil);
	std::shared_ptr<Node> parent = this->nil;
	std::shared_ptr<Node> current = this->root;
	while (current != this->nil) // Traverse till we hit a leaf
	{
		parent = current;
		if (this->compare(node->data, current->data) < 0)
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}
	}
	node->parent = parent;
	if (parent == this->nil)
	{
		this->root = node;
	}
	else if (this->compare(node->data, parent->data) < 0)
	{
		parent->left = node;
	}
	else
	{
		parent->right = node;
	}
	node->left = this->nil;
	node->right = this->nil;
	node->isRed = true;
	this->insertFixup(node);
	this->elements++;
}

/**
 * @brief Fixup the tree after an insert
 *
 * @details
 *
 * @tparam T
 * @param node
 */
template <typename T>
void RBTree<T>::insertFixup(std::shared_ptr<Node> node)
{
	while (node->parent->isRed)
	{
		if (node->parent == node->parent->parent->left)
		{
			std::shared_ptr<Node> uncle = node->parent->parent->right;
			if (uncle->isRed) // Case 1
			{
				node->parent->isRed = false;
				uncle->isRed = false;
				node->parent->parent->isRed = true;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->right) // Case 2
				{
					node = node->parent;
					this->leftRotate(node);
				}
				// Case 3
				node->parent->isRed = false;
				node->parent->parent->isRed = true;
				this->rightRotate(node->parent->parent);
			}
		}
		else
		{
			std::shared_ptr<Node> uncle = node->parent->parent->left;
			if (uncle->isRed) // Case 1
			{
				node->parent->isRed = false;
				uncle->isRed = false;
				node->parent->parent->isRed = true;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->left) // Case 2
				{
					node = node->parent;
					this->rightRotate(node);
				}
				// Case 3
				node->parent->isRed = false;
				node->parent->parent->isRed = true;
				this->leftRotate(node->parent->parent);
			}
		}
	}
	this->root->isRed = false;
}

template <typename T>
void RBTree<T>::transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v)
{
	if (u->parent == this->nil)
	{
		this->root = v;
	}
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}
	v->parent = u->parent;
}

/**
 * @brief Remove a node from the tree
 *
 * @details
 * @tparam T
 * @param node
 */
template <typename T>
void RBTree<T>::remove(std::shared_ptr<Node> node)
{
	std::shared_ptr<Node> y = node;
	std::shared_ptr<Node> x;
	bool yOriginallyWasRed = y->isRed;
	if (node->left == this->nil)
	{
		x = node->right;
		this->transplant(node, node->right);
	}
	else if (node->right == this->nil)
	{
		x = node->left;
		this->transplant(node, node->left);
	}
	else
	{
		y = this->minimum(node->right);
		yOriginallyWasRed = y->isRed;
		x = y->right;
		if (y->parent == node)
		{
			x->parent = y;
		}
		else
		{
			this->transplant(y, y->right);
			y->right = node->right;
			y->right->parent = y;
		}
		this->transplant(node, y);
		y->left = node->left;
		y->left->parent = y;
		y->isRed = node->isRed;
	}
	if (!yOriginallyWasRed)
	{
		this->removeFixup(x);
	}
	this->elements--;
}

template <typename T>
void RBTree<T>::removeFixup(std::shared_ptr<Node> node)
{
	while (node != this->root && !node->isRed)
	{
		if (node == node->parent->left)
		{
			std::shared_ptr<Node> sibling = node->parent->right;
			if (sibling->isRed) // Case 1
			{
				sibling->isRed = false;
				node->parent->isRed = true;
				this->leftRotate(node->parent);
				sibling = node->parent->right;
			}
			if (!sibling->left->isRed && !sibling->right->isRed) // Case 2
			{
				sibling->isRed = true;
				node = node->parent;
			}
			else
			{
				if (!sibling->right->isRed) // Case 3
				{
					sibling->left->isRed = false;
					sibling->isRed = true;
					this->rightRotate(sibling);
					sibling = node->parent->right;
				}
				// Case 4
				sibling->isRed = node->parent->isRed;
				node->parent->isRed = false;
				sibling->right->isRed = false;
				this->leftRotate(node->parent);
				node = this->root;
			}
		}
		else
		{
			std::shared_ptr<Node> sibling = node->parent->left;
			if (sibling->isRed) // Case 1
			{
				sibling->isRed = false;
				node->parent->isRed = true;
				this->rightRotate(node->parent);
				sibling = node->parent->left;
			}
			if (!sibling->right->isRed && !sibling->left->isRed) // Case 2
			{
				sibling->isRed = true;
				node = node->parent;
			}
			else
			{
				if (!sibling->left->isRed) // Case 3
				{
					sibling->right->isRed = false;
					sibling->isRed = true;
					this->leftRotate(sibling);
					sibling = node->parent->left;
				}
				// Case 4
				sibling->isRed = node->parent->isRed;
				node->parent->isRed = false;
				sibling->left->isRed = false;
				this->rightRotate(node->parent);
				node = this->root;
			}
		}
	}
	node->isRed = false;
}

template <typename T>
inline size_t RBTree<T>::size()
{
	return elements;
}

template <typename T>
T RBTree<T>::extractMin()
{
	if (this->root != this->nil)
	{
		std::shared_ptr<Node> min = this->minimum(this->root);
		T data = std::move(min->data);
		this->remove(min);
		return data;
	}
	throw std::runtime_error("Tree is empty! Cannot extract minimum.");
}

template <typename T>
void RBTree<T>::printPreorder() const
{
	std::cout << "Printing the preorder traversal\n";
	_printPreorder(this->root);
}

template <typename T>
void RBTree<T>::printInorder() const
{
	std::cout << "Printing the inorder traversal\n";
	_printInorder(this->root);
}

template <typename T>
void RBTree<T>::printPostorder() const
{
	std::cout << "Printing the postorder traversal\n";
	_printPostorder(this->root);
}
