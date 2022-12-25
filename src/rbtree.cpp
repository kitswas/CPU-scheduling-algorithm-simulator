#include "rbtree.hpp"

template <typename T>
RBTree<T>::RBTree(int (*comparator)(const T &a, const T &b))
{
	this->compare = comparator;
	this->elements = 0;
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
	if (right->left != nullptr)
		right->left->parent = node;
	right->left = node;
	right->parent = node->parent;
	if (node->parent == nullptr)
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
	if (left->right != nullptr)
		left->right->parent = node;
	left->right = node;
	left->parent = node->parent;
	if (node->parent == nullptr)
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
