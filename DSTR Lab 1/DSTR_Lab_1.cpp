#include <iostream>
#include <string>
using namespace std;

int main()
{
	// display hello word
	cout << "Hello World\n" << endl;
	system("pause");



	// read input 
	string name;
	cout << "Enter your name: ";
	cin >> name;
	cout << "My name is " << name << endl;
	system("pause");

	//ignores the rest of the current line, up to '\n'
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Enter your name: ";
	getline(cin, name);
	cout << "My name is " << name << endl;
	system("pause");



	//if else
	int number = 10;
	if (number > 5 && number < 12)
	{
		cout << "The number is between 6 to 11";
	}
	else
	{
		cout << " The number is out of the range of 6 to 11";
	}

	if (number == 1)
	{
		cout << "1" << endl;
	}
	else if (number == 2)
	{
		cout << "2" << endl;
	}
	else
	{
		cout << "Not 1 or 2" << endl;
	}



	//switch
	switch (number)
	{
	case 1: cout << "1" << endl; break;
	case 2: cout << "2" << endl; break;
	default: cout << "Not 1 or 2" << endl;
	}



	//for 
	for (int i = 0; i < number; i++)
	{
		cout << i << endl;
	}



	//while
	int i = 0;
	while (i < number)
	{
		cout << i << endl;
		i++;
	}

	i = 0;
	do
	{
		cout << i << endl;
	} while (i < number);



	//Exercise 1
	/*
	
		A program is required to prompt for and accept a time and compute 
		the number of seconds elapsed since midnight. The time should be 
		entered in the format HH:MM:SS. 

		Sample:
		Please enter your elapsed time (in HH:MM:SS format) = 00:02:44
		Elapsed time in seconds = 164 seconds

	*/

	int hours, minutes, seconds, decision = 0;
	char seperator1, seperator2;

	do {
		cout << "Please enter your elapsed time (in HH::MM::SS format) = ";

		//      aa         :            bb          :             cc
		cin >> hours >> seperator1 >> minutes >> seperator2 >> seconds;
		while (cin.fail() || hours < 0 || minutes < 0 || minutes > 60
			|| seconds < 0 || seconds > 60 || seperator1 != ':' || seperator2 != ':')
		{
			cin.clear(); //remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //remove content

			cout << "Invalid Input!";
			cin >> hours >> seperator1 >> minutes >> seperator2 >> seconds;
		}

		int ElapsedTime = (hours * 60 * 60) + (minutes * 60) + seconds;
		cout << "Elapse time is " << ElapsedTime << " seconds." << endl;

		cout << "\n Do you want to reset the timer? 1: Yes, others: No" << endl;
	} while (decision == 1);


	return 0;
}