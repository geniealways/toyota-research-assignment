#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "GetLargest.h"
#include "FileOperation.h"

using namespace std;

int main(int argc, char* argv[]) {
	FileOperation f;
	//f.create(10, "test", 3);
	std::istream *in;
	std::ifstream inFile;
	string fileName;
	if (argc <= 1){
		in = &cin;
	}
	else if (strcmp(argv[1], "createTestFile") == 0){
		if ((argc < 5)){
		cout <<"create test command format: ./main -createTestFile <num-of-lines> <name-of-file> <k-value for heap>\n";
		return 1;
		}
		bool randomizeUniqueIds = true;	
		if (argc == 6 && (strcmp(argv[5], "false") == 0))  
		randomizeUniqueIds = false;	
		f.create (atoi(argv[2]), argv[3], atoi(argv[4]), randomizeUniqueIds);
	}
	else {
		if ((argc < 3)){
			cout <<"Create test/expected-result file format: ./main -createTestFile <num-of-lines> <required-test-file-name> <k-value for heap>\n";
			cout <<"Find ids associated with k largest num: ./main <file-name> <k> \n";
			return 1;

		}

		fileName = argv[1];
		inFile.open(fileName, ifstream::binary);         
	        if (inFile.is_open()) {
			in = (&inFile);
	        }
		else{
			cout<< "Unable to open File:" << fileName <<":" << endl;
			return 1;
		}
		GetLargest g(in, atoi(argv[2]), fileName );
		g.getResult();  

	}


	return 0;
}
