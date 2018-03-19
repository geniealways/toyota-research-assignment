#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "GetLargest.h"
#include "FileOperation.h"
#include <sys/stat.h>
using namespace std;

int main(int argc, char* argv[]) {
	FileOperation f;
	f.create(10, "test", 3);
	std::istream *in;
	std::ifstream inFile;
	if (argc <= 1){
		in = &cin;
	}
	else {
		inFile.open(argv[1], ifstream::binary);         
	        if (inFile.is_open()) {
			in = (&inFile);
	        }
		else{
			cout<< "Unable to open File:" << argv[1] <<":" << endl;
			exit (EXIT_FAILURE);
		}
	}
	//file size calculation for multi-threaded solution: applicable when input file path is given
	struct stat s;
	size_t fileSize = 0;
	if ((argc > 1) && !(stat(argv[1], &s))){ 
		fileSize = s.st_size;	
	}

	GetLargest g(in, 3, fileSize);
	g.getResult();  

	return 0;
}
