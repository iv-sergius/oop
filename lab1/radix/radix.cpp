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


char DigitToLetter(long digit, int radix, int & errorCode)
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

long LetterToDigit(char letter, int radix, int & errorCode)
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
	errorCode = CONVERT_ERROR_LETTER_OUT_RANGE;
	return 0;
}

long StringToLong(const string str, int radix, int & errorCode)
{
	errorCode = CONVERT_NO_ERROR;
	unsigned long resultLong = 0;
	if (str.empty())
	{
		errorCode = CONVERT_ERROR_EMPTY_STRING;
		return 0;
	}
	unsigned int firstDigitPosition = (int)(str[0] == '-');
	long sign = 1 - 2 * firstDigitPosition;
	unsigned int i = firstDigitPosition;
	while ((i < str.length()))
	{
		unsigned int digit = LetterToDigit(str[i++], radix, errorCode);
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

string LongToString(const long number, int radix, int & errorCode)
{
	errorCode = CONVERT_NO_ERROR;
	string resultStr = "";
	bool isNegative = number < 0; // save sing of numbers
	unsigned long numberLocal = abs(number);
	int innerError = CONVERT_NO_ERROR;
	
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
		resultStr = nextCh + resultStr;
		rest = numberLocal % radix;
		numberLocal = numberLocal / radix;
	}
	if (isNegative) resultStr = '-' + resultStr;
	if (!number)
	{
		resultStr = "0";
	}
	return resultStr;
}

int main(int argv, char *argc[])
{
	int baseFrom, baseTo;
	if (argv != 4)
	{
		cout << "Invalid arguments amount\n"
			<< "Usage radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}
	int errorCode = CONVERT_NO_ERROR;
	
	baseFrom = StringToLong(argc[2], 10, errorCode);
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
	baseTo = StringToLong(argc[3], 10, errorCode);
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
	long internLong = StringToLong(argc[1], baseFrom, errorCode);
	if (errorCode != CONVERT_NO_ERROR)
	{
		cout << endl;
		return errorCode;
	}
	string resultStr = LongToString(internLong, baseTo, errorCode);
	if (errorCode != CONVERT_NO_ERROR)
	{
		cout << endl;
		return errorCode;
	}
	cout << resultStr << endl;
	return 0;
}