#include<iostream>
#include<string>
#include<stdlib.h> //Clear Text in Output 
#include<ctime> //Get Current Date and Time 
using namespace std;


struct Station {

	int StationID;
	string StationName;
	string PreviousStationName;
	string NextStationName;
	double DistanceBetweenPreviousStation;
	double CostBetweenPreviousStation;
	double TimeBetweenPreviousStation;
	double DistanceBetweenNextStation;
	double CostBetweenNextStation;
	double TimeBetweenNextStation;
	string NearbySightseeingSpots;

	Station* nextAdd;
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
}*ticketHead, * ticketCurrent;

void drawopening() {
	cout << "      -------------------------------------" << endl;
	cout << "      -------Ticket Booking System---------" << endl;
	cout << "      -------------------------------------" << endl << endl;
	cout << "    Welcome to Kuala Lumpur Light Rail Transit(LRT) - Titiwangsa Station - Chan Sow Lin Station Route" << endl << endl;

}


void drawmap() {

	cout << "       Titiwangsa   PWTC   Sultan Ismail   Majils Jamek   Plaza Rakyat   Hang Tuah   Pudu   Chan Sow Lin" << endl;
	cout << "    -------/\\--------/\\---------/\\--------------/\\------------/\\------------/\\--------/\\---------/\\--------" << endl;
	cout << "    -------\\/--------\\/---------\\/--------------\\/------------\\/------------\\/--------\\/---------\\/--------";

}


//create a Station node function
Station* createStationNode(int StationID, string StationName, string PreviousStationName, string NextStationName, 
	double DistanceBetweenPreviousStation, double CostBetweenPreviousStation, double TimeBetweenPreviousStation,
	double DistanceBetweenNextStation, double CostBetweenNextStation, double TimeBetweenNextStation, string NearbySightseeingSpots)
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

	return StationNode;
}


//Insert to the End of the list
void insertToTheEndList(Station* StationNode)
{
	// If the list still empty
	if (stationHead == NULL)
	{
		stationHead = StationNode;
	}

	// If the list not empty
	else
	{
		stationCurrent = stationHead;	
		while (stationCurrent->nextAdd != NULL)
		{
			stationCurrent = stationCurrent->nextAdd;
		}
		stationCurrent->nextAdd = StationNode;
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

		case 2://Can be change to doubly linked list
			for (int i = 1; i <= 8; i++)
			{
				if (stationCurrent->StationID < departure)
				{
					cout << stationCurrent->StationID << ") ";
					cout << stationCurrent->StationName << endl;
					stationCurrent = stationCurrent->nextAdd;
				}
				else
				{
					stationCurrent = stationCurrent->nextAdd;
				}
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
		
		return 5;
	}

	return 6;
}


//List all possible Departure Time
void listAllPossibleDepartureTime(int route, int departure) //int todaydate)
{
	if (route == 1)
	{
		int possibleMinutes[2] = { 0,0 };
		// list all possible minutes
		stationCurrent = stationHead;
		for (int i = 1; i <= departure; i++)
		{
			cout << possibleMinutes[0];
			cout << stationCurrent->TimeBetweenPreviousStation;
			possibleMinutes[0] = possibleMinutes[0] + stationCurrent->TimeBetweenPreviousStation;
			stationCurrent->nextAdd;
		}
		possibleMinutes[1] = possibleMinutes[0] + 30;

		cout << "1)" << possibleMinutes[0] << "2)" << possibleMinutes[1] << endl;


	}
	else
	{

	}
	stationCurrent = stationHead;
}


void displayDetailsBetweenTwoSelectedCities(int route, int departure, int arrival)
{
	stationCurrent = stationHead;
	double totaldistance = 0;
	double totalexpenses = 0;
	double totaltime = 0;

	string PassengerName;
	string PassengerIcOrPassport;



	if (route == 1)
	{
		for (int i = 1; i < departure; i++)
		{
			stationCurrent = stationCurrent->nextAdd;
		}

		for (int i = departure; i < arrival; i++)
		{
			totaldistance = totaldistance + stationCurrent->DistanceBetweenNextStation;
			totalexpenses = totalexpenses + stationCurrent->CostBetweenNextStation;
			totaltime = totaltime + stationCurrent->TimeBetweenNextStation;
			stationCurrent = stationCurrent->nextAdd;
		}

		cout << "Total Distance: " << totaldistance << " KM" << endl;
		cout << "Total Expenses: RM " << totalexpenses << endl;
		cout << "Total Time: " << totaltime << " Minutes" << endl << endl;

		cout << "Please Enter your name: ";
		cin >> PassengerName;
		cout << "Please Enter your passport: ";
		cin >> PassengerIcOrPassport;


	}
}

int main()
{
	stationHead = NULL;

	int role = 0;
	Station* StationNode1 = createStationNode(1, "Titiwangsa", "", "PWTC", 0, 0, 0, 4, 0.4, 3, "NearbySeeingSpot1");
	Station* StationNode2 = createStationNode(2, "PWTC", "Titiwangsa", "Sultan Ismail", 4, 0.4, 3, 8, 0.8, 7, "NearbySeeingSpot2");
	Station* StationNode3 = createStationNode(3, "Sultan Ismail", "PWTC", "Majlis Jamek", 8, 0.8, 7, 8, 0.8, 7, "NearbySeeingSpot3");
	Station* StationNode4 = createStationNode(4, "Majlis Jamek", "Sultan Ismail", "Plaza Rakyat", 8, 0.8, 7, 6, 0.6, 5, "NearbySeeingSpot4");
	Station* StationNode5 = createStationNode(5, "Plaza Rakyat", "Majlis Jamek", "Hang Tuah", 6, 0.6, 5, 10, 1.0, 9, "NearbySeeingSpot5");
	Station* StationNode6 = createStationNode(6, "Hang Tuah", "Plaza Rakyat", "Pudu", 10, 1, 9, 5, 0.5, 4, "NearbySeeingSpot6");
	Station* StationNode7 = createStationNode(7, "Pudu", "Hang Tuah", "Chan Sow Lin", 5, 0.5, 4, 5, 0.5, 4, "NearbySeeingSpot7");
	Station* StationNode8 = createStationNode(8, "Chan Sow Lin", "Pudu", "", 5, 0.5, 4, 0, 0, 0, "NearbySeeingSpot8");

	while (role == 0)
	{
		cout << "1) Passenger" << endl;
		cout << "2) Admin" << endl;
		cout << "Select your role: ";
		cin >> role;

		if (role == 1)
		{
			insertToTheEndList(StationNode1);
			insertToTheEndList(StationNode2);
			insertToTheEndList(StationNode3);
			insertToTheEndList(StationNode4);
			insertToTheEndList(StationNode5);
			insertToTheEndList(StationNode6);
			insertToTheEndList(StationNode7);
			insertToTheEndList(StationNode8);


			int route;
			cout << "1) Titiwangsa -> Chan Sow Lin" << endl;
			cout << "2) Chan Sow Lin -> Titiwangsa" << endl;
			cout << "Choose your route: " << endl;
			cin >> route;

			int departure;
			cout << "Choose your Departure location: " << endl;
			cin >> departure;
			listAllPossibleArrivalStation(route, departure);

			int arrival;
			cout << "Choose your Arrival location: " << endl;
			cin >> arrival;

			listAllPossibleDepartureTime(route, departure);

			//Get Current Date and Time
			struct tm newtime;
			time_t now = time(0);
			localtime_s(&newtime, &now);

			int CurrentHours = newtime.tm_hour;
			int CurrentMins = newtime.tm_min;


			int DepartureYear, DepartureMonth, DepartureDay, DepartureHours, DepartureMins = 0;
			char seperator1, seperator2;
			int InputCorrect = 0;
			int TodayDate = 0;

			do {
				cout << "Please enter your departure Date (in YYYY/MM/DD format): " << endl;
				cout << "Note: Ticket can only be bought before 2025" << endl;
				cin >> DepartureYear >> seperator1 >> DepartureMonth >> seperator2 >> DepartureDay;

				if (cin.fail() || seperator1 != '/' || seperator2 != '/')
				{
					cin.clear(); //remove the input operation
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); //remove content
					cout << "Invalid Format";
					continue;
				}

				switch (isValidDate(DepartureYear, DepartureMonth, DepartureDay)) {
				case 0:
					cout << "Invalid Year" << endl;
					break;
				case 1:
					cout << "Invalid Month" << endl;
					break;
				case 2:
					cout << "Invalid Day" << endl;
					break;
				case 3:
					cout << "This year Febuary only has 28 days" << endl;;
					break;
				case 4:
					cout << "The selected date is past" << endl;
					break;
				case 5:
					cout << "Correct1" << endl;
					InputCorrect = 1;
					TodayDate = 1;
					break;
				case 6:
					cout << "Correct2" << endl;
					InputCorrect = 1;
				}

			} while (InputCorrect == 0);



			//displayDetailsBetweenTwoSelectedCities(route, departure, arrival);

		}
		else if (role == 2)
		{
			//Admin
			cout << "Admin";
		}

	}
	
	cout << "Bye";
	
	//Clear Text
	//system("CLS");

	//Pause System
	//system("pause");

	return 0;
}