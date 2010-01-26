#include <iostream>
#include <string>
#include <boost/lexical_cast

#include "load.h"
#include "trace.h"



int main(int argc, char** argv)
{
	
	if (argc < 4)
	{
		std::cout << "usage:\tmain [filename] [width] [height]" << std::endl;
		return -1;
	}
	
	// Laod the data
	std::string fn(argv[1]);
	std::cout << "Loading file: " << fn << std::endl;

	size_t w = 

	// Measure the loading time
	Tracer trc;
	TablePtr table = TableFactory::loadFile(fn, 3, 3, ColRead);
	Tracer::res_t tmp = trc();

	std::cout << "Loaded table in (us): " << tmp << std::endl;

	table->print();


	

	std::cout << "Finished..." << std::endl;
}
