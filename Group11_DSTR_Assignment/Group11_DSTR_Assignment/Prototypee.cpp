#include <iostream>
#include <string>
#include <stdlib.h> //Clear Text in Output
#include <ctime>	//Get Current Date and Time
#include <iomanip>	//Make character to 2 digit
#include <limits>
using namespace std;

struct Station
{

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

	Station *nextAdd;
	Station *prevAdd;

} * stationHead, *stationCurrent, *stationTail;

int ticketCounts = 0; // calculate total tickets in the system
struct Ticket
{
	int TransactionID;
	int TicketID;
	string TicketRoute;
	string NameOfTheSourceStation;
	string NameofTheTargetStation;
	int TicketAmount;
	string TransactionDateAndTime;
	string DepartureDate;
	string DepartureTime;
	int TotalTicketPrice;
	int CustomerID;
	string CustomerName;
	string CustomerIcOrPassport;

	Ticket *nextAdd;

} * ticketHead, *ticketCurrent;

struct Customer
{
	int CustomerId;
	string CustomerName;
	string CustomerIcOrPassport;
	string CustomerPassword;

	Customer *nextAdd;
} * customerHead, *customerCurrent;

// Draw Opening
void drawopening()
{
	cout << "      -------------------------------------" << endl;
	cout << "      -------Ticket Booking System---------" << endl;
	cout << "      -------------------------------------" << endl
		 << endl;
	cout << "    Welcome to Kuala Lumpur Light Rail Transit(LRT) - Titiwangsa Station - Chan Sow Lin Station Route" << endl
		 << endl;
}

// Draw Map
void drawmap()
{

	cout << "       Titiwangsa     PWTC   Sultan Ismail    Majils Jamek    Plaza Rakyat    Hang Tuah    Pudu     Chan Sow Lin" << endl;
	cout << "    -------/\\--------/\\---------/\\--------------/\\------------/\\------------/\\--------/\\---------/\\--------" << endl;
	cout << "    -------\\/--------\\/---------\\/--------------\\/------------\\/------------\\/--------\\/---------\\/--------" << endl;
}

// Station
// create a Station node function
Station *createStationNode(int StationID, string StationName, string PreviousStationName, string NextStationName,
						   double DistanceBetweenPreviousStation, double CostBetweenPreviousStation, int TimeBetweenPreviousStation,
						   double DistanceBetweenNextStation, double CostBetweenNextStation, int TimeBetweenNextStation, string NearbySightseeingSpots)
{
	Station *StationNode = new Station;
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

// Insert Station Node to the End of the list
void insertStationNodeToTheEndList(Station *StationNode)
{
	// If the list still empty
	if (stationHead == NULL && stationTail == NULL)
	{
		stationHead = stationTail = StationNode;
	}
	// If the list is not empty
	else
	{
		StationNode->prevAdd = stationTail;
		stationTail->nextAdd = StationNode;
		stationTail = StationNode;
	}
}

// Customer Loging and Create Account
// create a Customer node function
Customer *createCustomerNode(int customerId, string customerName, string customerIcOrPassport, string customerPassword)
{
	Customer *CustomerNode = new Customer;
	CustomerNode->CustomerId = customerId;
	CustomerNode->CustomerName = customerName;
	CustomerNode->CustomerIcOrPassport = customerIcOrPassport;
	CustomerNode->CustomerPassword = customerPassword;

	CustomerNode->nextAdd = NULL;

	return CustomerNode;
}
// Insert Customer Node to the End of the list
void insertCustomerNodeToTheEndList(Customer *CustomerNode)
{
	// Situation 1: List still empty
	if (customerHead == NULL)
	{
		customerHead = CustomerNode;
	}

	// Situation 2: List not empty
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
// Check Customer Account when Creating a new Customer Account
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
		// Check account existed or not
		if (customerCurrent->CustomerIcOrPassport == customerIcOrPassport)
		{
			return 0;
		}
		while (customerCurrent->nextAdd != NULL)
		{
			customerCurrent = customerCurrent->nextAdd;
			// Check account existed or not
			if (customerCurrent->CustomerIcOrPassport == customerIcOrPassport)
			{
				return 0;
			}
		}
		// Create a Customer Id
		customerId = customerCurrent->CustomerId + 1;
	}

	// If the customer does not exist in the system, the account will be created
	Customer *customerNode = createCustomerNode(customerId, customerName, customerIcOrPassport, customerPassword);
	insertCustomerNodeToTheEndList(customerNode);
	return 1;
}
// Check Customer Account and password when logging
int checkCustomerLoggingAccount(string customerIcOrPassport, string customerPassword)
{
	// If there is no account exists in this system
	if (customerHead == NULL)
	{
		cout << "This system has no customer account" << endl;
		system("pause");
		return 0;
	}
	// If there is only one account exists in this system
	else if (customerHead->nextAdd == NULL)
	{
		// check customer account
		if (customerHead->CustomerIcOrPassport == customerIcOrPassport)
		{

			if (customerHead->CustomerPassword == customerPassword)
			{
				cout << "Welcome Mr/Mrs " << customerHead->CustomerName << endl;
				return customerHead->CustomerId;
			}
			else
			{
				cout << "Incorrect Password. " << endl;
				system("pause");
				return 0;
			}
		}
	}
	else
	{
		customerCurrent = customerHead;
		while (customerCurrent->nextAdd != NULL)
		{
			customerCurrent = customerCurrent->nextAdd;

			// check customer account
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
	}
	cout << "This IC or Passport Number does not exist in this system, Please create a new account." << endl;
	return 0;
}

// Generating Ticket
// create a Ticket node function
Ticket *createTicketNode(int transactionId, int ticketId, string TicketRoute, string departureStation, string arrivalStation, int ticketAmount,
						 string transactionDateAndTime, string departureDate, string departureTime,
						 int totalTicketPrice, int customerId, string customerName, string customerIcOrPassport)
{
	Ticket *TicketNode = new Ticket;
	TicketNode->TransactionID = transactionId;
	TicketNode->TicketID = ticketId;
	TicketNode->TicketRoute = TicketRoute;
	TicketNode->NameOfTheSourceStation = departureStation;
	TicketNode->NameofTheTargetStation = arrivalStation;
	TicketNode->TicketAmount = ticketAmount;
	TicketNode->TransactionDateAndTime = transactionDateAndTime;
	TicketNode->DepartureDate = departureDate;
	TicketNode->DepartureTime = departureTime;
	TicketNode->TotalTicketPrice = totalTicketPrice;
	TicketNode->CustomerID = customerId;
	TicketNode->CustomerName = customerName;
	TicketNode->CustomerIcOrPassport = customerIcOrPassport;

	TicketNode->nextAdd = NULL;

	return TicketNode;
}
// Insert Ticket Node to the Front of the lisst
void insertTicketNodeToTheFrontList(Ticket *ticketNode)
{
	// Situation 1: List still empty
	if (ticketHead == NULL)
	{
		ticketHead = ticketNode;
	}

	// Situation 2: List not empty
	else
	{
		ticketNode->nextAdd = ticketHead;
		ticketHead = ticketNode;
	}
	ticketCounts++;
}

// Create Ticket
void createTicket(string TicketRoute, string departureStation, string arrivalStation, string departureDate, string departureTime, int ticketAmount, int totalTicketPrice, int customerId)
{
	// get newest transaction id and ticket id
	int transactionId = 0;
	int ticketId = 0;
	if (ticketHead == NULL)
	{
		transactionId = 1;
		ticketId = 1;
	}
	else
	{
		ticketCurrent = ticketHead;
		while (ticketCurrent != NULL)
		{
			// Generating Transaction ID
			if (ticketCurrent->TransactionID > transactionId)
			{
				transactionId = ticketCurrent->TransactionID + 1;
			}
			// Geneating Ticket ID
			if (ticketCurrent->TicketID > ticketId)
			{
				transactionId = ticketCurrent->TicketID + 1;
			}
			ticketCurrent = ticketCurrent->nextAdd;
		}
	}

	// Get transaction date and time
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	int Year = 1900 + newtime.tm_year;
	int Month = 1 + newtime.tm_mon;
	int Day = newtime.tm_mday;
	int Hours = newtime.tm_hour;
	int Mins = newtime.tm_min;

	string transactionDateAndTime = to_string(Year) + "/" + to_string(Month) + "/" + to_string(Day) + " " + to_string(Hours) + ":" + to_string(Mins);

	// Get Customer Name and IC/Passport
	string customerName;
	string customerIcOrPassport;

	customerCurrent = customerHead;
	while (true)
	{
		if (customerCurrent->CustomerId == customerId)
		{
			customerName = customerCurrent->CustomerName;
			customerIcOrPassport = customerCurrent->CustomerIcOrPassport;
			break;
		}
		else
		{
			customerCurrent = customerCurrent->nextAdd;
		}
	}

	for (int i = 0; i < ticketAmount; i++)
	{
		Ticket *ticketNode = createTicketNode(transactionId, ticketId, TicketRoute, departureStation, arrivalStation, ticketAmount, transactionDateAndTime, departureDate, departureTime, totalTicketPrice, customerId, customerName, customerIcOrPassport);
		insertTicketNodeToTheFrontList(ticketNode);
		ticketId = ticketId + 1;
	}
}

// 1) Purchase Ticket
// List all possible arrival route
void listAllPossibleArrivalStation(int route, int departure)
{

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
// Date Validator
int isValidDate(int DepartureYear, int DepartureMonth, int DepartureDay)
{
	// Get current date
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
		// leap year
		if (DepartureYear % 4 == 0 && DepartureDay > 29)
		{
			return 1;
		}
		// not leap year
		if (DepartureYear % 4 != 0 && DepartureDay == 29)
		{
			return 3;
		}
		// incorrect day
		if (DepartureYear % 4 != 0 && DepartureDay > 29)
		{
			return 1;
		}
	}

	// Check Apr, Jun, Sept, and Nov
	if ((DepartureMonth == 4 || DepartureMonth == 6 || DepartureMonth == 9 || DepartureMonth == 11) && DepartureDay > 30)
	{
		return 2;
	}

	// Check Date is past or Not
	if (DepartureYear == CurrentYear)
	{
		// Past Months
		if (DepartureMonth < CurrentMonth)
		{
			return 4;
		}

		// Past Day
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
// List all possible Departure Time
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

	// Create a empty array to contain all possible departure time
	string TrainArrivalTime[38];

	// Calculate all possible departure time
	int hour = 6;
	int arrayindex1 = 0;
	while (arrayindex1 != 38)
	{
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
	string TodayTrainArrivalTime[38];

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
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
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
// Display Ticket Details
void displayDetailsBetweenTwoSelectedCities(int route, int departure, int arrival, int Year, int Month, int Days, int Hours, int Minutes, int customerId)
{

	double totaldistance = 0;
	double totalexpenses = 0;
	int totaltime = 0;

	string TicketRoute;

	string departureStation;
	string arrivalStation;
	if (route == 1)
	{
		TicketRoute = "Titiwangsa -> Chan Sow Lin";
		stationCurrent = stationHead;
		for (int i = 1; i < departure; i++)
		{
			stationCurrent = stationCurrent->nextAdd;
		}

		departureStation = stationCurrent->StationName;
		cout << "Departure Station: " << departureStation << endl;

		for (int i = departure; i < arrival; i++)
		{
			totaldistance = totaldistance + stationCurrent->DistanceBetweenNextStation;
			totalexpenses = totalexpenses + stationCurrent->CostBetweenNextStation;
			totaltime = totaltime + stationCurrent->TimeBetweenNextStation;
			stationCurrent = stationCurrent->nextAdd;
		}

		arrivalStation = stationCurrent->StationName;
		cout << "Arrival Station: " << arrivalStation << endl;
	}
	else if (route == 2)
	{
		TicketRoute = "Chan Sow Lin -> Titiwangsa";
		stationCurrent = stationTail;
		for (int i = 8; i > departure; i--)
		{
			stationCurrent = stationCurrent->prevAdd;
		}

		departureStation = stationCurrent->StationName;
		cout << "Departure Station: " << departureStation << endl;

		for (int i = departure; i > arrival; i--)
		{
			totaldistance = totaldistance + stationCurrent->DistanceBetweenPreviousStation;
			totalexpenses = totalexpenses + stationCurrent->CostBetweenPreviousStation;
			totaltime = totaltime + stationCurrent->TimeBetweenPreviousStation;
			stationCurrent = stationCurrent->prevAdd;
		}

		arrivalStation = stationCurrent->StationName;
		cout << "Arrival Station: " << arrivalStation << endl;
	}
	cout << "Total Distance: " << totaldistance << " KM" << endl;
	cout << "Total Expenses per ticket: RM " << fixed << setprecision(2) << setfill('0') << totalexpenses << endl;
	cout << "Total Time: " << totaltime << " Minutes" << endl
		 << endl;

	cout << "Departure Date: " << Year << "/" << setw(2) << setfill('0') << Month << "/" << setw(2) << setfill('0') << Days << endl;
	cout << "Departure Time: " << setw(2) << setfill('0') << Hours << ":" << setw(2) << setfill('0') << Minutes << endl
		 << endl;

	string departureDate = to_string(Year) + "/" + to_string(Month) + "/" + to_string(Days);
	string departureTime = to_string(Hours) + ":" + to_string(Minutes);

	int arrival_year = Year;
	int arrival_month = Month;
	int arrival_days = Days;
	int arrival_hours = Hours;
	int arrival_minutes = Minutes + totaltime;

	// Check Minutes
	if (arrival_minutes > 59)
	{
		arrival_minutes = arrival_minutes - 60;
		arrival_hours = arrival_hours + 1;
	}

	// Check Hours
	if (arrival_hours > 23)
	{
		arrival_hours = 0;
		arrival_days = arrival_days + 1;
	}

	// Check Days
	if ((arrival_month == 4 || arrival_month == 6 || arrival_month == 9 || arrival_month == 11) && arrival_days > 30)
	{
		arrival_days = 1;
		arrival_month = arrival_month + 1;
	}
	else if (arrival_month == 2)
	{
		// leap year
		if (arrival_year % 4 == 0 && arrival_days > 29)
		{
			arrival_days = 1;
			arrival_month = arrival_month + 1;
		}
		// not leap year
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

	// Check Months
	if (arrival_month > 12)
	{
		arrival_month = 1;
		arrival_year = arrival_year + 1;
	}

	cout << "Arrival Date: " << arrival_year << "/" << setw(2) << setfill('0') << arrival_month << "/" << setw(2) << setfill('0') << arrival_days << endl;
	cout << "Estimate Arrival Time: " << setw(2) << setfill('0') << arrival_hours << ":" << setw(2) << setfill('0') << arrival_minutes << endl
		 << endl;

	string arrivalDate = to_string(arrival_year) + "/" + to_string(arrival_month) + "/" + to_string(arrival_days);
	string arrivalTime = to_string(arrival_hours) + ":" + to_string(arrival_minutes);

	int ticketAmount;
	int totalTicketPrice;

	while (true)
	{
		cout << "Please input your ticket amount: " << endl;
		cout << "Press 0 is to return main menu: " << endl;
		cout << "Ticket amount: " << endl;
		cin >> ticketAmount;

		if (ticketAmount < 1)
		{
			return;
		}
		else if (ticketAmount > 0)
		{
			totalTicketPrice = ticketAmount * totalexpenses;
			break;
		}
		else
		{
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "Invalid Input" << endl;
		}
	}

	cout << "Total ticket price is: RM " << fixed << setprecision(2) << setfill('0') << totalTicketPrice << endl;

	int confirmPurchase;
	while (true)
	{
		cout << "Confirm Puchase? " << endl;
		cout << "1)Yes     2)No " << endl;
		cin >> confirmPurchase;

		if (confirmPurchase == 1)
		{
			break;
		}
		else if (confirmPurchase == 2)
		{
			cout << "Returning to main menu" << endl;
			return;
		}
		else
		{
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "Invalid Input" << endl;
		}
	}

	while (true)
	{
		unsigned long long int creditCardNumber;
		int CVV;
		int valid;
		cout << "Please input your Credit Card Number (16 digits): ";
		cin >> creditCardNumber;

		valid = creditCardNumber / 1000000000000000;
		cout << valid;
		if (cin.fail() || valid < 1 || valid > 9)
		{
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "Invalid Credit Card number" << endl;
			continue;
		}
		cout << "Please input your CVV Number (3 digits): ";
		cin >> CVV;
		cout << valid;
		valid = CVV / 100;

		if (cin.fail() || valid < 1 || valid > 9)
		{
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "Invalid CVV number" << endl;
			continue;
		}

		break;
	}

	createTicket(TicketRoute, departureStation, arrivalStation, departureDate, departureTime, ticketAmount, totalTicketPrice, customerId);

	cout << "Thank You Very Much" << endl;
	system("pause");
}
// Customer Purchase Ticket
void purchaseticket(int customerId)
{
	int route;
	// Select Route
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
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
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
		cout << "9) Return to Main Menu" << endl
			 << endl;
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
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
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
		cout << "9) Return to Main Menu" << endl
			 << endl;
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
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "Incorrect Input" << endl;
			system("pause");
		}
	}

	// Select Departure Date
	int DepartureYear, DepartureMonth, DepartureDay;
	char seperator1, seperator2;
	int InputCorrect = 0;
	int TodayDate = 0;

	while (InputCorrect == 0)
	{
		system("CLS");
		cout << "Please enter your departure Date (in YYYY/MM/DD format): " << endl;
		cout << "Note: Ticket can only be bought before 2025" << endl;
		cout << "Date: ";
		cin >> DepartureYear >> seperator1 >> DepartureMonth >> seperator2 >> DepartureDay;

		if (cin.fail() || seperator1 != '/' || seperator2 != '/')
		{
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "Invalid Format" << endl;
			system("pause");
			continue;
		}

		switch (isValidDate(DepartureYear, DepartureMonth, DepartureDay))
		{
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

	// display details between two cities and confirm purchase
	displayDetailsBetweenTwoSelectedCities(route, departure, arrival, DepartureYear, DepartureMonth, DepartureDay, DepartureHour, DepartureMinutes, customerId);
}

// 2) Print Station Details
void printStationDetails()
{
	int decision;
	cout << "1) Titiwangsa" << endl;
	cout << "2) PWTC" << endl;
	cout << "3) Sultan Ismail" << endl;
	cout << "4) Majlis Jamek" << endl;
	cout << "5) Plaza Rakyat" << endl;
	cout << "6) Hang Tuah" << endl;
	cout << "7) Pudu" << endl;
	cout << "8) Chan Sow Lin" << endl;
	cout << "9) Return to Main Menu" << endl
		 << endl;
	cin >> decision;

	if (decision > 0 && decision < 9)
	{
		stationCurrent = stationHead;
		while (stationCurrent != NULL)
		{
			if (stationCurrent->StationID == decision)
			{
				cout << "Station ID: " << stationCurrent->StationID << endl;
				cout << "Staion Name: " << stationCurrent->StationName << endl;
				cout << "Station Previous Station Name: " << stationCurrent->PreviousStationName << endl;
				cout << "Station Next Station Name: " << stationCurrent->NextStationName << endl;
				cout << "Distance Between Previous Station: " << stationCurrent->DistanceBetweenPreviousStation << endl;
				cout << "Cost Between Previous Station: " << stationCurrent->CostBetweenPreviousStation << endl;
				cout << "Time Between Previous Station: " << stationCurrent->TimeBetweenPreviousStation << endl;
				cout << "Distance Between Next Station: " << stationCurrent->DistanceBetweenNextStation << endl;
				cout << "Cost Between Next Station: " << stationCurrent->CostBetweenNextStation << endl;
				cout << "Time Between Next Station: " << stationCurrent->TimeBetweenNextStation << endl;
				cout << "Nearby Sightseeing Spots: " << stationCurrent->NearbySightseeingSpots << endl;
				break;
			}
			stationCurrent = stationCurrent->nextAdd;
		}

		int Continue;
		while (true)
		{
			cout << "Continue Searching for station details ?" << endl;
			cout << "1) Yes     2) No" << endl;
			cin >> Continue;

			if (Continue == 1)
			{
				printStationDetails();
			}
			else if (Continue == 2)
			{
				return;
			}
			else
			{
				cin.clear();										 // remove the input operation
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
				cout << "Incorrect Input" << endl;
			}
		}
	}
	else if (decision == 9)
	{
		return;
	}
	else
	{
		cin.clear();										 // remove the input operation
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
		cout << "Incorrect Input" << endl;
		printStationDetails();
	}
}
void printAllStationDetails()
{
	stationCurrent = stationHead;
	while (stationCurrent != NULL)
	{
		cout << "Station ID: " << stationCurrent->StationID << endl;
		cout << "Staion Name: " << stationCurrent->StationName << endl;
		cout << "Station Previous Station Name: " << stationCurrent->PreviousStationName << endl;
		cout << "Station Next Station Name: " << stationCurrent->NextStationName << endl;
		cout << "Distance Between Previous Station: " << stationCurrent->DistanceBetweenPreviousStation << endl;
		cout << "Cost Between Previous Station: " << stationCurrent->CostBetweenPreviousStation << endl;
		cout << "Time Between Previous Station: " << stationCurrent->TimeBetweenPreviousStation << endl;
		cout << "Distance Between Next Station: " << stationCurrent->DistanceBetweenNextStation << endl;
		cout << "Cost Between Next Station: " << stationCurrent->CostBetweenNextStation << endl;
		cout << "Time Between Next Station: " << stationCurrent->TimeBetweenNextStation << endl;
		cout << "Nearby Sightseeing Spots: " << stationCurrent->NearbySightseeingSpots << endl;
		stationCurrent = stationCurrent->nextAdd;
	}
}

// 3) Check, Print and Delete Transaction History
void deletePurchaseTransaction(int customerId)
{
	int transactionId;
	int confirm = 0;
	cout << "Please input your transaction id: " << endl;
	cin >> transactionId;

	// check whehter this transaction id is in this passenger account
	ticketCurrent = ticketHead;
	Ticket *ticketTemp;
	while (ticketCurrent != NULL)
	{
		if (ticketCurrent->TransactionID == transactionId && ticketCurrent->CustomerID == customerId)
		{
			if (ticketCurrent == ticketHead)
			{
				ticketHead = ticketHead->nextAdd;
			}

			ticketTemp = ticketCurrent;
			ticketCurrent = ticketCurrent->nextAdd;
			delete ticketTemp;
			confirm++;
			ticketCounts--;
		}
		else
		{
			ticketCurrent = ticketCurrent->nextAdd;
		}
	}

	if (confirm > 0)
	{
		cout << "Transaction deleted sucessful, fund will be refund to your credit card" << endl;
		return;
	}
	else
	{
		cout << "Transaction is not found, returning to main menu" << endl;
	}
}
void printAndDeleteTransactionHistory(int customerId)
{
	// If system has no ticket history
	if (ticketHead == NULL)
	{
		cout << "This system has no transaction history" << endl;
		return;
	}

	else
	{
		int ticketCount = 0;
		ticketCurrent = ticketHead;
		while (ticketCurrent != NULL)
		{
			if (ticketCurrent->CustomerID == customerId)
			{
				cout << "Transaction Id: " << ticketCurrent->TransactionID << endl;
				cout << "Ticket id: " << ticketCurrent->TicketID << endl;
				cout << "Ticket Route: " << ticketCurrent->TicketRoute << endl;
				cout << "Departure Station: " << ticketCurrent->NameOfTheSourceStation << endl;
				cout << "Arrival Station: " << ticketCurrent->NameofTheTargetStation << endl;
				cout << "Ticket Amount: " << ticketCurrent->TicketAmount << endl;
				cout << "Transaction Date And Time: " << ticketCurrent->TransactionDateAndTime << endl;
				cout << "Departure Date: " << ticketCurrent->DepartureDate << endl;
				cout << "Departure Time: " << ticketCurrent->DepartureTime << endl;
				cout << "Total Ticket Price: " << ticketCurrent->TotalTicketPrice << endl
					 << endl;
				ticketCount++;
			}
			ticketCurrent = ticketCurrent->nextAdd;
		}

		if (ticketCount > 0)
		{
			cout << "You have total of " << ticketCount << " tickets in your account" << endl;
		}
		else
		{
			cout << "This account has no purchase history" << endl;
		}
	}

	int choice;
	while (true)
	{
		cout << "1) Delete purchase transaction" << endl;
		cout << "2) Return to Main menu " << endl;
		cin >> choice;
		if (choice == 1)
		{
			deletePurchaseTransaction(customerId);
			return;
		}
		else if (choice == 2)
		{
			return;
		}
		else
		{
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "Invalid Input" << endl;
		}
	}
}

// Admin 1.13
void addNewSubwayStationInformation()
{
	string stationName, previousStationName, nextStationName, nearbyBySightseeingSpots;
	double distanceBetweenPreviousStation, costBetweenPreviousStation, distanceBetweenNextStation, costBetweenNextStation;
	int timeBetweenPreviousStation, timeBetweenNextStation;
	int stationId = stationTail->StationID + 1;
	cout << "What is the name of the station: ";
	cin >> stationName;
	cout << "What is the name of previous station: ";
	cin >> previousStationName;
	cout << "What is the name of next station: ";
	cin >> nextStationName;
	cout << "What is the distance between previous station: ";
	cin >> distanceBetweenPreviousStation;
	cout << "What is the cost between previous station: ";
	cin >> costBetweenPreviousStation;
	cout << "What is the time between previous station: ";
	cin >> timeBetweenPreviousStation;
	cout << "What is the distance between next station: ";
	cin >> distanceBetweenNextStation;
	cout << "What is the cost between next station: ";
	cin >> costBetweenNextStation;
	cout << "What is the time between next station: ";
	cin >> timeBetweenNextStation;
	cout << "What is the nearby sight seeing spots: ";
	getline(cin, nearbyBySightseeingSpots);

	Station *newStationNode = createStationNode(stationId, stationName, previousStationName, nextStationName,
												distanceBetweenPreviousStation, costBetweenPreviousStation,
												timeBetweenPreviousStation, distanceBetweenNextStation, costBetweenNextStation,
												timeBetweenNextStation, nearbyBySightseeingSpots);
	insertStationNodeToTheEndList(newStationNode);
	cout << "The new subway station is successfully added" << endl;
}
void editCurrentSubwayStationsInformation()
{
	bool found = false, subwayOption = true, editOption = true;
	int stationId, option;
	while (subwayOption)
	{
		printAllStationDetails();
		cout << "Please enter the subway station's id that you would like to edit or enter 0 to exit to admin menu: ";
		cin >> stationId;
		if (stationId == 0)
		{
			subwayOption = false;
			continue;
		}
		// if no station in dataset
		if (stationHead == NULL)
		{
			cout << "There is no station for you to edit. Please add new station";
			cout << subwayOption = false;
			continue;
		}

		// validate station Id
		stationCurrent = stationHead;
		while (stationCurrent != NULL)
		{
			if (stationCurrent->StationID == stationId)
			{
				found = true;
				break;
			}
			stationCurrent = stationCurrent->nextAdd;
		}

		// if not found
		if (!found)
		{
			cout << "Invalid stationId. Please enter the correct input";
			continue;
		}

		// choose which information to edit
		while (editOption)
		{
			// menu
			cout << "You will be editing " << stationCurrent->StationID << ": " << stationCurrent->StationName << " subway station's information" << endl;
			cout << "1) Station Name" << endl;
			cout << "2) Cost Between Previous Station" << endl;
			cout << "3) Cost Between Next Station" << endl;
			cout << "4) Time Between Previous Station" << endl;
			cout << "5) Time Between Next Station" << endl;
			cout << "6) Exit to select another staiton" << endl;
			cout << "Please enter the number you option: ";
			cin >> option;

			// edit information options based on selection
			switch (option)
			{
			case 1:
				string name;
				cout << "Please enter the new station name: ";
				cin >> name;
				stationCurrent->StationName = name;
				cout >> "You had successfully updated the station name" << endl;
				cout >> endl;
				break;
			case 2:
				double cost;
				cout << "Please enter the new cost between previous station: ";
				cin >> cost;
				stationCurrent->CostBetweenPreviousStation = name;
				cout >> "You had successfully updated the cost between previous station" << endl;
				cout >> endl;
				break;
			case 3:
				double cost;
				cout << "Please enter the new cost between next station: ";
				cin >> cost;
				stationCurrent->CostBetweenNextStation = name;
				cout >> "You had successfully updated the cost between next station" << endl;
				cout >> endl;
				break;
			case 4:
				int time;
				cout << "Please enter the new time between previous station: ";
				cin >> time;
				stationCurrent->TimeBetweenPreviousStation = time;
				cout >> "You had successfully updated the time between previous station" << endl;
				cout >> endl;
				break;
			case 5:
				int time;
				cout << "Please enter the new time between next station: ";
				cin >> time;
				stationCurrent->TimeBetweenNextStation = time;
				cout >> "You had successfully updated the time between next station" << endl;
				cout >> endl;
				break;
			case 6:
				editOption = false;
				break;
			// if other inputs will considered as invalid input
			default:
				cout << "Invalid option . Please enter again" << endl;
			}
		}
	}
}
void viewAllPurchaseTransactions()
{
	ticketCurrent = ticketHead;
	while (ticketCurrent != NULL)
	{
		cout >> "Transaction ID: " >> ticketCurrent->TransactionID >> endl;
		cout >> "Ticket ID: " >> ticketCurrent->TicketID >> endl;
		cout >> "Ticket Route: " >> ticketCurrent->TicketRoute >> endl;
		cout >> "Name of The Source Station: " >> ticketCurrent->NameOfTheSourceStation >> endl;
		cout >> "Name of The Target Station: " >> ticketCurrent->NameofTheTargetStation >> endl;
		cout >> "Transaction Date and Time: " >> ticketCurrent->TransactionDateAndTime >> endl;
		cout >> "Depature Date: " >> ticketCurrent->DepartureDate >> endl;
		cout >> "Depature Time: " >> ticketCurrent->DepartureTime >> endl;
		cout >> "Total Ticket Price: " >> ticketCurrent->TotalTicketPrice >> endl;
		cout >> "Customer ID: " >> ticketCurrent->Customer ID >> endl;
		cout >> "Customer Name: " >> ticketCurrent->Name >> endl;
		cout >> "Customer IC / Passport: " >> ticketCurrent->CustomerIcOrPassport >> endl;
		ticketCurrent = ticketCurrent->nextAdd;
	}
	cout >> "This is the end of the purchase transaction" >> endl;
}
void sortPurchaseTransaction()
{
	ticketCurrent = ticketHead;
	Ticket ticketArray[ticketCounts] = {};
	int index = 0;
	while (ticketCurrent != NULL)
	{
		Ticket *tempNode = createTicketNode(ticketCurrent->TransactionID,
											ticketCurrent->TicketID,
											ticketCurrent->TicketRoute,
											ticketCurrent->NameOfTheSourceStation,
											ticketCurrent->NameofTheTargetStation,
											ticketCurrent->TicketAmount,
											ticketCurrent->TransactionDateAndTime,
											ticketCurrent->DepartureDate,
											ticketCurrent->DepartureTime,
											ticketCurrent->TotalTicketPrice,
											ticketCurrent->CustomerID,
											ticketCurrent->CustomerName,
											ticketCurrent->CustomerIcOrPassport)
	}
}
void searchPurchaseCustomerTicketPurchaseInformation() {}
int checkTransactionIdAvailable(int transactionId)
{
	ticketCurrent = ticketHead;
	if (ticketHead == NULL)
	{
		return 0;
	}
	while (ticketCurrent != NULL)
	{
		if (ticketCurrent->TransactionID == transactionId)
		{
			return 1;
		}
		ticketCurrent = ticketCurrent->nextAdd;
	}
	return 0;
}
void editCustomerTicket()
{
	int transactionid;
	cout << "Input transaction id: " << endl;
	cin >> transactionid;

	int status = checkTransactionIdAvailable(transactionid);

	if (status == 0)
	{
		cout << " Transaction id is not found " << endl;
		editCustomerTicket();
	}

	int editSelection;
	cout << "1) Edit destinaton" << endl;
	cout << "2) Edit departure time" << endl;
	cin >> editSelection;

	// Select route
	int route;
	while (true)
	{
		cout << "1) Titiwangsa -> Chan Sow Lin" << endl;
		cout << "2) Chan Sow Lin -> Titiwangsa" << endl;
		cout << "3) Return to main menu" << endl;
		cout << "Select your route: " << endl;
		cin >> route;

		if (route == 1)
		{
			break;
		}
		else if (route == 2)
		{
			break;
		}
		else
		{
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "Incorrect Input" << endl;
			system("pause");
		}
	}

	// Select Departure Station
	int departure;
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
		cout << "9) Return to Main Menu" << endl
			 << endl;
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
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "Incorrect Input" << endl;
		}
		system("pause");
	}

	if (editSelection == 1)
	{
		// Select Arrival Station
		int arrival;
		while (true)
		{
			system("CLS");
			listAllPossibleArrivalStation(route, departure);
			cout << "9) Return to Main Menu" << endl
				 << endl;
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
				cin.clear();										 // remove the input operation
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
				cout << "Incorrect Input" << endl;
				system("pause");
			}
		}

		string TicketRoute;
		string departureStation;
		string arrivalStation;
		int totalNewExpensesPerTicket = 0;

		if (route == 1)
		{
			TicketRoute = "Titiwangsa -> Chan Sow Lin";
			stationCurrent = stationHead;
			for (int i = 1; i < departure; i++)
			{
				stationCurrent = stationCurrent->nextAdd;
			}

			departureStation = stationCurrent->StationName;
			cout << "Departure Station: " << departureStation << endl;

			for (int i = departure; i < arrival; i++)
			{
				totalNewExpensesPerTicket = totalNewExpensesPerTicket + stationCurrent->CostBetweenNextStation;
				stationCurrent = stationCurrent->nextAdd;
			}

			arrivalStation = stationCurrent->StationName;
			cout << "Arrival Station: " << arrivalStation << endl;
		}
		else if (route == 2)
		{
			TicketRoute = "Chan Sow Lin -> Titiwangsa";
			stationCurrent = stationTail;
			for (int i = 8; i > departure; i--)
			{
				stationCurrent = stationCurrent->prevAdd;
			}

			departureStation = stationCurrent->StationName;
			cout << "Departure Station: " << departureStation << endl;

			for (int i = departure; i > arrival; i--)
			{
				totalNewExpensesPerTicket = totalNewExpensesPerTicket + stationCurrent->CostBetweenPreviousStation;
				stationCurrent = stationCurrent->prevAdd;
			}

			arrivalStation = stationCurrent->StationName;
			cout << "Arrival Station: " << arrivalStation << endl;
		}

		int oldTotalTicketPrice;
		int confirm;
		cout << "Confirm Exchange ?" << endl;
		cout << "1) Yes 2) No" << endl;
		cin >> confirm;

		while (true)
		{
			if (confirm == 1)
			{
				ticketCurrent = ticketHead;
				while (ticketCurrent != NULL)
				{
					if (ticketCurrent->TransactionID == transactionid)
					{
						ticketCurrent->TicketRoute = TicketRoute;
						ticketCurrent->NameOfTheSourceStation = departureStation;
						ticketCurrent->NameofTheTargetStation = arrivalStation;
						oldTotalTicketPrice = ticketCurrent->TotalTicketPrice;
						ticketCurrent->TotalTicketPrice = totalNewExpensesPerTicket * ticketCurrent->TicketAmount;
					}
					ticketCurrent = ticketCurrent->nextAdd;
				}

				int additionalPayment = totalNewExpensesPerTicket - oldTotalTicketPrice;
				if (additionalPayment > 0)
				{
					cout << "Additional payment is needed: RM " << fixed << setprecision(2) << setfill('0') << additionalPayment << endl;
				}
				else if (additionalPayment < 0)
				{
					cout << "Return change: RM " << fixed << setprecision(2) << setfill('0') << additionalPayment * -1 << endl;
				}
				else
				{
					cout << "No additional payment is needed" << endl;
				}
			}
			else if (confirm == 2)
			{
				return;
			}
			else
			{
				cin.clear();										 // remove the input operation
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
				cout << "Incorrect Input" << endl;
				system("pause");
			}
		}
	}

	else if (editSelection == 2)
	{
		// Select Departure Date
		int DepartureYear, DepartureMonth, DepartureDay;
		char seperator1, seperator2;
		int InputCorrect = 0;
		int TodayDate = 0;

		while (InputCorrect == 0)
		{
			system("CLS");
			cout << "Please enter your departure Date (in YYYY/MM/DD format): " << endl;
			cout << "Date: ";
			cin >> DepartureYear >> seperator1 >> DepartureMonth >> seperator2 >> DepartureDay;

			if (cin.fail() || seperator1 != '/' || seperator2 != '/')
			{
				cin.clear();										 // remove the input operation
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
				cout << "Invalid Format" << endl;
				system("pause");
				continue;
			}

			switch (isValidDate(DepartureYear, DepartureMonth, DepartureDay))
			{
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

		string departureDate = to_string(DepartureYear) + "/" + to_string(DepartureMonth) + "/" + to_string(DepartureDay);
		string departureTime = to_string(DepartureHour) + ":" + to_string(DepartureMinutes);

		ticketCurrent = ticketHead;
		while (ticketCurrent != NULL)
		{
			if (ticketCurrent->TransactionID == transactionid)
			{
				ticketCurrent->DepartureDate = departureDate;
				ticketCurrent->DepartureTime = DepartureTime;
			}
		}
	}
	cout << "Edit Sucessful" << endl;
	system("pause");
	system("cls");
}

int main()
{
	stationHead = stationTail = NULL;

	Station *StationNode1 = createStationNode(1, "Titiwangsa", "", "PWTC", 0, 0, 0, 4, 0.40, 3, "Providence KL");
	Station *StationNode2 = createStationNode(2, "PWTC", "Titiwangsa", "Sultan Ismail", 4, 0.40, 3, 8, 0.80, 7, "Sunway Putra Mall");
	Station *StationNode3 = createStationNode(3, "Sultan Ismail", "PWTC", "Majlis Jamek", 8, 0.80, 7, 8, 0.80, 7, "Jalan Tunku Abdul Rahman");
	Station *StationNode4 = createStationNode(4, "Majlid Jamek", "Sultan Ismail", "Plaza Rakyat", 8, 0.80, 7, 6, 0.60, 5, "Jamek Mosque");
	Station *StationNode5 = createStationNode(5, "Plaza Rakyat", "Majlis Jamek", "Hang Tuah", 6, 0.60, 5, 10, 1.00, 9, "St. Anthony Chruch");
	Station *StationNode6 = createStationNode(6, "Hang Tuah", "Plaza Rakyat", "Pudu", 10, 1.00, 9, 5, 0.50, 4, "Berjaya Time Square");
	Station *StationNode7 = createStationNode(7, "Pudu", "Hang Tuah", "Chan Sow Lin", 5, 0.50, 4, 5, 0.50, 4, "Pasar Besar Pudu");
	Station *StationNode8 = createStationNode(8, "Chan Sow Lin", "Pudu", "", 5, 0.50, 4, 0, 0, 0, "East Club");

	insertStationNodeToTheEndList(StationNode1);
	insertStationNodeToTheEndList(StationNode2);
	insertStationNodeToTheEndList(StationNode3);
	insertStationNodeToTheEndList(StationNode4);
	insertStationNodeToTheEndList(StationNode5);
	insertStationNodeToTheEndList(StationNode6);
	insertStationNodeToTheEndList(StationNode7);
	insertStationNodeToTheEndList(StationNode8);

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
				cout << "3) Return to Main Menu" << endl;
				cout << "Select your role: ";
				cin >> role;

				// Passenger
				if (role == 1)
				{
					string customerAccount;
					string customerPassword;
					cout << "Please Enter your IC or Passport Number" << endl;
					cin >> customerAccount;
					cout << "Please Enter your Password" << endl;
					cin >> customerPassword;

					int customerId = checkCustomerLoggingAccount(customerAccount, customerPassword);

					if (customerId != 0)
					{
						int customerDecision;
						while (true)
						{
							cout << "1) Purchase Ticket" << endl;
							cout << "2) Search subway station details" << endl;
							cout << "3) View and delete transaction history" << endl;
							cout << "5) Exit to Main Menu" << endl;
							cin >> customerDecision;
							if (customerDecision == 1)
							{
								purchaseticket(customerId);
							}
							else if (customerDecision == 2)
							{
								printStationDetails();
							}
							else if (customerDecision == 3)
							{
								printAndDeleteTransactionHistory(customerId);
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

				// Admin
				else if (role == 2)
				{
					string adminAccount;
					string adminPassword;
					cout << "Please Enter username" << endl;
					cin >> adminAccount;
					cout << "Please Enter password" << endl;
					cin >> adminPassword;

					if (adminAccount == "admin" && adminPassword == "12345")
					{
						int decision;
						bool loop = true;
						while (loop)
						{
							cout << "1) Add new subway information" << endl;
							cout << "2) Edit current subway stations' information" << endl;
							cout << "3) View all purchase transactions" << endl;
							cout << "4) Sort purchase transaction based on passenger name" << endl;
							cout << "5) Search specific customer ticket purchase information" << endl;
							cout << "6) Edit specific customer ticket purchase information" << endl;
							cout << "7) Delete specific customer ticket purchase information" << endl;
							cout << "8) Exit to Main Menu" << endl;
							cout << "Please enter your option: ";
							cin >> decision;
							switch (decision)
							{
							case 1:
								addNewSubwayStationInformation();
								break;
							case 2:
								editCurrentSubwayStationsInformation();
								break;
							case 3:
								viewAllPurchaseTransactions();
								break;
							case 4:
								sortPurchaseTransaction();
								break;
							case 5:
								searchPurchaseCustomerTicketPurchaseInformation();
								break;
							case 6:
								editCustomerTicket();
								break;
							case 7:
								int customerId;
								cout << "Input Customer Id: " << endl;
								cin >> customerId;
								deletePurchaseTransaction(customerId);
								break;
							case 8:
								loop = false;
								break;
							default:
								cout << "Invalid input" << endl;
							}
						}
					}
				}
				else if (role == 3)
				{
					break;
				}
				else
				{
					cin.clear();										 // remove the input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
					cout << "Invalid Format" << endl;
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
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "Invalid Format" << endl;
			system("pause");
		}
	}

	cout << "Bye";

	return 0;
}