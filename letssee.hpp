/*
   std_lib_facilities.h
*/

/*
	simple "Programming: Principles and Practice using C++ (second edition)" course header to
	be used for the first few weeks.
	It provides the most common standard headers (in the global namespace)
	and minimal exception/error support.
	Students: please don't try to understand the details of headers just yet.
	All will be explained. This header is primarily used so that you don't have
	to understand every concept all at once.
	By Chapter 10, you don't need this file and after Chapter 21, you'll understand it
	Revised April 25, 2010: simple_error() added
	
	Revised November 25 2013: remove support for pre-C++11 compilers, use C++11: <chrono>
	Revised November 28 2013: add a few container algorithms
	Revised June 8 2014: added #ifndef to workaround Microsoft C++11 weakness
*/

/*
    Copied from std_lib_facilities.h
*/

#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<list>
#include<forward_list>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<array>
#include<regex>
#include<random>
#include<stdexcept>

// error() simply disguises throws:
inline void error(const std::string& s)
{
	throw std::runtime_error(s);
}

inline void error(const std::string& s, const std::string& s2)
{
	error(s+s2);
}

inline void error(const std::string& s, int i)
{
	std::ostringstream os;
	os << s <<": " << i;
	error(os.str());
}

inline void keep_window_open_exit()
{
	std::cin.clear();
	std::cout << "Please enter a character to exit\n";
    char c = char(32);
	char* ch = &c;
	std::cin.std::istream::get(ch, 2);
	return;
}

inline void keep_window_open_cont() {
    std::cin.clear();
	std::cout << "Please enter any character to continue:\n";
    char c = char(32);
	char* ch = &c;
	std::cin.std::istream::get(ch, 2);
	return;
}

inline void keep_window_open(std::string s)
{
	if (s=="") return;
	std::cin.clear();
	std::cin.ignore(120,'\n');
	for (;;) {
		std::cout << "Please enter " << s << " to exit\n";
		std::string ss;
		while (std::cin >> ss && ss!=s)
			std::cout << "Please enter " << s << " to exit\n";
		return;
	}
}