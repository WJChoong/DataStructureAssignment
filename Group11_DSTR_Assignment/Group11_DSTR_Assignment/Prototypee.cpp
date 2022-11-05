#include <iostream>
#include <string>
#include <stdlib.h> //Clear Text in Output
#include <ctime>	//Get Current Date and Time
#include <iomanip>	//Make character to 2 digit
#include <limits>
#include <chrono>
#include <thread>
using namespace std;
using std::cout;
using std::cin;



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
	string TransactionID; 		// (Transaction ID Starting from T000, auto increment)
	string TicketID; 			// (Ticket ID Starting from K000, auto increment)
	string TicketRoute;
	string NameOfTheSourceStation;
	string NameofTheTargetStation;
	int TicketAmount;
	string TransactionDateAndTime;
	string DepartureDate;
	string DepartureTime;
	double TotalTicketPrice;
	string CustomerID; 			// (Customer ID Starting from C000, auto increament when new account is created)
	string CustomerName;
	string CustomerIcOrPassport;

	//Ticket Node Address
	Ticket* nextAdd; // Linked List - Address of Next Node

} *ticketHead, * ticketCurrent, * ticketTail;

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

class ticketClass {
public:
	string TransactionID; 		// (Transaction ID Starting from T000, auto increment)
	string TicketID; 			// (Ticket ID Starting from K000, auto increment)
	string TicketRoute;
	string NameOfTheSourceStation;
	string NameofTheTargetStation;
	int TicketAmount;
	string TransactionDateAndTime;
	string DepartureDate;
	string DepartureTime;
	double TotalTicketPrice;
	string CustomerID; 			// (Customer ID Starting from C000, auto increament when new account is created)
	string CustomerName;
	string CustomerIcOrPassport;
};




//----------------------------------------------------
//-------------------   Intro   ----------------------
//----------------------------------------------------


// Draw Opening
void drawopening()
{
	cout << "-------------------------------------" << endl;
	cout << "-------Ticket Booking System---------" << endl;
	cout << "-------------------------------------" << endl
		<< endl;
	cout << "Welcome to Kuala Lumpur Light Rail Transit(LRT) - Titiwangsa Station - Chan Sow Lin Station Route" << endl
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

string idMaker(string idType, int ID)
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
		cout << "This system currently does not have any passenger account registered." << endl;
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
				cout << "Welcome Mr/Mrs/Miss " << customerHead->CustomerName << endl;
				return customerHead->CustomerId;
			}
			else
			{
				cout << "----- Incorrect Password -----" << endl;
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
					cout << "Welcome Mr/Mrs/Miss " << customerCurrent->CustomerName << endl;
					return customerCurrent->CustomerId;
				}
				else
				{
					cout << "----- Incorrect Password -----" << endl;
					return "";
				}
			}
		}
	}
	cout << "This IC or Passport Number Does Not Exist In This System! Please Create A New Account!" << endl;
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
	int transactionIdno;
	int ticketIdno;

	if (ticketHead == NULL)
	{
		transactionIdno = 0;
		ticketIdno = 0;
	}
	else
	{
		transactionIdno = idExtract(ticketTail->TransactionID) + 1;
		ticketIdno = idExtract(ticketTail->TicketID) + 1;
	}

	string transactionId = idMaker("T", transactionIdno);



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
		Ticket* ticketNode = createTicketNode(transactionId, idMaker("K", ticketIdno + i), TicketRoute, departureStation, arrivalStation, ticketAmount, transactionDateAndTime, departureDate, departureTime, totalTicketPrice, customerId, customerName, customerIcOrPassport);
		insertTicketNodeToTheEndList(ticketNode);
	}
}





//----------------------------------------------------
//-----------------   Customer  ----------------------
//----------------------------------------------------

//List Route
int listRoute()
{
	int route;
	while (true)
	{
		cout << "1) " << stationHead->StationName << " -> " << stationTail->StationName << endl;
		cout << "2) " << stationHead->StationName << " <- " << stationTail->StationName << endl;
		cout << "3) Return To Main Menu" << endl;
		cout << "Select Your Route: " << endl;

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
			cin.clear();                                         // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "----- Incorrect Input -----" << endl;
			system("pause");
			system("CLS");
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

	cout << totalNumberofStation << ") Return to Main Menu" << endl;

	int departure;
	while (true)
	{
		cout << "\nChoose Your Departure Location: ";
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
		else if (departure == totalNumberofStation)
		{
			return 0;
		}
		else
		{
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "----- Incorrect Input -----" << endl;
			system("pause");
		}
	}
}

// List All Possible Arrival Routes
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

	cout << lastSelection << ") Return to Main Menu" << endl;

	int arrival;
	while (true)
	{
		cout << "\nChoose Your Arrival Location: ";
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
			cout << "----- Incorrect Input -----" << endl;
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
	if (DepartureYear > 2025)
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

	if (DepartureYear < CurrentYear) {
		return 4;
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
		cout << "Select Your Departure Time Or Enter (0) To Return Back To Main Menu: " << endl;
		cin >> DepartureTimeIndex;

		if (cin.fail() || DepartureTimeIndex > size || DepartureTimeIndex < 0)
		{
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "----- Invalid Input -----" << endl;
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
	cout << "\nTotal Distance: " << totaldistance << " KM" << endl;
	cout << "Total Expenses Per Ticket: RM " << fixed << setprecision(2) << setfill('0') << totalexpenses << endl;
	cout << "Total Time: " << totaltime << " Minutes" << endl << endl;

	cout << "Departure Date: " << Year << "/" << setw(2) << setfill('0') << Month << "/" << setw(2) << setfill('0') << Days << endl;
	cout << "Departure Time: " << setw(2) << setfill('0') << Hours << ":" << setw(2) << setfill('0') << Minutes << endl << endl;

	string departureDate = to_string(Year) + "/" + to_string(Month) + "/" + to_string(Days);
	string departureTime;

	int timecheck;
	string letterHour;
	string letterMinute;

	timecheck = Hours - 10;
	if (timecheck < 0)
	{
		letterHour = "0" + to_string(Hours);
	}
	else
	{
		letterHour = to_string(Hours);
	}

	timecheck = Minutes - 10;
	if (timecheck < 0)
	{
		letterMinute = "0" + to_string(Minutes);
	}
	else
	{
		letterMinute = to_string(Minutes);
	}

	departureTime = letterHour + ":" + letterMinute;



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


	int ticketAmount;
	double totalTicketPrice = 0;

	while (true)
	{
		cout << "--- Please input your ticket amount or Press 0 to return back to main menu ---" << endl;
		cout << "Ticket Amount: " << endl;
		cin >> ticketAmount;

		if (cin.fail() || ticketAmount < 0)
		{
			cin.clear();                                         // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "----- Invalid Input -----" << endl;
		}
		else if (ticketAmount == 0)
		{
			return;
		}
		else
		{
			totalTicketPrice = ticketAmount * totalexpenses;
			break;
		}
	}



	cout << "Total Ticket Price: RM " << fixed << setprecision(2) << setfill('0') << totalTicketPrice << endl;



	int confirmPurchase;
	while (true)
	{
		cout << "Confirm Purchase? " << endl;
		cout << "1)Yes     2)No " << endl;
		cin >> confirmPurchase;

		if (confirmPurchase == 1)
		{
			break;
		}
		else if (confirmPurchase == 2)
		{
			cout << "----- Returning to Main Menu -----" << endl;
			return;
		}
		else
		{
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "----- Invalid Input -----" << endl;
		}
	}

	while (true)
	{
		unsigned long long int creditCardNumber;
		int CVV;
		int valid;
		cout << "Please Input Your Credit Card Number (16 digits): ";
		cin >> creditCardNumber;

		valid = creditCardNumber / 1000000000000000;                                                            // CHANGE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!FELICIA
		if (cin.fail() || valid < 1 || valid > 9)
		{
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "----- Invalid Credit Card number -----" << endl;
			continue;
		}
		cout << "Please Input Your CVV Number (3 digits): ";
		cin >> CVV;
		valid = CVV / 100;

		if (cin.fail() || valid < 1 || valid > 9)
		{
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "----- Invalid CVV number -----" << endl;
			continue;
		}

		break;
	}

	createTicket(TicketRoute, departureStation, arrivalStation, departureDate, departureTime, ticketAmount, totalTicketPrice, customerId);

	cout << "----- Thank You Very Much -----" << endl;
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
		cout << "Please Enter Your Departure Date (in YYYY/MM/DD format): " << endl;
		cout << "Note: Ticket can only be purchased before 2025!" << endl;
		cout << "Date: ";
		cin >> DepartureYear >> seperator1 >> DepartureMonth >> seperator2 >> DepartureDay;

		if (cin.fail() || seperator1 != '/' || seperator2 != '/')
		{
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "----- Invalid Format -----" << endl;
			system("pause");
			continue;
		}

		switch (isValidDate(DepartureYear, DepartureMonth, DepartureDay))
		{
		case 0:
			cout << "----- Invalid Year -----" << endl;
			system("pause");
			break;
		case 1:
			cout << "----- Invalid Month -----" << endl;
			system("pause");
			break;
		case 2:
			cout << "----- Invalid Day -----" << endl;
			system("pause");
			break;
		case 3:
			cout << "----- This Year February Only Has 28 Days -----" << endl;
			system("pause");
			break;
		case 4:
			cout << "----- The Selected Date Is Already Past -----" << endl;
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
int printStationDetails()
{
	int decision = 0;
	int count = 1;

	stationCurrent = stationHead;
	while (stationCurrent != NULL)
	{

		cout << count << ") " << "Station Name : " << stationCurrent->StationName << endl;

		stationCurrent = stationCurrent->nextAdd;
		count++;
	}

	cout << count << ") " << "Return to main menu" << endl;
	cout << "\nSelect Your Station:" << endl;
	cin >> decision;


	if (decision == count)
	{
		return 0;
	}
	else if (decision > 0 && decision < count)
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
			cout << "Continue Searching For Station Details ?" << endl;
			cout << "1) Yes     2) No" << endl;
			cin >> Continue;

			if (Continue == 1)
			{
				return 1;
			}
			else if (Continue == 2)
			{
				return 0;
			}
			else
			{
				cin.clear();										 // remove the input operation
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
				cout << "----- Incorrect Input -----" << endl;
			}
		}
	}
	else
	{
		cin.clear();										 // remove the input operation
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
		cout << "----- Incorrect Input -----" << endl;
		printStationDetails();
	}
}

void printAllStationDetails()
{
	stationCurrent = stationHead;
	while (stationCurrent != NULL)
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
		cout << endl;
		stationCurrent = stationCurrent->nextAdd;
	}
}

// 3) Check, Print and Delete Transaction History
void deletePurchaseTransaction(string customerId)
{
	string transactionId;
	int confirm = 0;
	cout << "Please Input Your Transaction ID: " << endl;
	cin >> transactionId;

	//Temporary variable to delete ticket node
	Ticket* ticketDelete;
	int changeTicketTail = 0;

	//If there is only one ticket in the system
	if (ticketHead == ticketTail)
	{
		// check whether this transaction id is in this passenger account
		if (ticketHead->TransactionID == transactionId && ticketHead->CustomerID == customerId)
		{
			changeTicketTail = 0;
			ticketDelete = ticketHead;

			ticketHead = ticketTail = NULL;

			delete ticketDelete;
			confirm++;
			ticketCounts--;
		}
	}


	//If there are many tickets in the system
	else
	{
		ticketCurrent = ticketHead->nextAdd;
		Ticket* Temp = ticketHead;

		while (ticketCurrent != NULL)
		{
			// check whether this transaction id is in this passenger account
			if (ticketCurrent->TransactionID == transactionId && ticketCurrent->CustomerID == customerId)
			{

				if (ticketCurrent == ticketTail)
				{
					ticketTail = NULL;
					changeTicketTail = 1;
				}
				ticketDelete = ticketCurrent;
				ticketCurrent = ticketCurrent->nextAdd;
				Temp->nextAdd = ticketCurrent;
				delete ticketDelete;
				confirm++;
				ticketCounts--;
			}
			else
			{
				ticketCurrent = ticketCurrent->nextAdd;
				Temp = Temp->nextAdd;
			}
		}

		//Check Ticket Head
		if (ticketHead->TransactionID == transactionId && ticketHead->CustomerID == customerId)
		{
			ticketDelete = ticketHead;

			ticketHead = ticketHead->nextAdd;

			if (ticketHead == NULL)
			{
				changeTicketTail = 0;
			}

			delete ticketDelete;
			confirm++;
			ticketCounts--;
		}
	}



	//Relocate Ticket Tail if neccesary
	if (changeTicketTail == 1)
	{
		ticketCurrent = ticketHead;
		while (ticketCurrent != NULL)
		{
			if (ticketCurrent->nextAdd == NULL)
			{
				ticketTail = ticketCurrent;
			}
			ticketCurrent = ticketCurrent->nextAdd;
		}
	}

	if (confirm > 0)
	{
		cout << "----- Transaction Deleted Sucessfully! Fund Will Be Refunded To Passenger's Credit Card -----" << endl;
		return;
	}
	else
	{
		cout << "----- Transaction is not found, returning to main menu -----" << endl;
	}
}

void printAndDeleteTransactionHistory(string customerId)
{

	// If system has no ticket history
	if (ticketHead == NULL)
	{
		cout << "This system does not have any transaction history" << endl;
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
				cout << "Transaction ID: " << ticketCurrent->TransactionID << endl;
				cout << "Ticket ID: " << ticketCurrent->TicketID << endl;
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
			cout << "There are a total of " << ticketCount << " ticket(s) in this account." << endl;
		}
		else
		{
			cout << "This account does not have any purchase history, Returning to main menu" << endl;
			system("pause");
			return;
		}
	}

	int choice;
	while (true)
	{


		cout << "1) Delete Purchase Transaction" << endl;
		cout << "2) Return Back to Main menu " << endl;
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
			cout << "----- Invalid Input -----" << endl;
		}
	}
}





void swapTicket(ticketClass* a, ticketClass* b) {
	ticketClass t = *a;
	*a = *b;
	*b = t;
}

void exch(ticketClass array[], int i, int j) {
	ticketClass temp;
	temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

void printArray(ticketClass array[], int size) {
	int i;
	for (i = 0; i < size; i++) {
		cout << "Transaction ID: " << array[i].TransactionID << endl;
		cout << "Ticket ID: " << array[i].TicketID << endl;
		cout << "Ticket Route: " << array[i].TicketRoute << endl;
		cout << "Name of The Source Station: " << array[i].NameOfTheSourceStation << endl;
		cout << "Name of The Target Station: " << array[i].NameofTheTargetStation << endl;
		cout << "Transaction Date and Time: " << array[i].TransactionDateAndTime << endl;
		cout << "Depature Date: " << array[i].DepartureDate << endl;
		cout << "Depature Time: " << array[i].DepartureTime << endl;
		cout << "Total Ticket Price: " << array[i].TotalTicketPrice << endl;
		cout << "Customer ID: " << array[i].CustomerID << endl;
		cout << "Customer Name: " << array[i].CustomerName << endl;
		cout << "Customer IC / Passport: " << array[i].CustomerIcOrPassport << endl;
		cout << endl;
	}
	cout << endl;
}

void bubbleSort(ticketClass array[], int arrayLength)
{
	for (int i = arrayLength - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (array[j].CustomerName > array[j + 1].CustomerName)
			{
				exch(array, j, j + 1);
			}
		}
	}
}

void addNewSubwayStationInformation()
{
	// need to change
	string stationName, previousStationName, nearbyBySightseeingSpots;
	double distanceBetweenPreviousStation, costBetweenPreviousStation;
	int timeBetweenPreviousStation;
	int stationNum = idExtract(stationTail->StationID) + 1;
	string stationId = idMaker("S", stationNum);
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
	int option;
	string stationId;
	while (subwayOption)
	{
		printAllStationDetails();
		cout << "Please enter the subway station's id that you would like to edit or enter 0 to exit to admin menu: ";
		cin >> stationId;
		if (stationId == "0")
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
			cout << "6) Exit to select another station" << endl;
			cout << "Please enter the number you option: ";
			cin >> option;

			// edit information options based on selection
			switch (option)
			{
			case 1:
				cout << "Please enter the new station name: ";
				getline(cin >> ws, name);
				stationCurrent->StationName = name;
				if (stationCurrent->prevAdd != NULL)
				{
					stationCurrent->prevAdd->NextStationName = name;
				}
				if (stationCurrent->nextAdd != NULL)
				{
					stationCurrent->nextAdd->PreviousStationName = name;
				}
				displayMessage("You had successfully updated the station name");
				editOption = false;
				break;
			case 2:
				cout << "Please enter the new cost between previous station: ";
				cin >> cost;
				if (stationCurrent->prevAdd == NULL)
				{
					displayMessage("There is no previous station for the selected station. ");
					editOption = false;
					break;
				}
				stationCurrent->CostBetweenPreviousStation = cost;
				stationCurrent->prevAdd->CostBetweenNextStation = cost;
				displayMessage("You had successfully updated the cost between previous station");
				editOption = false;
				break;
			case 3:
				cout << "Please enter the new cost between next station: ";
				cin >> cost;
				if (stationCurrent->nextAdd == NULL)
				{
					displayMessage("There is no next station for the selected station. ");
					editOption = false;
					break;
				}
				stationCurrent->CostBetweenNextStation = cost;
				stationCurrent->nextAdd->CostBetweenPreviousStation = cost;
				displayMessage("You had successfully updated the cost between next station");
				editOption = false;
				break;
			case 4:
				cout << "Please enter the new time between previous station: ";
				cin >> time;
				if (stationCurrent->prevAdd == NULL)
				{
					displayMessage("There is no previous station for the selected station. ");
					editOption = false;
					break;
				}
				stationCurrent->TimeBetweenPreviousStation = time;
				stationCurrent->prevAdd->TimeBetweenNextStation = time;
				displayMessage("You had successfully updated the time between previous station");
				editOption = false;
				break;
			case 5:
				cout << "Please enter the new time between next station: ";
				cin >> time;
				if (stationCurrent->nextAdd == NULL)
				{
					displayMessage("There is no next station for the selected station. ");
					editOption = false;
					break;
				}

				stationCurrent->TimeBetweenNextStation = time;
				stationCurrent->nextAdd->TimeBetweenPreviousStation = time;
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
			cout << endl;
			ticketCurrent = ticketCurrent->nextAdd;
		}
		displayMessage("This is the end of the purchase transaction");
	}
}

void sortPurchaseTransaction()
{
	ticketCurrent = ticketHead;
	// error
	cout << "TicketCounts" << ticketCounts << endl;
	ticketClass* ticketArray = new ticketClass[ticketCounts];
	int index = 0;
	while (ticketCurrent != NULL)
	{
		ticketArray[index].TransactionID = ticketCurrent->TransactionID;
		ticketArray[index].TicketID = ticketCurrent->TicketID;
		ticketArray[index].TicketRoute = ticketCurrent->TicketRoute;
		ticketArray[index].NameOfTheSourceStation = ticketCurrent->NameOfTheSourceStation;
		ticketArray[index].NameofTheTargetStation = ticketCurrent->NameofTheTargetStation;
		ticketArray[index].TicketAmount = ticketCurrent->TicketAmount;
		ticketArray[index].TransactionDateAndTime = ticketCurrent->TransactionDateAndTime;
		ticketArray[index].DepartureDate = ticketCurrent->DepartureDate;
		ticketArray[index].DepartureTime = ticketCurrent->DepartureTime;
		ticketArray[index].TotalTicketPrice = ticketCurrent->TotalTicketPrice;
		ticketArray[index].CustomerID = ticketCurrent->CustomerID;
		ticketArray[index].CustomerName = ticketCurrent->CustomerName;
		ticketArray[index].CustomerIcOrPassport = ticketCurrent->CustomerIcOrPassport;

		ticketCurrent = ticketCurrent->nextAdd;
		index++;
	}
	cout << "Hello" << endl;
	printArray(ticketArray, ticketCounts);
	bubbleSort(ticketArray, ticketCounts);
	cout << "yo yo" << endl;
	printArray(ticketArray, ticketCounts);
	cout << "The above is the sorted transaction order " << endl;
}

void searchPurchaseCustomerTicketPurchaseInformation()
{
	string ID;
	bool status = false;
	cout << "Please enter the ticket ID: ";
	cin >> ID;
	ticketCurrent = ticketHead;
	while (ticketCurrent != NULL)
	{
		if (ticketCurrent->TicketID == ID)
		{
			cout << endl;
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
			cout << endl;
			status = true;
			break;
		}
		ticketCurrent = ticketCurrent->nextAdd;
	}
	if (status)
	{
		cout << "The specific customer ticket purchase information is found." << endl;
		cout << endl;
	}
	else
	{
		cout << "The specific customer ticket purchase information is not found." << endl;
		cout << endl;
	}
}



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

	string CurrentDate = to_string(CurrentYear) + "/" + to_string(CurrentMonth) + "/" + to_string(CurrentDay);

	//Check Date
	if (CurrentDate == oldDepartureDate)
	{
		todaydate = 1;
	}
	else
	{
		todaydate = 0;
	}

	string newDepartureTime = listAllPossibleDepartureTime(route, departure, todaydate);


	if (newDepartureTime != "")
	{
		int pos = newDepartureTime.find(":");

		int DepartureHour = stoi(newDepartureTime.substr(0, pos));
		int DepartureMinutes = stoi(newDepartureTime.substr(pos + 1));

		int timecheck;
		string newDepartureHour;
		string newDepartureMinute;

		timecheck = DepartureHour - 10;
		if (timecheck < 0)
		{
			newDepartureHour = "0" + to_string(DepartureHour);
		}
		else
		{
			newDepartureHour = to_string(DepartureHour);
		}

		timecheck = DepartureMinutes - 10;
		if (timecheck < 0)
		{
			newDepartureMinute = "0" + to_string(DepartureMinutes);
		}
		else
		{
			newDepartureMinute = to_string(DepartureMinutes);
		}

		newDepartureTime = newDepartureHour + ":" + newDepartureMinute;
	}


	return newDepartureTime;
}

double calculateNewFund(double oldprice, int ticketamount, int departure, int arrival)
{
	double newprice = 0;

	if (arrival > departure) // route 1
	{
		stationCurrent = stationHead;
		for (int i = 1; i < departure; i++)
		{
			stationCurrent = stationCurrent->nextAdd;
		}

		for (int i = departure; i < arrival; i++)
		{
			newprice = newprice + stationCurrent->CostBetweenNextStation;
			stationCurrent = stationCurrent->nextAdd;
		}

	}

	else if (departure > arrival) // route 2
	{
		stationCurrent = stationTail;
		for (int i = idExtract(stationTail->StationID); i > departure; i--)
		{
			stationCurrent = stationCurrent->prevAdd;
		}

		for (int i = departure; i > arrival; i--)
		{
			newprice = newprice + stationCurrent->CostBetweenPreviousStation;
			stationCurrent = stationCurrent->prevAdd;
		}
	}


	newprice = newprice * ticketamount;

	double change = 0;
	cout << "The current ticket price is RM " << fixed << setprecision(2) << setfill('0') << newprice << "." << endl;
	if (newprice > oldprice)
	{
		change = newprice - oldprice;
		cout << "Total of RM " << fixed << setprecision(2) << setfill('0') << change << " has to be paid by the passenger" << endl;
	}
	else if (newprice < oldprice)
	{
		change = oldprice - newprice;
		cout << "Total of RM " << fixed << setprecision(2) << setfill('0') << change << " has to be refunded by the passenger" << endl;
	}
	else
	{
		cout << "----- The price remains the same -----" << endl;
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
	cout << "Input Transaction ID: " << endl;
	cin >> transactionid;

	int status = checkTransactionIdAvailable(transactionid);

	if (status == 0)
	{
		cout << " Transaction ID is not found " << endl;
		editCustomerTicket();
	}


	int editSelection;



	while (true)
	{
		cout << "1) Edit Route" << endl;
		cout << "2) Edit Destination Location" << endl;
		cout << "3) Edit Arrival Location" << endl;
		cout << "4) Edit Date" << endl;
		cout << "5) Edit Departure Time" << endl;
		cout << "6) Return to Main Menu" << endl;

		cout << "Select Your Decision: ";
		cin >> editSelection;


		// Use for extracting info
		Ticket* Temp = ticketCurrent;

		//Edit Route
		if (editSelection == 1)
		{
			string leftToRightStation = stationHead->StationName + " -> " + stationTail->StationName;
			string rightToLeftStation = stationHead->StationName + " <- " + stationTail->StationName;

			cout << "Current Ticket Route Is: " << Temp->TicketRoute << endl;
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

					cout << "-------------------------------------------------" << endl;
					cout << "Steps To Edit Route: " << endl;
					cout << "1) Current Route: " << Temp->TicketRoute << " will be changed." << endl;
					cout << "2) Reselect Departure Time" << endl;
					cout << "3) Route Will Be Changed" << endl;
					cout << "4) Your Destination Location and Arrival Location Will Be Switched" << endl;
					cout << "-------------------------------------------------" << endl;


					//Change time
					string DepartureTime = changeDepartureTime(route, newdepartureId, Temp->DepartureDate);
					if (DepartureTime == "")
					{
						return;
					}

					cout << "Departure Time: " << DepartureTime << endl;

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

					break;
				}
				else if (change == 2)
				{
					return;
				}
				else
				{
					cin.clear();										 // remove the input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
					cout << "----- Incorrect Input -----" << endl;
					system("pause");
				}

			}
		}

		//Edit Departure
		else if (editSelection == 2)
		{
			cout << "Current Ticket Departure Station Is: " << Temp->NameOfTheSourceStation << endl;
			cout << "Do you wish to change? " << endl;

			int change;
			int route;


			while (true)
			{
				cout << "1) Yes      2) No  :";
				cin >> change;

				if (change == 1)
				{

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
						cout << "Select Your Departure Station: ";
						cin >> newDepartureId;
						if (newDepartureId > 0 && newDepartureId < count)
						{
							switch (route)
							{
							case 1:
								newDepartureId = newDepartureId;
								break;
							case 2:
								newDepartureId = newDepartureId + currentArrivalStationid;
							}
							break;
						}
						else if (newDepartureId == count)
						{
							return;
						}
						else
						{
							cin.clear();										 // remove the input operation
							cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
							cout << "----- Incorrect Input -----" << endl;
							system("pause");
						}
					}


					//Get new Departure Station Name
					string newDepartureName = getStationName(newDepartureId);


					//Change time
					string DepartureTime = changeDepartureTime(route, newDepartureId, Temp->DepartureDate);
					if (DepartureTime == "")
					{
						return;
					}

					//Check edited ticket price
					double newprice = calculateNewFund(Temp->TotalTicketPrice, Temp->TicketAmount, newDepartureId, currentArrivalStationid);


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
					break;
				}
				else if (change == 2)
				{
					return;
				}
				else
				{
					cin.clear();										 // remove the input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
					cout << "----- Incorrect Input -----" << endl;
					system("pause");
				}
			}

		}

		//Edit Arrival
		else if (editSelection == 3)
		{
			cout << "Current Ticket Arrival Is: " << Temp->NameofTheTargetStation << endl;
			cout << "Do you wish to change?" << endl;

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
						cout << "Select Your Arrival Station: ";
						cin >> newArrivalId;
						if (newArrivalId > 0 && newArrivalId < count)
						{
							switch (route)
							{
							case 1:
								newArrivalId = newArrivalId + currentDepartureStationid;
								break;
							case 2:
								newArrivalId = newArrivalId;
							}
							break;

						}
						else if (newArrivalId == count)
						{
							return;
						}
						else
						{
							cin.clear();										 // remove the input operation
							cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
							cout << "----- Incorrect Input -----" << endl;
							system("pause");
						}

					}


					//Get new Arrival Station Name
					string newArrivalName = getStationName(newArrivalId);


					//Check edited ticket price
					double newprice = calculateNewFund(Temp->TotalTicketPrice, Temp->TicketAmount, currentDepartureStationid, newArrivalId);

					//Edit Ticket
					ticketCurrent = ticketHead;
					while (ticketCurrent != NULL)
					{
						if (ticketCurrent->TransactionID == transactionid)
						{

							ticketCurrent->NameofTheTargetStation = newArrivalName;
							ticketCurrent->TotalTicketPrice = newprice;

						}
						ticketCurrent = ticketCurrent->nextAdd;

					}
					break;

				}
				else if (change == 2)
				{
					return;
				}
				else
				{
					cin.clear();										 // remove the input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
					cout << "----- Incorrect Input -----" << endl;
					system("pause");
				}
			}
		}

		//Edit Date
		else if (editSelection == 4)
		{
			cout << "Current Ticket Departure Date Is: " << Temp->DepartureDate << endl;
			cout << "Do you wish to change? " << endl;

			int change;
			int route;

			while (true)
			{
				cout << "1) Yes      2) No  :";
				cin >> change;

				if (change == 1)
				{
					// Select Departure Date
					int DepartureYear, DepartureMonth, DepartureDay;
					char seperator1, seperator2;
					int InputCorrect = 0;
					int TodayDate = 0;
					while (InputCorrect == 0)
					{
						system("CLS");
						cout << "Please Enter Your Departure Date (in YYYY/MM/DD format): " << endl;
						cout << "Note: Ticket can only be purchased before 2025" << endl;
						cout << "Date: ";
						cin >> DepartureYear >> seperator1 >> DepartureMonth >> seperator2 >> DepartureDay;

						if (cin.fail() || seperator1 != '/' || seperator2 != '/')
						{
							cin.clear();										 // remove the input operation
							cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
							cout << "----- Invalid Format -----" << endl;
							system("pause");
							continue;
						}

						switch (isValidDate(DepartureYear, DepartureMonth, DepartureDay))
						{
						case 0:
							cout << "----- Invalid Year -----" << endl;
							system("pause");
							break;
						case 1:
							cout << "----- Invalid Month -----" << endl;
							system("pause");
							break;
						case 2:
							cout << "----- Invalid Day -----" << endl;
							system("pause");
							break;
						case 3:
							cout << "----- This year February only has 28 days -----" << endl;
							system("pause");
							break;
						case 4:
							cout << "----- The selected date is already past -----" << endl;
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

						if (DepartureHour <= CurrentHours)
						{
							if (DepartureMinutes <= CurrentMins)
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
					break;
				}
				else if (change == 2)
				{
					return;
				}
				else
				{
					cin.clear();										 // remove the input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
					cout << "----- Incorrect Input -----" << endl;
					system("pause");
				}

			}



		}

		//Edit Time
		else if (editSelection == 5)
		{
			cout << "Current Ticket Departure Time Is: " << Temp->DepartureTime << endl;
			cout << "Do you wish to change? " << endl;

			int change;
			int route;

			while (true)
			{
				cout << "1) Yes      2) No  :";
				cin >> change;

				if (change == 1)
				{
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


					ticketCurrent = ticketHead;
					if (ticketCurrent != NULL)
					{
						if (ticketCurrent->TransactionID == transactionid)
						{
							ticketCurrent->DepartureTime = DepartureTime;
						}
						ticketCurrent = ticketCurrent->nextAdd;
					}
					break;
				}
				else if (change == 2)
				{
					return;
				}
				else
				{
					cin.clear();										 // remove the input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
					cout << "----- Incorrect Input -----" << endl;
					system("pause");
				}
			}



		}

		//Retrun to main menu
		else if (editSelection == 6)
		{
			break;
		}

		else
		{
			cin.clear();										 // remove the input operation
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
			cout << "Incorrect Input" << endl;
			system("pause");
			system("CLS");
		}

		cout << "Edit Sucessfully, returning to main menu" << endl;
		system("pause");
		system("CLS");
		break;
	}

	return;
}

// Admin 1.14
string checkCustomerId(string IcPassport)
{
	int exist = 0;
	string customerId;

	customerCurrent = customerHead;
	while (customerCurrent != NULL)
	{
		if (customerCurrent->CustomerIcOrPassport == IcPassport)
		{
			customerId = customerCurrent->CustomerId;
			exist = 1;
		}
		customerCurrent = customerCurrent->nextAdd;
	}

	if (exist == 1)
	{
		return customerId;
	}
	else
	{
		return "";
	}

}





//----------------------------------------------------
//--------------------   Main  -----------------------
//----------------------------------------------------

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
	createCustomerAccount("Edmund", "1", "1");
	createCustomerAccount("Alvin", "2", "2");
	createCustomerAccount("Kelvin", "3", "3");

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
		drawopening();
		cout << "1) Login To Existing Account" << endl;
		cout << "2) Create A New Account As Passenger" << endl;
		cout << "3) Exit System" << endl;
		cout << "Select Your Decision: ";
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
				cout << "Select Your Role: ";
				cin >> role;

				// Passenger
				if (role == 1)
				{
					system("CLS");
					string customerAccount;
					string customerPassword;
					cout << "Please Enter Your IC or Passport Number: ";
					cin >> customerAccount;
					cout << "Please Enter Your Password: ";
					cin >> customerPassword;

					string customerId = checkCustomerLoggingAccount(customerAccount, customerPassword);

					if (customerId != "")
					{
						int customerDecision;
						while (true)
						{
							cout << "1) Purchase Ticket" << endl;
							cout << "2) Search Subway Station Details" << endl;
							cout << "3) View and Delete Transaction History" << endl;
							cout << "4) Exit to Main Menu" << endl;
							cin >> customerDecision;
							if (customerDecision == 1)
							{
								purchaseticket(customerId);
							}
							else if (customerDecision == 2)
							{
								while (true)
								{
									int decision = printStationDetails();
									if (decision == 0)
									{
										break;
									}
								}
							}
							else if (customerDecision == 3)
							{
								printAndDeleteTransactionHistory(customerId);
							}
							else if (customerDecision == 4)
							{
								cout << "Thank You, Have A Nice Day! " << endl;
								system("pause");
								break;
							}
							else
							{
								cin.clear();										 // remove the input operation
								cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
								cout << "----- Incorrect Input -----" << endl;
								system("pause");
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
					cout << "Please Enter Username" << endl;
					cin >> adminAccount;
					cout << "Please Enter Password" << endl;
					cin >> adminPassword;

					if (adminAccount == "admin" && adminPassword == "12345")
					{
						int decision;
						while (true)
						{
							cout << "1) Add New Subway Information" << endl;
							cout << "2) Edit Current Subway Station Information" << endl;
							cout << "3) View All Purchase Transactions" << endl;
							cout << "4) Sort Purchase Transaction Based On Passenger Name" << endl;
							cout << "5) Search Specific Customer Ticket Purchase Information" << endl;
							cout << "6) Edit Specific Customer Ticket Purchase Information" << endl;
							cout << "7) Delete Specific Customer Ticket Purchase Information" << endl;
							cout << "8) Exit to Main Menu" << endl;
							cout << "Please Enter Your Option: ";
							cin >> decision;

							if (decision == 1)
							{
								addNewSubwayStationInformation();
							}
							else if (decision == 2)
							{
								editCurrentSubwayStationsInformation();
							}
							else if (decision == 3)
							{
								viewAllPurchaseTransactions();
							}
							else if (decision == 4)
							{
								sortPurchaseTransaction();
							}
							else if (decision == 5)
							{
								searchPurchaseCustomerTicketPurchaseInformation();
							}
							else if (decision == 6)
							{
								editCustomerTicket();
							}
							else if (decision == 7)
							{
								string IcPassport;
								cout << "Input Customer Ic Or Passport: " << endl;
								cin >> IcPassport;
								string customerid = checkCustomerId(IcPassport);

								if (customerid == "")
								{
									cout << "This IC or Passport does not exist in this system" << endl;
								}
								else
								{
									printAndDeleteTransactionHistory(customerid);
								}
							}
							else if (decision == 8)
							{
								cout << "Thank You, Have A Nice Day! " << endl;
								system("pause");
								break;
							}
							else
							{
								cin.clear();										 // remove the input operation
								cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove content
								cout << "----- Incorrect Input -----" << endl;
								system("pause");
							}
						}
						break;
					}
					else
					{
						cout << "----- Incorrect Username Or Password -----" << endl;
						system("pause");
						break;
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
					cout << "----- Invalid Format -----" << endl;
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
				cout << "Please Enter Your Full Name: ";
				cin >> customerName;
				cout << "Please Enter Your IC or Passport Number: ";
				cin >> customerIcOrPassport;
				cout << "Please Create A Password: ";
				cin >> customerPassword;

				int status = createCustomerAccount(customerName, customerIcOrPassport, customerPassword);
				if (status == 0)
				{

					string ContinueCreate;
					cout << "----- This Account Is Already Existed -----" << endl;
					cout << "Continue Create Account? " << endl;
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
						cout << "----- Invalid Input. Returning to Main Menu -----" << endl;
						system("pause");
					}
				}
				else
				{
					cout << "----- Account Created Successfully -----" << endl;
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
			cout << "----- Invalid Format -----" << endl;
			system("pause");
		}
	}

	cout << "Bye!";

	return 0;
}