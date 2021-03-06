#include "MinHeap.h"
using namespace std;
MinHeap :: MinHeap (int s, bool checkUnique): size(s), checkUniqueness(checkUnique) 
{
}

void MinHeap :: push (pair<long, int> pairVal){
	int val = pairVal.second;
	long id = pairVal.first;
	if (checkUniqueness && !(checkUnique.empty()) && (checkUnique.find(id) != checkUnique.end())){
		return; 
	}
	if ((minpq.size() == size) ){
		if (val < minpq.top().second){
			return;
		}
		minpq.pop();
		minpq.push(pairVal);
	}
	else {
		minpq.push(pairVal);
	}
	if (checkUniqueness){
		checkUnique.insert(id);
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


