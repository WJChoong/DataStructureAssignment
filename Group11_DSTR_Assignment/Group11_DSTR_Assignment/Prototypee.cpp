﻿#include <iostream>
#include <string>
#include <stdlib.h> //Clear Text in Output
#include <ctime>	//Get Current Date and Time
#include <iomanip>	//Make character to 2 digit
#include <limits>
#include <chrono>
#include <thread>
using namespace std;



//----------------------------------------------------
//---------------   Data Structure   -----------------
//----------------------------------------------------


struct Station
{
	// Station Details
	string StationID; // (Station ID Starting from S001, manually input at first, but auto increment if more station is added)
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

	//Station Node Address
	Station* nextAdd; // Linked List - Address of Next Node
	Station* prevAdd; // Linked List - Address of Previous Node

} *stationHead, * stationCurrent, * stationTail;
int ticketCounts = 0; // calculate total tickets in the system
struct Ticket
{
	//Ticket Details
	string TransactionID; // (Transaction ID Starting from T001, auto increment)
	string TicketID; // (Ticket ID Starting from K001, auto increment)
	string TicketRoute;
	string NameOfTheSourceStation;
	string NameofTheTargetStation;
	int TicketAmount;
	string TransactionDateAndTime;
	string DepartureDate;
	string DepartureTime;
	double TotalTicketPrice;
	string CustomerID; // (Customer ID Starting from C001, auto increament when new account is created)
	string CustomerName;
	string CustomerIcOrPassport;

	//Ticket Node Address
	Ticket* nextAdd; // Linked List - Address of Next Node

} *ticketHead, * ticketCurrent, *ticketTail;
struct Customer
{
	// Customer Details
	string CustomerId; // (Customer ID Starting from C001, auto increament when new account is created)
	string CustomerName;
	string CustomerIcOrPassport;
	string CustomerPassword;

	// Customer Node Address
	Customer* nextAdd; // Linked List - Address of next node
} *customerHead, * customerCurrent, * customerTail;





//----------------------------------------------------
//-------------------   Intro   ----------------------
//----------------------------------------------------


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
void displayMessage(string message)
{
	cout << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << message << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << endl;
	std::this_thread::sleep_for(3000ms);
}





//----------------------------------------------------
//-------------   ID Extract and Making   ------------
//----------------------------------------------------


//Extract number from id
int idExtract(string ID)
{
	string idArray[4];

	for (int i = 0; i < 4; i++)
	{
		idArray[i] = ID[i];
	}

	int number;
	int value1, value2, value3;
	value1 = stoi(idArray[1]);
	value2 = stoi(idArray[2]);
	value3 = stoi(idArray[3]);
	string s;
	if (value1 > 0)
	{
		s = idArray[1] + idArray[2] + idArray[3];
		number = stoi(s);
	}
	else if (value2 > 0)
	{
		s = idArray[2] + idArray[3];
		number = stoi(s);
	}
	else
	{
		s = idArray[3];
		number = stoi(s);
	}

	return number;
}
string idMaker(string idType,int ID)
{
	string LeadingZero;
	string id = idType;
	
	int test;
	test = ID - 10;

	if (test >= 90)
	{
		LeadingZero = "";
	}
	else if (test >= 0)
	{
		LeadingZero = "0";
	}
	else
	{
		LeadingZero = "00";
	}


	id = id + LeadingZero + to_string(ID);

	return id;
}





//----------------------------------------------------
//------------------   Station   ---------------------
//----------------------------------------------------


// create a Station node function
Station* createStationNode(string StationID, string StationName, string PreviousStationName, string NextStationName,
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
// Insert Station Node to the End of the list
void insertStationNodeToTheEndList(Station* StationNode)
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





//----------------------------------------------------
//------   Customer Loging and Create Account   ------
//----------------------------------------------------


// create a Customer node function
Customer* createCustomerNode(string customerId, string customerName, string customerIcOrPassport, string customerPassword)
{
	Customer* CustomerNode = new Customer;
	CustomerNode->CustomerId = customerId;
	CustomerNode->CustomerName = customerName;
	CustomerNode->CustomerIcOrPassport = customerIcOrPassport;
	CustomerNode->CustomerPassword = customerPassword;

	CustomerNode->nextAdd = NULL;

	return CustomerNode;
}
// Insert Customer Node to the End of the list
void insertCustomerNodeToTheEndList(Customer* CustomerNode)
{
	// Situation 1: List still empty
	if (customerHead == NULL)
	{
		customerHead = customerTail = CustomerNode;
	}

	// Situation 2: List not empty
	else
	{
		customerTail->nextAdd = CustomerNode;
		customerTail = CustomerNode;
	}
}
// Check Customer Account when Creating a new Customer Account
int createCustomerAccount(string customerName, string customerIcOrPassport, string customerPassword)
{
	int customerIdNo;
	if (customerHead == NULL)
	{
		customerIdNo = 1;
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
		customerIdNo = idExtract(customerCurrent->CustomerId) + 1;
	}

	string customerId = idMaker("C", customerIdNo);

	// If the customer does not exist in the system, the account will be created
	Customer* customerNode = createCustomerNode(customerId, customerName, customerIcOrPassport, customerPassword);
	insertCustomerNodeToTheEndList(customerNode);
	return 1;
}
// Check Customer Account and password when logging
string checkCustomerLoggingAccount(string customerIcOrPassport, string customerPassword)
{
	// If there is no account exists in this system
	if (customerHead == NULL)
	{
		cout << "This system has no customer account" << endl;
		system("pause");
		return "";
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
				return "";
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
					return "";
				}
			}
		}
	}
	cout << "This IC or Passport Number does not exist in this system, Please create a new account." << endl;
	system("pause");
	return "";
}





//----------------------------------------------------
//------------   Generating Ticket   -----------------
//----------------------------------------------------


// create a Ticket node function
Ticket* createTicketNode(string transactionId, string ticketId, string TicketRoute, string departureStation, string arrivalStation, int ticketAmount,
	string transactionDateAndTime, string departureDate, string departureTime,
	double totalTicketPrice, string customerId, string customerName, string customerIcOrPassport)
{
	Ticket* TicketNode = new Ticket;
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
// Insert Ticket Node to the Front of the list
void insertTicketNodeToTheEndList(Ticket* ticketNode) 
{
	// Situation 1: List still empty
	if (ticketHead == NULL)
	{
		ticketHead = ticketTail = ticketNode;
	}

	// Situation 2: List not empty
	else
	{
		ticketTail->nextAdd = ticketNode;
		ticketTail = ticketNode;
	}
	ticketCounts++;
}
// Create Ticket
void createTicket(string TicketRoute, string departureStation, string arrivalStation, string departureDate, string departureTime, int ticketAmount, double totalTicketPrice, string customerId)
{
	// get newest transaction id and ticket id
	int transactionIdno = 0;
	int ticketIdno = 0;
	if (ticketHead == NULL)
	{
		transactionIdno = 1;
		ticketIdno = 1;
	}
	else
	{
		ticketCurrent = ticketHead;
		while (ticketCurrent != NULL)
		{
			// Generating Transaction ID
			if (idExtract(ticketCurrent->TransactionID) > transactionIdno)
			{
				transactionIdno = idExtract(ticketCurrent->TransactionID) + 1;
			}
			// Geneating Ticket ID
			if (idExtract(ticketCurrent->TicketID) > ticketIdno)
			{
				ticketIdno = idExtract(ticketCurrent->TicketID) + 1;
			}
			ticketCurrent = ticketCurrent->nextAdd;
		}
	}

	string transactionId = idMaker("T", transactionIdno);
	string ticketId = idMaker("K", ticketIdno);



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
		Ticket* ticketNode = createTicketNode(transactionId, ticketId, TicketRoute, departureStation, arrivalStation, ticketAmount, transactionDateAndTime, departureDate, departureTime, totalTicketPrice, customerId, customerName, customerIcOrPassport);
		insertTicketNodeToTheEndList(ticketNode);
	}
}





//----------------------------------------------------
//-----------------   Customer  ----------------------
//----------------------------------------------------

//List route
int listRoute()
{
	int route;
	cout << "1) " << stationHead->StationName << " -> " << stationTail->StationName << endl;
	cout << "2) " << stationHead->StationName << " <- " << stationTail->StationName << endl;
	cout << "3) Return to main menu" << endl;
	cout << "Select your route: " << endl;

	while (true)
	{
		cin >> route;
		if (route == 3)
		{
			return 0;
		}
		else if (route == 1 || route == 2)
		{
			return route;
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
//List Departure
int listAllPossibleDeparture(int route)
{
	int totalNumberofStation = idExtract(stationTail->StationID);
	switch (route)
	{
	case 1:
		stationCurrent = stationHead;
		for (int i = 1; i < totalNumberofStation; i++)
		{
			cout << i << ") ";
			cout << stationCurrent->StationName << endl;
			stationCurrent = stationCurrent->nextAdd;
		}
		break;

	case 2:
		stationCurrent = stationHead->nextAdd;
		for (int i = 1; i < totalNumberofStation; i++)
		{
			cout << i << ") ";
			cout << stationCurrent->StationName << endl;
			stationCurrent = stationCurrent->nextAdd;
		}
	}

	cout << totalNumberofStation << ") Return to Main menu" << endl;

	int departure;
	while (true)
	{
		cin >> departure;
		if (departure > 0 && departure < totalNumberofStation)
		{
			switch (route)
			{
			case 1:
				return departure;
			case 2:
				return departure + 1;
			}
			
		}
		else if(departure == totalNumberofStation)
		{
			return 0;
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
// List all possible arrival route
int listAllPossibleArrivalStation(int route, int departure)
{
	int totalNumberofStation = idExtract(stationTail->StationID);
	stationCurrent = stationHead;

	int lastSelection = 1;
	switch (route)
	{
	case 1:
		for (int i = 1; i <= totalNumberofStation; i++)
		{
			if (idExtract(stationCurrent->StationID) <= departure)
			{
				stationCurrent = stationCurrent->nextAdd;
			}
			else
			{
				cout << lastSelection << ") ";
				cout << stationCurrent->StationName << endl;
				stationCurrent = stationCurrent->nextAdd;
				lastSelection++;
			}
		}
		break;

	case 2:
		for (int i = 1; i < departure; i++)
		{
			lastSelection++;
			cout << i << ") ";
			cout << stationCurrent->StationName << endl;
			stationCurrent = stationCurrent->nextAdd;
		}
	}

	cout << lastSelection << ") Return to main menu" << endl;

	int arrival;
	while (true)
	{
		cin >> arrival;

		if (arrival > 0 && arrival < lastSelection)
		{
			switch (route)
			{
			case 1:
				return departure + arrival;
			case 2:
				return arrival;
			}
		}
		else if (arrival == lastSelection)
		{
			return 0;
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
		cout << "Select (0) to return to main menu" << endl;
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
void displayDetailsBetweenTwoSelectedCities(int route, int departure, int arrival, int Year, int Month, int Days, int Hours, int Minutes, string customerId)
{

	double totaldistance = 0;
	double totalexpenses = 0;
	int totaltime = 0;

	string TicketRoute;

	string departureStation;
	string arrivalStation;
	if (route == 1)
	{
		TicketRoute = stationHead->StationName + " -> " + stationTail->StationName;
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
		TicketRoute = stationHead->StationName + " <- " + stationTail->StationName;
		stationCurrent = stationTail;
		for (int i = idExtract(stationTail->StationID); i > departure; i--)
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
	double totalTicketPrice = 0;

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
// 1) Customer Purchase Ticket
void purchaseticket(string customerId)
{

	// Select Route
	system("CLS");
	int route;
	route = listRoute();
	if (route == 0)
	{
		return;
	}



	// Select Departure Station
	system("CLS");
	int departure;
	departure = listAllPossibleDeparture(route);
	if (departure == 0)
	{
		return;
	}


	// Select Arrival Station
	system("CLS");
	int arrival;
	arrival = listAllPossibleArrivalStation(route, departure);
	if (arrival == 0)
	{
		return;
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
	idExtract(stationTail->StationID);
	int decision;

	int count = 1;
	stationCurrent = stationHead;
	while (stationCurrent != NULL)
	{

		cout << count << ") " << "Station Name : " << stationCurrent->StationName << endl;

		stationCurrent = stationCurrent->nextAdd;
		count++;
	}

	cout << count << ") " << "Return to main menu" << endl;
	cout << "Select your station" << endl;
	cin >> decision;

	if (decision > 0 && decision < count)
	{
		stationCurrent = stationHead;
		while (stationCurrent != NULL)
		{
			if (idExtract(stationCurrent->StationID) == decision)
			{
				cout << "Station ID: " << stationCurrent->StationID << endl;
				cout << "Station Name: " << stationCurrent->StationName << endl;
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
	else if (decision == count)
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
		cout << endl;
		stationCurrent = stationCurrent->nextAdd;
	}
}

// 3) Check, Print and Delete Transaction History
void deletePurchaseTransaction(string customerId)
{
	string transactionId;
	int confirm = 0;
	cout << "Please input your transaction id: " << endl;
	cin >> transactionId;

	// check whether this transaction id is in this passenger account
	ticketCurrent = ticketHead;
	Ticket* ticketTemp;
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
void printAndDeleteTransactionHistory(string customerId)
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




//----------------------------------------------------
//-----------------    Admin    ----------------------
//----------------------------------------------------


// quick sort
/*
// https://www.geeksforgeeks.org/cpp-program-for-quicksort/
void swapTicket(Ticket* arr, int start, int end)
{
	Ticket tempTicket = arr[start];
	arr[start] = arr[end];
	arr[end] = tempTicket;
}
int partition(Ticket arr[], int start, int end)
{
	Ticket pivot = arr[start];
	int count = 0;
	for (int i = start + 1; i <= end; i++)
	{
		if (arr[i].CustomerName <= pivot.CustomerName)
			count++;
	}

	int pivotIndex = start + count;

	// sorting
	swapTicket(arr, pivotIndex, start);

	int i = start, j = end;

	while (i < pivotIndex && j > pivotIndex)
	{
		while (arr[i].CustomerName <= pivot.CustomerName)
		{
			i++;
		}
		while (arr[j].CustomerName > pivot.CustomerName)
		{
			j--;
		}

		if (i < pivotIndex && j > pivotIndex)
		{
			Ticket tempTicket = arr[i++];
			arr[pivotIndex] = arr[start];
			arr[start] = tempTicket;
		}
	}
	return pivotIndex;
}
void quickSort(Ticket* arr, int start, int end)
{
	if (start >= end)
		return;

	int p = partition(arr, start, end);

	quickSort(arr, start, p - 1);

	quickSort(arr, p + 1, end);
}


void addNewSubwayStationInformation()
{
	// need to change
	string stationName, previousStationName, nearbyBySightseeingSpots;
	double distanceBetweenPreviousStation, costBetweenPreviousStation;
	int timeBetweenPreviousStation;
	int stationId = stationTail->StationID + 1;
	cout << "What is the name of the station: ";
	getline(cin >> ws, stationName);

	previousStationName = stationTail->StationName;
	cout << "What is the distance between previous station: ";
	cin >> distanceBetweenPreviousStation;
	cout << "What is the cost between previous station: ";
	cin >> costBetweenPreviousStation;
	cout << "What is the time between previous station: ";
	cin >> timeBetweenPreviousStation;
	cout << "What are the nearby sight seeing spotes of the station: ";
	getline(cin >> ws, nearbyBySightseeingSpots);

	Station* tempStationNode = createStationNode(stationId, stationName, previousStationName, "",
		distanceBetweenPreviousStation, costBetweenPreviousStation,
		timeBetweenPreviousStation, 0.0, 0.0,
		0, nearbyBySightseeingSpots);
	stationTail->NextStationName = stationName;
	stationTail->DistanceBetweenNextStation = distanceBetweenPreviousStation;
	stationTail->CostBetweenNextStation = costBetweenPreviousStation;
	stationTail->TimeBetweenNextStation = timeBetweenPreviousStation;
	stationTail->nextAdd = tempStationNode;
	printAllStationDetails();
	cout << "The new subway station is successfully added" << endl;
	cout << endl;
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
			displayMessage("There is no station for you to edit. Please add new station");
			subwayOption = false;
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
			displayMessage("Invalid stationId. Please enter the correct input");
			continue;
		}
		cin.clear();
		string name;
		double cost;
		int time;
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
				cout << "Please enter the new station name: ";
				getline(cin >> ws, name);
				stationCurrent->StationName = name;
				displayMessage("You had successfully updated the station name");
				editOption = false;
				break;
			case 2:
				cout << "Please enter the new cost between previous station: ";
				cin >> cost;
				stationCurrent->CostBetweenPreviousStation = cost;
				displayMessage("You had successfully updated the cost between previous station");
				editOption = false;
				break;
			case 3:
				cout << "Please enter the new cost between next station: ";
				cin >> cost;
				stationCurrent->CostBetweenNextStation = cost;
				displayMessage("You had successfully updated the cost between next station");
				editOption = false;
				break;
			case 4:
				cout << "Please enter the new time between previous station: ";
				cin >> time;
				stationCurrent->TimeBetweenPreviousStation = time;
				displayMessage("You had successfully updated the time between previous station");
				editOption = false;
				break;
			case 5:
				cout << "Please enter the new time between next station: ";
				cin >> time;
				stationCurrent->TimeBetweenNextStation = time;
				displayMessage("You had successfully updated the time between next station");
				editOption = false;
				break;
			case 6:
				editOption = false;
				break;
				// if other inputs will considered as invalid input
			default:
				displayMessage("Invalid option . Please enter again");
			}
		}
	}
}
void viewAllPurchaseTransactions()
{
	if (ticketHead == NULL)
	{
		displayMessage("There is no transaction record!");
	}
	else
	{
		ticketCurrent = ticketHead;
		while (ticketCurrent != NULL)
		{
			cout << "Transaction ID: " << ticketCurrent->TransactionID << endl;
			cout << "Ticket ID: " << ticketCurrent->TicketID << endl;
			cout << "Ticket Route: " << ticketCurrent->TicketRoute << endl;
			cout << "Name of The Source Station: " << ticketCurrent->NameOfTheSourceStation << endl;
			cout << "Name of The Target Station: " << ticketCurrent->NameofTheTargetStation << endl;
			cout << "Transaction Date and Time: " << ticketCurrent->TransactionDateAndTime << endl;
			cout << "Depature Date: " << ticketCurrent->DepartureDate << endl;
			cout << "Depature Time: " << ticketCurrent->DepartureTime << endl;
			cout << "Total Ticket Price: " << ticketCurrent->TotalTicketPrice << endl;
			cout << "Customer ID: " << ticketCurrent->CustomerID << endl;
			cout << "Customer Name: " << ticketCurrent->CustomerName << endl;
			cout << "Customer IC / Passport: " << ticketCurrent->CustomerIcOrPassport << endl;
			ticketCurrent = ticketCurrent->nextAdd;
		}
		displayMessage("This is the end of the purchase transaction");
	}
}
void sortPurchaseTransaction()
{
	ticketCurrent = ticketHead;
	// error
	Ticket* ticketArray = new Ticket[ticketCounts];
	int index = 0;
	while (ticketCurrent != NULL)
	{
		Ticket* tempNode = createTicketNode(ticketCurrent->TransactionID,
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
			ticketCurrent->CustomerIcOrPassport);
		ticketArray[index] = *tempNode;
		delete tempNode;
	}
	quickSort(ticketArray, 0, ticketCounts);

	for (int i = 0; i < ticketCounts; i++)
	{
		cout << "Transaction ID: " << ticketArray[i].TransactionID << endl;
		cout << "Ticket ID: " << ticketArray[i].TicketID << endl;
		cout << "Ticket Route: " << ticketArray[i].TicketRoute << endl;
		cout << "Name of the Source Station: " << ticketArray[i].NameOfTheSourceStation << endl;
		cout << "Name of the Target Station: " << ticketArray[i].NameofTheTargetStation << endl;
		cout << "Ticket Amount: " << ticketArray[i].TicketAmount << endl;
		cout << "Transaction Date and Time: " << ticketArray[i].TransactionDateAndTime << endl;
		cout << "Depature Date: " << ticketArray[i].DepartureDate << endl;
		cout << "Depature Time: " << ticketArray[i].DepartureTime << endl;
		cout << "Total Ticket Price: " << ticketArray[i].TotalTicketPrice << endl;
		cout << "Customer ID: " << ticketArray[i].CustomerID << endl;
		cout << "Customer Name: " << ticketArray[i].CustomerName << endl;
		cout << "Customer IC or Passport: " << ticketArray[i].CustomerIcOrPassport << endl;
	}
	cout << "The above is the sorted transaction order " << endl;
}
void searchPurchaseCustomerTicketPurchaseInformation()
{
	int ID;
	bool status = false;
	cout << "Please enter the ticket ID: ";
	cin >> ID;
	ticketCurrent = ticketHead;
	while (ticketCurrent != NULL)
	{
		if (ticketCurrent->TicketID == ID)
		{
			cout << "Transaction ID: " << ticketCurrent->TransactionID << endl;
			cout << "Ticket ID: " << ticketCurrent->TicketID << endl;
			cout << "Ticket Route: " << ticketCurrent->TicketRoute << endl;
			cout << "Name of The Source Station: " << ticketCurrent->NameOfTheSourceStation << endl;
			cout << "Name of The Target Station: " << ticketCurrent->NameofTheTargetStation << endl;
			cout << "Transaction Date and Time: " << ticketCurrent->TransactionDateAndTime << endl;
			cout << "Depature Date: " << ticketCurrent->DepartureDate << endl;
			cout << "Depature Time: " << ticketCurrent->DepartureTime << endl;
			cout << "Total Ticket Price: " << ticketCurrent->TotalTicketPrice << endl;
			cout << "Customer ID: " << ticketCurrent->CustomerID << endl;
			cout << "Customer Name: " << ticketCurrent->CustomerName << endl;
			cout << "Customer IC / Passport: " << ticketCurrent->CustomerIcOrPassport << endl;
			status = true;
			break;
		}
		ticketCurrent = ticketCurrent->nextAdd;
	}
	if (status)
	{
		cout << "The specific customer ticket purchase information is found." << endl;
	}
	else
	{
		cout << "The specific customer ticket purchase information is not found." << endl;
	}
} 

*/


// Admin 1.13
int getStationId(string stationName)
{
	//Getting Station id from Name
	stationCurrent = stationHead;
	int stationId;
	while (stationCurrent != NULL)
	{
		if (stationCurrent->StationName == stationName)
		{
			stationId = idExtract(stationCurrent->StationID);
			return stationId;
		}
		stationCurrent = stationCurrent->nextAdd;
	}
}
string getStationName(int stationId)
{
	//Getting Station Name from id
	string stationName;
	stationCurrent = stationHead;
	while (stationCurrent != NULL)
	{
		if (idMaker("S", stationId) == stationCurrent->StationID)
		{
			stationName = stationCurrent->StationName;
			return stationName;
		}

		stationCurrent = stationCurrent->nextAdd;
	}
}
string changeDepartureTime(int route, int departure, string oldDepartureDate)
{
	int todaydate;

	// Get current date
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	int CurrentYear = 1900 + newtime.tm_year;
	int CurrentMonth = 1 + newtime.tm_mon;
	int CurrentDay = newtime.tm_mday;

	string CurrentDate = to_string(CurrentYear) + "/" + to_string(CurrentMonth) + "/" + to_string(CurrentYear);

	//Check Date
	if (CurrentDate == oldDepartureDate)
	{
		todaydate = 1;
	}
	else
	{
		todaydate = 0;
	}

	return listAllPossibleDepartureTime(route, departure, todaydate);
}
double calculateNewFund(double oldprice, int ticketamount,int departure, int arrival)
{
	double newprice = 0;
	stationCurrent = stationHead;

	while (true)
	{
		if (arrival > departure) // route 1
		{
			if (idExtract(stationCurrent->StationID) == departure)
			{
				newprice = newprice + stationCurrent->CostBetweenNextStation;
				if (idExtract(stationCurrent->nextAdd->StationID) == arrival)
				{
					break;
				}
			}
			stationCurrent = stationCurrent->nextAdd;
			
		}
		else if (departure > arrival) // route 2
		{
			if (idExtract(stationCurrent->StationID) == arrival)
			{
				newprice = newprice + stationCurrent->CostBetweenNextStation;
				if (idExtract(stationCurrent->nextAdd->StationID) == departure)
				{
					break;
				}
			}
			stationCurrent = stationCurrent->nextAdd;
		}
	}

	newprice = newprice * ticketamount;

	int change;
	cout << "The current ticket price is RM " << fixed << setprecision(2) << setfill('0') << newprice << endl;
	if (newprice > oldprice)
	{
		change = newprice - oldprice;
		cout << "Total of RM " << fixed << setprecision(2) << setfill('0') << change << "has to be paid" << endl;
	}
	else
	{
		change = oldprice - newprice;
		cout << "Total of RM " << fixed << setprecision(2) << setfill('0') << change << "has to be refunded" << endl;
	}

	return newprice;
	
}
int checkTransactionIdAvailable(string transactionId)
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
	string transactionid;
	cout << "Input transaction id: " << endl;
	cin >> transactionid;

	int status = checkTransactionIdAvailable(transactionid);

	if (status == 0)
	{
		cout << " Transaction id is not found " << endl;
		editCustomerTicket();
	}

	int editSelection;
	cout << "1) Edit Route" << endl;
	cout << "2) Edit Destinaton" << endl;
	cout << "3) Edit Arrival" << endl;
	cout << "4) Edit Date" << endl;
	cout << "5) Edit departure time" << endl;
	cin >> editSelection;


	// Use for extracting info
	Ticket* Temp = ticketCurrent;

	//Edit Route
	if (editSelection == 1)
	{
		string leftToRightStation = stationHead->StationName + " -> " + stationTail->StationName;
		string rightToLeftStation = stationHead->StationName + " <- " + stationTail->StationName;

		cout << "Current the ticket's route is: " << Temp->TicketRoute << endl;
		cout << "Do you wish to change? " << endl;
		

		int change;
		int route;

		while (true)
		{
			cout << "1) Yes      2) No  :";
			cin >> change;

			if (change == 1)
			{
				string departureToArrivalStation;
				string arrivalToDepartureStation;

				if (ticketCurrent->TicketRoute == leftToRightStation)
				{
					route = 2;
				}
				else
				{
					route = 1;
				}

				
				int newdepartureId = getStationId(Temp->NameofTheTargetStation);
				cout << "Departure ID: " << newdepartureId << endl;

				//Change time
				string DepartureTime = changeDepartureTime(route, newdepartureId, Temp->DepartureDate);
				if (DepartureTime == "")
				{
					return;
				}

				//Edit Ticket
				ticketCurrent = ticketHead;
				while (ticketCurrent != NULL)
				{
					if (ticketCurrent->TransactionID == transactionid)
					{
						if (ticketCurrent->TicketRoute == leftToRightStation)
						{
							ticketCurrent->TicketRoute = rightToLeftStation;
						}
						else
						{
							ticketCurrent->TicketRoute = leftToRightStation;
						}

						//Interchange deprature and arrival station
						departureToArrivalStation = ticketCurrent->NameOfTheSourceStation;
						arrivalToDepartureStation = ticketCurrent->NameofTheTargetStation;

						ticketCurrent->NameOfTheSourceStation = arrivalToDepartureStation;
						ticketCurrent->NameofTheTargetStation = departureToArrivalStation;

						ticketCurrent->DepartureTime = DepartureTime;

					}
					ticketCurrent = ticketCurrent->nextAdd;

				}


			}
			else if (change == 2)
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

	//Edit Departure
	else if (editSelection == 2)
	{
		cout << "Current Ticket Departure is: " << Temp->NameOfTheSourceStation << endl;
		cout << "Do you wish to change: " << endl;

		int change;
		int route;


		while (true)
		{
			cout << "1) Yes      2) No  :";
			cin >> change;

			if (change == 1)
			{
				string departureToArrivalStation;
				string arrivalToDepartureStation;

				//Getting route
				if (Temp->TicketRoute == stationHead->StationName + " -> " + stationTail->StationName)
				{
					route = 1;
				}
				else
				{
					route = 2;
				}

				int currentArrivalStationid = getStationId(Temp->NameofTheTargetStation);
				int count = 1;

				//Get All possible departure station based on arrival station and route
				stationCurrent = stationHead;
				while (stationCurrent != NULL)
				{
					if (route == 1)
					{
						if (idExtract(stationCurrent->StationID) == currentArrivalStationid)
						{
							break;
						}
						else
						{
							cout << count << ") " << stationCurrent->StationName << endl;
							count++;
						}
					}
					else if (route == 2)
					{
						if (idExtract(stationCurrent->StationID) > currentArrivalStationid)
						{
							cout << count << ") " << stationCurrent->StationName << endl;
							count++;
						}
					}
					stationCurrent = stationCurrent->nextAdd;
					
				}


				cout << count << ") Return to Main menu" << endl;

				//Select new departure
				int newDepartureId;
				while (true)
				{
					cout << "Select your departure station: ";
					cin >> newDepartureId;
					if (newDepartureId > 0 && newDepartureId < count)
					{
						switch (route)
						{
						case 1:
							newDepartureId = newDepartureId;
						case 2:
							newDepartureId = newDepartureId + currentArrivalStationid;
						}

					}
					else if (newDepartureId == count)
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

				cout << "Departure ID: " << newDepartureId << endl;

				//Get new Departure Station Name
				string newDepartureName = getStationName(newDepartureId);

				//Change time
				string DepartureTime = changeDepartureTime(route, newDepartureId, Temp->DepartureDate);
				if (DepartureTime == "")
				{
					return;
				}

				//Check edited ticket price
				double newprice = calculateNewFund(Temp->TotalTicketPrice, Temp->TicketAmount,newDepartureId, currentArrivalStationid);

				//Edit Ticket
				ticketCurrent = ticketHead;
				while (ticketCurrent != NULL)
				{
					if (ticketCurrent->TransactionID == transactionid)
					{

						ticketCurrent->NameOfTheSourceStation = newDepartureName;
						ticketCurrent->DepartureTime = DepartureTime;
						ticketCurrent->TotalTicketPrice = newprice;

					}
					ticketCurrent = ticketCurrent->nextAdd;

				}

			}
		}
	}

	//Edit Arrival
	else if (editSelection == 3) 
	{
		cout << "Current Ticket Arrival is: " << Temp->NameofTheTargetStation << endl;
		cout << "Do you wish to change: " << endl;

		int change;
		int route;


		while (true)
		{
			cout << "1) Yes      2) No  :";
			cin >> change;

			if (change == 1)
			{
				string departureToArrivalStation;
				string arrivalToDepartureStation;

				//Getting route
				if (Temp->TicketRoute == stationHead->StationName + " -> " + stationTail->StationName)
				{
					route = 1;
				}
				else
				{
					route = 2;
				}

				int currentDepartureStationid = getStationId(Temp->NameOfTheSourceStation);
				int count = 1;

				//Get All possible departure station based on arrival station and route
				stationCurrent = stationHead;
				while (stationCurrent != NULL)
				{
					if (route == 2)
					{
						if (idExtract(stationCurrent->StationID) == currentDepartureStationid)
						{
							break;
						}
						else
						{
							cout << count << ") " << stationCurrent->StationName << endl;
							count++;
						}
					}
					else if (route == 1)
					{
						if (idExtract(stationCurrent->StationID) > currentDepartureStationid)
						{
							cout << count << ") " << stationCurrent->StationName << endl;
							count++;
						}
					}
					stationCurrent = stationCurrent->nextAdd;

				}


				cout << count << ") Return to Main menu" << endl;

				//Select new departure
				int newArrivalId;
				while (true)
				{
					cout << "Select your departure station: ";
					cin >> newArrivalId;
					if (newArrivalId > 0 && newArrivalId < count)
					{
						switch (route)
						{
						case 1:
							newArrivalId = newArrivalId + currentDepartureStationid;
						case 2:
							newArrivalId = newArrivalId;
						}

					}
					else if (newArrivalId == count)
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

				cout << "Departure ID: " << newArrivalId << endl;

				//Get new Departure Station Name
				string newDepartureName = getStationName(newArrivalId);


				//Check edited ticket price
				double newprice = calculateNewFund(Temp->TotalTicketPrice, Temp->TicketAmount, currentDepartureStationid, newArrivalId);

				//Edit Ticket
				ticketCurrent = ticketHead;
				while (ticketCurrent != NULL)
				{
					if (ticketCurrent->TransactionID == transactionid)
					{

						ticketCurrent->NameOfTheSourceStation = newDepartureName;
						ticketCurrent->TotalTicketPrice = newprice;

					}
					ticketCurrent = ticketCurrent->nextAdd;

				}

			}
		}
	}

	//Edit Date
	else if (editSelection == 4)
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

		int changeTime = 0;
		int newDepartureHour = 0;
		int newDepartureMinute = 0;

		if (TodayDate == 1)
		{
			struct tm newtime;
			time_t now = time(0);
			localtime_s(&newtime, &now);
			int CurrentHours = newtime.tm_hour;
			int CurrentMins = newtime.tm_min;

			int pos = Temp->DepartureTime.find(":");

			int DepartureHour = stoi(Temp->DepartureTime.substr(0, pos));
			int DepartureMinutes = stoi(Temp->DepartureTime.substr(pos + 1));

			if (DepartureHour < CurrentHours)
			{
				if (DepartureMinutes < CurrentMins)
				{
					changeTime = 1;
					int route;
					//Getting route
					if (Temp->TicketRoute == stationHead->StationName + " -> " + stationTail->StationName)
					{
						route = 1;
					}
					else
					{
						route = 2;
					}

					int departure = getStationId(Temp->NameOfTheSourceStation);

					string DepartureTime = listAllPossibleDepartureTime(route, departure, TodayDate);
					if (DepartureTime == "")
					{
						return;
					}


					int pos1 = DepartureTime.find(":");

					newDepartureHour = stoi(DepartureTime.substr(0, pos1));
					newDepartureMinute = stoi(DepartureTime.substr(pos1 + 1));
				}
			}
		}
		
		ticketCurrent = ticketHead;
		if (ticketCurrent != NULL)
		{
			if (ticketCurrent->TransactionID == transactionid)
			{
				ticketCurrent->DepartureDate = to_string(DepartureYear) + "/" + to_string(DepartureMonth) + "/" + to_string(DepartureDay);

				if (changeTime == 1)
				{
					ticketCurrent->DepartureTime = to_string(newDepartureHour) + ":" + to_string(newDepartureMinute);
				}
			}
			ticketCurrent = ticketCurrent->nextAdd;
		}

	}

	//Edit Time
	else if (editSelection == 5)
	{
		int route;
		//Getting route
		if (Temp->TicketRoute == stationHead->StationName + " -> " + stationTail->StationName)
		{
			route = 1;
		}
		else
		{
			route = 2;
		}

		int departure = getStationId(Temp->NameOfTheSourceStation);

		// Get current date
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);

		int CurrentYear = 1900 + newtime.tm_year;
		int CurrentMonth = 1 + newtime.tm_mon;
		int CurrentDay = newtime.tm_mday;

		int TodayDate = 0;

		if (Temp->DepartureDate == to_string(CurrentYear) + "/" + to_string(CurrentMonth) + "/" + to_string(CurrentDay))
		{
			TodayDate = 1;
		}

		string DepartureTime = listAllPossibleDepartureTime(route, departure, TodayDate);
		if (DepartureTime == "")
		{
			return;
		}

		int pos = DepartureTime.find(":");

		int newDepartureHour = stoi(DepartureTime.substr(0, pos));
		int newDepartureMinute = stoi(DepartureTime.substr(pos + 1));

		ticketCurrent = ticketHead;
		if (ticketCurrent != NULL)
		{
			if (ticketCurrent->TransactionID == transactionid)
			{
				ticketCurrent->DepartureTime = to_string(newDepartureHour) + ":" + to_string(newDepartureMinute);
			}
			ticketCurrent = ticketCurrent->nextAdd;
		}

	}



	cout << "Edit Sucessful" << endl;
	system("pause");
	system("CLS");
	return;
}






int main()
{
	stationHead = stationTail = NULL;

	Station* StationNode1 = createStationNode("S001", "Titiwangsa", "", "PWTC", 0, 0, 0, 4, 0.40, 3, "Providence KL");
	Station* StationNode2 = createStationNode("S002", "PWTC", "Titiwangsa", "Sultan Ismail", 4, 0.40, 3, 8, 0.80, 7, "Sunway Putra Mall");
	Station* StationNode3 = createStationNode("S003", "Sultan Ismail", "PWTC", "Majlis Jamek", 8, 0.80, 7, 8, 0.80, 7, "Jalan Tunku Abdul Rahman");
	Station* StationNode4 = createStationNode("S004", "Majlid Jamek", "Sultan Ismail", "Plaza Rakyat", 8, 0.80, 7, 6, 0.60, 5, "Jamek Mosque");
	Station* StationNode5 = createStationNode("S005", "Plaza Rakyat", "Majlis Jamek", "Hang Tuah", 6, 0.60, 5, 10, 1.00, 9, "St. Anthony Chruch");
	Station* StationNode6 = createStationNode("S006", "Hang Tuah", "Plaza Rakyat", "Pudu", 10, 1.00, 9, 5, 0.50, 4, "Berjaya Time Square");
	Station* StationNode7 = createStationNode("S007", "Pudu", "Hang Tuah", "Chan Sow Lin", 5, 0.50, 4, 5, 0.50, 4, "Pasar Besar Pudu");
	Station* StationNode8 = createStationNode("S008", "Chan Sow Lin", "Pudu", "", 5, 0.50, 4, 0, 0, 0, "East Club");

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
		cout << "Select your decision: ";
		cin >> decision;

		if (decision == 1)
		{
			while (true)
			{
				system("CLS");
				int role;
				cout << "1) Passenger" << endl;
				cout << "2) Admin" << endl;
				cout << "3) Return to Main Menu" << endl;
				cout << "Select your role: ";
				cin >> role;

				// Passenger
				if (role == 1)
				{
					system("CLS");
					string customerAccount;
					string customerPassword;
					cout << "Please Enter your IC or Passport Number: ";
					cin >> customerAccount;
					cout << "Please Enter your Password: ";
					cin >> customerPassword;

					string customerId = checkCustomerLoggingAccount(customerAccount, customerPassword);

					if (customerId != "")
					{
						int customerDecision;
						while (true)
						{
							cout << "1) Purchase Ticket" << endl;
							cout << "2) Search subway station details" << endl;
							cout << "3) View and delete transaction history" << endl;
							cout << "4) Exit to Main Menu" << endl;
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

				/*
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
				*/
				else if (role == 3)
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
						system("pause");
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