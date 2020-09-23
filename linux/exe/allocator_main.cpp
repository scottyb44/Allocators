#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../lib/Allocator.h"

void DoStdAllocStuff()
{
	// Examine regulator allocators provided by the standard
	std::vector<int, std::allocator<int>> stdVec;
	for (int i = 0; i < 10000; ++i)
	{
		stdVec.push_back(i);
	}
	std::cout << "stdVec size: " << stdVec.size() << std::endl;
	auto alloc = stdVec.get_allocator();
	alloc.deallocate(stdVec.data(), sizeof(int));
	// This is deallocated but what is in the memory is still there, since its deallocated when the 
	// vector is destroyed at the end of the scope there will be an exception when the destructor 
	// attempts to deallocate again
	std::cout << "stdVec size: " << stdVec.size() << std::endl;
}

int main()
{

//	DoStdAllocStuff();


	// Examine my allocator
	{
		std::vector<int, Allocator<int>> intVec;
		// Without the reserve we can clearly see the allocations and deallocations
		intVec.reserve(10);
		for (int i = 0; i < 10; ++i)
		{
			intVec.insert(std::end(intVec), i);
		}
		std::cout << "Full memory usage vector: " << global_memory_used.load() << std::endl;
	}

	{
		std::map<int, std::string, std::less<int>, Allocator<std::pair<const int, std::string>>> myMap;
		for (int i = 0; i < 10; ++i)
		{
			myMap[i] = "random string";
		}
		std::cout << "Full memory usage map: " << global_memory_used.load() << std::endl;
	}
}
