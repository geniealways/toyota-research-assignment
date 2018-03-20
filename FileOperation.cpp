#include "FileOperation.h"
using namespace std;

FileOperation :: FileOperation(){
}

void FileOperation :: create (int lines, string name, int nMax, bool randomizeIds){
	//cout<<"num of lines: "<<lines<<" name of file: "<<name<<" nMax: "<<nMax<<endl;
	if (!randomizeIds)
	cout<<"randomize unset\n";
	ofstream file;
	file.open (name.c_str());
	MinHeap *heap = new MinHeap(nMax);
	set<long> checkUnique;
	srand (time(NULL));
	int num;
	long id = 0;
	long span = 500000000; 	long min = 1000000000;
	if (lines > span){
		cout<<"Test File Create WARNING: Adding unique ids sequentially due to large line count\n ";
		randomizeIds = false;
	}

	while (lines > 0){ 
		num = rand() % lines + 1;
		if (randomizeIds){
		bool found = false;
			while (!found){
				id = min + (rand() * span) / RAND_MAX; //will generate num between 1000000000 and 1500000000
				if (checkUnique.find(id) == checkUnique.end()){
					found = true;
					checkUnique.insert(id);
				}
			}
		}
		else{
			id = id+1;
		}
		file << id <<" "<<num<<endl;
		if (nMax){
			heap->push(make_pair(id, num));
		}
		lines--; 
	}
	if (nMax){
		string resultFile = name + "_expected";
		cout<<"Adding expected result in file: "<<resultFile<<endl;
		ofstream fileRes;
		fileRes.open(resultFile.c_str());
		vector<pair<long, int>> contents = heap->getContents();
		for (vector<pair<long,int>>::iterator it = contents.begin(); it != contents.end(); it++)
		fileRes<<it->first <<" "<< it->second<<endl;
		fileRes.close();
	}
	delete heap;
	file.close();

}
