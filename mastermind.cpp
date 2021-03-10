/*
Change Directory: cd ~/Desktop/ACodes/CPP_Files
Compile command:clang++ -std=c++11 -lncurses mastermind.cpp -o mastermind
Run: ./mastermind
*/
#include "ncurses.h"
#include "letssee.h"
#include "mastermindprep.hpp"
using namespace std;

// The overarching function.
void overarch();

/*
    Hello Brent!
    Lots of the stuff here will be your work.
*/

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
    preparatory::startup();
}