CFLAGS = -std=c++11 -O3

.PHONY: all

all: main

main: optimized/MemoryManager.o optimized/Algorithm.o optimized/Tools.o optimized/DegeneracyTools.o optimized/DegeneracyAlgorithm.o optimized/EnuBundle.o main.cpp
	g++ optimized/MemoryManager.o optimized/Algorithm.o optimized/Tools.o optimized/DegeneracyTools.o optimized/DegeneracyAlgorithm.o optimized/EnuBundle.o main.cpp $(CFLAGS) -o main

optimized/MemoryManager.o: quick-cliques/MemoryManager.cpp quick-cliques/MemoryManager.h
	g++ quick-cliques/MemoryManager.cpp -Winline -O2 -std=c++11 -g -DALLOW_ALLOC_ZERO_BYTES -c -o optimized/MemoryManager.o

optimized/Algorithm.o: quick-cliques/Algorithm.cpp quick-cliques/Algorithm.h
	g++ quick-cliques/Algorithm.cpp -Winline -O2 -std=c++11 -g -DALLOW_ALLOC_ZERO_BYTES -c -o optimized/Algorithm.o

optimized/Tools.o: quick-cliques/Tools.cpp quick-cliques/Tools.h
	g++ quick-cliques/Tools.cpp -Winline -O2 -std=c++11 -g -DALLOW_ALLOC_ZERO_BYTES -c -o optimized/Tools.o

optimized/DegeneracyTools.o: quick-cliques/DegeneracyTools.cpp quick-cliques/DegeneracyTools.h
	g++ quick-cliques/DegeneracyTools.cpp -Winline -O2 -std=c++11 -g -DALLOW_ALLOC_ZERO_BYTES -c -o optimized/DegeneracyTools.o

optimized/DegeneracyAlgorithm.o: quick-cliques/DegeneracyAlgorithm.cpp quick-cliques/DegeneracyAlgorithm.h
	g++ quick-cliques/DegeneracyAlgorithm.cpp -Winline -O2 -std=c++11 -g -DALLOW_ALLOC_ZERO_BYTES -c -o optimized/DegeneracyAlgorithm.o

optimized/EnuBundle.o: EnuBundle.cpp EnuBundle.h
	g++ EnuBundle.cpp $(CFLAGS) -Wall -c -o optimized/EnuBundle.o


