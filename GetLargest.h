#ifndef GETLARGEST_H
#define GETLARGEST_H
#include <iostream>
#include <fstream> 
#include <string>
#include <stdlib.h>  
#include <sstream>
#include <string>
#include <thread>
#include <sys/stat.h>
#include "MinHeap.h"

class GetLargest
{
     private :
		std::istream *instream;
		int k;
		std::string fileName;
		std::vector<std::vector<std::pair<long, int>>> threadResults;
     public :
		GetLargest(std::istream *input, int k, std::string fileName = "");
		int getResult();
		int getResultThreaded(size_t blocksize, std::streamoff offset, bool isFirstThread, int i);

};
 
#endif
