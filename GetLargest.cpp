#include "GetLargest.h"

using namespace std;

GetLargest :: GetLargest(std::istream *instream, int k, size_t size) : in(instream), heap(new MinHeap(k)), fileSize(size) {
}

GetLargest :: ~GetLargest(){
	delete heap;
}

void GetLargest :: getResult(){

	if (fileSize){
		int threadCount = 4;
		size_t blockSize = fileSize/threadCount; 
		size_t lastBlockSize = blockSize + (fileSize % blockSize);
		cout << "File Size:"<<fileSize<< ", Block size: " << blockSize <<", Last Block Size: "<< lastBlockSize<< endl;	
		vector<streamoff> fileLocOffset;
		streamoff offset = ios::beg;
		bool isFirstThread = true;
		for (int i = 0; i < threadCount; i++){
			size_t blockSizeLimit; 
			if (i == threadCount-1){
				getResultThreaded(lastBlockSize, offset, isFirstThread);

			}
			else{
				getResultThreaded(blockSize, offset, isFirstThread);
			
			}

			offset = offset + blockSize;
			isFirstThread = false;
		}

		}

	else {
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


}

void GetLargest :: getResultThreaded(size_t blockSizeLimit, streamoff offset, bool isFirstThread){
		cout <<"In Threaded application\n";
		int bytes = 0;
		in->seekg (offset,ios::beg );
		string line;
		if (!isFirstThread){ //discard the first line read(this may be a partial line), this has been taken care of in the previous thread where we read an extra line.
			getline (*in, line);
			bytes+= line.size();
			cout <<"\noffset: "<<offset<<"**discarding"<<line<<"***\n";
		}
		while (getline (*in, line ) && bytes <= blockSizeLimit){
			cout<<line<<".";
			bytes+= line.size() +1; //1 for endof line char
		}
		cout<<endl<<"Bytes:"<<bytes<<"\n";

}
