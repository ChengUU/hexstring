#include "hex_tool.hpp"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main()
{
	const char* str = "abc hello";
	string hexString;
	bytesToHex(str, hexString, false);
	cout << str << " = 0x" << hexString << endl;
	string str1;
	hexToBytes(hexString.c_str(), str1);
	cout << "0x" << hexString << " = " << str1 << endl;
	//
	const char* hexString1 = "55AA001122AA55";
	vector<char> itemBytes;
	hexToBytes(hexString1, itemBytes);
	string hexString2;
	bytesToHex(itemBytes, hexString2);
	cout << "0x" << hexString1 << endl;
	cout << "0x" << hexString2 << endl;
	//
	const char* longStr = "hello world this is a long string test";
	string longStrDebug;
	bytesToHexDebug(longStr, longStrDebug);
	cout << longStr << endl;
	cout << longStrDebug << endl;
	cin.get();
	return 0;
}

