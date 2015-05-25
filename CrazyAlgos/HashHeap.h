#include <vector>
#include "GeneralHashFunctions.h"

template<typename T>
class HashHeap //Note the heap must have a string() operator conversion
{
	protected:
		std::vector<std::vector<T>> heap;
	public:
		HashHeap(){};
		HashHeap<T>(std::vector<T> inp)
		{
			unsigned int index = 0;
			for(int i = 0; i < inp.size(); ++i)
			{
				index = APHash(reinterpret_cast<std::string>(inp[i]));
				heap[index].push_back(inp[i]);
			}
		}
};