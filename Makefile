CXX := g++
source := src/dot_writer.cpp src/header_crawler.cpp
LIBS := -lstdc++fs

all:
	mkdir -p bin
	$(CXX) $(source) -o bin/header_crawler $(LIBS)
	
clean:
	rm -r bin
