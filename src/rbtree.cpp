#include "rbtree.hpp"

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
 * @param value
 */
template <typename T>
void RBTree<T>::insert(const T &value)
{
	std::shared_ptr<Node> node = std::make_shared<Node>(value);
	std::shared_ptr<Node> parent = this->nil;
	std::shared_ptr<Node> current = this->root;
	while (current != this->nil) // Traverse till we hit a leaf
	{
		parent = current;
		if (this->compare(value, current->value) < 0)
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
	else if (this->compare(value, parent->value) < 0)
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
