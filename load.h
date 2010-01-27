#ifndef LOAD_H
#define LOAD_H

//#include <stdlib.h>
#include <sys/types.h>
#include <string>
#include <vector>

#include "index.h"

// For smart pointers and resource management
#include <boost/shared_ptr.hpp>

typedef enum {
	RowRead,
	ColRead
} ReadingType;


/*
  Easy Resource management system
 */
class Table;
typedef boost::shared_ptr<Table> TablePtr;


/*
  Factory Loading class
 */
class TableFactory
{
public:

	static TablePtr loadFile(std::string fn, size_t w, size_t h, ReadingType rt=ColRead);

	static IndexPtr loadIndex(std::string fn);


	static std::vector<std::string> split(std::string line, std::string sep);
};


/*
  This is the classic table like structure to cover
  separate the data handling from the data structure. Since
  reading the data row or column wise is different on a single 
  array the reading type has to be given when creating an instance
  of this class.

  The constructor is private so that it can only be instantiated using the
  factory class.

 */
class Table 
{

	friend class TableFactory;

public:

	typedef long value_type;

	typedef long* ptr_type;
	

	virtual ~Table();

	void setData(ptr_type r);

	value_type at(size_t col, size_t row);
	
	void set(size_t col, size_t row, value_type val);

	void print();

private:

	Table(ReadingType t, size_t width, size_t height);

	ReadingType rt;

	ptr_type data;

	size_t width;

	size_t height;
};


#endif // LOAD_H
