﻿#include<iostream>
#include<string>
#include<stdlib.h> //Clear Text in Output 
#include<ctime> //Get Current Date and Time 
#include<iomanip> //Make character to 2 digit
using namespace std;


struct Station {

	int StationID;
	string StationName;
	string PreviousStationName;
	string NextStationName;
	double DistanceBetweenPreviousStation;
	double CostBetweenPreviousStation;
	int TimeBetweenPreviousStation;
	double DistanceBetweenNextStation;
	double CostBetweenNextStation;
	int TimeBetweenNextStation;
	string NearbySightseeingSpots;

	Station* nextAdd;
	Station* prevAdd;

}*stationHead, * stationCurrent, * stationTail;


struct Ticket {

	int TransactionID;
	int TicketID;
	string NameOfTheSourceStation;
	string NameofTheTargetStation;
	int TicketAmount;
	string TransactionDateAndTime;
	string DepartureTime;
	string CustomerID;
	string CustomerName;
	string CustomerIcOrPassport;

	Ticket* nextAdd;
	Ticket* prevAdd;

}*ticketHead, * ticketCurrent;


struct Customer {
	int CustomerId;
	string CustomerName;
	string CustomerIcOrPassport;
	string CustomerPassword;

	Customer* nextAdd;
}*customerHead,*customerCurrent;


//Draw Opening
void drawopening() {
	cout << "      -------------------------------------" << endl;
	cout << "      -------Ticket Booking System---------" << endl;
	cout << "      -------------------------------------" << endl << endl;
	cout << "    Welcome to Kuala Lumpur Light Rail Transit(LRT) - Titiwangsa Station - Chan Sow Lin Station Route" << endl << endl;

}

//Draw Map
void drawmap() {

	cout << "       Titiwangsa     PWTC   Sultan Ismail    Majils Jamek    Plaza Rakyat    Hang Tuah    Pudu     Chan Sow Lin" << endl;
	cout << "    -------/\\--------/\\---------/\\--------------/\\------------/\\------------/\\--------/\\---------/\\--------" << endl;
	cout << "    -------\\/--------\\/---------\\/--------------\\/------------\\/------------\\/--------\\/---------\\/--------" << endl;

}


//create a Station node function
Station* createStationNode(int StationID, string StationName, string PreviousStationName, string NextStationName, 
	double DistanceBetweenPreviousStation, double CostBetweenPreviousStation, int TimeBetweenPreviousStation,
	double DistanceBetweenNextStation, double CostBetweenNextStation, int TimeBetweenNextStation, string NearbySightseeingSpots)
{
	Station* StationNode = new Station;
	StationNode->StationID = StationID;
	StationNode->StationName = StationName;
	StationNode->PreviousStationName = PreviousStationName;
	StationNode->NextStationName = NextStationName;
	StationNode->DistanceBetweenPreviousStation = DistanceBetweenPreviousStation;
	StationNode->CostBetweenPreviousStation = CostBetweenPreviousStation;
	StationNode->TimeBetweenPreviousStation = TimeBetweenPreviousStation;
	StationNode->DistanceBetweenNextStation = DistanceBetweenNextStation;
	StationNode->CostBetweenNextStation = CostBetweenNextStation;
	StationNode->TimeBetweenNextStation = TimeBetweenNextStation;
	StationNode->NearbySightseeingSpots = NearbySightseeingSpots;

	StationNode->nextAdd = NULL;
	StationNode->prevAdd = NULL;

	return StationNode;
}


//create a Customer node function
Customer* createCustomerNode(int customerId, string customerName, string customerIcOrPassport, string customerPassword)
{
	Customer* CustomerNode = new Customer;
	CustomerNode->CustomerId = customerId;
	CustomerNode->CustomerName = customerName;
	CustomerNode->CustomerIcOrPassport = customerIcOrPassport;
	CustomerNode->CustomerPassword = customerPassword;

	CustomerNode->nextAdd = NULL;

	return CustomerNode;
}


//Insert Customer Node to the End of the list
void insertCustomerNodeToTheEndList(Customer* CustomerNode) 
{
	//Situation 1: List still empty
	if (customerHead == NULL)
	{
		customerHead = CustomerNode;
	}

	//Situation 2: List not empty
	else
	{
		customerCurrent = customerHead;
		while (customerCurrent->nextAdd != NULL)
		{
			customerCurrent = customerCurrent->nextAdd;
		}
		customerCurrent->nextAdd = CustomerNode;
	}
}


//Check and Create Customer Account
int createCustomerAccount(string customerName, string customerIcOrPassport, string customerPassword)
{
	int customerId;
	if (customerHead == NULL)
	{
		customerId = 1;
	}
	else
	{
		customerCurrent = customerHead;
		//Check account existed or not
		if (customerCurrent->CustomerIcOrPassport == customerIcOrPassport)
		{
			return 0;
		}
		while (customerCurrent->nextAdd != NULL)
		{
			customerCurrent = customerCurrent->nextAdd;
			//Check account existed or not
			if (customerCurrent->CustomerIcOrPassport == customerIcOrPassport)
			{
				return 0;
			}
		}
		//Create a Customer Id
		customerId = customerCurrent->CustomerId + 1;
	}

	//If the customer does not exist in the system, the account will be created
	Customer* customerNode = createCustomerNode(customerId, customerName, customerIcOrPassport, customerPassword);
	insertCustomerNodeToTheEndList(customerNode);
	return 1;
}


//Check Customer Account and password
int checkCustomerAccount(string customerIcOrPassport, string customerPassword)
{
	if (customerHead == NULL)
	{
		cout << "This system has no customer account" << endl;
		system("pause");
		return 0;
	}
	else
	{
		customerCurrent = customerHead;
		//check customer account
		if (customerCurrent->CustomerIcOrPassport == customerIcOrPassport)
		{

			if (customerCurrent->CustomerPassword == customerPassword)
			{
				cout << "Welcome Mr/Mrs " << customerCurrent->CustomerName << endl;
				return customerCurrent->CustomerId;
			}
			else
			{
				cout << "Incorrect Password. " << endl;
				system("pause");
				return 0;
			}
		}
		while (customerCurrent->nextAdd != NULL)
		{
			customerCurrent = customerCurrent->nextAdd;

			//check customer account
			if (customerCurrent->CustomerIcOrPassport == customerIcOrPassport)
			{
				if (customerCurrent->CustomerPassword == customerPassword)
				{
					cout << "Welcome Mr/Mrs " << customerCurrent->CustomerName << endl;
					return customerCurrent->CustomerId;
				}
				else
				{
					cout << "Incorrect Password. " << endl;
					return 0;
				}
			}
		}

		cout << "This IC or Passport Number does not exist in this system, Please create a new account." << endl;
		return 0;
	}
}

//Insert to the Front of the list
void insertStationNodeToTheFrontList(Station* StationNode)
{
	// If the list still empty
	if (stationHead == NULL && stationTail == NULL)
	{
		stationHead = stationTail = StationNode;
	}
	// If the list is not empty
	else
	{
		StationNode->nextAdd = stationHead;
		stationHead->prevAdd = StationNode;
		stationHead = StationNode;
	}
}


//List all possible arrival route
void listAllPossibleArrivalStation(int route, int departure) {

	stationCurrent = stationHead;

	switch (route)
	{
		case 1:
			for (int i = 1; i <= 8; i++)
			{
				if (stationCurrent->StationID <= departure)
				{
					stationCurrent = stationCurrent->nextAdd;
				}
				else
				{
					cout << stationCurrent->StationID << ") ";
					cout << stationCurrent->StationName << endl;
					stationCurrent = stationCurrent->nextAdd;
				}

			}
			break;

		case 2:
			for (int i = 1; i < departure; i++)
			{
				cout << stationCurrent->StationID << ") ";
				cout << stationCurrent->StationName << endl;
				stationCurrent = stationCurrent->nextAdd;
			}
	}
}


//Date Validator
int isValidDate(int DepartureYear, int DepartureMonth, int DepartureDay)
{
	//Get current date
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	int CurrentYear = 1900 + newtime.tm_year;
	int CurrentMonth = 1 + newtime.tm_mon;
	int CurrentDay = newtime.tm_mday;

	// Check Departure Year, month and day are in the within range
	if (DepartureYear > 2025 || DepartureYear < 2022)
	{
		return 0;
	}
	if (DepartureMonth < 1 || DepartureMonth > 12)
	{
		return 1;
	}
	if (DepartureDay < 1 || DepartureDay > 31)
	{
		return 2;
	}

	// Check Feb month
	if (DepartureMonth == 2)
	{
		//leap year
		if (DepartureYear % 4 == 0 && DepartureDay > 29)
		{
			return 1;
		}
		//not leap year
		if (DepartureYear % 4 != 0 && DepartureDay == 29)
		{
			return 3;
		}
		//incorrect day
		if (DepartureYear % 4 != 0 && DepartureDay > 29)
		{
			return 1;
		}
	}

	//Check Apr, Jun, Sept, and Nov
	if ((DepartureMonth == 4 || DepartureMonth == 6 || DepartureMonth == 9 || DepartureMonth == 11) && DepartureDay > 30)
	{
		return 2;
	}

	//Check Date is past or Not
	if (DepartureYear == CurrentYear)
	{
		//Past Months
		if (DepartureMonth < CurrentMonth)
		{
			return 4;
		}

		//Past Day
		if (DepartureMonth == CurrentMonth && DepartureDay < CurrentDay)
		{
			return 4;
		}

		if (DepartureMonth == CurrentMonth && DepartureDay == CurrentDay)
		{
			return 5;
		}
	}

	return 6;
}


//List all possible Departure Time
string listAllPossibleDepartureTime(int route, int departure, int todaydate)
{
	// calculate first possible minutes
	int minutes = 0;
	switch (route)
	{
	case 1:
		stationCurrent = stationHead->nextAdd;
		for (int i = 1; i < departure; i++)
		{
			minutes = minutes + stationCurrent->TimeBetweenPreviousStation;
			stationCurrent = stationCurrent->nextAdd;
		}
		break;
	case 2:
		stationCurrent = stationTail->prevAdd;
		for (int i = 8; i > departure; i--)
		{
			minutes = minutes + stationCurrent->TimeBetweenNextStation;
			stationCurrent = stationCurrent->prevAdd;
		}
	}
	

	int size = 38; // use for input checking later

	//Create a empty dynamic array to contain all possible departure time
	string* TrainArrivalTime = new string [38];

	//Calculate all possible departure time
	int hour = 6;
	int arrayindex1 = 0;
	while (arrayindex1 != 38) {
		if (hour == 24)
		{
			hour = 0;
		}
		if (todaydate == 0)
		{
			cout << arrayindex1 + 1 << ") " << setw(2) << setfill('0') << to_string(hour) << ":" << setw(2) << setfill('0') << to_string(minutes) << endl;
		}
		TrainArrivalTime[arrayindex1] = to_string(hour) + ":" + to_string(minutes);
		arrayindex1++;
		minutes = minutes + 30;
		if (minutes > 59)
		{
			minutes = minutes - 60;
			hour = hour + 1;
		}
	}

	int check_hours;
	int check_minutes;
	int arrayindex2 = 0;
	string* TodayTrainArrivalTime = new string[38];

	if (todaydate == 1)
	{
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);
		int CurrentHours = newtime.tm_hour;
		int CurrentMins = newtime.tm_min;

		for (int i = 0; i < 38; i++)
		{
			int pos = TrainArrivalTime[i].find(":");

			check_hours = stoi(TrainArrivalTime[i].substr(0, pos));
			check_minutes = stoi(TrainArrivalTime[i].substr(pos + 1));

			if (CurrentHours > check_hours)
			{
				size--;
				continue;
			}
			else if (CurrentHours == check_hours)
			{
				if (CurrentMins >= check_minutes)
				{
					size--;
					continue;
				}

			}

			cout << arrayindex2 + 1 << ") " << setw(2) << setfill('0') << to_string(check_hours) << ":" << setw(2) << setfill('0') << to_string(check_minutes) << endl;
			TodayTrainArrivalTime[arrayindex2] = TrainArrivalTime[i];
			arrayindex2++;
			
		}
	}


	while (true)
	{
		int DepartureTimeIndex;
		cout << "Select your departure time" << endl;
		cin >> DepartureTimeIndex;

		if (cin.fail() || DepartureTimeIndex > size || DepartureTimeIndex < 0)
		{
			cin.clear(); //remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //remove content
			cout << "Invalid input" << endl;
		}
		else if (DepartureTimeIndex == 0)
		{
			return "";
		}
		else
		{
			if (todaydate == 0)
			{
				return TrainArrivalTime[DepartureTimeIndex - 1];
			}
			else if (todaydate == 1)
			{
				return TodayTrainArrivalTime[DepartureTimeIndex - 1];
			}
		}
	}


}


//Display Ticket Details
void displayDetailsBetweenTwoSelectedCities(int route, int departure, int arrival,int Year,int Month,int Days,int Hours,int Minutes)
{
	stationCurrent = stationHead;
	double totaldistance = 0;
	double totalexpenses = 0;
	int totaltime = 0;

	if (route == 1)
	{
		for (int i = 1; i < departure; i++)
		{
			stationCurrent = stationCurrent->nextAdd;
		}

		cout << "Departure Station: " << stationCurrent->StationName << endl;

		for (int i = departure; i < arrival; i++)
		{
			totaldistance = totaldistance + stationCurrent->DistanceBetweenNextStation;
			totalexpenses = totalexpenses + stationCurrent->CostBetweenNextStation;
			totaltime = totaltime + stationCurrent->TimeBetweenNextStation;
			stationCurrent = stationCurrent->nextAdd;
		}

		cout << "Arrival Station: " << stationCurrent->StationName << endl;
		cout << "Total Distance: " << totaldistance << " KM" << endl;
		cout << "Total Expenses per ticket: RM " << totalexpenses << endl;
		cout << "Total Time: " << totaltime << " Minutes" << endl << endl;

		cout << "Departure Time: " << Year << "/" << setw(2) << setfill('0') << Month << "/" << setw(2) << setfill('0') <<
			Days << " " << setw(2) << setfill('0') << Hours << ":" << setw(2) << setfill('0') << Minutes << endl;

		
		int arrival_year = Year;
		int arrival_month = Month;
		int arrival_days = Days;
		int arrival_hours = Hours;
		int arrival_minutes = Minutes + totaltime;
		

		//Check Minutes
		if (arrival_minutes > 59)
		{
			arrival_minutes = arrival_minutes - 60;
			arrival_hours = arrival_hours + 1;
		}

		//Check Hours
		if (arrival_hours > 23)
		{
			arrival_hours = 0;
			arrival_days = arrival_days + 1;
		}

		//Check Days
		if ((arrival_month == 4 || arrival_month == 6 || arrival_month == 9 || arrival_month == 11) && arrival_days > 30)
		{
			arrival_days = 1;
			arrival_month = arrival_month + 1;
		}
		else if (arrival_month == 2)
		{
			//leap year
			if (arrival_year % 4 == 0 && arrival_days > 29)
			{
				arrival_days = 1;
				arrival_month = arrival_month + 1;
			}
			//not leap year
			if (arrival_year % 4 != 0 && arrival_days > 28)
			{
				arrival_days = 1;
				arrival_month = arrival_month + 1;
			}
		}
		else if (arrival_days > 31)
		{
			arrival_days = 1;
			arrival_month = arrival_month + 1;
		}

		//Check Months
		if (arrival_month > 12)
		{
			arrival_month = 1;
			arrival_year = arrival_year + 1;
		}

		cout << "Estimate Arrival Time: " << arrival_year << "/" << setw(2) << setfill('0') << arrival_month << "/" << setw(2) << setfill('0') <<
			arrival_days << " " << setw(2) << setfill('0') << arrival_hours << ":" << setw(2) << setfill('0') << arrival_minutes << endl << endl;

	}
}


//Customer Purchase Ticket
void purchaseticket(int customerId)
{
	int route;
	//Select Route
	while (true)
	{
		system("CLS");
		cout << "1) Titiwangsa -> Chan Sow Lin" << endl;
		cout << "2) Chan Sow Lin -> Titiwangsa" << endl;
		cout << "3) Return to main menu" << endl;
		cout << "Select your route: " << endl;
		cin >> route;


		if (route == 3)
		{
			return;
		}
		else if (route == 1 || route == 2)
		{
			break;
		}
		else
		{
			cin.clear(); //remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //remove content
			cout << "Incorrect Input" << endl;
			system("pause");
		}

	}


	// Select Departure Station
	int departure = 0;
	while (true)
	{
		system("CLS");
		cout << "1) Titiwangsa" << endl;
		cout << "2) PWTC" << endl;
		cout << "3) Sultan Ismail" << endl;
		cout << "4) Majlis Jamek" << endl;
		cout << "5) Plaza Rakyat" << endl;
		cout << "6) Hang Tuah" << endl;
		cout << "7) Pudu" << endl;
		cout << "8) Chan Sow Lin" << endl;
		cout << "9) Return to Main Menu" << endl << endl;
		cout << "Choose your Departure location: ";
		cin >> departure;



		if (departure == 1 && route == 2)
		{
			cout << "Titiwangsa station is the last stop, choose another station" << endl;
		}
		else if (departure == 8 && route == 1)
		{
			cout << "Chan Sow Lin station is the last stop, choose another station" << endl;
		}
		else if (departure == 9)
		{
			return;
		}
		else if (departure > 0 && departure < 9)
		{
			break;
		}
		else
		{
			cin.clear(); //remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //remove content
			cout << "Incorrect Input" << endl;
		}
		system("pause");
	}

	// Select Arrival Station
	int arrival = 0;
	while (true)
	{
		system("CLS");
		listAllPossibleArrivalStation(route, departure);
		cout << "9) Return to Main Menu" << endl << endl;
		cout << "Choose your Arrival location: ";
		cin >> arrival;

		if (route == 2 && arrival < departure && arrival > 0)
		{
			break;

		}
		else if (route == 1 && arrival > departure && arrival < 9)
		{
			break;
		}
		else if (arrival == 9)
		{
			return;
		}
		else
		{
			cin.clear(); //remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //remove content
			cout << "Incorrect Input" << endl;
			system("pause");
		}
	}

	//Select Departure Date
	int DepartureYear, DepartureMonth, DepartureDay;
	char seperator1, seperator2;
	int InputCorrect = 0;
	int TodayDate = 0;

	while (InputCorrect == 0) {
		system("CLS");
		cout << "Please enter your departure Date (in YYYY/MM/DD format): " << endl;
		cout << "Note: Ticket can only be bought before 2025" << endl;
		cout << "Date: ";
		cin >> DepartureYear >> seperator1 >> DepartureMonth >> seperator2 >> DepartureDay;

		if (cin.fail() || seperator1 != '/' || seperator2 != '/')
		{
			cin.clear(); //remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //remove content
			cout << "Invalid Format" << endl;
			system("pause");
			continue;
		}

		switch (isValidDate(DepartureYear, DepartureMonth, DepartureDay)) {
		case 0:
			cout << "Invalid Year" << endl;
			system("pause");
			break;
		case 1:
			cout << "Invalid Month" << endl;
			system("pause");
			break;
		case 2:
			cout << "Invalid Day" << endl;
			system("pause");
			break;
		case 3:
			cout << "This year Febuary only has 28 days" << endl;
			system("pause");
			break;
		case 4:
			cout << "The selected date is past" << endl;
			system("pause");
			break;
		case 5:
			InputCorrect = 1;
			TodayDate = 1;
			break;
		case 6:
			InputCorrect = 1;
		}

	}

	// Select Departure Time
	int DepartureHour = 0;
	int DepartureMinutes = 0;

	string DepartureTime = listAllPossibleDepartureTime(route, departure, TodayDate);

	if (DepartureTime == "")
	{
		return;
	}
	else
	{
		int pos = DepartureTime.find(":");

		DepartureHour = stoi(DepartureTime.substr(0, pos));
		DepartureMinutes = stoi(DepartureTime.substr(pos + 1));
	}

	displayDetailsBetweenTwoSelectedCities(route, departure, arrival, DepartureYear, DepartureMonth, DepartureDay, DepartureHour, DepartureMinutes);
	
}


int main()
{
	stationHead = stationTail = NULL;

	
	Station* StationNode1 = createStationNode(1, "Titiwangsa", "", "PWTC", 0, 0, 0, 4, 0.40, 3, "NearbySeeingSpot1");
	Station* StationNode2 = createStationNode(2, "PWTC", "Titiwangsa", "Sultan Ismail", 4, 0.40, 3, 8, 0.80, 7, "NearbySeeingSpot2");
	Station* StationNode3 = createStationNode(3, "Sultan Ismail", "PWTC", "Majlis Jamek", 8, 0.80, 7, 8, 0.80, 7, "NearbySeeingSpot3");
	Station* StationNode4 = createStationNode(4, "Majlis Jamek", "Sultan Ismail", "Plaza Rakyat", 8, 0.80, 7, 6, 0.60, 5, "NearbySeeingSpot4");
	Station* StationNode5 = createStationNode(5, "Plaza Rakyat", "Majlis Jamek", "Hang Tuah", 6, 0.60, 5, 10, 1.00, 9, "NearbySeeingSpot5");
	Station* StationNode6 = createStationNode(6, "Hang Tuah", "Plaza Rakyat", "Pudu", 10, 1.00, 9, 5, 0.50, 4, "NearbySeeingSpot6");
	Station* StationNode7 = createStationNode(7, "Pudu", "Hang Tuah", "Chan Sow Lin", 5, 0.50, 4, 5, 0.50, 4, "NearbySeeingSpot7");
	Station* StationNode8 = createStationNode(8, "Chan Sow Lin", "Pudu", "", 5, 0.50, 4, 0, 0, 0, "NearbySeeingSpot8");

	while (true)
	{

		int decision;
		system("CLS");
		cout << "1) Login to existing account" << endl;
		cout << "2) Create a new account as passenger" << endl;
		cout << "3) Exit system" << endl;
		cout << "Select your decision: " << endl;
		cin >> decision;


		if (decision == 1)
		{
			while (true)
			{
				int role;
				cout << "1) Passenger" << endl;
				cout << "2) Admin" << endl;
				cout << "Select your role: ";
				cin >> role;

				//Passenger
				if (role == 1)
				{
					string customerAccount;
					string customerPassword;
					cout << "Please Enter your IC or Passport Number" << endl;
					cin >> customerAccount;
					cout << "Please Enter your Password" << endl;
					cin >> customerPassword;

					int customerId = checkCustomerAccount(customerAccount, customerPassword);

					if (customerId != 0)
					{
						insertStationNodeToTheFrontList(StationNode8);
						insertStationNodeToTheFrontList(StationNode7);
						insertStationNodeToTheFrontList(StationNode6);
						insertStationNodeToTheFrontList(StationNode5);
						insertStationNodeToTheFrontList(StationNode4);
						insertStationNodeToTheFrontList(StationNode3);
						insertStationNodeToTheFrontList(StationNode2);
						insertStationNodeToTheFrontList(StationNode1);

						int customerDecision;
						while (true)
						{
							cout << "1) Purchase Ticket" << endl;
							cout << "2) Search subway station details" << endl;
							cout << "3) View transaction history" << endl;
							cout << 
							cout << "2) Exit to Main Menu" << endl;
							cin >> customerDecision;
							if (customerDecision == 1)
							{
								purchaseticket(customerId);
							}
							else
							{
								cout << "Thank you, have a nice day. " << endl;
								system("pause");
								break;
							}

						}
					}

					break;
				}

				//Admin
				else if (role == 2)
				{

					cout << "Admin";
				}
			}

		}
		else if (decision == 2)
		{
			while (true)
			{
				system("CLS");
				string customerName;
				string customerIcOrPassport;
				string customerPassword;
				cout << "Please Enter your Full Name: ";
				cin >> customerName;
				cout << "Please Enter your IC or Passport Number: ";
				cin >> customerIcOrPassport;
				cout << "Please Create a password: ";
				cin >> customerPassword;

				int status = createCustomerAccount(customerName, customerIcOrPassport, customerPassword);
				if (status == 0)
				{
					
					string ContinueCreate;
					cout << "This account is already existed. " << endl;
					cout << "Continue Create account? " << endl;
					cout << "1) Yes    2) No";
					cin >> ContinueCreate;

					if (ContinueCreate == "1")
					{
						continue;
					}
					else if (ContinueCreate == "2")
					{
						break;
					}
					else
					{
						cout << "Invalid Input. Returning to Main Menu." << endl;
					}
				}
				else
				{
					cout << "Account created successfully." << endl;
					system("pause");
					break;

				}
			}

		}
		else if (decision == 3)
		{
			break;
		}
		else
		{
			cin.clear(); //remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //remove content
			cout << "Invalid Format" << endl;
			system("pause");
		}

	}
	
	cout << "Bye";
	
	return 0;
}