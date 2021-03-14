/*
Change Directory: cd ~/Desktop/ACodes/CPP_Files/Masterminds && clang++ -std=c++11 -lncurses mastermind.cpp -o mastermind && ./mastermind
Compile command:clang++ -std=c++11 -lncurses mastermind.cpp -o mastermind
Run: ./mastermind
input: OVB ORB ROB RVB RYB RGB
*/
//#include "ncurses.h"
//#include "letssee.hpp"
#include "mastermindprep.hpp"
using namespace std;

// The overarching function.
void overarch();

/*
    Hello Brent!
    Lots of the stuff here will be your work.
*/

// an array containing all valid choices of color
char choiceClr[6] = {'R', 'O', 'Y', 'G', 'B', 'V'};
// will represent the indexes in the for loop
char x, y;
// the 3 correct answers and the 3 guesses
// char(82) = "R", char(71) = "G", char(66) is "B"
char color [3] = {char(82), char(71), char(66)};
// char(95) is the underline _
char guess [7][3] = 
{
    {char(95), char(95), char(95)},
    {char(95), char(95), char(95)},
    {char(95), char(95), char(95)},
    {char(95), char(95), char(95)},
    {char(95), char(95), char(95)},
    {char(95), char(95), char(95)},
    {char(95), char(95), char(95)}
};
int validity [7][3] = 
{
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};

bool choiceCheck (char input, char arr[6]) {
    int sum = 0;
    for (int i = 0; i <= 6; ++i) {
        if (input == arr[i]) {
            sum = 1;
        }
    }
    if (sum == 1) {
        return true;
    } else {
        return false;
    }
}

// input function
void cinput (int row) {
    bool will_run_again = false;

    do {
        cout << "Choices (R,O,Y,G,B,V)" << endl;
        cout << "Enter Your Three Guesses:";

        cin >> guess[row][0] >> guess[row][1] >> guess[row][2];

        // checks if input is part of the choices (R,O,Y,B,G,V)
        bool truOne, truTwo, truThr;
        truOne = choiceCheck(guess[row][0], choiceClr);
        truTwo = choiceCheck(guess[row][1], choiceClr);
        truThr = choiceCheck(guess[row][2], choiceClr);
        if (!truOne || !truTwo || !truThr) {
            cout << "Your guess is invalid, please try again." << endl;
            will_run_again = true;
        } else {
            will_run_again = false;
        }
    } while (will_run_again);
}

void result(int row) {
    for (int col=0;col < 3;col++)
        {
            if (col == 0)
            {
                x = 1;
                y = 2;
            }

            if (col == 1)
            {
                x = 0;
                y = 2;
            }

            if (col == 2)
            {
                x = 0;
                y = 1;
            }
    
            if (guess[row][col] == color[col])
            {
                validity[row][col] = 2;
            }

            else if ((guess[row][col] == color[x]) || (guess[row][col] == color[y])) 
            {
                validity[row][col] = 1;
            }

            else
            {
                validity[row][col] = 0;
            }
        }

        sort(begin(validity[row]), end(validity[row]), greater<int>());
}

// output function
bool coutput (){
    for (int c = 1; c < 8; c++){
        cout << endl << "------------------------------" << endl;
        cout << "|    " << c << " | " << guess[c-1][0] << " " << guess[c-1][1] << " " << guess[c-1][2] << " ";
        cout << "   | " << validity[c-1][0] << " " << validity[c-1][1] << " " << validity[c-1][2] << "    |" << endl;
    }
    cout << "------------------------------" << endl << endl;

    for (int i = 0; i < 7; ++i) 
    {
        if ((guess[i][0] == color[0]) && (guess[i][1] == color[1]) && (guess[i][2] == color[2]))
        {
            cout << "VICTORY ROYALE!!!" << endl;
            return true;
        }
    }
    return false;
}

int main (int argc, char* argv[]) {
    try {
    	overarch(); 
	    return 0;
    }
    catch (exception& e) {
	    std::cerr << "exception: " << e.what() << std::endl;
	    keep_window_open_exit();
	    return 1;
    }
    catch (...) {
	    std::cerr << "exception\n";
	    keep_window_open_exit();
	    return 2;
    }
}

void overarch() {
    preparatory::antecedent();
    preparatory::begin_ncurses();
    preparatory::startup();
    /*
    for (int i = 0; i < 7; ++i)
    {
        cinput(i);
        result(i);
        bool given_out = coutput();
        if (given_out == true) {
            break;
        }
    }
    */
    preparatory::end_ncurses();
}