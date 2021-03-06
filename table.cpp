#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "table.h"
#include <stdexcept>
#include <fstream>
#include <vector>
#include <iostream>


Table::Table(ReadingType t, size_t c, size_t r): rt(t), cols(c), rows(r)
{
}

Table::~Table()
{
	free(data);
}

void Table::setData(Table::ptr_type r)
{
	data = r;
}

Table::value_type Table::at(size_t col, size_t row)
{
	switch(rt)
	{
	case ColRead:
		return *(data + col * rows + row);
		break;
	case RowRead:
		return *(data + row * cols + col);
		break;
	default:
		throw std::runtime_error("Reading type not supported");
	}
}

void Table::set(size_t col, size_t row, Table::value_type val)
{
	switch(rt)
	{
	case ColRead:
		*(data + col * rows + row) = val;
		break;
	case RowRead:
		*(data + row * cols + col) = val;
		break;
	default:
		throw std::runtime_error("Reading type not supported");
	}
}

void Table::print()
{
	const size_t mw = 7;
	std::string tmp;

	tmp = "-";
	tmp.resize((10 + 3) * cols + 2, '-');
	std::cout << tmp << std::endl;

	for(size_t r=0; r < rows; ++r)
	{
		
		std::cout << "| ";
		for(size_t c=0; c < cols; ++c)
		{
			std::cout << " ";
			tmp = boost::lexical_cast<std::string>(at(c,r));
			tmp.resize(mw, ' ');
			std::cout << tmp << " |";
		}

		std::cout << std::endl;
		tmp = "-";
		tmp.resize((10 + 3) * cols + 2, '-');
		std::cout << tmp << std::endl;
	}
}


std::vector<std::string> TableFactory::split(std::string line, std::string sep)
{
	std::vector<std::string> result;
	boost::split(result, line, boost::is_any_of(sep));
	return result;
}

#define SEP_CHAR "|"

TablePtr TableFactory::loadFile(std::string fn, size_t w, size_t h, ReadingType rt)
{
	std::ifstream data_file(fn.c_str());
	std::string line;

	// Create the table
	TablePtr p(new Table(rt, w, h));

	// Allocate the memory and pass it to the table
	Table::ptr_type d = (Table::ptr_type) calloc(w * h, sizeof(Table::value_type));
	p->setData(d);

	size_t r = 0;
	while(std::getline(data_file, line))
	{
		std::vector<std::string> splitted = split(line, SEP_CHAR);
		for(size_t i=0; i < splitted.size(); ++i)
		{
			boost::trim(splitted[i]);
			p->set(i, r, boost::lexical_cast<Table::value_type>(splitted[i]));
		}

		++r;
	}
	
	return p;
}


IndexPtr TableFactory::loadIndex(std::string fn)
{
	std::ifstream data_file(fn.c_str());
	std::string line;

	IndexPtr p(new InvertedIndex());

	while( std::getline(data_file, line) )
	{
		std::vector<std::string> splitted = split(line, SEP_CHAR);
		boost::trim(splitted[0]);

		Table::value_type key = boost::lexical_cast<Table::value_type>(splitted[0]);

		// The second part must be splitted again
		std::vector<std::string> rows = split(splitted[1], ",");
		BOOST_FOREACH(std::string r, rows)
		{
			boost::trim(r);
			Table::value_type v = boost::lexical_cast<Table::value_type>(r);

			p->add(key, v);
		}

	}

	return p;
}
