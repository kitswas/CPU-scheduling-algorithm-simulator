// #include <iostream>

#include "min_heap.h"
// #include "process.h"
// #include "process_creator.h"

// int main()
// {
// 	std::vector<std::unique_ptr<Process>> processes = ProcessCreator::createProcesses(9);
// 	std::cout << "Processes created" << std::endl;
// 	for (const auto &process : processes)
// 	{
// 		std::cout << *process << std::endl;
// 	}
// 	std::cout << "After heapifying" << std::endl;
// 	MinHeap<std::unique_ptr<Process>> heap(processes);
// 	heap.printHeap();
// 	heap.extractMin();
// 	std::cout << "After extracting min" << std::endl;
// 	heap.printHeap();
// 	heap.insert(std::make_unique<Process>(10, 0, 1));
// 	std::cout << "After inserting" << std::endl;
// 	heap.printHeap();
// 	return 0;
// }

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
void MinHeap<T>::heapify(int index)
{
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int smallest = index;
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
	for (int i = heap.size() / 2 - 1; i >= 0; i--)
	{
		heapify(i);
	}
}

template <typename T>
void MinHeap<T>::insert(T element)
{
	heap.push_back(std::move(element));
	int index = heap.size() - 1;
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
void MinHeap<T>::decreaseKey(int index, T element)
{
	heap[index] = std::move(element);
	while (index > 0 && heap[index]->arrivalTime < heap[(index - 1) / 2]->arrivalTime)
	{
		heap[index].swap(heap[(index - 1) / 2]);
		index = (index - 1) / 2;
	}
}
