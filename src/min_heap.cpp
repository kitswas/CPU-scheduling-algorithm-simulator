#include "min_heap.hpp"
#include "process.hpp"
#include "scheduler.hpp"

template class MinHeap<std::unique_ptr<Process>>;
template class MinHeap<std::unique_ptr<RRProcess>>;

template <typename T>
MinHeap<T>::MinHeap(int (*comparator)(const T &a, const T &b))
{
	this->compare = comparator;
}

template <typename T>
MinHeap<T>::MinHeap(std::vector<T> &vec, int (*comparator)(const T &a, const T &b))
{
	heap = std::move(vec);
	this->compare = comparator;
	buildHeap();
}

template <typename T>
void MinHeap<T>::printHeap() const
{
	for (const auto &element : heap)
	{
		std::cout << *element << std::endl;
	}
}

template <typename T>
void MinHeap<T>::heapify(size_t index)
{
	size_t left = 2 * index + 1;
	size_t right = 2 * index + 2;
	size_t smallest = index;
	if (left < heap.size() && compare(heap[left], heap[smallest]) < 0)
	{
		smallest = left;
	}
	if (right < heap.size() && compare(heap[right], heap[smallest]) < 0)
	{
		smallest = right;
	}
	if (smallest != index)
	{
		heap[index].swap(heap[smallest]);
		heapify(smallest);
	}
}

template <typename T>
void MinHeap<T>::buildHeap()
{
	for (size_t i = heap.size() / 2 - 1; i >= 1; i--)
	{
		heapify(i);
	}
	if (heap.size() > 0)
	{
		// This split is necessary because the size_t type is unsigned
		// Hence, i >= 0 will always be true
		heapify(0);
	}
}

template <typename T>
void MinHeap<T>::insert(T element)
{
	heap.push_back(std::move(element));
	size_t index = heap.size() - 1;
	while (index > 0 && compare(heap[index], heap[(index - 1) / 2]) < 0)
	{
		heap[index].swap(heap[(index - 1) / 2]);
		index = (index - 1) / 2;
	}
}

template <typename T>
T MinHeap<T>::extractMin()
{
	T min = std::move(heap[0]);
	heap[0].swap(heap[heap.size() - 1]);
	heap.pop_back();
	heapify(0);
	return min;
}

template <typename T>
void MinHeap<T>::decreaseKey(size_t index, T element)
{
	heap[index] = std::move(element);
	while (index > 0 && compare(heap[index], heap[(index - 1) / 2]) < 0)
	{
		heap[index].swap(heap[(index - 1) / 2]);
		index = (index - 1) / 2;
	}
}

template <typename T>
size_t MinHeap<T>::size() const
{
	return heap.size();
}

template <typename T>
bool MinHeap<T>::isEmpty() const
{
	return heap.size() == 0;
}
