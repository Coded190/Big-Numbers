//Big Numbers

#include <iostream>
#include <string>
using namespace std;

const int MAX_NUM = 13;
const int MAX_INPUT = 12;

struct Node
{
	int num;
	struct Node* next;
};

void displayGreetings();
int getNumSize();			//gets how many numbers the user will enter
string getUserNumbers(int);	//gets the very large numbers
string validateNum(string);		//validates the max num
string validateString(string, int);		//validates the large numbers and MAX_INPUT(12)
void addition(string[], int);
int multiply(string, string, string[], string&, int&);
void displayAddition(string[], int, int);		
void displayMultiply(string, string);		
string reverseString(string);
void reverseArray(string[], int);
string sumString(string, string);
string sumMultiply(string[], int);
string addSpace(string, int);
string sumArray(string[], int);
int findLargest(string[], int);

int main()
{
	string stringArr[MAX_NUM];	//pointer array to hold the large numbers. 
	string addDisplay[MAX_NUM];
	string multiplyDisplay[2];	//for first and last
	int totalNum = 0;
	string min;
	string max;

	displayGreetings();

	totalNum = getNumSize();

	for (int i = 0; i < totalNum; i++)
	{
		stringArr[i] = getUserNumbers(i);
		addDisplay[i] = stringArr[i];

		if (i == 0)
		{
			multiplyDisplay[0] = stringArr[i];
		}

		if (i == totalNum - 1)
		{
			multiplyDisplay[1] = stringArr[i];
		}

	}

	displayAddition(stringArr, totalNum, findLargest(stringArr, totalNum));

	addition(stringArr, totalNum);
	
	displayMultiply(stringArr[0], stringArr[totalNum - 1]);

	return 0;
}


//-------------------------------------------------------------
// Displays the greeting message to the user
// 
// @param - void
// @return - void
//-------------------------------------------------------------

void displayGreetings()
{
	cout << "This program adds 2 and up to 13 very large numbers accurately.\n";
	cout << "It multiplies the first 2 numbers and shows the intermediate steps of the product.\n\n";
}


//-------------------------------------------------------------
// Gets the size of the total number user wants to input
// 
// @param - void
// @return - int
//-------------------------------------------------------------

int getNumSize()
{
	string strNum;
	int num = 0;

	strNum = validateNum(strNum);
	num = stoi(strNum);

	return num;
}


//-------------------------------------------------------------
// Validates the inputted number from user
// 
// @param - string
// @return - string
//-------------------------------------------------------------

string validateNum(string str)
{
	bool error = false;

	cout << "How many numbers? -> ";
	getline(cin >> ws, str);

	if (str.length() == 0 || str.length() > 2)
	{
		cout << "Try again.\n";
		 return validateNum(str);
	}
	else
	{
		for (int i = 0; i < str.length(); i++)
		{
			if (!isdigit(str[i]))
			{
				error = true;
			}

			if (str.length() == 1 && (str[0] < '2' || str[0] > '13'))
			{
				error = true;
			}

			if (str.length() == 2 && (str[0] != '1' || str[1] > '3'))
			{
				error = true;
			}
		}
	}

	if (error)
	{
		cout << "Try again.\n";
		return validateNum(str);
	}


	return str;

}


//-------------------------------------------------------------
// Gets the user Big Numbers and validates the int. 
// Returns the integer as a string
// 
// @param - int
// @return - string
//-------------------------------------------------------------

string getUserNumbers(int index)
{
	string str;

	str = validateString(str, index);

	return str;
}


//-------------------------------------------------------------
// Validates the inputted Big Number
// 
// @param - string, int
// @return - string
//-------------------------------------------------------------

string validateString(string str, int index)
{
	bool error = false;

	cout << "Input number #" << index + 1 << " -> ";
	getline(cin >> ws, str);

	if (str.length() < 1 || str.length() > 12)
	{
		cout << "Try again.\n";
		return validateString(str, index);
	}
	else
	{
		for (int i = 0; i < str.length(); i++)
		{
			if (!isdigit(str[i]))
			{
				error = true;
			}
		}
	}


	if (error)
	{
		cout << "Try again.\n";
		return validateString(str, index);
	}

	return str;
}


//-------------------------------------------------------------
// Reverses the string for arithmetic functions
// 
// @param - string
// @return - string
//-------------------------------------------------------------

string reverseString(string str)
{
	string temp;
	int j = 0;

	for (int i = str.length() - 1; i >= 0; i--)
	{
		temp += str[i];
		j++;
	}

	return temp;
}


//-------------------------------------------------------------
// Sums 2 Big Numbers together and returns the result as 1
// string.
// 
// @param - string, string
// @return - string
//-------------------------------------------------------------

string sumString(string str1, string str2)
{
	if (str1.size() < str2.size())
	{
		swap(str1, str2);
	}

	int j = str1.size() - 1;

	for (int i = str2.size() - 1; i >= 0; i--, j--)
	{
		str1[j] += (str2[i] - '0');	//this gives offset of symbols if over 9
	}

	for (int i = str1.size() - 1; i > 0; i--)
	{
		if (str1[i] > '9')	//this is gonna have that offset
		{
			int d = str1[i] - '0';	//change d
			str1[i - 1] = ((str1[i - 1] - '0') + d / 10) + '0';	//places 13/10, adds the result to the next element, then places back into element
			str1[i] = (d % 10) + '0';	//places remainder back into element
		}
	}

	if (str1[0] > '9')							//if first element is over 9
	{
		string k;
		k += str1[0];							//say a[0]=13, 
		str1[0] = ((str1[0] - '0') % 10) + '0';	//places 3/ones place into element
		k[0] = ((k[0] - '0') / 10) + '0';		//places 1/tens place into element
		str1 = k + str1;						//concatenates string into one
	}

	return str1;
}


//-------------------------------------------------------------
// Adds all the Big Numbers saved in the array together
// 
// @param - string[], int
// @return - void
//-------------------------------------------------------------

void addition(string strArr[], int totalNum)
{
	string arr[MAX_INPUT + 1];
	string str;
	string tempStr;

	
	for (int i = 0; i < totalNum; i++)
	{
		if (i == 0)
		{
			str = strArr[i];

		}
		else
		{
			str = sumString(str, strArr[i]);
		}
	}

	cout << str << endl;
}


//-------------------------------------------------------------
// Multiplies the first and last inputted Big Numbers together
// and shows the intermediate steps
// 
// @param - string, string, string[], string&, int&
// @return - int
//-------------------------------------------------------------

int multiply(string first, string last, string str[], string& product, int& end)
{
	string sum[MAX_INPUT + 1];
	string temp;
	int num1 = 0;
	int num2 = 0;
	int size = 0;

	if (last.length() > first.length())
	{
		temp = last;
		last = first;
		first = temp;
	}

	first = reverseString(first);	//needed to sum correctly
	last = reverseString(last);

	for (int i = 0; i < last.length(); i++)
	{
		num1 = last[i] - '0';
		string s[MAX_INPUT + 1];

		for (int j = 0; j < i; j++)
		{
			if (i > 0)
			{
				num1 *= 10;
			}
		}

		//cout << "This is the first sum: " << num1 << endl;

		for (int j = 0; j < first.length(); j++)
		{
			//cout << "This is the number from the first string -> " << first[j] - '0' << endl;

			if (j > 0)
			{
				//for (int k = 0; k < j; k++)
				//{
				//	num1 *= 10;
				//}

				num2 = num1 * (first[j] - '0');

				//create a loop to multiply the sum by the times of j
				for (int k = 0; k < j; k++)
				{
					num2 *= 10;
				}
			}
			else
			{
				num2 = num1 * (first[j] - '0');
			}
			s[j] = to_string(num2);	
			//cout << s[j] << endl;
			size++;
		}

		sum[i] = sumMultiply(s, size);
		str[i] = sum[i];
		end++;
		//cout << "Sum array: " << sum[i] << endl;
		size = 0;
	}

	for (int i = 0; i < last.length(); i++)
	{
		if (i == 0)
		{
			product = sum[i];
		}
		else
		{
			product = sumString(product, sum[i]);
			//cout << product << endl;
		}
	}

	return product.length();
}


//-------------------------------------------------------------
// Sums the product string together
// 
// @param - string[], int
// @return - string
//-------------------------------------------------------------

string sumMultiply(string str[], int size)
{
	string str1 = str[0];

	for (int i = 1; i < size; i++)
	{
		str1 = sumString(str1, str[i]);
	}

	return str1;
}


//-------------------------------------------------------------
// Displays the addition process to the user
// 
// @param - string[], int, int
// @return - void
//-------------------------------------------------------------

void displayAddition(string str[], int totalNum, int largest)
{
	cout << "The sum of:\n\n";
	largest += 3;

	for (int i = 0; i < totalNum; i++)
	{
		if (i == (totalNum - 1))
		{
			cout << "+)";

			for (int j = 0; j < (largest - str[i].length() - 2); j++)
			{
				cout << " ";
			}
			cout << str[i] << endl;

		}
		else
		{
			for (int j = 0; j < (largest - str[i].length()); j++)
			{
				cout << " ";
			}
			cout << str[i] << endl;
		}
	
	}

	for (int i = 0; i < largest; i++)
	{
		cout << "-";
	}
	cout << endl;

}


//-------------------------------------------------------------
// Displays multiplication process to the user
// 
// @param - string, string
// @return - void
//-------------------------------------------------------------

void displayMultiply(string first, string last)		//maybe pass in the final product string
{
	int num = 2;	//for first and last in array
	int largest = 0;
	int end = 0;
	string product;
	string str[MAX_INPUT];
	string starting[2];

	starting[0] = first;
	starting[1] = last;

	cout << "The product of:\n\n";
	



	largest = multiply(first, last, str, product, end);	//returns the size of the largest string

	largest += 3;

	for (int i = 0; i < 2; i++)	//displays the first and last
	{
		if (i == 1)
		{
			cout << "*)";

			for (int j = 0; j < (largest - starting[i].length() - 2); j++)
			{
				cout << " ";
			}
			cout << starting[i] << endl;

		}
		else
		{
			for (int j = 0; j < (largest - starting[i].length()); j++)
			{
				cout << " ";
			}
			cout << starting[i] << endl;

		}
	}

	for (int i = 0; i < largest; i++)
	{
		cout << "-";
	}
	cout << endl;

	//reverse the string arr
	reverseArray(str, end);


	for (int i = 0; i < end; i++)
	{
		if (i == (end - 1))
		{
			cout << "+)";

			for (int j = 0; j < (largest - str[i].length() - 2); j++)
			{
				cout << " ";
			}
			cout << str[i] << endl;

		}
		else
		{
			for (int j = 0; j < (largest - str[i].length()); j++)
			{
				cout << " ";
			}
			cout << str[i] << endl;

		}
	}

	for (int i = 0; i < largest; i++)
	{
		cout << "-";
	}
	cout << endl;

	for (int i = 0; i < largest - product.length(); i++)
	{
		cout << " ";
	}

	cout << product;
}


//-------------------------------------------------------------
// Reverses the elements within a given array
// 
// @param - string[], int
// @return - void
//-------------------------------------------------------------

void reverseArray(string str[], int size)
{
	string temp[MAX_INPUT];
	int j = 0;

	for (int i = (size - 1); i >= 0; i--)
	{
		temp[j] = str[i];
		j++;
	}

	for (int i = 0; i < size; i++)
	{
		str[i] = temp[i];
	}
}


//-------------------------------------------------------------
// Finds the largest length within a given array of strings.
// Returns the size as an integer.
// 
// @param - string[], int
// @return - int
//-------------------------------------------------------------

int findLargest(string str[], int index)
{
	int largest = str[0].length();

	for (int i = 1; i < index; i++)
	{
		if (str[i].length() > largest)
		{
			largest = str[i].length();
		}
	}

	return largest;
}

//string sumString(string str1, string str2)	//original sumString
//{	
//	int largest = MAX_INPUT;
//	int num1 = 0;
//	int num2 = 0;
//
//	for (int i = 0; i < largest; i++)
//	{
//		if (i == str2.length())
//		{
//			break;	//leaves the for loop
//		}
//		else if (i >= str1.length())
//		{
//			str1 += str2[i];
//			continue;
//		}
//
//		num1 = str1[i] - '0';
//		num2 = str2[i] - '0';
//		num1 += num2;
//
//		if (num1 > 9)
//		{
//			str1[i] = '0' + num1 % 10;	//converts to a char
//			//cout << "Overflow\n";
//			//cout << "The modded value-> " << str1[i] << endl;
//
//			if (i < str1.length())	//if we are not at the last element yet
//			{
//				str1[i + 1] = '0' + (str1[i + 1] - '0') + 1;	//handle if this is 9 already later
//			}
//			else
//			{
//				str1[i + 1] = 1;
//			}
//		}
//		else
//		{
//			//cout << "Not overflow\n";
//			str1[i] = '0' + num1;
//			//cout << str1[i] - '0' << endl;
//		}
//
//	}
//	//str1 = reverseString(str1);
//	//cout << "This is the summed string -> " << str1 << endl;
//
//	return str1;
//}