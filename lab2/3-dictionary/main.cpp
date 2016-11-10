#include "stdafx.h"
#include "3-dictionary.h"

int main(int argv, char * argc[])
{
	std::multimap <std::string, std::string> dictionary;

	dictionary.emplace("cat", "кошка");
	dictionary.emplace("cat", "кот");

	std::multimap<std::string, float> mymultimap;

	mymultimap.emplace("apple", 1.50);
	mymultimap.emplace("coffee", 2.10);
	mymultimap.emplace("apple", 1.40);

	std::cout << "mymultimap contains:";
	for (auto &x : mymultimap) {
		std::cout << " [" << x.first << ":" << x.second << "]";
	}
	std::cout << std::endl;

	ConsoleInteraction();

	std::multimap<char, int> mymm;

	mymm.insert(std::pair<char, int>('a', 10));
	mymm.insert(std::pair<char, int>('b', 20));
	mymm.insert(std::pair<char, int>('b', 30));
	mymm.insert(std::pair<char, int>('b', 40));
	mymm.insert(std::pair<char, int>('c', 50));
	mymm.insert(std::pair<char, int>('c', 60));
	mymm.insert(std::pair<char, int>('d', 60));

	std::cout << "mymm contains:\n";
	for (char ch = 'a'; ch <= 'd'; ch++)
	{
		std::pair <std::multimap<char, int>::iterator, std::multimap<char, int>::iterator> ret;
		ret = mymm.equal_range(ch);
		std::cout << ch << " =>";
		for (std::multimap<char, int>::iterator it = ret.first; it != ret.second; ++it)
			std::cout << ' ' << it->second;
		std::cout << '\n';
	}

	return 0;
}