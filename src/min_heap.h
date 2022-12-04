#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <vector>
#include <memory>
#include <iostream>

template <typename T>
class MinHeap
{
private:
	std::vector<T> heap;

public:
	MinHeap() = default;
	MinHeap(std::vector<T> &vec);
	~MinHeap() = default;

	void printHeap() const;
	void heapify(int index);
	void buildHeap();
	void insert(T element);
	T extractMin();
	void decreaseKey(int index, T element);
};

#endif // MIN_HEAP_H
