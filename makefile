CC=g++
CPPFLAGS=-std=c++11 -I.
DEPS = GetLargest.h MinHeap.h FileOperation.h 

%.o: %.c %.cpp $(DEPS)
	$(CC) -cpp -o $@ $< $(CPPFLAGS)

main: GetLargest.o main.o MinHeap.o FileOperation.o 
	g++ -o main main.o GetLargest.o MinHeap.o FileOperation.o -I.
clean:
	rm -f  *.o
