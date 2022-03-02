#include "LRUCache.h"
#include <algorithm>

using namespace std;

LRUCache::LRUCache(int capacity)
{
	this->capacity = capacity;
}

vector<int> LRUCache::processRequests(vector<int> requestsNo)
{
	vector <int>::iterator i, j;
	vector <int> cache;
	int found = 0, aux = 0;

	for (i = requestsNo.begin(); i != requestsNo.end(); i++)
	{
		if (cache.size() == 0)
		{
			cache.push_back(*i);
		}
		else
		{
			found = 0;
			for (j = cache.begin(); j != cache.end(); j++)
			{
				if (*i == *j)
				{
					aux = *j;
					cache.erase(j);
					cache.push_back(aux);
					found = 1;
				}
			}
			if (found == 0)
			{
				if (cache.size() < capacity)
				{
					cache.push_back(*i);
				}
				else
				{	
					cache.push_back(*i);
					cache.erase(cache.begin());
				}
			}
		}	
	}

	vector<int>::reverse_iterator ir;

	for(ir = cache.rbegin(); ir != cache.rend(); ++ir)
		lru.push_back(*ir);

    size = lru.size();

    return lru;
}
int LRUCache::getCapacity()
{
	return capacity;
}

int LRUCache::getSize()
{
	return size;
}

vector<int> LRUCache::getLRU()
{
	return lru;
}

int LRUCache::getLRUCapacity()
{
	return lru.capacity();
}

void LRUCache::setCapacity(int capacity)
{
	this->capacity = capacity;
}

void LRUCache::setLRU(vector<int> aux)
{
	this->lru = aux;
}
