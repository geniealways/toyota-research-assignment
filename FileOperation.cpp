#include "FileOperation.h"
using namespace std;

FileOperation :: FileOperation(){
}

void FileOperation :: create (int lines, string name, int nMax){
	//cout<<"num of lines: "<<lines<<" name of file: "<<name<<" nMax: "<<nMax<<endl;
	ofstream file;
	file.open (name.c_str());
	MinHeap *heap = new MinHeap(nMax);
	set<long> checkUnique;
	srand (time(NULL));
	int num;
	long id;
	long span = 500000000; 	long min = 1000000000;
	if (lines > span)
		cout<<"File Create WARNING: can't find as many unique ids\n ";
	while (lines > 0){ 
		num = rand() % lines + 1;
		bool found = false;
		while (!found){
			id = min + (rand() * span) / RAND_MAX; //will generate num between 1000000000 and 1500000000
			if (checkUnique.find(id) == checkUnique.end()){
				found = true;
				checkUnique.insert(id);
			}
		}
		file << id <<" "<<num<<endl;
		if (nMax){
			//cout<<"pushing:" << num <<endl;
			heap->push(num);
			//cout<<"Done"<<endl;
		}
		lines--; 
	}
	if (nMax){
		vector<int> contents = heap->getContents();
		for (vector<int>::iterator it = contents.begin(); it != contents.end(); it++)
		cout<<*it<<" ";
		cout<<endl; 
	}
	delete heap;
	file.close();
}
