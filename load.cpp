#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "load.h"
#include <stdexcept>
#include <fstream>
#include <vector>
#include <iostream>


Table::Table(ReadingType t, size_t w, size_t h): rt(t), width(w), height(h)
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
		return *(data + col * height + row);
		break;
	case RowRead:
		return *(data + row * width + col);
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
		*(data + col * height + row) = val;
		break;
	case RowRead:
		*(data + row * width + col) = val;
		break;
	default:
		throw std::runtime_error("Reading type not supported");
	}
}

void Table::print()
{
	const size_t mw = 10;
	std::string tmp;

	tmp = "-";
	tmp.resize((10 + 3) * width + 2, '-');
	std::cout << tmp << std::endl;

	for(size_t r=0; r < height; ++r)
	{
		
		std::cout << "| ";
		for(size_t c=0; c < width; ++c)
		{
			std::cout << " ";
			tmp = boost::lexical_cast<std::string>(at(c,r));
			tmp.resize(mw, ' ');
			std::cout << tmp << " |";
		}

		std::cout << std::endl;
		tmp = "-";
		tmp.resize((10 + 3) * width + 2, '-');
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
