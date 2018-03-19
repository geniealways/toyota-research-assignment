#ifndef GETLARGEST_H
#define GETLARGEST_H
#include <iostream>
#include <fstream> 
#include <string>
#include <stdlib.h>  
#include <sstream>
#include <string>
#include <thread>
#include "MinHeap.h"

class GetLargest
{
     private :
		MinHeap *heap;
		std::istream *in;
		size_t fileSize;
		int k;
		std::vector<std::vector<int>> threadResults;
     public :
		GetLargest(std::istream *input, int k, size_t fileSize = 0);
		~GetLargest();
		void getResult();
		void getResultThreaded(size_t blocksize, std::streamoff offset, bool isFirstThread, int i);

};
 
#endif
