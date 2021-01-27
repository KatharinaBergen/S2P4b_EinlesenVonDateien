#include <exception>
#include <iostream>
#include <map>
using std::map;
#include <string>
#include <fstream>
using std::string;
using std::ifstream;
using std::cout;
using std::cin;
#include "Testfunctions.h"

int main() try
{
	//container
	map<string, int> words{};

	//open infile
	string nameIn{ "p4a2.txt" };
	ifstream infile{ nameIn.c_str() };
	if (!infile) throw std::runtime_error("Kein Lesezugriff auf Datei");

	std::istream_iterator<string> in{ infile };
	std::istream_iterator<string> eof{};
	string word{};
	string i{};
	
	while (in != eof) {
		word = *in;
		++in;
		if (in == eof) break;
		i = *in;
		++in;
		words[word] = stoi( i );
	}

	checkEquals("#!comment:", words.cbegin()->first, "Test input beginning string");
	checkEquals(1015, words.cbegin()->second, "Test input beginning count");

	//print optionally on screen
	char c{};
	cout << "Would you like to print the words on the screen? Answer 'y' for 'yes' or 'n' for 'no'.\n>";
	cin >> c;
	if (!cin) { throw std::runtime_error{ "incorrect input at cin in main()" }; }
	if (c == 'y')
	{
		using citer = map<string, int>::const_iterator;
		for (citer p{ words.cbegin() }; p != words.cend(); ++p)
			cout << p->first << ':' << p->second << '\n';
	}

	return 0;
}
catch (const std::exception& e)
{
	std::cerr << e.what();
	return -1;
}
catch (...)
{
	std::cerr << "unknown error";
	return -2;
}