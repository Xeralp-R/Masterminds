#include "ncurses.h"
#include "letssee.hpp"
#include <thread>
#include <chrono>
#include <locale.h>

// The structure that will contain color and boldness information.
// Font-character information
struct FC_info {
    /*
     * The permitted colors of any given character.
     * Called Coloration because Color is defined in mastermind.cpp.
    */
    enum class Coloration{Naught = 1, Red, Orange, Yellow, Green, Blue, Violet};

    // The initialization of the enum class:
    Coloration given_color = Coloration::Naught;

    // TODO: Add boldness information

    // Constructor with 1 color?
    FC_info(Coloration col) :
        given_color(col) {}
    // Constructor with nothing?
    FC_info() :
        given_color(Coloration::Naught) {}
};

// The structure that will contain the outputted things.
struct Output_con {
    // The character that will be outputted
    std::string output_char;
    // The x-dimension
    int x_dim;
    // The y dimension
    int y_dim;
    // The time to wait in milliseconds
    int wait_time;
    // Whether the char will return after couting
    bool return_now; 
    // a modifier to make it bold or colored or something.
    FC_info state_mod; 
    // to confirm if something is empty " "
    const char empty = char(32);

    // Constructor for Output_con given string and x,y dim
    Output_con(std::string str, int y1, int x1) :
        output_char(str), 
        x_dim(x1), 
        y_dim(y1), 
        wait_time(30), 
        return_now(true) { }
    // Constructor for Output_con given all except mod
    Output_con(std::string str, int y1, int x1, int wait, bool return_n) :
        output_char(str),
        x_dim(x1),
        y_dim(y1),
        wait_time(wait),
        return_now(return_n) { }
    // Constructor for Output_con given all
    Output_con(std::string str, int y1, int x1, int wait, bool return_n, FC_info mod) :
        output_char(str),
        x_dim(x1),
        y_dim(y1),
        wait_time(wait),
        return_now(return_n),
        state_mod(mod) {}
    // Constructor given just a color
    Output_con(std::string str, int y1, int x1, FC_info mod) :
        output_char(str),
        x_dim(x1),
        y_dim(y1),
        wait_time(30),
        return_now(true),
        state_mod(mod) {}
};

// The namespace that will contain all of the preparatory functions.
namespace preparatory {
    // The general, overarching preparatory function.
    void startup();
    
    class Title {
        public:
            // Constructor.
            //Title();

            // Prints the title screen and accept the inputs given to it.
            void title_screen();

            // Prints the title itself.
            void title_screen_1(
                std::vector<Output_con>& title_1_bord_1, 
                std::vector<Output_con>& title_1_bord_2, 
                std::vector<Output_con>& title_1_text
            );

            // Prints the creators.
            void title_screen_2(
                std::vector<Output_con>& title_2_border,
                std::vector<Output_con>& title_2_text
            );

            // Prints the current settings.
            void title_screen_3(
                std::vector<Output_con>& title_3_subtitle,
                std::vector<Output_con>& title_3_border,
                std::vector<Output_con>& title_3_text
            );

            // Prints the menu.
            void title_screen_4();
        private:
            // The vector that will contain the borders and text of the title.
            std::vector<Output_con> title_1_bord_1 {};
            std::vector<Output_con> title_1_bord_2 {};
            std::vector<Output_con> title_1_text {};

            // The vectors that will contain the creators.
            std::vector<Output_con> title_2_border {};
            std::vector<Output_con> title_2_text {};

            // The vectors that will contain the current settings.
            std::vector<Output_con> title_3_subtitle {};
            std::vector<Output_con> title_3_border {};
            std::vector<Output_con> title_3_text {};

            // The vectors that will set up the menu.
            std::vector<Output_con> title_4_subtitle {};
            std::vector<Output_con> title_4_border {};
            std::vector<Output_con> title_4_text {};
    };

    // Prints the help screen and accepts the inputs given to it.
    void help_screen();

    // All of the private data that needs to be kept away from mastermind.
    // Primarily helper functions and other such things.
    namespace priv {
        int terminal_x = -1, terminal_y = -1;

        // The required termwidth.
        const int termwidth = 80;

        // Output the outputcons correctly
        void printcon(std::vector<Output_con>& outputvec);

        // Pass a vector of Output_cons to printcon.
        // Meant to help with sweeping function.
        void scanner(std::vector <Output_con>& granvec, std::vector <std::string> vecstr, int y_dimu, int x_dimu);

        void center_lr(std::vector <Output_con>& granvec, std::string outstr, int y_dimu, int lastwait);
    }
    
}

// ==> Definitions

void preparatory::startup() {
    // before NCURSES is called
    std::cout << "This file has been designed with the library \u001b[1mNCURSES\u001b[0m in mind." << std::endl;
    std::cout << "You will also require an \u001b[1m80-pixel width terminal or wider.\u001b[0m" << std::endl;
    std::cout << "The program will call an error if you are at neither." << std::endl;
    keep_window_open_cont();
    /*
    if (can_change_color() == false) {
        std::cout << "Your terminal is unable to change colors."
        "Due to this, the color orange may be invisible or discolored." << std::endl;
        keep_window_open_cont();
    }
    */
    //call NCURSES
    setlocale(LC_ALL, "");
    initscr();
    
    // confirm that the screen is, in fact, at least 80 pixels wide
    getmaxyx(stdscr, preparatory::priv::terminal_y, preparatory::priv::terminal_x);
    // call error if not
    if (preparatory::priv::terminal_x < preparatory::priv::termwidth) {
        error("Your screen is not wide enough to play this game.");
    }
    if (has_colors() == false) {
        error("Your terminal does not support colors.");
    }
    
    start_color();
    //use_default_colors();
    wbkgd(stdscr, COLOR_PAIR(1));

    // prepare the game title
    preparatory::Title Game_Title;
    Game_Title.preparatory::Title::title_screen();
    refresh();
    getch();
    endwin();
}

void preparatory::Title::title_screen() {

    // wait for 1 second before beginning the run
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Define color pairs
    init_pair(1, 15, 0);
    init_pair(2, COLOR_RED, 0);
    init_pair(3, 172, 0); // Orange
    init_pair(4, 220, 0); // Gold?
    init_pair(5, COLOR_GREEN, 0);
    init_pair(6, COLOR_BLUE, 0);
    init_pair(7, COLOR_MAGENTA, 0);

    // The title itself
    preparatory::Title::title_screen_1(
        preparatory::Title::title_1_bord_1,
        preparatory::Title::title_1_bord_2,
        preparatory::Title::title_1_text
    );

    // The creator boxes
    preparatory::Title::title_screen_2(
        preparatory::Title::title_2_border,
        preparatory::Title::title_2_text
    );

    preparatory::Title::title_screen_3(
        preparatory::Title::title_3_subtitle,
        preparatory::Title::title_3_border,
        preparatory::Title::title_3_text
    );

    // Move on to next part of screen
	refresh();
	getch();
}

void preparatory::Title::title_screen_1(
    std::vector<Output_con>& title_1_bord_1, 
    std::vector<Output_con>& title_1_bord_2, 
    std::vector<Output_con>& title_1_text
) {
    /*
    This function has 2 things to do:
    it will load the necessary vectors,
    and it will output that vector to the standard window.
    The actual outputting will be done by a private function,
    to ensure that the program will not accidentally call it.
    */

    // Top corner
    title_1_bord_1.push_back(Output_con("┏", 0, 0));
    // Left side
    for (int i = 1; i <= 5; ++i) {
        title_1_bord_1.push_back(Output_con("┃", i, 0));
    }
    // Bottom Left Corner
    title_1_bord_1.push_back(Output_con("┗", 6, 0));
    // Bottom Side
    for (int i = 1; i <= 78; ++i) {
        title_1_bord_1.push_back(Output_con("━", 6, i));
    }
    // Bottom Right Corner
    title_1_bord_1.push_back(Output_con("┛", 6, 79));
    // Right Side
    for (int i = 5; i >= 1; --i) {
        title_1_bord_1.push_back(Output_con("┃", i, 79));
    }
    // Top Right Corner
    title_1_bord_1.push_back(Output_con("┓", 0, 79));
    // Top side
    for (int i = 78; i >= 1; --i) {
        title_1_bord_1.push_back(Output_con("━", 0, i));
    }

    preparatory::priv::printcon(title_1_bord_1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Top side
    for (int i = 4; i <= 75; ++i) {
        title_1_bord_2.push_back(Output_con("═", 1, i));
    }
    // Left side
    for (int i = 1; i <= 5; ++i) {
        title_1_bord_2.push_back(Output_con("*", i, 77));
    }
    // Bottom side
    for (int i = 75; i >= 4; --i) {
        title_1_bord_2.push_back(Output_con("═", 5, i));
    }
    // Left side
    for (int i = 5; i >= 1; --i) {
        title_1_bord_2.push_back(Output_con("*", i, 2));
    }

    preparatory::priv::printcon(title_1_bord_2);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    // M
    preparatory::priv::scanner(title_1_text, {"╭", "│", "╵"}, 2, 8);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 9);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 10);
    preparatory::priv::scanner(title_1_text, {"┬", "│", "╵"}, 2, 11);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 12);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 13);
    preparatory::priv::scanner(title_1_text, {"╮", "│", "╵"}, 2, 14);
    preparatory::priv::scanner(title_1_text, {" ", " ", " "}, 2, 15);
    // A
    preparatory::priv::scanner(title_1_text, {"╭", "├", "╵"}, 2, 16);
    preparatory::priv::scanner(title_1_text, {"─", "─", " "}, 2, 17);
    preparatory::priv::scanner(title_1_text, {"─", "─", " "}, 2, 18);
    preparatory::priv::scanner(title_1_text, {"─", "─", " "}, 2, 19);
    preparatory::priv::scanner(title_1_text, {"─", "─", " "}, 2, 20);
    preparatory::priv::scanner(title_1_text, {"╮", "┤", "╵"}, 2, 21);
    preparatory::priv::scanner(title_1_text, {" ", " ", " "}, 2, 22);
    // S
    preparatory::priv::scanner(title_1_text, {"╭", "╰", "╶"}, 2, 23);
    preparatory::priv::scanner(title_1_text, {"─", "─", "─"}, 2, 24);
    preparatory::priv::scanner(title_1_text, {"─", "─", "─"}, 2, 25);
    preparatory::priv::scanner(title_1_text, {"─", "─", "─"}, 2, 26);
    preparatory::priv::scanner(title_1_text, {"╴", "╮", "╯"}, 2, 27);
    preparatory::priv::scanner(title_1_text, {" ", " ", " "}, 2, 28);
    // T
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 29);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 30);
    preparatory::priv::scanner(title_1_text, {"┬", "│", "╵"}, 2, 31);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 32);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 33);
    preparatory::priv::scanner(title_1_text, {" ", " ", " "}, 2, 34);
    // E
    preparatory::priv::scanner(title_1_text, {"┌", "├", "└"}, 2, 35);
    preparatory::priv::scanner(title_1_text, {"─", "─", "─"}, 2, 36);
    preparatory::priv::scanner(title_1_text, {"─", "─", "─"}, 2, 37);
    preparatory::priv::scanner(title_1_text, {"─", "─", "─"}, 2, 38);
    preparatory::priv::scanner(title_1_text, {"╴", "╴", "╴"}, 2, 39);
    preparatory::priv::scanner(title_1_text, {" ", " ", " "}, 2, 40);
    // R
    preparatory::priv::scanner(title_1_text, {"┌", "│", "╵"}, 2, 41);
    preparatory::priv::scanner(title_1_text, {"─", "─", " "}, 2, 42);
    preparatory::priv::scanner(title_1_text, {"─", "─", " "}, 2, 43);
    preparatory::priv::scanner(title_1_text, {"─", "┬", "╰"}, 2, 44);
    preparatory::priv::scanner(title_1_text, {"╮", "╯", "─"}, 2, 45);
    preparatory::priv::scanner(title_1_text, {" ", " ", " "}, 2, 46);
    // M
    preparatory::priv::scanner(title_1_text, {"╭", "│", "╵"}, 2, 47);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 48);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 49);
    preparatory::priv::scanner(title_1_text, {"┬", "│", "╵"}, 2, 50);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 51);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 52);
    preparatory::priv::scanner(title_1_text, {"╮", "│", "╵"}, 2, 53);
    preparatory::priv::scanner(title_1_text, {" ", " ", " "}, 2, 54);
    // I
    preparatory::priv::scanner(title_1_text, {"╶", " ", "╶"}, 2, 55);
    preparatory::priv::scanner(title_1_text, {"─", " ", "─"}, 2, 56);
    preparatory::priv::scanner(title_1_text, {"┬", "│", "┴"}, 2, 57);
    preparatory::priv::scanner(title_1_text, {"─", " ", "─"}, 2, 58);
    preparatory::priv::scanner(title_1_text, {"╴", " ", "╴"}, 2, 59);
    preparatory::priv::scanner(title_1_text, {" ", " ", " "}, 2, 60);
    // N
    preparatory::priv::scanner(title_1_text, {"╭",  "│", "╵"}, 2, 61);
    preparatory::priv::scanner(title_1_text, {"\\", " ", " "}, 2, 62);
    preparatory::priv::scanner(title_1_text, {" ", "\\", " "}, 2, 63);
    preparatory::priv::scanner(title_1_text, {" ", " ", "\\"}, 2, 64);
    preparatory::priv::scanner(title_1_text, {"╷",  "│", "╯"}, 2, 65);
    preparatory::priv::scanner(title_1_text, {" ",  " ", " "}, 2, 66);
    // D
    preparatory::priv::scanner(title_1_text, {"┌", "│", "└"}, 2, 67);
    preparatory::priv::scanner(title_1_text, {"─", " ", "─"}, 2, 68);
    preparatory::priv::scanner(title_1_text, {"─", " ", "─"}, 2, 69);
    preparatory::priv::scanner(title_1_text, {"─", " ", "─"}, 2, 70);
    preparatory::priv::scanner(title_1_text, {"╮", "│", "╯"}, 2, 71);

    preparatory::priv::printcon(title_1_text);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void preparatory::Title::title_screen_2(
    std::vector<Output_con>& title_2_border,
    std::vector<Output_con>& title_2_text
) {
    // Top side, border
    for (int i = 0; i <= 19; ++i) {
        title_2_border.push_back(Output_con("═", 8, (39 + i), 30, false));
        title_2_border.push_back(Output_con("═", 8, (39 - i), 30, true));
    }
    // Top corners, border
    title_2_border.push_back(Output_con("╔", 8, 19, 30, false));
    title_2_border.push_back(Output_con("╗", 8, 59, 30, true));
    // Sides, border
    // Will try a 60 millisecond delay– will that work better?
    for (int i = 0; i <= 3; ++i) {
        title_2_border.push_back(Output_con("║", (9 + i), 19, 60, false));
        title_2_border.push_back(Output_con("║", (9 + i), 59, 60, true));
    }
    // Bottom corners, border
    title_2_border.push_back(Output_con("╚", 13, 19, 30, false));
    title_2_border.push_back(Output_con("╝", 13, 59, 30, true));
    // Bottom side, border
    for (int i = 19; i >= 0; --i) {
        title_2_border.push_back(Output_con("═", 13, (39 + i), 30, false));
        title_2_border.push_back(Output_con("═", 13, (39 - i), 30, true));
    }

    preparatory::priv::printcon(title_2_border);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    preparatory::priv::center_lr(title_2_text, "By:", 9, 120);
    preparatory::priv::center_lr(title_2_text, "<=|   Rex Alphonse Reventar  |=>", 10, 120);
    preparatory::priv::center_lr(title_2_text, "And:", 11, 120);
    preparatory::priv::center_lr(title_2_text, "<=|      Brent Cristobal     |=>", 12, 120);

    preparatory::priv::printcon(title_2_text);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void preparatory::Title::title_screen_3 (
    std::vector<Output_con>& title_3_subtitle,
    std::vector<Output_con>& title_3_border,
    std::vector<Output_con>& title_3_text
) {
    // The subtitle, "current settings"
    preparatory::priv::center_lr(title_3_subtitle, "Current Settings:", 15, 120);

    preparatory::priv::printcon(title_3_subtitle);

    // The borders, in 2 opposite sweeping fashions
    for (int i = 0; i <= 29; ++i) {
        title_3_border.push_back(Output_con("~", 16, (25+i), 15, false));
        title_3_border.push_back(Output_con("~", 19, (54-i), 15, true));
    }

    preparatory::priv::printcon(title_3_border);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    preparatory::priv::center_lr(title_3_text, "No Repeats, Randomized", 17, 500);
    title_3_text.push_back(Output_con("R", 18, 33, FC_info(FC_info::Coloration::Red)));
    title_3_text.push_back(Output_con(" ", 18, 34));
    title_3_text.push_back(Output_con("O", 18, 35, FC_info(FC_info::Coloration::Orange)));
    title_3_text.push_back(Output_con(" ", 18, 36));
    title_3_text.push_back(Output_con("Y", 18, 37, FC_info(FC_info::Coloration::Yellow)));
    title_3_text.push_back(Output_con(" ", 18, 38));
    title_3_text.push_back(Output_con("G", 18, 39, FC_info(FC_info::Coloration::Green)));
    title_3_text.push_back(Output_con(" ", 18, 40));
    title_3_text.push_back(Output_con("B", 18, 41, FC_info(FC_info::Coloration::Blue)));
    title_3_text.push_back(Output_con(" ", 18, 42));
    title_3_text.push_back(Output_con("V", 18, 43, FC_info(FC_info::Coloration::Violet)));

    preparatory::priv::printcon(title_3_text);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

// ==> Auxiliary Functions

void preparatory::priv::printcon(std::vector<Output_con>& outputvec) {
    for (Output_con outputc : outputvec) {
        // Move to the necessary location
        move(outputc.y_dim, outputc.x_dim);
        /*
        // Actually output the thing
        if (outputc.state_mod.given_color == FC_info::Coloration::Naught) {
            //we need to use c_str() because printw is a c-style function
            printw(outputc.output_char.c_str());
        } else {
            attron(COLOR_PAIR(static_cast<int>(outputc.state_mod.given_color)));
            printw(outputc.output_char.c_str());
            attroff(COLOR_PAIR(static_cast<int>(outputc.state_mod.given_color)));
        }
        */

        attron(COLOR_PAIR(static_cast<int>(outputc.state_mod.given_color)));
        printw(outputc.output_char.c_str());
        attroff(COLOR_PAIR(static_cast<int>(outputc.state_mod.given_color)));

        // If we need to return, return
        if (outputc.return_now == true) {
            refresh();
        }

        // Wait for the given time in milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(outputc.wait_time));
    }
}

void preparatory::priv::scanner(
    std::vector <Output_con>& granvec, 
    std::vector <std::string> vecstr, 
    int y_dimu,
    int x_dimu
) {
    for (int i = 0; i < vecstr.size(); ++i) {
        // Likely area for bugs
        if (i != (vecstr.size()-1)) {
            granvec.push_back(Output_con(vecstr[i], (y_dimu + i), x_dimu, round(30.0/vecstr.size()), false));
        } else if (i == (vecstr.size()-1)) {
            granvec.push_back(Output_con(vecstr[i], (y_dimu + i), x_dimu, round(30.0/vecstr.size()), true));
            return;
        }
    }
}

void preparatory::priv::center_lr(
    std::vector <Output_con>& granvec, 
    std::string outstr, 
    int y_dimu,
    int lastwait
) {
    int len = outstr.length();
    // Distance from side
    int dis = 39 - static_cast<int>(floor(len/2.0));
    for (int i = 0; i < len; ++i) {
        std::string s(1, outstr[i]);
        granvec.push_back(Output_con(s, y_dimu, (dis + i)));
        if (i == len-1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(lastwait));
            return;
        }
    }
}