#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream>
#include <queue>  
#include <vector>


//template <class T>
class MinHeap
{
     private:
		int size;
		std::priority_queue <int, std::vector<int>, std::greater<int> > minpq;

     public:
		MinHeap(int size);
		void push(int val);
		std::vector<int> getContents(); 
		//void push(T val);
		//std::vector<T> getContents(); 
};
 
#endif
