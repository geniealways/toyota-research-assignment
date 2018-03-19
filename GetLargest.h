#ifndef GETLARGEST_H
#define GETLARGEST_H
#include <iostream>
#include <fstream> 
#include <string>
#include <stdlib.h>  
#include <time.h>
#include <set> 
#include "MinHeap.h"

class GetLargest
{
     private :
		MinHeap *heap;
		std::istream *in;
		size_t fileSize;
     public :
		GetLargest(std::istream *input, int k, size_t fileSize = 0);
		~GetLargest();
		void getResult();
		void getResultThreaded();
};
 
#endif
