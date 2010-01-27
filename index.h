#ifndef INDEX_H
#define INDEX_H

#include <map>
#include <vector>

#include <boost/shared_ptr.hpp>


class InvertedIndex
{
public:
	
	typedef long row_num;
	typedef long key;
	typedef std::vector<row_num> row_num_list;
	typedef std::vector<key> key_list;
	typedef std::map<key, row_num_list> index_type;


	InvertedIndex();

	virtual ~InvertedIndex(){}

	void add(key k, row_num r);
	
	row_num_list get(key k);

	bool remove(key k, row_num r);

	key_list keys();

private:

	index_type index;
	

};

typedef boost::shared_ptr<InvertedIndex> IndexPtr;

#endif // INDEX_H
