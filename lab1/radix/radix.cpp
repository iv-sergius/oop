#include <iostream>
#include <string>
#include <climits>
#include <stdio.h>

enum error {
 CONVERT_NO_ERROR,
 CONVERT_ERROR_EMPTY_STRING,
 CONVERT_ERROR_LONG_OVERFLOW,
 CONVERT_ERROR_LETTER_OUT_RANGE,
 CONVERT_ERROR_DIGIT_OUT_RANGE,
 CONVERT_ERROR_INCORRECT_BASE,
};

using namespace std;


char DigitToLetter(long digit, int radix, error & errorCode)
{
	errorCode = CONVERT_NO_ERROR;
	if (digit >= 0 && digit <= 9)
	{
		return (char)('0' + digit);
	}
	if (digit < radix && digit >= 10)
	{
		return (char)('A' - 10  + digit);
	}
	errorCode = CONVERT_ERROR_DIGIT_OUT_RANGE;
	return '\0';
}

long LetterToDigit(char letter, int radix, error & errorCode)
{
	errorCode = CONVERT_NO_ERROR;
	if (letter >= '0' && letter <= '9')
	{
		return (long)(letter - '0');
	}
	if (letter >= 'A' && letter < 'A' - 10 + radix)
	{
		return (long)(letter - 'A' + 10);
	}
	if (letter >= 'a' && letter < 'a' - 10 + radix)
	{
		return (long)(letter - 'a' + 10);
	}
	errorCode = CONVERT_ERROR_LETTER_OUT_RANGE;
	return 0;
}

long StringToLong(const string & str, int radix, error & errorCode)
{
	errorCode = CONVERT_NO_ERROR;
	unsigned long resultLong = 0;
	if (str.empty())
	{
		errorCode = CONVERT_ERROR_EMPTY_STRING;
		return 0;
	}
	unsigned int firstDigitPosition = (str[0] == '+' || str[0] == '-') ? 1 : 0;
	long sign = (str[0] == '-') ? -1 : 1;
	for (size_t i = firstDigitPosition; i < str.length(); ++i)
	{
		unsigned int digit = LetterToDigit(str[i], radix, errorCode);
		// check on limits
		if (resultLong <= (LONG_MAX - digit + firstDigitPosition) / radix)
		{
			resultLong = radix * resultLong + digit;
		}
		else
		{
			errorCode = CONVERT_ERROR_LONG_OVERFLOW;
			return 0;
		}
	}
	return (long) sign * resultLong;
}

string LongToString(const long number, int radix, error & errorCode)
{
	errorCode = CONVERT_NO_ERROR;
	string resultStr = "";
	bool isNegative = number < 0; // save sign of numbers
	unsigned long numberLocal = abs(number);
	error innerError = CONVERT_NO_ERROR;
	
	unsigned long remainder;
	do
	{
		remainder = numberLocal % radix;
		numberLocal = numberLocal / radix;
		char nextCh = DigitToLetter(remainder, radix, innerError);
		if (innerError != CONVERT_NO_ERROR)
		{
			errorCode = innerError;
			return "";
		}
		resultStr.push_back(nextCh);
	} while (numberLocal > 0);
/*
	unsigned long rest = numberLocal % radix; 
	numberLocal = numberLocal / radix;
	while (rest || numberLocal)
//	while (rest > 0 && numberLocal > 0)
	{
		innerError = CONVERT_NO_ERROR;
		char nextCh = DigitToLetter(rest, radix, innerError);
		if (innerError != CONVERT_NO_ERROR)
		{
			errorCode = innerError;
			return "";
		}
		resultStr.push_back(nextCh);
		rest = numberLocal % radix;
		numberLocal = numberLocal / radix;
	}
*/
	if (isNegative) resultStr.push_back('-');
	if (!number)
	{
		resultStr = "0";
	}
	std::reverse(resultStr.begin(), resultStr.end());
	return resultStr;
}

error radix(const std::string &sourceNotation, const std::string &destinationNotation, const std::string &value, std::string & resultValue)
{
	resultValue = "";
	error errorCode = CONVERT_NO_ERROR;
	int baseFrom, baseTo;
	baseFrom = StringToLong(sourceNotation, 10, errorCode);
	if (errorCode != CONVERT_NO_ERROR)
	{
		cout << endl;
		return errorCode;
	}
	if (baseFrom < 2 || baseFrom > 36)
	{
		cout << endl;
		return CONVERT_ERROR_INCORRECT_BASE;
	}
	baseTo = StringToLong(destinationNotation, 10, errorCode);
	if (errorCode != CONVERT_NO_ERROR)
	{
		cout << endl;
		return errorCode;
	}
	if (baseTo < 2 || baseTo > 36)
	{
		cout << endl;
		return CONVERT_ERROR_INCORRECT_BASE;
	}
	long internLong = StringToLong(value, baseFrom, errorCode);
	if (errorCode != CONVERT_NO_ERROR)
	{
		cout << endl;
		return errorCode;
	}
	resultValue = LongToString(internLong, baseTo, errorCode);
	if (errorCode != CONVERT_NO_ERROR)
	{
		cout << endl;
		return errorCode;
	}
	return errorCode;
}

int main(int argv, char *argc[])
{
	if (argv != 4)
	{
		cout << "Invalid arguments amount\n"
			<< "Usage radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}
	std::string resultValue;
	error errorCode = radix(argc[1], argc[2], argc[3], resultValue);
	std::cout << resultValue << endl;
	return errorCode;
}