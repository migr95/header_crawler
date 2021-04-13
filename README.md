# header_crawler

Littel tool to generate a graph of include hierarchies using dot.

Creates a graph in PostScript which displays the include hirachy as tree-diagram starting from a specified file. 
E.g. for this repository starting at "src/header_crawler.cpp" it produces:

![header_crawler example result](imgs/headers.jpg)

## Requirements

For generating the graphs, _dot_ from Graphviz is needed. Install from [here](https://graphviz.org/download/) or by using:

	sudo apt install graphviz

## Build

Build with

	make
	
To remove build, call

	make clean
