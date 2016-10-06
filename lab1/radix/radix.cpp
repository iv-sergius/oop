#include <iostream>
#include <string>
#include <climits>
#include <stdio.h>

#define CONVERT_NO_ERROR 0
#define CONVERT_ERROR_EMPTY_STRING 1
#define CONVERT_ERROR_LONG_OVERFLOW 2
#define CONVERT_ERROR_LETTER_OUT_RANGE 3
#define CONVERT_ERROR_DIGIT_OUT_RANGE 4
#define ERROR_INCORRECT_BASE 5
using namespace std;


char DigitToLetter(long digit, int radix, int & wasError)
{
	wasError = CONVERT_NO_ERROR;
	if (digit >= 0 && digit <= 9)
	{
		return (char)('0' + digit);
	}
	if (digit < radix && digit >= 10)
	{
		return (char)('A' - 10  + digit);
	}
	wasError = CONVERT_ERROR_DIGIT_OUT_RANGE;
	return '\0';
}

long LetterToDigit(char letter, int radix, int & wasError)
{
	wasError = CONVERT_NO_ERROR;
	if (letter >= '0' && letter <= '9')
	{
		return (long)(letter - '0');
	}
	if (letter >= 'A' && letter < 'A' - 10 + radix)
	{
		return (long)(letter - 'A' + 10);
	}
	wasError = CONVERT_ERROR_LETTER_OUT_RANGE;
	return 0;
}

long StringToLong(const string str, int radix, int & wasError)
{
	wasError = CONVERT_NO_ERROR;
	unsigned long resultLong = 0;
	if (!str.length())
	{
		wasError = CONVERT_ERROR_EMPTY_STRING;
		return 0;
	}
	unsigned int firstDigitPosition = (int)(str[0] == '-');
	long sign = 1 - 2 * firstDigitPosition;
	unsigned int i = firstDigitPosition;
	while ((i < str.length()))
	{
		unsigned int digit = LetterToDigit(str[i++], radix, wasError);
		// check on limits
		if (resultLong <= (LONG_MAX - digit + firstDigitPosition) / radix)
		{
			resultLong = radix * resultLong + digit;
		}
		else
		{
			wasError = CONVERT_ERROR_LONG_OVERFLOW;
			return 0;
		}
	}
	return (long) sign * resultLong;
}

string LongToString(const long number, int radix, int & wasError)
{
	wasError = CONVERT_NO_ERROR;
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
			wasError = innerError;
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
	int wasError = CONVERT_NO_ERROR;
	
	baseFrom = StringToLong(argc[2], 10, wasError);
	if (wasError != CONVERT_NO_ERROR)
	{
		cout << endl;
		return wasError;
	}
	if (baseFrom < 2 || baseFrom > 36)
	{
		cout << endl;
		return ERROR_INCORRECT_BASE;
	}
	baseTo = StringToLong(argc[3], 10, wasError);
	if (wasError != CONVERT_NO_ERROR)
	{
		cout << endl;
		return wasError;
	}
	if (baseTo < 2 || baseTo > 36)
	{
		cout << endl;
		return ERROR_INCORRECT_BASE;
	}
	long internLong = StringToLong(argc[1], baseFrom, wasError);
	if (wasError != CONVERT_NO_ERROR)
	{
		cout << endl;
		return wasError;
	}
	string resultStr = LongToString(internLong, baseTo, wasError);
	if (wasError != CONVERT_NO_ERROR)
	{
		cout << endl;
		return wasError;
	}
	cout << resultStr << endl;
	return 0;
}