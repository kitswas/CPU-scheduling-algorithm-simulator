#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <vector>
#include <memory>
#include <iostream>

/**
 * @brief A min heap implementation
 *
 * @tparam T The type of the elements in the heap
 */
template <typename T>
class MinHeap
{
private:
	std::vector<T> heap;
	void heapify(size_t index);
	size_t size() const;
	int (*compare)(const T &a, const T &b);

public:
	/**
	 * @brief Construct a new Min Heap object
	 *
	 * @param vec The vector to be converted into a heap
	 * @param comparator The comparator function to be used for comparing elements
	 */
	MinHeap(std::vector<T> &vec, int (*comparator)(const T &a, const T &b));
	~MinHeap() = default;

	void printHeap() const;
	void buildHeap();
	void insert(T element);
	T extractMin();
	void decreaseKey(size_t index, T element);
	bool isEmpty() const;
};

#endif // MIN_HEAP_H
