#include<iostream>
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


void drawopening() {
	cout << "      -------------------------------------" << endl;
	cout << "      -------Ticket Booking System---------" << endl;
	cout << "      -------------------------------------" << endl << endl;
	cout << "    Welcome to Kuala Lumpur Light Rail Transit(LRT) - Titiwangsa Station - Chan Sow Lin Station Route" << endl << endl;

}


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


//Insert to the Front of the list
void insertToTheFrontList(Station* StationNode)
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
	

	int size = 38;
	string* TrainArrivalTime;
	if (todaydate == 0)
	{
		//Create a empty dynamic array to contain all possible departure time
		TrainArrivalTime = new string[size];

		//Calculate all possible departure time
		int hour = 6;
		int count = 0;
		while (count != 38) {
			if (hour == 24)
			{
				hour = 0;
			}
			cout << count + 1 << ") " << setw(2) << setfill('0') << to_string(hour) << ":" << setw(2) << setfill('0') << to_string(minutes) << endl;
			TrainArrivalTime[count] = to_string(hour) + ":" + to_string(minutes);
			count++;
			minutes = minutes + 30;
			if (minutes > 59)
			{
				minutes = minutes - 60;
				hour = hour + 1;
			}
		}

	}
	else //VERY BUGGGGGGY NEED MORE TESTING
	{	
		//Get Current Date and Time
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);
		int CurrentHours = newtime.tm_hour;
		int CurrentMins = newtime.tm_min;

		//possible hour
		int hour = CurrentHours;

		// Calculating the size of the dynamic array needed
		if (hour < 6) // if passenger book on midnight of the current date
		{
			hour = 6;
			size = 38;
		}
		else
		{
			size = size - ((hour - 6) * 2);
			if (CurrentMins >= minutes)
			{
				size = size - 1;
				minutes = minutes + 30;
				if (minutes > 59)
				{
					minutes = minutes - 60;
					hour = hour + 1;
				}
				else if (CurrentMins >= minutes)
				{
					size = size - 1;
					minutes = minutes - 30;
					hour = hour + 1;
				}
			}
		}
		

		//Create a empty dynamic array to contain all possible departure time
		TrainArrivalTime = new string[size];

		//Calculate all possible departure time
		int count = 0;
		while (count != size) {
			if (hour == 24)
			{
				hour = 0;
			}
			
			cout << count + 1 << ") " << setw(2) << setfill('0') << to_string(hour) << ":" << setw(2) << setfill('0') << to_string(minutes) << endl;
			TrainArrivalTime[count] = to_string(hour) + ":" + to_string(minutes);
			count++;
			minutes = minutes + 30;
			if (minutes > 59)
			{
				minutes = minutes - 60;
				hour = hour + 1;
			}
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
			return TrainArrivalTime[DepartureTimeIndex - 1];
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
		cout << "Total Expenses: RM " << totalexpenses << endl;
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
void purchaseticket()
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

	int role = 0;
	Station* StationNode1 = createStationNode(1, "Titiwangsa", "", "PWTC", 0, 0, 0, 4, 0.40, 3, "NearbySeeingSpot1");
	Station* StationNode2 = createStationNode(2, "PWTC", "Titiwangsa", "Sultan Ismail", 4, 0.40, 3, 8, 0.80, 7, "NearbySeeingSpot2");
	Station* StationNode3 = createStationNode(3, "Sultan Ismail", "PWTC", "Majlis Jamek", 8, 0.80, 7, 8, 0.80, 7, "NearbySeeingSpot3");
	Station* StationNode4 = createStationNode(4, "Majlis Jamek", "Sultan Ismail", "Plaza Rakyat", 8, 0.80, 7, 6, 0.60, 5, "NearbySeeingSpot4");
	Station* StationNode5 = createStationNode(5, "Plaza Rakyat", "Majlis Jamek", "Hang Tuah", 6, 0.60, 5, 10, 1.00, 9, "NearbySeeingSpot5");
	Station* StationNode6 = createStationNode(6, "Hang Tuah", "Plaza Rakyat", "Pudu", 10, 1.00, 9, 5, 0.50, 4, "NearbySeeingSpot6");
	Station* StationNode7 = createStationNode(7, "Pudu", "Hang Tuah", "Chan Sow Lin", 5, 0.50, 4, 5, 0.50, 4, "NearbySeeingSpot7");
	Station* StationNode8 = createStationNode(8, "Chan Sow Lin", "Pudu", "", 5, 0.50, 4, 0, 0, 0, "NearbySeeingSpot8");

	while (role == 0)
	{
		cout << "1) Passenger" << endl;
		cout << "2) Admin" << endl;
		cout << "Select your role: ";
		cin >> role;

		if (role == 1)
		{
			insertToTheFrontList(StationNode8);
			insertToTheFrontList(StationNode7);
			insertToTheFrontList(StationNode6);
			insertToTheFrontList(StationNode5);
			insertToTheFrontList(StationNode4);
			insertToTheFrontList(StationNode3);
			insertToTheFrontList(StationNode2);
			insertToTheFrontList(StationNode1);

			purchaseticket();
		}

			

	
		else if (role == 2)
		{
			//Admin
			cout << "Admin";
		}

	}
	
	cout << "Bye";
	
	return 0;
}