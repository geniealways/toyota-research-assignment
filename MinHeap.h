#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream>
#include <queue>  
#include <vector>
#include <utility> 
#include <set>

struct Order
{
    bool operator() (std::pair<long, int> a, std::pair<long, int> b)
    {
        return (a.second > b.second); 
    }
};

class MinHeap
{
     private:
		int size;
		std::priority_queue <std::pair<long, int>, std::vector<std::pair<long, int>>, Order > minpq;
		bool checkUniqueness;
		std::set<long> checkUnique; // when using threads sometimes, we can get same record in two threads if the file offset falls in the middle of the line (the reason why for thread function, we make heap of k+1 elements.when we combine results of all threads, we set checkUniqueness to true and use this set for that.  

     public:
		MinHeap(int size, bool checkUnique = false);
		void push(std::pair<long, int> val);
		std::vector<std::pair<long, int>> getContents(); 
		//void push(T val);
		//std::vector<T> getContents(); 
};
 
#endif
