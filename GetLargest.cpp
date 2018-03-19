#include "GetLargest.h"

using namespace std;

GetLargest :: GetLargest(std::istream *instream, int kLargest, size_t size) : in(instream), k(kLargest), heap(new MinHeap(k)), fileSize(size) {
}

GetLargest :: ~GetLargest(){
	delete heap;
}

void GetLargest :: getResult(){

	if (fileSize){
		int threadCount =4 ;
		size_t blockSize = fileSize/threadCount; 
		size_t lastBlockSize = blockSize + (fileSize % blockSize);
		cout << "File Size:"<<fileSize<< ", Block size: " << blockSize <<", Last Block Size: "<< lastBlockSize<< endl;	
		vector<streamoff> fileLocOffset;
		streamoff offset = ios::beg;
		bool isFirstThread = true;
		vector<thread> threads;
		
		for (int i = 0; i < threadCount; i++){
			size_t blockSizeLimit; 
			if (i == threadCount-1){
				thread t(&GetLargest::getResultThreaded, this, lastBlockSize, offset, isFirstThread, i);
				threads.push_back (move(t));
				threadResults.push_back(vector<int>(1, -1));
				//getResultThreaded(lastBlockSize, offset, isFirstThread);

			}
			else{				
				thread t(&GetLargest::getResultThreaded, this, lastBlockSize, offset, isFirstThread, i);
				threads.push_back (move(t));
				threadResults.push_back(vector<int>(1, -1));
				//getResultThreaded(blockSize, offset, isFirstThread);
			
			}

			offset = offset + blockSize;
			isFirstThread = false;
		}
		for (vector<thread>::iterator it = threads.begin(); it != threads.end(); it++){
			it->join();

		}
		MinHeap *minHeap = new MinHeap (k);
		for (int i = 0; i < threadCount; i++){
			vector<int> v = threadResults[i];
			for (vector<int>::iterator it =  v.begin()+1; it != v.end(); it++ ){
			cout<<"pushing: "<<*it<<" to heap "<<endl;
			minHeap->push(*it);
			}
		}
		vector<int> contents = minHeap->getContents();
		for (vector<int>::iterator it = contents.begin(); it != contents.end(); it++)
			cout<<*it<<" ";
		cout<<endl; 
		
		}

	else {	
		/*string line;
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
		*/

}}

void GetLargest :: getResultThreaded(size_t blockSizeLimit, streamoff offset, bool isFirstThread, int i){
		cout <<"In Threaded application: "<<i<<"\n";
		MinHeap *minHeap = new MinHeap (k);
		int bytes = 0;
		in->seekg (offset,ios::beg );
		string line;
		if (!isFirstThread){ //discard the first line read(this may be a partial line), this has been taken care of in the previous thread where we read an extra line.
			getline (*in, line);
			bytes+= line.size();
			cout <<"\noffset: "<<offset<<"**discarding"<<line<<"***\n";
		}
		while (getline (*in, line ) && bytes <= blockSizeLimit){
			cout<<line<<"\n";
			string id, num;
			std::stringstream ss(line);
			getline (ss, id, ' ');
			getline (ss, num,' ' );
			int numInt = stoi (num);
			minHeap->push(numInt);
			bytes+= line.size() +1; //1 for endof line char
		}
		cout<<endl<<"Bytes:"<<bytes<<"\n";
		vector<int> contents = minHeap->getContents();
		for (vector<int>::iterator it = contents.begin(); it != contents.end(); it++){
			threadResults[i].push_back(*it);
			cout <<"Pushed "<<*it<<" to ith vector:"<<i<<endl;
		}
		delete minHeap;


}
