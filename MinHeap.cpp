#include "MinHeap.h"
using namespace std;
MinHeap :: MinHeap (int s): size(s) 
{
}

void MinHeap :: push (int val){
	if ((minpq.size() == size) ){
		if (val < minpq.top()){
			return;
		}
		minpq.pop();
		minpq.push(val);
	}
	else{
		minpq.push(val);
	}
		
}

vector<int> MinHeap :: getContents(){
	vector<int> result;
	while (!minpq.empty()){
		result.push_back(minpq.top());
		minpq.pop();
	}
	return result;
}

/*template<class T>
MinHeap<int> :: MinHeap (int s): size(s)
{
}
template <class T>
void MinHeap<T> :: push (T val){
	if (minpq.size() == size){
		minpq.pop();
		minpq.push(val);
	}
	else{
		minpq.push(val);
	}
		
}

template <class T>
vector<T> MinHeap<T> :: getContents(){
	vector<T> result;
	while (!minpq.empty()){
		result.push_back(minpq.top());
		minpq.pop();
	}
	return result;
}*/
