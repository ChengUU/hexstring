#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;
//char数组转换
void hexToBytes(const char * input, vector<char>& output);
void bytesToHex(const vector<char>& input, string & output, bool upperCase = true);
//c字符串转换
void hexToBytes(const char * input, string& output);
void bytesToHex(const char * input, string & output, bool upperCase = true);