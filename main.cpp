#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>

#include "table.h"
#include "trace.h"



int main(int argc, char** argv)
{
	
	if (argc < 4)
	{
		std::cout << "usage:\tmain [filename] [num_cols] [num_rows] [idx]" << std::endl;
		return -1;
	}
	
	// Laod the data
	std::string fn(argv[1]);
	std::cout << "Loading file: " << fn << std::endl;

	size_t c = boost::lexical_cast<size_t>(argv[2]);
	size_t r = boost::lexical_cast<size_t>(argv[3]);

	// Measure the loading time
	Tracer trc;
	TablePtr table = TableFactory::loadFile(fn, c, r, ColRead);
	Tracer::res_t tmp = trc();

	std::cout << "Loaded table in (us): " << tmp << std::endl;


	// Load the inverted index
	if (argc == 5)
	{
		trc.restart();
		IndexPtr idx = TableFactory::loadIndex(argv[4]);
		tmp = trc();

		std::cout << "Loaded Index in (us): " << tmp << std::endl;


		// Make one simple test
		InvertedIndex::key_list keys = idx->keys();
		InvertedIndex::row_num_list rows=  idx->get(keys[0]);
		assert(table->at(0, rows[0]) == keys[0]);
	}


	
	//table->print();

	std::cout << "Finished..." << std::endl;
}
