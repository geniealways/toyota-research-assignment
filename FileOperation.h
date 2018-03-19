#ifndef FILEOPERATION_H
#define FILEOPERATION_H
#include <iostream>
#include <fstream> 
#include <string>
#include <stdlib.h>  
#include <time.h>
#include <set> 
#include "MinHeap.h"

class FileOperation
{
     private :
		//int fName;
     public :
		FileOperation();
		void create(int lines, std::string name, int nMax = 0);
};
 
#endif
