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

namespace primary {
    // the state that will declare whether we are in the 1st, second, or 3rd character
    enum class Input_state {
        Play_again,
        Go_Out
    };

    // loads the table of values
    void game_screen_2l(
        std::vector<Output_con>& game_2_subtitle,
        std::vector<Output_con>& game_2_table,
        const std::vector< std::vector<std::string> >& guess,
        const std::vector< std::vector<std::string> >& validity
    );

    // print and clear the table of values
    void game_screen_2p(
        std::vector<Output_con>& game_2_subtitle,
        std::vector<Output_con>& game_2_table,
        WINDOW * given_win
    );

    // loads the main text and the border
    void game_screen_3l(
        std::vector<Output_con>& game_3_subtitle,
        std::vector<Output_con>& game_3_border
    );

    // loads the main text and the border again, in case of invalid input
    void game_screen_3la(
        std::vector<Output_con>& game_3_subtitle,
        std::vector<Output_con>& game_3_border
    );

    // print and clear out the main text and border
    void game_screen_3p(
        std::vector<Output_con>& game_3_subtitle,
        std::vector<Output_con>& game_3_border,
        WINDOW * given_win
    );

    // load the victory screeen
    void game_screen_4l(
        std::vector <Output_con>& game_4_subtitle,
        std::vector <Output_con>& game_4_border,
        std::vector <Output_con>& game_4_bigtext,
        std::vector <Output_con>& game_4_ornaments,
        std::vector <Output_con>& game_4_mtext,
        std::vector <Output_con>& game_4_sbord
    );

    //print the victory screen
    void game_screen_4p(
        std::vector <Output_con>& game_4_subtitle,
        std::vector <Output_con>& game_4_border,
        std::vector <Output_con>& game_4_bigtext,
        std::vector <Output_con>& game_4_ornaments,
        std::vector <Output_con>& game_4_mtext,
        std::vector <Output_con>& game_4_sbord
    );

    std::vector<Output_con> game_1_border {};
    std::vector<Output_con> game_2_subtitle {};
    std::vector<Output_con> game_2_table {};
    std::vector<Output_con> game_3_subtitle {};
    std::vector<Output_con> game_3_border {};
    std::vector<Output_con> game_3_text {};
    std::vector <Output_con> game_4_subtitle {};
    std::vector <Output_con> game_4_border {};
    std::vector <Output_con> game_4_bigtext {};
    std::vector <Output_con> game_4_ornaments {};
    std::vector <Output_con> game_4_mtext {};
    std::vector <Output_con> game_4_sbord {};
    std::vector <Output_con> game_4_stext {};

    // act as the sorter
    void arrsortstr( std::vector< std::vector<std::string> >& arr );

    // create an outputcon for the table's roygbv
    Output_con token_placer(string str, int y_dimu, int x_dimu);

    void game_choice_printer_1(primary::Input_state given_choice, std::vector<Output_con>& granvec);
};

/*
 * Everything past this line was primarily developed by brent.
*/

// an array containing all valid choices of color
char choiceClr[6] = {'R', 'O', 'Y', 'G', 'B', 'V'};
// will represent the indexes in the for loop
int x, y;
// the 3 correct answers and the 3 guesses
// char(82) = "R", char(71) = "G", char(66) is "B"
string color [3] = {"R", "G", "B"};
// char(95) is the underline _
std::vector< std::vector<std::string> > guess = 
{
    {"_", "_", "_"},
    {"_", "_", "_"},
    {"_", "_", "_"},
    {"_", "_", "_"},
    {"_", "_", "_"},
    {"_", "_", "_"},
    {"_", "_", "_"}
};
std::vector< std::vector<std::string> > validity = 
{
    {"_", "_", "_"},
    {"_", "_", "_"},
    {"_", "_", "_"},
    {"_", "_", "_"},
    {"_", "_", "_"},
    {"_", "_", "_"},
    {"_", "_", "_"}
};

bool choiceCheck (string input, std::vector<std::string> arr) {
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

// output function
void coutput (WINDOW * given_win_1, WINDOW * given_win_2){
    wclear(given_win_1);
    wclear(given_win_2);
    //primary::game_screen_1l(primary::game_1_border);

    //primary::game_screen_1p(primary::game_1_border);
    
    primary::game_screen_2l(
        primary::game_2_subtitle,
        primary::game_2_table,
        guess,
        validity
    );

    primary::game_screen_2p(primary::game_2_subtitle, primary::game_2_table, given_win_1);

    primary::game_screen_3l(primary::game_3_subtitle, primary::game_3_border);

    primary::game_screen_3p(primary::game_3_subtitle, primary::game_3_border, given_win_2);
}

// input function
void cinput (int row, WINDOW * given_win) {
    bool will_run_again = false;

    do {
        nocbreak();
        echo();
        curs_set(1);

        wmove(given_win, 4, 37);

        char given[10];
        wgetstr(given_win, given);

        char given_1 = given[0];
        char given_2 = given[1];
        char given_3 = given[2];

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        string gs1 (1, given_1);
        string gs2 (1, given_2);
        string gs3 (1, given_3);

        // checks if input is part of the choices (R,O,Y,B,G,V)
        bool truOne, truTwo, truThr;
        truOne = choiceCheck(given_1, choiceClr);
        truTwo = choiceCheck(given_2, choiceClr);
        truThr = choiceCheck(given_3, choiceClr);

        if (!truOne || !truTwo || !truThr) {
            curs_set(0);
            noecho();
            cbreak();
            wclear(given_win);
            //cout << "Your guess is invalid, please try again." << endl;
            primary::game_screen_3la(primary::game_3_subtitle, primary::game_3_border);
            primary::game_screen_3p(primary::game_3_subtitle, primary::game_3_border, given_win);
            will_run_again = true;
        } else {
            curs_set(0);
            noecho();
            cbreak();
            guess[row][0] = gs1;
            guess[row][1] = gs2;
            guess[row][2] = gs3;
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
                validity[row][col] = "2";
            }

            else if ((guess[row][col] == color[x]) || (guess[row][col] == color[y])) 
            {
                validity[row][col] = "1";
            }

            else
            {
                validity[row][col] = "0";
            }
        }

        primary::arrsortstr(validity);
}

bool is_victory () {
    for (int i = 0; i < 7; ++i) 
    {
        if ((guess[i][0] == color[0]) && (guess[i][1] == color[1]) && (guess[i][2] == color[2]))
        {
            //cout << "VICTORY ROYALE!!!" << endl;
            return true;
        }
    }
    return false;
}

bool act_victory ();

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
    /*
    preparatory::antecedent();
    preparatory::startup();
    */
    preparatory::begin_ncurses();
    /*
    WINDOW * Board;
    Board = newwin(17, 80, 0, 0);
    WINDOW * Text;
    Text = newwin(7, 80, 17, 0);
    wbkgd(Board, COLOR_PAIR(1));
    wbkgd(Text, COLOR_PAIR(1));

    bool given_out = false;
    for (int i = 0; i < 7; ++i)
    {
        coutput(Board, Text);
        cinput(i, Text);
        result(i);
        given_out = is_victory();
        if (given_out == true) {
            break;
        }
    }

    delwin(Board);
    delwin(Text);
*/
    act_victory();

    preparatory::end_ncurses();
}

/*
 * Everything after this line was primarily developed by rex
*/

// ==> Primary Functions

bool act_victory () {
    primary::game_screen_4l(
        primary::game_4_subtitle,
        primary::game_4_border,
        primary::game_4_bigtext,
        primary::game_4_ornaments,
        primary::game_4_mtext,
        primary::game_4_sbord
    );

    primary::game_screen_4p(
        primary::game_4_subtitle,
        primary::game_4_border,
        primary::game_4_bigtext,
        primary::game_4_ornaments,
        primary::game_4_mtext,
        primary::game_4_sbord
    );

    // prepare the default game state
    primary::Input_state given_game_choice_1 = primary::Input_state::Play_again;

    // make out that first change
    primary::game_choice_printer_1(given_game_choice_1, primary::game_4_stext);

    // initilize the input char
    int given_game_switcher_1 = 0;

    // whether the person has made a choice yet
    bool game_got_in_1 = false;

    while (!game_got_in_1) {
        given_game_switcher_1 = getch();

        switch(given_game_switcher_1) {
            case KEY_RIGHT:
            case KEY_LEFT:
                if (given_game_choice_1 == primary::Input_state::Play_again){
                    given_game_choice_1 = primary::Input_state::Go_Out;
                } else if (given_game_choice_1 == primary::Input_state::Go_Out) {
                    given_game_choice_1 = primary::Input_state::Play_again;
                }

                primary::game_choice_printer_1(given_game_choice_1, primary::game_4_stext);
                break;
            case 10:
                game_got_in_1 = true;
                break;
        }
    }

    if (given_game_choice_1 == primary::Input_state::Play_again) {
        return true;
    } else {
        return false;
    }
}

// ==> Loaders

void primary::game_screen_2l(
    std::vector<Output_con>& game_2_subtitle,
    std::vector<Output_con>& game_2_table,
    const std::vector< std::vector<std::string> >& guess,
    const std::vector< std::vector<std::string> >& validity
) {
    preparatory::priv::center_lr(
        game_2_subtitle, 
        "The board, as it stands:", 
        1, 60, 
        Output_con::Coloration::Yellow
    );

    preparatory::priv::scanner(
        game_2_table,
        {"╒", "│", "╞", "│", "╞", "│", "╞", "│", "╞", "│", "╞", "│", "╞", "│", "╘"},
        2, 20
    );
    preparatory::priv::scanner(
        game_2_table,
        {"═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═"},
        2, 21
    );
    preparatory::priv::scanner(
        game_2_table,
        {"═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═"},
        2, 22
    );
    preparatory::priv::scanner(
        game_2_table,
        {"═", "1", "═", "2", "═", "3", "═", "4", "═", "5", "═", "6", "═", "7", "═"},
        2, 23
    );
    preparatory::priv::scanner(
        game_2_table,
        {"═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═"},
        2, 24
    );
    preparatory::priv::scanner(
        game_2_table,
        {"═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═"},
        2, 25
    );
    preparatory::priv::scanner(
        game_2_table,
        {"╤", "│", "╪", "│", "╪", "│", "╪", "│", "╪", "│", "╪", "│", "╪", "│", "╧"},
        2, 26
    );
    preparatory::priv::scanner(
        game_2_table,
        {"═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═"},
        2, 27
    );
    preparatory::priv::scanner(
        game_2_table,
        {"═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═"},
        2, 28
    );
    preparatory::priv::scanner(
        game_2_table,
        {"═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═"},
        2, 29
    );
    // begin the options
    for (int i = 0, j = 30; i <= 2 && j <= 38; ++i, j += 4) {
        // first line
        game_2_table.push_back(Output_con("═", 2, j, 0, false));
        for (int k = 3, l = 0; k <= 15 && l <= 6; k += 2, ++l) {
            //! may be buggy
            game_2_table.push_back(primary::token_placer(guess[l][i], k, j));
            game_2_table.push_back(Output_con("═", (k+1), j, 0, true));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        // 3 empty spaces
        preparatory::priv::scanner(
            game_2_table,
            {"═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═"},
            2, j+1
        );
        preparatory::priv::scanner(
            game_2_table,
            {"═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═"},
            2, j+2
        );
        preparatory::priv::scanner(
            game_2_table,
            {"═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═"},
            2, j+3
        );
    }
    preparatory::priv::scanner(
        game_2_table,
        {"╤", "│", "╪", "│", "╪", "│", "╪", "│", "╪", "│", "╪", "│", "╪", "│", "╧"},
        2, 42
    );
    preparatory::priv::scanner(
        game_2_table,
        {"═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═"},
        2, 43
    );
    preparatory::priv::scanner(
        game_2_table,
        {"═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═"},
        2, 44
    );
    preparatory::priv::scanner(
        game_2_table,
        {"═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═"},
        2, 45
    );
    for (int i = 0, j = 46; i <= 2 && j <= 54; ++i, j += 4){
        // first line
        game_2_table.push_back(Output_con("═", 2, j, 0, false));
        for (int k = 3, l = 0; k <= 15 && l <= 6; k += 2, ++l) {
            //! may be buggy
            game_2_table.push_back(primary::token_placer(validity[l][i], k, j));
            game_2_table.push_back(Output_con("═", (k+1), j, 0, true));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        // 3 empty spaces
        preparatory::priv::scanner(
            game_2_table,
            {"═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═"},
            2, j+1
        );
        preparatory::priv::scanner(
            game_2_table,
            {"═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═"},
            2, j+2
        );
        preparatory::priv::scanner(
            game_2_table,
            {"═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═", " ", "═"},
            2, j+3
        );
    }
    preparatory::priv::scanner(
        game_2_table,
        {"╕", "│", "╡", "│", "╡", "│", "╡", "│", "╡", "│", "╡", "│", "╡", "│", "╛"},
        2, 58
    );
}

void primary::game_screen_3l(
    std::vector<Output_con>& game_3_subtitle,
    std::vector<Output_con>& game_3_border
) {
    // the subtitel
    preparatory::priv::center_lr(game_3_subtitle, "And your guess is: (Input 3 letters, then an enter)", 1, 60);
    preparatory::priv::valid_color_loader(game_3_subtitle, valid_tokens, 2);
    // the border of the inputs
    preparatory::priv::scanner(game_3_border, {"╓", "║", "╙"}, 3, 30);
    for (int i = 0; i <= 16; ++i) {
        preparatory::priv::scanner(game_3_border, {"─", " ", "─"}, 3, 31+i);
    }
    preparatory::priv::scanner(game_3_border, {"╖", "║", "╜"}, 3, 48);
}

void primary::game_screen_3la(
    std::vector<Output_con>& game_3_subtitle,
    std::vector<Output_con>& game_3_border
) {
    // the subtitel
    preparatory::priv::center_lr(game_3_subtitle, "Ah, it looks like your guess is invalid. Please try again.", 1, 60);
    preparatory::priv::valid_color_loader(game_3_subtitle, valid_tokens, 2);
    // the border of the inputs
    preparatory::priv::scanner(game_3_border, {"╓", "║", "╙"}, 3, 30);
    for (int i = 0; i <= 16; ++i) {
        preparatory::priv::scanner(game_3_border, {"─", " ", "─"}, 3, 31+i);
    }
    preparatory::priv::scanner(game_3_border, {"╖", "║", "╜"}, 3, 48);
}

void primary::game_screen_4l(
    std::vector <Output_con>& game_4_subtitle,
    std::vector <Output_con>& game_4_border,
    std::vector <Output_con>& game_4_bigtext,
    std::vector <Output_con>& game_4_ornaments,
    std::vector <Output_con>& game_4_mtext,
    std::vector <Output_con>& game_4_sbord
) {
    // subtitle
    preparatory::priv::center_lr(
        game_4_subtitle, 
        "Oh my, it looks like the code has been guessed!", 
        1, 60
    );
    preparatory::priv::center_lr(
        game_4_subtitle, 
        ("The code was, in fact, "+color[0]+color[1]+color[2]+","),
        2, 60
    );
    preparatory::priv::center_lr(
        game_4_subtitle,
        "and thus, we can safely declare...",
        3, 1000
    );

    // border,outer
    // Top side, border
    for (int i = 0; i <= 39; ++i) {
        game_4_border.push_back(Output_con("━", 8, (39 + i), 15, false, Output_con::Coloration::Yellow));
        game_4_border.push_back(Output_con("━", 8, (40 - i), 15, true, Output_con::Coloration::Yellow));
    }
    // Top corners, border
    game_4_border.push_back(Output_con("┏", 8, 0, 15, false, Output_con::Coloration::Yellow));
    game_4_border.push_back(Output_con("┓", 8, 79, 15, true, Output_con::Coloration::Yellow));
    // Sides, border
    // Will try a 60 millisecond delay– will that work better?
    for (int i = 0; i <= 4; ++i) {
        game_4_border.push_back(Output_con("┃", (9 + i), 0, 15, false, Output_con::Coloration::Yellow));
        game_4_border.push_back(Output_con("┃", (9 + i), 79, 15, true, Output_con::Coloration::Yellow));
    }
    // Bottom corners, border
    game_4_border.push_back(Output_con("┗", 14, 0, 15, false, Output_con::Coloration::Yellow));
    game_4_border.push_back(Output_con("┛", 14, 79, 15, true, Output_con::Coloration::Yellow));
    // Bottom side, border
    for (int i = 39; i >= 0; --i) {
        game_4_border.push_back(Output_con("━", 14, (39 + i), 15, false, Output_con::Coloration::Yellow));
        game_4_border.push_back(Output_con("━", 14, (40 - i), 15, true, Output_con::Coloration::Yellow));
    }

    // border, inner
    // Top side, border
    for (int i = 0; i <= 37; ++i) {
        game_4_border.push_back(Output_con("═", 13, (39 + i), 15, false, Output_con::Coloration::Violet));
        game_4_border.push_back(Output_con("═", 13, (40 - i), 15, true, Output_con::Coloration::Violet));
    }
    // Bottom corners, border
    game_4_border.push_back(Output_con("╚", 13, 2, 15, false, Output_con::Coloration::Violet));
    game_4_border.push_back(Output_con("╝", 13, 77, 15, true, Output_con::Coloration::Violet));
    // Sides, border
    // Will try a 60 millisecond delay– will that work better?
    for (int i = 2; i >= 0; --i) {
        game_4_border.push_back(Output_con("║", (10 + i), 2, 15, false, Output_con::Coloration::Violet));
        game_4_border.push_back(Output_con("║", (10 + i), 77, 15, true, Output_con::Coloration::Violet));
    }
    // Top corners, border
    game_4_border.push_back(Output_con("╔", 9, 2, 15, false, Output_con::Coloration::Violet));
    game_4_border.push_back(Output_con("╗", 9, 77, 15, true, Output_con::Coloration::Violet));
    // Bottom side, border
    for (int i = 37; i >= 0; --i) {
        game_4_border.push_back(Output_con("═", 9, (39 + i), 15, false, Output_con::Coloration::Violet));
        game_4_border.push_back(Output_con("═", 9, (40 - i), 15, true, Output_con::Coloration::Violet));
    }

    // the big text that says victory
    preparatory::alpha::letter_v(game_4_bigtext, 10, 19, Output_con::Coloration::Yellow);
    preparatory::alpha::letter_i(game_4_bigtext, 10, 26, Output_con::Coloration::Yellow);
    preparatory::alpha::letter_c(game_4_bigtext, 10, 32, Output_con::Coloration::Yellow);
    preparatory::alpha::letter_t(game_4_bigtext, 10, 38, Output_con::Coloration::Yellow);
    preparatory::alpha::letter_o(game_4_bigtext, 10, 44, Output_con::Coloration::Yellow);
    preparatory::alpha::letter_r(game_4_bigtext, 10, 50, Output_con::Coloration::Yellow);
    preparatory::alpha::letter_y(game_4_bigtext, 10, 56, Output_con::Coloration::Yellow);

    // ornamentation, top row
    preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, 0);
    for (int i = 1, j = 1; i <= 6 && j <= 62; ++i, j += 12) {
        preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j);
        preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+1);
        preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+2);
        preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+3);
        preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+4);
        if (i == 1) {
            game_4_ornaments.push_back(Output_con("*", 5, j+5, 10, false, Output_con::Coloration::Red));
            game_4_ornaments.push_back(Output_con("✠", 6, j+5, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 7, j+5, 10, true, Output_con::Coloration::Red));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+6);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+7);
            game_4_ornaments.push_back(Output_con("✠", 5, j+8, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 6, j+8, 10, false, Output_con::Coloration::Red));
            game_4_ornaments.push_back(Output_con("✠", 7, j+8, 10, true, Output_con::Coloration::Naught));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+9);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+10);
            game_4_ornaments.push_back(Output_con("*", 5, j+11, 10, false, Output_con::Coloration::Red));
            game_4_ornaments.push_back(Output_con("✠", 6, j+11, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 7, j+11, 10, true, Output_con::Coloration::Red));
        } else if (i == 2) {
            game_4_ornaments.push_back(Output_con("✠", 5, j+5, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 6, j+5, 10, false, Output_con::Coloration::Orange));
            game_4_ornaments.push_back(Output_con("✠", 7, j+5, 10, true, Output_con::Coloration::Naught));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+6);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+7);
            game_4_ornaments.push_back(Output_con("*", 5, j+8, 10, false, Output_con::Coloration::Orange));
            game_4_ornaments.push_back(Output_con("✠", 6, j+8, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 7, j+8, 10, true, Output_con::Coloration::Orange));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+9);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+10);
            game_4_ornaments.push_back(Output_con("✠", 5, j+11, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 6, j+11, 10, false, Output_con::Coloration::Orange));
            game_4_ornaments.push_back(Output_con("✠", 7, j+11, 10, true, Output_con::Coloration::Naught));
        } else if (i == 3) {
            game_4_ornaments.push_back(Output_con("*", 5, j+5, 10, false, Output_con::Coloration::Yellow));
            game_4_ornaments.push_back(Output_con("✠", 6, j+5, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 7, j+5, 10, true, Output_con::Coloration::Yellow));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+6);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+7);
            game_4_ornaments.push_back(Output_con("✠", 5, j+8, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 6, j+8, 10, false, Output_con::Coloration::Yellow));
            game_4_ornaments.push_back(Output_con("✠", 7, j+8, 10, true, Output_con::Coloration::Naught));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+9);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+10);
            game_4_ornaments.push_back(Output_con("*", 5, j+11, 10, false, Output_con::Coloration::Yellow));
            game_4_ornaments.push_back(Output_con("✠", 6, j+11, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 7, j+11, 10, true, Output_con::Coloration::Yellow));
        } else if (i == 4) {
            game_4_ornaments.push_back(Output_con("✠", 5, j+5, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 6, j+5, 10, false, Output_con::Coloration::Green));
            game_4_ornaments.push_back(Output_con("✠", 7, j+5, 10, true, Output_con::Coloration::Naught));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+6);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+7);
            game_4_ornaments.push_back(Output_con("*", 5, j+8, 10, false, Output_con::Coloration::Green));
            game_4_ornaments.push_back(Output_con("✠", 6, j+8, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 7, j+8, 10, true, Output_con::Coloration::Green));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+9);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+10);
            game_4_ornaments.push_back(Output_con("✠", 5, j+11, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 6, j+11, 10, false, Output_con::Coloration::Green));
            game_4_ornaments.push_back(Output_con("✠", 7, j+11, 10, true, Output_con::Coloration::Naught));
        } else if (i == 5) {
            game_4_ornaments.push_back(Output_con("*", 5, j+5, 10, false, Output_con::Coloration::Blue));
            game_4_ornaments.push_back(Output_con("✠", 6, j+5, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 7, j+5, 10, true, Output_con::Coloration::Blue));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+6);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+7);
            game_4_ornaments.push_back(Output_con("✠", 5, j+8, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 6, j+8, 10, false, Output_con::Coloration::Blue));
            game_4_ornaments.push_back(Output_con("✠", 7, j+8, 10, true, Output_con::Coloration::Naught));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+9);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+10);
            game_4_ornaments.push_back(Output_con("*", 5, j+11, 10, false, Output_con::Coloration::Blue));
            game_4_ornaments.push_back(Output_con("✠", 6, j+11, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 7, j+11, 10, true, Output_con::Coloration::Blue));
        } else {
            game_4_ornaments.push_back(Output_con("✠", 5, j+5, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 6, j+5, 10, false, Output_con::Coloration::Violet));
            game_4_ornaments.push_back(Output_con("✠", 7, j+5, 10, true, Output_con::Coloration::Naught));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+6);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+7);
            game_4_ornaments.push_back(Output_con("*", 5, j+8, 10, false, Output_con::Coloration::Violet));
            game_4_ornaments.push_back(Output_con("✠", 6, j+8, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 7, j+8, 10, true, Output_con::Coloration::Violet));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+9);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, j+10);
            game_4_ornaments.push_back(Output_con("✠", 5, j+11, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 6, j+11, 10, false, Output_con::Coloration::Violet));
            game_4_ornaments.push_back(Output_con("✠", 7, j+11, 10, true, Output_con::Coloration::Naught));
        }
    }
    preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, 73);
    preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, 74);
    preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, 75);
    preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, 76);
    preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, 77);
    preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, 78);
    preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 5, 79);

    // ornamentation, bottom row
    preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, 0);
    for (int i = 1, j = 1; i <= 6 && j <= 62; ++i, j += 12) {
        preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j);
        preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+1);
        preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+2);
        preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+3);
        preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+4);
        if (i == 1) {
            game_4_ornaments.push_back(Output_con("✠", 15, j+5, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 16, j+5, 10, false, Output_con::Coloration::Red));
            game_4_ornaments.push_back(Output_con("✠", 17, j+5, 10, true, Output_con::Coloration::Naught));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+6);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+7);
            game_4_ornaments.push_back(Output_con("*", 15, j+8, 10, false, Output_con::Coloration::Red));
            game_4_ornaments.push_back(Output_con("✠", 16, j+8, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 17, j+8, 10, true, Output_con::Coloration::Red));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+9);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+10);
            game_4_ornaments.push_back(Output_con("✠", 15, j+11, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 16, j+11, 10, false, Output_con::Coloration::Red));
            game_4_ornaments.push_back(Output_con("✠", 17, j+11, 10, true, Output_con::Coloration::Naught));
        } else if (i == 2) {
            game_4_ornaments.push_back(Output_con("*", 15, j+5, 10, false, Output_con::Coloration::Orange));
            game_4_ornaments.push_back(Output_con("✠", 16, j+5, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 17, j+5, 10, true, Output_con::Coloration::Orange));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+6);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+7);
            game_4_ornaments.push_back(Output_con("✠", 15, j+8, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 16, j+8, 10, false, Output_con::Coloration::Orange));
            game_4_ornaments.push_back(Output_con("✠", 17, j+8, 10, true, Output_con::Coloration::Naught));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+9);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+10);
            game_4_ornaments.push_back(Output_con("*", 15, j+11, 10, false, Output_con::Coloration::Orange));
            game_4_ornaments.push_back(Output_con("✠", 16, j+11, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 17, j+11, 10, true, Output_con::Coloration::Orange));
        } else if (i == 3) {
            game_4_ornaments.push_back(Output_con("✠", 15, j+5, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 16, j+5, 10, false, Output_con::Coloration::Yellow));
            game_4_ornaments.push_back(Output_con("✠", 17, j+5, 10, true, Output_con::Coloration::Naught));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+6);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+7);
            game_4_ornaments.push_back(Output_con("*", 15, j+8, 10, false, Output_con::Coloration::Yellow));
            game_4_ornaments.push_back(Output_con("✠", 16, j+8, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 17, j+8, 10, true, Output_con::Coloration::Yellow));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+9);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+10);
            game_4_ornaments.push_back(Output_con("✠", 15, j+11, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 16, j+11, 10, false, Output_con::Coloration::Yellow));
            game_4_ornaments.push_back(Output_con("✠", 17, j+11, 10, true, Output_con::Coloration::Naught));
        } else if (i == 4) {
            game_4_ornaments.push_back(Output_con("*", 15, j+5, 10, false, Output_con::Coloration::Green));
            game_4_ornaments.push_back(Output_con("✠", 16, j+5, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 17, j+5, 10, true, Output_con::Coloration::Green));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+6);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+7);
            game_4_ornaments.push_back(Output_con("✠", 15, j+8, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 16, j+8, 10, false, Output_con::Coloration::Green));
            game_4_ornaments.push_back(Output_con("✠", 17, j+8, 10, true, Output_con::Coloration::Naught));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+9);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+10);
            game_4_ornaments.push_back(Output_con("*", 15, j+11, 10, false, Output_con::Coloration::Green));
            game_4_ornaments.push_back(Output_con("✠", 16, j+11, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 17, j+11, 10, true, Output_con::Coloration::Green));
        } else if (i == 5) {
            game_4_ornaments.push_back(Output_con("✠", 15, j+5, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 16, j+5, 10, false, Output_con::Coloration::Blue));
            game_4_ornaments.push_back(Output_con("✠", 17, j+5, 10, true, Output_con::Coloration::Naught));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+6);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+7);
            game_4_ornaments.push_back(Output_con("*", 15, j+8, 10, false, Output_con::Coloration::Blue));
            game_4_ornaments.push_back(Output_con("✠", 16, j+8, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 17, j+8, 10, true, Output_con::Coloration::Blue));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+9);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+10);
            game_4_ornaments.push_back(Output_con("✠", 15, j+11, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 16, j+11, 10, false, Output_con::Coloration::Blue));
            game_4_ornaments.push_back(Output_con("✠", 17, j+11, 10, true, Output_con::Coloration::Naught));
        } else {
            game_4_ornaments.push_back(Output_con("*", 15, j+5, 10, false, Output_con::Coloration::Violet));
            game_4_ornaments.push_back(Output_con("✠", 16, j+5, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 17, j+5, 10, true, Output_con::Coloration::Violet));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+6);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+7);
            game_4_ornaments.push_back(Output_con("✠", 15, j+8, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 16, j+8, 10, false, Output_con::Coloration::Violet));
            game_4_ornaments.push_back(Output_con("✠", 17, j+8, 10, true, Output_con::Coloration::Naught));
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+9);
            preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, j+10);
            game_4_ornaments.push_back(Output_con("*", 15, j+11, 10, false, Output_con::Coloration::Violet));
            game_4_ornaments.push_back(Output_con("✠", 16, j+11, 10, false, Output_con::Coloration::Naught));
            game_4_ornaments.push_back(Output_con("*", 17, j+11, 10, true, Output_con::Coloration::Violet));
        }
    }
    preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, 73);
    preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, 74);
    preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, 75);
    preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, 76);
    preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, 77);
    preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, 78);
    preparatory::priv::scanner(game_4_ornaments, {" ", " ", " "}, 15, 79);

    // the main text
    preparatory::priv::center_lr(game_4_mtext, "Would you like to play again?", 19, 60);
    // the border
    preparatory::priv::scanner(
        game_4_sbord,
        {"╒", "│", "╘"},
        20, 20,
        Output_con::Coloration::Naught
    );
    for (int i = 0; i <= 17; ++i) {
        preparatory::priv::scanner(
            game_4_sbord,
            {"═", " ", "═"},
            20, (21 + i),
            Output_con::Coloration::Naught
        );
    }
    preparatory::priv::scanner(
        game_4_sbord,
        {"╤", "│", "╧"},
        20, 39,
        Output_con::Coloration::Naught
    );
    for (int i = 0; i <= 17; ++i) {
        preparatory::priv::scanner(
            game_4_sbord,
            {"═", " ", "═"},
            20, (40 + i),
            Output_con::Coloration::Naught
        );
    }
    preparatory::priv::scanner(
        game_4_sbord,
        {"╕", "│", "╛"},
        20, 58,
        Output_con::Coloration::Naught
    );
}

// ==> Printers

void primary::game_screen_2p(
    std::vector<Output_con>& game_2_subtitle,
    std::vector<Output_con>& game_2_table,
    WINDOW * given_win
) {
    preparatory::priv::wprintcon(given_win, game_2_subtitle);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    preparatory::priv::wprintcon(given_win, game_2_table);

    game_2_subtitle.clear();
    game_2_table.clear();
}

void primary::game_screen_3p(
    std::vector<Output_con>& game_3_subtitle,
    std::vector<Output_con>& game_3_border,
    WINDOW * given_win
) {
    preparatory::priv::wprintcon(given_win, game_3_subtitle);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    preparatory::priv::wprintcon(given_win, game_3_border);

    game_3_subtitle.clear();
    game_3_border.clear();
}

void primary::game_screen_4p(
    std::vector <Output_con>& game_4_subtitle,
    std::vector <Output_con>& game_4_border,
    std::vector <Output_con>& game_4_bigtext,
    std::vector <Output_con>& game_4_ornaments,
    std::vector <Output_con>& game_4_mtext,
    std::vector <Output_con>& game_4_sbord
) {
    preparatory::priv::printcon(game_4_subtitle);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    preparatory::priv::printcon(game_4_border);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    preparatory::priv::printcon(game_4_bigtext);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    preparatory::priv::printcon(game_4_ornaments);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    preparatory::priv::printcon(game_4_mtext);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    preparatory::priv::printcon(game_4_sbord);

    game_4_subtitle.clear();
    game_4_border.clear();
    game_4_bigtext.clear();
    game_4_ornaments.clear();
    game_4_mtext.clear();
    game_4_sbord.clear();
}

void primary::game_choice_printer_1(
    primary::Input_state given_choice, 
    std::vector<Output_con>& granvec
) {
    if (given_choice == primary::Input_state::Play_again) {
        preparatory::priv::passer_lr(
            granvec,
            "Yes",
            22, 28, // 29?
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Reversed,
            false
        );
        preparatory::priv::passer_lr(
            granvec,
            "No",
            22, 48, // 49?
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::printcon(granvec);
        granvec.clear();
    } else if (given_choice == primary::Input_state::Go_Out) {
        preparatory::priv::passer_lr(
            granvec,
            "Yes",
            22, 28, // 29?
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::passer_lr(
            granvec,
            "No",
            22, 48, // 49?
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Reversed,
            false
        );
        preparatory::priv::printcon(granvec);
        granvec.clear();
    } else {
        error("Absurd victory choice given");
    }
}

// ==> Others

void primary::arrsortstr( std::vector< std::vector<std::string> >& arr ) {
    for (int row = 0; row < 7; ++row) {
        string s1 = arr[row][0];
        // check if this first one is valid
        if (s1 == "0" || s1 == "1" || s1 == "2") {
            int si1 = stoi(s1);
            // begin work with the second thing
            string s2 = arr[row][1];
            int si2 = stoi(s2);
            if (si2 > si1) {
                int tempi = si2;
                si2 = si1;
                si1 = tempi;
                arr[row][1] = s1;
                arr[row][0] = s2;
            }
            // begin work with the thrd value
            string s3 = arr[row][2];
            int si3 = stoi(s3);
            if (si3 > si1) {
                int tempi = si3;
                si3 = si2;
                si2 = si1;
                si1 = tempi;
                arr[row][2] = s2;
                arr[row][1] = s1;
                arr[row][0] = s3;
            } else if (si3 > si2) {
                int tempi = si3;
                si3 = si2;
                si2 = tempi;
                arr[row][2] = s2;
                arr[row][1] = s3;
            }
        } else if (s1 != "_") {
            error("Invalid validity");
        }
    }
}

Output_con primary::token_placer(string str, int y_dimu, int x_dimu) {
    if (str == valid_tokens[0]) {
        return Output_con(str, y_dimu, x_dimu, 0, false, Output_con::Coloration::Red);
    } else if (str == valid_tokens[1]) {
        return Output_con(str, y_dimu, x_dimu, 0, false, Output_con::Coloration::Orange);
    } else if (str == valid_tokens[2]) {
        return Output_con(str, y_dimu, x_dimu, 0, false, Output_con::Coloration::Yellow);
    } else if (str == valid_tokens[3]) {
        return Output_con(str, y_dimu, x_dimu, 0, false, Output_con::Coloration::Green);
    } else if (str == valid_tokens[4]) {
        return Output_con(str, y_dimu, x_dimu, 0, false, Output_con::Coloration::Blue);
    } else if (str == valid_tokens[5]) {
        return Output_con(str, y_dimu, x_dimu, 0, false, Output_con::Coloration::Violet);
    } else {
        return Output_con(str, y_dimu, x_dimu, 0, false, Output_con::Coloration::Naught);
    }
}