#include "GetLargest.h"

using namespace std;

GetLargest :: GetLargest(std::istream *istr, int kLargest, string name) : instream(istr), k(kLargest), heap(new MinHeap(k)), fileName(name) {
}

GetLargest :: ~GetLargest(){
	delete heap;
}

void GetLargest :: getResult(){
	if (k <= 0){
		cout <<"Nothing to return, put a positive k value\n";	
		return;
	}
	size_t fileSize = 0;
	int threadCount; 	
	if (!fileName.empty()){
		struct stat s;
		if (!(stat(fileName.c_str(), &s))){ 
			fileSize = s.st_size;	
		}
		threadCount = thread::hardware_concurrency();
		if (!threadCount || fileSize < threadCount)
		threadCount = 1;


	}
	/*when input is given as filename, we can find out filesize, blocksize, offset info to divide tasks into different threads that read the file from a different non overlapping blocks starting at different offsets solution.*/
	if (fileSize){
		//file size calculation for multi-threaded solution: applicable when input file path is given
		size_t blockSize = fileSize/threadCount; 
		size_t lastBlockSize = blockSize + (fileSize % blockSize);
		//cout << "File Size:"<<fileSize<< ", Block size: " << blockSize <<", Last Block Size: "<< lastBlockSize<< endl;	
		vector<streamoff> fileLocOffset;
		streamoff offset = ios::beg;
		bool isFirstThread = true;
		vector<thread> threads;
			
		for (int i = 0; i < threadCount; i++){
			size_t blockSizeLimit; 
			if (i == threadCount-1){
				thread t(&GetLargest::getResultThreaded, this, lastBlockSize, offset, isFirstThread, i);
				threads.push_back (move(t));
				threadResults.push_back(vector<pair<long, int>>(1, make_pair(-1, -1)));
				
			}
			else{				
				thread t(&GetLargest::getResultThreaded, this, lastBlockSize, offset, isFirstThread, i);
				threads.push_back (move(t));
				threadResults.push_back(vector<pair<long,int>>(1, make_pair(-1, -1)));
		
			}
			offset = offset + blockSize;
			isFirstThread = false;
		}
		for (vector<thread>::iterator it = threads.begin(); it != threads.end(); it++){
			it->join();
		}
		/* when using threads sometimes, we can get same record in two threads if the file offset falls in the middle of the line (the reason why for thread function, we make heap of k+1 elements. when we combine results of all threads, we set checkUniqueness to true, to ignore duplicates, if any. */ 
		bool checkUniqueId = true; 
		MinHeap minHeap(k, checkUniqueId);
		for (int i = 0; i < threadCount; i++){
			vector<pair<long, int>> v = threadResults[i];
			for (vector<pair<long,int>>::iterator it =  v.begin()+1; it != v.end(); it++ ){
				//cout<<"For thread"<<i<<", pushing: "<<(*it).first<<", "<<(*it).second<<"  to heap "<<endl;
				minHeap.push(*it);
			}
		}
		vector<pair<long,int>> contents = minHeap.getContents();
		cout <<"Ids for the "<<k<<" largest values are:\n";
		for (vector<pair<long,int>>::iterator it = contents.begin(); it != contents.end(); it++){
			cout<<it->first<<endl;
		}
		
	}
	
	/*when input is given as stdin, we dont have filename to know the filesize, blocksize info for threaded solution.*/
	else {
		string line;
  		while(getline(*instream, line)) {
			string id, num;
			std::stringstream ss(line);
			getline (ss, id, ' ');
			getline (ss, num,' ' );
			int numInt = stoi(num);
			long idInt = stoi(id); 
			heap->push(make_pair(idInt, numInt));
		}	
		vector<pair<long,int>> contents = heap->getContents();
		cout <<"Ids for the "<<k<<" largest values are:\n";
		for (vector<pair<long, int>>::iterator it = contents.begin(); it != contents.end(); it++)
			cout<<it->first<<endl;
		}
		

	
}

void GetLargest :: getResultThreaded(size_t blockSizeLimit, streamoff offset, bool isFirstThread, int i){
		std::ifstream inFile;
		inFile.open(fileName, ifstream::binary);
		istream *in = &inFile;
		stringstream r;
		//r << "\n**********In Threaded application: " << i  <<" Offset:" << offset << "***********\n";
		MinHeap *threadHeap = new MinHeap (k+1);
		int bytes = 0;
		in->seekg (offset,ios::beg );
		string line;
		if (!isFirstThread){ //discard the first line read(this may be a partial line), this has been taken care of in the previous thread where we read an extra line.
			getline (*in, line);
			bytes+= line.size();
			//r << "\n" << offset << "**discarding**:" << line << "\n";
		}
		while (getline (*in, line ) && bytes <= blockSizeLimit){
			//cout<<line<<"\n";
			string id, num;
			std::stringstream ss(line);
			getline (ss, id, ' ');
			getline (ss, num,' ' );
			int numInt = stoi(num);
			long idInt = stoi(id); 
			//r << "\npushing line : " << line << "\n";
			threadHeap->push(make_pair(idInt,numInt));
			bytes+= line.size() +1; //+1 for end of line char
		}
		//r << "Total Bytes:" << bytes<<"\n";
		vector<pair<long,int>> contents = threadHeap->getContents();
		for (vector<pair<long,int>>::iterator it = contents.begin(); it != contents.end(); it++){
			threadResults[i].push_back(*it);
			//r << "result Pushed " << (*it).second << " to ith vector:"<<i <<"\n";
		}
		//r << "\n*******END*******\n";
		//cout <<r.str();
		delete threadHeap;


}
