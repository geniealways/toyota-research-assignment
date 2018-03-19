#include "MinHeap.h"
using namespace std;
MinHeap :: MinHeap (int s, bool checkUnique): size(s), checkUniqueness(checkUnique) 
{
}

void MinHeap :: push (pair<long, int> pairVal){
	int val = pairVal.second;
	long id = pairVal.first;
	if (checkUniqueness && !(checkUnique.empty()) && (checkUnique.find(id) != checkUnique.end())){
		cout <<"**MINHEAP Val "<<id<<" is duplicate for num "<<val<<endl;
		return; 
	}
	if ((minpq.size() == size) ){
		if (val < minpq.top().second){
			return;
		}
		minpq.pop();
		minpq.push(pairVal);
		if (checkUniqueness){
		cout <<"**MINHEAP uniqueset "<<id<<", "<<val<<endl;
			checkUnique.insert(id);
		}
	}
	else{
		minpq.push(pairVal);
		if (checkUniqueness){
		cout <<"**MINHEAP uniqueset "<<id<<" "<<val<<endl;
			checkUnique.insert(id);
		}

	}
		
}

vector<pair<long, int>> MinHeap :: getContents(){
	vector<pair<long, int>> result;
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
