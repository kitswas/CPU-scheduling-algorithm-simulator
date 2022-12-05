#include "min_heap.h"
#include "process.h"

template class MinHeap<std::unique_ptr<Process>>;

template <typename T>
MinHeap<T>::MinHeap(std::vector<T> &vec)
{
	heap = std::move(vec);
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
	if (left < heap.size() && heap[left]->arrivalTime < heap[smallest]->arrivalTime)
	{
		smallest = left;
	}
	if (right < heap.size() && heap[right]->arrivalTime < heap[smallest]->arrivalTime)
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
	while (index > 0 && heap[index]->arrivalTime < heap[(index - 1) / 2]->arrivalTime)
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
	while (index > 0 && heap[index]->arrivalTime < heap[(index - 1) / 2]->arrivalTime)
	{
		heap[index].swap(heap[(index - 1) / 2]);
		index = (index - 1) / 2;
	}
}
