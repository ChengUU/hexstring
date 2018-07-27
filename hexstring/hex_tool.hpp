#pragma once
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>

//char数组转换
inline void hexToBytes(const char * input, std::vector<char>& output);
inline void bytesToHex(const std::vector<char>::const_iterator& itBegin, const std::vector<char>::const_iterator& itEnd, std::string & output, bool upperCase = true);
inline void bytesToHex(const std::vector<char>& input, std::string & output, bool upperCase = true);
//c字符串转换
inline void hexToBytes(const char * input, std::string& output);
inline void bytesToHex(const char * input, std::string & output, bool upperCase = true);
//debug工具
inline void bytesToHexDebug(const std::vector<char>::const_iterator& rawBytesBegin, const std::vector<char>::const_iterator& rawBytesEnd, std::string& debugStr, std::size_t rowBytesCount = 16, bool upperCase = true);
inline void bytesToHexDebug(const std::vector<char>& rawBytes, std::string& debugStr, std::size_t rowBytesCount = 16, bool upperCase = true);
inline void bytesToHexDebug(const char * rawBytes, std::string& debugStr, std::size_t rowBytesCount = 16, bool upperCase = true);

//=================================================================

void hexToBytes(const char * input, std::vector<char>& output) {
	size_t leng = strlen(input);
	output.resize(2 * leng);
	output.clear();
	size_t outputIndex;
	for (size_t i = 0; i < leng; i++) {
		if (i % 2 == 0) {
			outputIndex = i / 2;
			output.emplace_back(input[i]);
		}
		else {
			outputIndex = (i - 1) / 2;
			output[outputIndex] += input[i];
		}
		if ((input[i] >= '0') && (input[i] <= '9')) {
			output[outputIndex] -= '0';
		}
		else if ((input[i] >= 'A') && (input[i] <= 'F')) {
			output[outputIndex] -= '7';
		}
		else if ((input[i] >= 'a') && (input[i] <= 'f')) {
			output[outputIndex] -= 'W';
		}
		else {
			//非16进制格式
			throw std::out_of_range("bad hex std::string format");
		}
		if (i % 2 == 0) {
			output[outputIndex] = output[outputIndex] << 4;
		}
	}
}
void hexToBytes(const char * input, std::string& output) {
	std::vector<char> charArr;
	hexToBytes(input, charArr);
	output.resize(charArr.size());
	output.clear();
	for (auto it = charArr.begin(); it != charArr.end(); it++) {
		output.append(1, *it);
	}
}

void bytesToHex(const std::vector<char>::const_iterator& itBegin, const std::vector<char>::const_iterator& itEnd, std::string & output, bool upperCase)
{
	size_t leng = static_cast<size_t>((itEnd - itBegin) * 2);
	output.resize(leng);
	output.clear();
	size_t inputIndex;
	unsigned char tmpChar;
	for (size_t i = 0; i < leng; i++) {
		if (i % 2 == 0) {
			//字符前4位
			inputIndex = i / 2;
			tmpChar = static_cast<unsigned char>(*(itBegin + inputIndex));
			tmpChar = tmpChar >> 4;
		}
		else {
			//字符后4位
			inputIndex = (i - 1) / 2;
			tmpChar = static_cast<unsigned char>(*(itBegin + inputIndex));
			tmpChar = tmpChar & 0xf;
		}
		if ((tmpChar >= 0) && (tmpChar <= 9)) {
			tmpChar += '0';
		}
		else {
			if (upperCase) {
				tmpChar += '7';
			}
			else {
				tmpChar += 'W';
			}
		}
		output.append(1, tmpChar);
	}
}

void bytesToHex(const std::vector<char>& input, std::string & output, bool upperCase) {
	bytesToHex(input.begin(), input.end(), output, upperCase);
}

void bytesToHex(const char * input, std::string & output, bool upperCase) {
	size_t inputLength = strlen(input);
	std::vector<char> inputArr(inputLength);
	inputArr.clear();
	for (size_t i = 0; i < inputLength; i++) {
		inputArr.emplace_back(input[i]);
	}
	bytesToHex(inputArr, output, upperCase);
}

//debug工具
void bytesToHexDebug(const std::vector<char>::const_iterator& rawBytesBegin, const std::vector<char>::const_iterator& rawBytesEnd, std::string& debugStr, std::size_t rowBytesCount, bool upperCase)
{
	std::string hexStr;
	bytesToHex(rawBytesBegin, rawBytesEnd, hexStr, upperCase);
	debugStr.clear();
	debugStr.append(rowBytesCount * 4, '=');
	std::string tmpStr;
	tmpStr.resize(rowBytesCount);
	unsigned char tmpChar;
	for (size_t i = 0; i < hexStr.length(); i++) {
		if (i % 2 == 0) {
			if (i % (rowBytesCount * 2) == 0) {
				if (i > 0) {
					debugStr.append(" ");
					debugStr.append(tmpStr);
				}
				tmpStr.clear();
				debugStr.append("\r\n");
			}
			else {
				debugStr.append(" ");
			}
			tmpChar = static_cast<unsigned char> (*(rawBytesBegin + i / 2));
			if ((tmpChar >= 0x20) && (tmpChar <= 0x7e)) {
				//可显示ascii字符范围
				tmpStr.append(1, tmpChar);
			}
			else {
				tmpStr.append(1, '*');
			}
		}
		debugStr.append(1, hexStr[i]);
	}
	if (hexStr.length() / 2 % rowBytesCount != 0) {
		//最后一行填充16进制空位
		debugStr.append(3 * (rowBytesCount - (hexStr.length() / 2 % rowBytesCount)), ' ');
	}
	debugStr.append(" ");
	debugStr.append(tmpStr);
	debugStr.append("\r\n");
	debugStr.append(rowBytesCount * 4, '=');
}
void bytesToHexDebug(const std::vector<char>& rawBytes, std::string& debugStr, size_t rowBytesCount, bool upperCase) {
	bytesToHexDebug(rawBytes.begin(), rawBytes.end(), debugStr, rowBytesCount, upperCase);
}

void bytesToHexDebug(const char * rawBytes, std::string& debugStr, size_t rowBytesCount, bool upperCase) {
	std::string hexStr;
	bytesToHex(rawBytes, hexStr, upperCase);
	debugStr.clear();
	debugStr.append(rowBytesCount * 4, '=');
	std::string tmpStr;
	tmpStr.resize(rowBytesCount);
	unsigned char tmpChar;
	for (size_t i = 0; i < hexStr.length(); i++) {
		if (i % 2 == 0) {
			if (i % (rowBytesCount * 2) == 0) {
				if (i > 0) {
					debugStr.append(" ");
					debugStr.append(tmpStr);
				}
				tmpStr.clear();
				debugStr.append("\r\n");
			}
			else {
				debugStr.append(" ");
			}
			tmpChar = (unsigned char)rawBytes[i / 2];
			if ((tmpChar >= 0x20) && (tmpChar <= 0x7e)) {
				//可显示ascii字符范围
				tmpStr.append(1, tmpChar);
			}
			else {
				tmpStr.append(1, '*');
			}
		}
		debugStr.append(1, hexStr[i]);
	}
	if (hexStr.length() / 2 % rowBytesCount != 0) {
		//最后一行填充16进制空位
		debugStr.append(3 * (rowBytesCount - (hexStr.length() / 2 % rowBytesCount)), ' ');
	}
	debugStr.append(" ");
	debugStr.append(tmpStr);
	debugStr.append("\r\n");
	debugStr.append(rowBytesCount * 4, '=');
}