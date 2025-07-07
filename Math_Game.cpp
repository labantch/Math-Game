#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iomanip>
#include <cmath>
#include<thread>
#include<chrono>

using namespace std;

enum enQuestionsLevel { Easy = 1, Mid = 2, Hard = 3, MixLevel = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOperation = 5 };

struct stGame {
    int QuestionsNumber;
    int FirstNumber;
    int SecondtNumber;
    float PlayerAnswer;
    float RightAnswer;
    int NumberOfRightAnswers = 0;
    int NumberOfWrongAnswers = 0;

    enQuestionsLevel QuestionsLevel;
    enOperationType OperationType;
    string FinalResult;
    char OperationChar;

    int OriginalLevelChoice;
    int OriginalOperationChoice;
};

int RandomNumber(int From, int To) {
    return rand() % (To - From + 1) + From;
}

int GetPositiveNumber(const string& message, int From, int To) {
    int number;
    while (true) {
        cout << message << endl;
        cin >> number;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        if (number < From || number > To) {
            cout << "Number must be between " << From << " and " << To << ". Try again." << endl;
            continue;
        }
        break;
    }
    return number;
}

float GetNumber() {
    float Number;
    while (true) {
        cin >> Number;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        break;
    }
    return Number;
}


bool AreEqual(float a, float b, float epsilon = 0.01f) {
    return fabs(a - b) < epsilon;
}

void StartOfTheGame(stGame& Game) {
    system("cls && color 0F");
    cout << "\n\t\tWelcome to Math Game\n\n";
    Game.QuestionsNumber = GetPositiveNumber("How many questions do you want to play? [1-100]", 1, 100);
}

void ReadQuestionsLevel(stGame& Game) {
    int level = GetPositiveNumber("Enter questions level: [1] Easy, [2] Mid, [3] Hard, [4] Mix", 1, 4);
    Game.OriginalLevelChoice = level;
}

void ReadOperationType(stGame& Game) {
    int type = GetPositiveNumber("Enter operation type: [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix", 1, 5);
    Game.OriginalOperationChoice = type;
}

void ProcessQuestionsLevel(stGame& Game) {
    int levelToUse = Game.OriginalLevelChoice == MixLevel ? RandomNumber(1, 3) : Game.OriginalLevelChoice;
    Game.QuestionsLevel = static_cast<enQuestionsLevel>(levelToUse);

    switch (Game.QuestionsLevel) {
        case Easy:
            Game.FirstNumber = RandomNumber(1, 10);
            Game.SecondtNumber = RandomNumber(1, 10);
            break;
        case Mid:
            Game.FirstNumber = RandomNumber(11, 50);
            Game.SecondtNumber = RandomNumber(11, 50);
            break;
        case Hard:
            Game.FirstNumber = RandomNumber(51, 100);
            Game.SecondtNumber = RandomNumber(51, 100);
            break;
    }
}

void ProcessQuestion(stGame& Game) {
    int operationToUse = Game.OriginalOperationChoice == MixOperation ? RandomNumber(1, 4) : Game.OriginalOperationChoice;
    Game.OperationType = static_cast<enOperationType>(operationToUse);

    switch (Game.OperationType) {
        case Add:
            Game.OperationChar = '+';
            Game.RightAnswer = Game.FirstNumber + Game.SecondtNumber;
            break;
        case Sub:
            Game.OperationChar = '-';
            Game.RightAnswer = Game.FirstNumber - Game.SecondtNumber;
            break;
        case Mul:
            Game.OperationChar = '*';
            Game.RightAnswer = Game.FirstNumber * Game.SecondtNumber;
            break;
        case Div:
            Game.OperationChar = '/';
            Game.RightAnswer = float(Game.FirstNumber) / Game.SecondtNumber;

            Game.RightAnswer = round(Game.RightAnswer * 10.0f) / 10.0f;
            break;
    }
}

void DisplayQuestion(stGame& Game, int Question) {
    
    
    cout << "Question [ " << Question << " / " << Game.QuestionsNumber << " ]" << endl;
    cout << Game.FirstNumber << endl;
    cout << '\t' << Game.OperationChar << endl;
    cout << Game.SecondtNumber << endl;
    cout << string(20, '-') << endl;

    if (Game.OperationType == Div) {
       cout << "Please round your answer to **one digit after the dot**, e.g., 0.8, 1.5, etc.\n";
    }

    Game.PlayerAnswer = GetNumber();

    if (AreEqual(Game.PlayerAnswer, Game.RightAnswer)) {
        Game.NumberOfRightAnswers += 1;
        system("color 2F");
        cout << endl << "Right answer :)" << endl << endl;
    } else {
        Game.NumberOfWrongAnswers += 1;
        system("color 4F");
        cout << endl << "Wrong answer :(" << endl << endl;
        cout << fixed << setprecision(1);
        cout << "Right answer is: " << Game.RightAnswer << endl<<endl;
    }
}

string GetLevelText(int choice) {
    switch (choice) {
        case Easy: return "Easy";
        case Mid: return "Mid";
        case Hard: return "Hard";
        case MixLevel: return "Mix";
        default: return "";
    }
}

string GetOperationText(int choice) {
    switch (choice) {
        case Add: return "Add";
        case Sub: return "Sub";
        case Mul: return "Mul";
        case Div: return "Div";
        case MixOperation: return "Mix";
        default: return "";
    }
}

void DisplayGameStatus(const stGame& Game) {
    
    system("cls && color 0F");

    stGame copy = Game;
    if (copy.NumberOfRightAnswers < copy.NumberOfWrongAnswers) {
        copy.FinalResult = "Fail :(";
        system("color 4F");
    } else {
        copy.FinalResult = "Pass :)";
        system("color 2F");
    }

    cout << string(4, '\t') << string(80, '_') << "\n\n";
    cout << string(7, '\t') << "+ + G a m e  O v e r + +" << endl;
    cout << string(4, '\t') << string(28, '_') << " [ Game results ] " << string(34, '_') << "\n\n\n";
    cout << string(4, '\t') << "Questions Level      : " << GetLevelText(copy.OriginalLevelChoice) << "\n";
    cout << string(4, '\t') << "Operation type       : " << GetOperationText(copy.OriginalOperationChoice) << "\n";
    cout << string(4, '\t') << "Player right answers : " << copy.NumberOfRightAnswers << "\n";
    cout << string(4, '\t') << "Player wrong answers : " << copy.NumberOfWrongAnswers << "\n";
    cout << string(4, '\t') << "Result               : " << copy.FinalResult << "\n";
    cout << string(4, '\t') << string(80, '_') << "\n\n";
}

void Game() {
    char PlayAgain;
    do {
        stGame Game;
        StartOfTheGame(Game);
        ReadQuestionsLevel(Game);
        ReadOperationType(Game);
        for (int Question = 1; Question <= Game.QuestionsNumber; ++Question) {
            ProcessQuestionsLevel(Game);
            ProcessQuestion(Game);
            DisplayQuestion(Game, Question);
        }
        this_thread::sleep_for(chrono::seconds(1));
        DisplayGameStatus(Game);

        cout << "Do you want to play again? [Y/N]: ";
        cin >> PlayAgain;
        PlayAgain = toupper(PlayAgain);
        while (cin.fail() || (PlayAgain != 'Y' && PlayAgain != 'N')) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter Y or N: ";
            cin >> PlayAgain;
            PlayAgain = toupper(PlayAgain);
        }
    } while (PlayAgain == 'Y');

    cout << "\nThanks for playing!\n";
}

int main() {
    srand((unsigned)time(NULL));
    cout << fixed << setprecision(1);
    Game();
}
