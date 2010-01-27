#include "index.h"
#include <algorithm>

InvertedIndex::InvertedIndex()
{
}

void InvertedIndex::add(key k, row_num r)
{
	if (index[k].size() == 0)
		index[k].push_back(r);

	

	if (std::find(index[k].begin(), index[k].end(), r) != index[k].end())
	{
		index[k].push_back(r);
	}
}

bool InvertedIndex::remove(key k, row_num r)
{

	if (index[k].size() == 0)
		return false;

	
	row_num_list::iterator p = std::find(index[k].begin(), index[k].end(), r);
	if (index[k].end() != p)
	{
		index[k].erase(p);
		return true;
	}

	return false;
}

InvertedIndex::row_num_list InvertedIndex::get(key k)
{
	return index[k];
}

InvertedIndex::key_list InvertedIndex::keys()
{
	key_list r;
	index_type::iterator i = index.begin();
	while(i != index.end())
	{
		r.push_back((*i).first);
		++i;
	}
	return r;
}
