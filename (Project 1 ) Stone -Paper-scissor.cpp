#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissor = 3 };

enum enWinner {Player1=1,Computer=2,Draw=3};

struct stRoundInfo
{
	short RoundNumber;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WninnerName = "";
};

struct stGameResults
{
	short GameRounds = 0;
	short Player1WonTimes = 0;
	short ComputerWonTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName;
};

int RandomNumber(int From, int To)
{
	int RandomNumber = rand() % (To - From + 1) + From;
	return RandomNumber;


}

short ReadHowManyRounds()
{
	short GameRounds = 1;
	do {
		cout << "How Many Rounds 1 to 10 ? \n";
		cin >> GameRounds;
	} while (GameRounds > 10 || GameRounds < 1);
	return GameRounds;
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

enGameChoice ReadPlayer1Choice()
{
	short Choice=1;
	do
	{
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissor ?";
		cin >> Choice;
	} while (Choice < 1 || Choice>3);
	return (enGameChoice)(Choice);
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)(RandomNumber(1, 3));
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
		return enWinner::Draw;
	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissor)
			return enWinner::Computer;
		break;
	case enGameChoice::Scissor:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
			return enWinner::Computer;
		break;
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
			return enWinner::Computer;
		break;
	}
	return enWinner::Player1;
}

string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player1","Computer","No Winner" };
	return arrWinnerName[Winner - 1];
}

void SetWinnerScreen(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("color 2F");
		break;

	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;
	default:
		system("color 6F");
		break;
	}
}

string Tabs(short NumberOfTabs)
{
	string t = "";
	for (int i = 0; i < NumberOfTabs; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}


string ChoiceName(enGameChoice Choice)
{
	string arrGameChoice[3] = { "Stone","Paper","Scissor" };
	return arrGameChoice[Choice - 1];
}

void PrintRoundResults(stRoundInfo Roundifo)
{
	cout << "_________________ Round[" << Roundifo.RoundNumber << "] _______________________________" << endl; 
	cout << "Player1  Choice: " << ChoiceName(Roundifo.Player1Choice )<< endl;
	cout << "Computer Choice: " << ChoiceName(Roundifo.ComputerChoice) << endl;
	cout << "Round Winner   : [" << Roundifo.WninnerName <<"] "<< endl;
	cout << "__________________________________________________________\n\n";
	SetWinnerScreen(Roundifo.Winner);
	

}

enWinner WhoWonTheGame(short Player1WonTimes, short ComputerWonTimes)
{
	if (Player1WonTimes > ComputerWonTimes)
		return enWinner::Player1;
	else if (ComputerWonTimes > Player1WonTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameResults FillGameResults(short GameRounds, short Player1WonTimes, short ComputerWonTimes, short DrawTimes)
{
	stGameResults GameResults;
	GameResults.GameRounds = GameRounds;
	GameResults.Player1WonTimes = Player1WonTimes;
	GameResults.ComputerWonTimes = ComputerWonTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(Player1WonTimes, ComputerWonTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);
	return GameResults;

}


void ShowGameOverScreen()
{
	cout << Tabs(2) << "_______________________________________________________" << endl;

	cout << Tabs(2) << "                 +++ G a m e O v e r +++               " << endl;
	cout << Tabs(2) << "_______________________________________________________" << endl;
}

void ShowFinalGameResuls(stGameResults GameResults)
{
	cout << Tabs(2) << "____________________ [Game Results ] _________________" << endl;
	cout << Tabs(2) << "GameRounds        : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player1 Won times : " << GameResults.Player1WonTimes << endl;
	cout << Tabs(2) << "Computer Won times: " << GameResults.ComputerWonTimes << endl;
	cout << Tabs(2) << "Draw times        : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner      : " <<WinnerName( GameResults.GameWinner )<< endl;
	cout << Tabs(2) << "______________________________________________________" << endl;

}


stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short Player1WonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;
	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WninnerName = WinnerName(RoundInfo.Winner);
		if (RoundInfo.Winner == enWinner::Player1)
			Player1WonTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWonTimes++;

		else
			DrawTimes++;
		PrintRoundResults(RoundInfo);
	}

	return FillGameResults(HowManyRounds, Player1WonTimes, ComputerWonTimes,DrawTimes);
	

}

void StartGame()
{
	char PlayAgain = 'Y';
	do {
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResuls(GameResults);
		cout << Tabs(2)<<"Do you want to play again? Y/N?";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}

////write a program that represent a stone-paper-scissor Game
//#include<iostream>
//#include<string>
//#include<iomanip>
//#include<cstdlib>
//using namespace std;
//int ReadNumber(string Message)
//{
//	int Number;
//	do {
//		cout << Message;
//		cin >> Number;
//	} while (Number <= 0);
//	return Number;
//}
//int RandomNumber(int From, int To)
//{
//	int RandomNumber = rand() % (To - From + 1) + From;
//	return RandomNumber;
//
//
//}
//
//string GetChoiceOfPlayer ()
//{
//	int Choice;
//	Choice = ReadNumber("Your Choice: [1]:Stone, [2]:Paper, [3]:Scissor ?");
//	switch (Choice)
//	{
//	case 1:
//		return "Stone";
//		break;
//	case 2:
//		return "Paper";
//		break;
//	case 3:
//		return "Scissor";
//		break;
//	}
//}
//string GetChoiceOfComputer()
//{
//	int Choice;
//	Choice = RandomNumber(1, 3);
//	switch (Choice)
//	{
//	case 1:
//		return "Stone";
//		break;
//	case 2:
//		return "Paper";
//		break;
//	case 3:
//		return "Scissor";
//		break;
//	}
//}
//string RoundWinner(string Player1Choice,string ComputerChoice,int&Player1WonTimes,int &ComputerWonTimes,int &DrawTimes)
//{
//	if (Player1Choice == ComputerChoice)
//	{
//		system("color 6F");
//		DrawTimes++;
//		return "[No Winner]\n";
//	}
//	else if (Player1Choice == "Paper" && ComputerChoice == "Stone")
//	{
//		system("color 2F");
//		Player1WonTimes++;
//		return "[Player1]\n";
//	}
//	else if (Player1Choice == "Paper" && ComputerChoice == "Scissor")
//	{
//		system("color 4F");
//		cout << "\a";
//		ComputerWonTimes++;
//		return "[Computer]\n";
//	}
//	else if (Player1Choice == "Stone" && ComputerChoice == "Paper")
//	{
//		system("color 4F");
//		cout << "\a";
//		ComputerWonTimes++;
//		return "[Computer]\n";
//	}
//	else if (Player1Choice == "Stone" && ComputerChoice == "Scissor")
//	{
//		system("color 2F");
//		Player1WonTimes++;
//		return "[Player1]\n";
//	}
//	else if (Player1Choice == "Scissor" && ComputerChoice == "Paper")
//	{
//		system("color 2F");
//		Player1WonTimes++;
//		return "[Player1]\n";
//	}
//	else if (Player1Choice == "Scissor" && ComputerChoice == "Stone")
//	{
//		system("color 4F");
//		cout << "\a";
//		ComputerWonTimes++;
//		return "[Computer]\n";
//	}
//}
//void RoundOfGame(int NumOfRound, int& Player1WonTimes, int &ComputerWonTimes, int& DrawTimes)
//{
//	string Player1Choic = GetChoiceOfPlayer();
//	cout <<"\n____________Round[" << NumOfRound << "]_____________\n";
//
//	cout <<"Player1  Choice: " << Player1Choic << endl;
//	string ComputerChoice = GetChoiceOfComputer();
//	cout <<"Computer Choice: " << ComputerChoice << endl;
//	cout <<"Round Winner   : " << RoundWinner( Player1Choic,ComputerChoice, Player1WonTimes, ComputerWonTimes, DrawTimes)<<endl;
//	cout << "---------------------------------\n";
//	
//}
//
//string FinalWinner(int& Player1WonTimes, int& ComputerWonTimes,int &DrawTimes)
//{
//	if (Player1WonTimes == ComputerWonTimes)
//	{
//		system("color 6F");
//		return "Draw";
//	}
//	else if (Player1WonTimes > ComputerWonTimes)
//	{
//		system("color 2F");
//		return "Player 1";
//	}
//	else
//	{
//		system("color 4F");
//		cout << "\a";
//		return "Computer";
//	}
//}
//void GameResults( int NumberOfRounds, int& Player1WonTimes,int &ComputerWonTimes,int &DrawTimes)
//{
//	cout << "                ------------------------------------------           \n"; 
//	cout << "                         +++ G a m e O v e r +++                      \n";
//	cout << "                -------------[Game Results ]--------------             \n";
//	cout << "                Game Rounds           : "<< NumberOfRounds<<endl;
//	cout << "                Player1 won times     : "<<Player1WonTimes<<endl;
//	cout << "                Computer won times    : "<<ComputerWonTimes<<endl;
//	cout << "                Draw tiems            : "<<DrawTimes<<endl;
//			                 
//	cout << "                Final Winner          : " << FinalWinner(Player1WonTimes, ComputerWonTimes, DrawTimes) << endl;
//}
//void LoopForRoundsOfGame(int& NumOfRounds,  int &Player1WonTimes, int& ComputerWonTimes, int &DrawTimes)
//{
//	NumOfRounds = ReadNumber("How Many Rounds 1 to 10 ?\n");
//	for (int i =1 ; i <= NumOfRounds; i++)
//	{
//		cout << "\nRound[" << i << "] begins:\n\n";
//		RoundOfGame(i, Player1WonTimes, ComputerWonTimes, DrawTimes);
//	}
//
//}
//int main()
//{
//	srand((unsigned)time(NULL));
//	char Answer;
//	do {
//		int Player1WonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0, NumberOfRounds = 0;
//
//		system("cls");
//		system("color 0F");
//		LoopForRoundsOfGame(NumberOfRounds, Player1WonTimes, ComputerWonTimes, DrawTimes);
//		
//		GameResults(NumberOfRounds,Player1WonTimes, ComputerWonTimes, DrawTimes);
//	cout << "                Do you want to play again? Y/N?";
//		cin >> Answer;
//
//	} while (Answer == 'Y' || Answer == 'y');
//
//	return 0;
//}
