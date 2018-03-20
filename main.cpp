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
		cout <<"STDIN input use format: ./main stdin <k-value>\n";
	}
	/*For stdin inputs*/
	else if (strcmp(argv[1], "stdin") == 0){
		if ((argc < 3)){
			cout <<"STDIN input use format: ./main stdin <k-value>\n";
		}
		int k = atoi(argv[2]);
		in = &cin;
		GetLargest g(in, k);
		return g.getResult();  

	}
	/*For test files creation*/
	else if (strcmp(argv[1], "createTestFile") == 0){
		if ((argc < 5)){
		cout <<"create test command format: ./main createTestFile <num-of-lines> <name-of-file> <k-value for heap> <randomized ids>\n";
		return 1;
		}
		bool randomizeUniqueIds = true;	
		if (argc == 6 && (strcmp(argv[5], "false") == 0))  
		randomizeUniqueIds = false;	
		f.create (atoi(argv[2]), argv[3], atoi(argv[4]), randomizeUniqueIds);
	}
	/*for filepath inputs- this solution uses multi-threads*/
	else {
		if ((argc < 3)){
			cout <<"Create test/expected-result file format: ./main createTestFile <num-of-lines> <required-test-file-name> <k-value for heap>\n";
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
		int k = atoi(argv[2]);
		GetLargest g(in, k, fileName );
		return g.getResult();  

	}


	return 0;
}
