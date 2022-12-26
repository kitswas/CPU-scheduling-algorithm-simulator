/**
 * References:
 * 1. https://www.programiz.com/dsa/red-black-tree
 * 2. Cormen, Leiserson, Rivest, and Stein; Introduction to Algorithms (MIT Press, 2009)
 * 3. https://www.boost.org/doc/libs/1_81_0/doc/html/intrusive/reference.html#header.boost.intrusive.rbtree_hpp
 */

#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <memory>

/**
 * @brief A red-black tree implementation
 *
 * @tparam T The type of the elements in the tree
 */
template <typename T>
class RBTree
{
private:
	struct Node
	{
		T data;
		std::shared_ptr<Node> left;
		std::shared_ptr<Node> right;
		std::shared_ptr<Node> parent;
		bool isRed;
		Node() = default;
		Node(T data, std::shared_ptr<Node> parent) : data(std::move(data)), left(nullptr), right(nullptr), parent(parent), isRed(true) {}
	};

	std::shared_ptr<Node> root;
	std::shared_ptr<Node> nil;
	int (*compare)(const T &a, const T &b);
	size_t elements;

	void leftRotate(std::shared_ptr<Node> node);
	void rightRotate(std::shared_ptr<Node> node);
	void insertFixup(std::shared_ptr<Node> node);
	void transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v);
	void removeFixup(std::shared_ptr<Node> node);
	inline std::shared_ptr<Node> minimum(std::shared_ptr<Node> min)
	{
		while (min->left != this->nil)
		{
			min = min->left;
		}
		return min;
	}
	void _printPreorder(const std::shared_ptr<Node> &node) const
	{
		if (node != this->nil)
		{
			std::cout << *(node->data) << "\t" << (node->isRed ? "R" : "B") << '\n';
			this->_printPreorder(node->left);
			this->_printPreorder(node->right);
		}
	}
	void _printInorder(const std::shared_ptr<Node> &node) const
	{
		if (node != this->nil)
		{
			this->_printInorder(node->left);
			std::cout << *(node->data) << "\t" << (node->isRed ? "R" : "B") << '\n';
			this->_printInorder(node->right);
		}
	}
	void _printPostorder(const std::shared_ptr<Node> &node) const
	{
		if (node != this->nil)
		{
			this->_printPostorder(node->left);
			this->_printPostorder(node->right);
			std::cout << *(node->data) << "\t" << (node->isRed ? "R" : "B") << '\n';
		}
	}

public:
	/**
	 * @brief Construct a new RBTree object
	 *
	 * @param comparator A function pointer to a function that compares two elements
	 */
	RBTree(int (*comparator)(const T &a, const T &b));

	/**
	 * @brief Destroy the RBTree object
	 *
	 */
	~RBTree();

	/**
	 * @brief Insert an element into the tree
	 *
	 * @param data The element to insert
	 */
	void insert(T &data);

	/**
	 * @brief Remove an element from the tree
	 *
	 * @param node The element to remove
	 */
	void remove(std::shared_ptr<Node> node);

	/**
	 * @brief Check if the tree contains an element
	 *
	 * @param data The element to check for
	 * @return true If the tree contains the element
	 * @return false If the tree does not contain the element
	 */
	// bool contains(T &data);

	/**
	 * @brief Get the number of elements in the tree
	 *
	 * @return size_t The number of elements in the tree
	 */
	size_t size();

	/**
	 * @brief Extract the minimum element from the tree
	 *
	 * @return T The minimum element
	 */
	T extractMin();

	/**
	 * @brief Print preorder traversal of the tree
	 *
	 */
	void printPreorder() const;

	/**
	 * @brief Print inorder traversal of the tree
	 *
	 */
	void printInorder() const;

	/**
	 * @brief Print postorder traversal of the tree
	 *
	 */
	void printPostorder() const;
};

#endif // RBTREE_H
