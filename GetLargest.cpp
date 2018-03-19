#include "GetLargest.h"
#include <sstream>
#include <string>
#include <string.h> 
using namespace std;

GetLargest :: GetLargest(std::istream *instream, int k, size_t size) : in(instream), heap(new MinHeap(k)), fileSize(size)
{
}
GetLargest :: ~GetLargest()
{
delete heap;
}

void GetLargest :: getResult(){

	if (fileSize)
	getResultThreaded();
	string line;
  	while(getline(*in, line)) {
    	cout<<line<<endl;
		string id, num;
		std::stringstream ss(line);
		getline (ss, id, ' ');
		getline (ss, num,' ' );
		int numInt = stoi (num);
		heap->push(numInt);
	//cout<<"."<<id <<"."<<num <<"."<<endl;
	}	
	vector<int> contents = heap->getContents();
	for (vector<int>::iterator it = contents.begin(); it != contents.end(); it++)
	cout<<*it<<" ";
	cout<<endl; 


}

void GetLargest :: getResultThreaded(){
	cout <<"In Threaded application\n";
	int threadCount = 4;
	
	size_t blockSize = fileSize/threadCount; 
	size_t lastBlockSize = blockSize + (fileSize % blockSize);
	cout << "Block size1: " << blockSize << endl;	
	char *str = new char [blockSize+1];
	while(threadCount > 0) {
                memset(str, 0, blockSize+1);
		in->read(str, blockSize);
		cout <<"read: "<<str<<endl;
		threadCount--; 
		if (threadCount ==1){
		blockSize = lastBlockSize;
		delete str;
		str = new char [blockSize];
		}

	}
	delete str;
	cout << "Block size: " << blockSize << endl;
}
