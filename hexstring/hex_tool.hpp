#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;
//char����ת��
void hexToBytes(const char * input, vector<char>& output);
void bytesToHex(const vector<char>& input, string & output, bool upperCase = true);
//c�ַ���ת��
void hexToBytes(const char * input, string& output);
void bytesToHex(const char * input, string & output, bool upperCase = true);