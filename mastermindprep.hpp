#include "ncurses.h"
#include "letssee.hpp"
#include <thread>
#include <chrono>
#include <locale.h>
#include <map>
#include <iterator>

// The structure that will contain the outputted things.
struct Output_con {
    // Will contain color information
    enum class Coloration{
        Naught = 15, 
        Red = 9, 
        Orange = 172, 
        Yellow = 220, 
        Green = 76, 
        Blue = 27, 
        Violet = 92
    };
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
    // a modifier to make it colored
    Coloration given_color; 
    // the color's pair number
    int pair_num;

    // Constructor for Output_con given string and x,y dim
    Output_con(std::string str, int y1, int x1) :
        output_char(str), 
        x_dim(x1), 
        y_dim(y1), 
        wait_time(30), 
        return_now(true),
        given_color(Coloration::Naught) { 
            pair_num = 1;
        }
    // Constructor for Output_con given all except mod
    Output_con(std::string str, int y1, int x1, int wait, bool return_n) :
        output_char(str),
        x_dim(x1),
        y_dim(y1),
        wait_time(wait),
        return_now(return_n),
        given_color(Coloration::Naught) { 
            pair_num = 1;
        }
    // Constructor for Output_con given all
    Output_con(std::string str, int y1, int x1, int wait, bool return_n, Coloration mod) :
        output_char(str),
        x_dim(x1),
        y_dim(y1),
        wait_time(wait),
        return_now(return_n),
        given_color(mod) {
            pair_num = color_table(mod);
        }
    // Constructor given just a color
    Output_con(std::string str, int y1, int x1, Coloration mod) :
        output_char(str),
        x_dim(x1),
        y_dim(y1),
        wait_time(30),
        return_now(true),
        given_color(mod) {
            pair_num = color_table(mod);
        }
    // Look for colors
    int color_table(Coloration col) {
        if (col == Coloration::Naught) {
            return 1;
        } else if (col == Coloration::Red) {
            return 2;
        } else if (col == Coloration::Orange) {
            return 3;
        } else if (col == Coloration::Yellow) {
            return 4;
        } else if (col == Coloration::Green) {
            return 5;
        } else if (col == Coloration::Blue) {
            return 6;
        } else if (col == Coloration::Violet) {
            return 7;
        } else {
            error("Invalid Color");
            return -1;
        }
    }
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

            // Loads the title itself.
            void title_screen_1l(
                std::vector<Output_con>& title_1_bord_1, 
                std::vector<Output_con>& title_1_bord_2, 
                std::vector<Output_con>& title_1_text
            );

            // Prints the title itself.
            void title_screen_1p(
                const std::vector<Output_con>& title_1_bord_1, 
                const std::vector<Output_con>& title_1_bord_2, 
                const std::vector<Output_con>& title_1_text
            );

            // Loads the creators.
            void title_screen_2l(
                std::vector<Output_con>& title_2_border,
                std::vector<Output_con>& title_2_text
            );

            // Prints the creators.
            void title_screen_2p(
                const std::vector<Output_con>& title_2_border,
                const std::vector<Output_con>& title_2_text
            );

            // Loads the current settings.
            void title_screen_3l(
                std::vector<Output_con>& title_3_subtitle,
                std::vector<Output_con>& title_3_border,
                std::vector<Output_con>& title_3_text
            );

            // Prints the current settings.
            void title_screen_3p(
                const std::vector<Output_con>& title_3_subtitle,
                const std::vector<Output_con>& title_3_border,
                const std::vector<Output_con>& title_3_text
            );

            // Loads the menu.
            void title_screen_4l(
                std::vector<Output_con>& title_4_subtitle,
                std::vector<Output_con>& title_4_border,
                std::vector<Output_con>& title_4_text
            );

            // Prints the menu.
            void title_screen_4p(
                const std::vector<Output_con>& title_4_subtitle,
                const std::vector<Output_con>& title_4_border,
                const std::vector<Output_con>& title_4_text
            );
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
        static const int termwidth = 80;

        // Output the outputcons correctly
        void const printcon (const std::vector<Output_con>& outputvec);

        // Pass a vertical vector of Output_cons to printcon.
        // Meant to help with sweeping function.
        void scanner(std::vector <Output_con>& granvec, std::vector <std::string> vecstr, int y_dimu, int x_dimu);

        // Pass a vertical vector of Output_cons to printcon, with color functionality.
        // Created to avoid compatibility problems with the multiple given declarations.
        void scanner(
            std::vector <Output_con>& granvec, 
            std::vector <std::string> vecstr, 
            int y_dimu, 
            int x_dimu, 
            Output_con::Coloration col
        );

        // Center text, and then sweep from left to right.
        void center_lr(std::vector <Output_con>& granvec, std::string outstr, int y_dimu, int lastwait);

        // Center text, whilst also providing colors.
        // Created to avoid compatibility problems with previous declarations.
        void center_lr(
            std::vector <Output_con>& granvec, 
            std::string outstr, 
            int y_dimu, 
            int lastwait, 
            Output_con::Coloration col
        );

        // Pass a string, horizontal, and it's positions.
        void passer_lr(
            std::vector <Output_con>& granvec, 
            std::string outstr, 
            int y_dimu, 
            int x_dimu, 
            int lastwait
        );

        // Pass a string, horizontal, its positions, and the prefered color.
        void passer_lr(
            std::vector <Output_con>& granvec,
            std::string outstr, 
            int y_dimu, 
            int x_dimu, 
            Output_con::Coloration col
        );

        // Pass a string, horizontal, its positions, the last wait, and the prefered color.
        void passer_lr(
            std::vector <Output_con>& granvec,
            std::string outstr, 
            int y_dimu, 
            int x_dimu, 
            int lastwait,
            Output_con::Coloration col
        );
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
    
    // The title itself
    preparatory::Title::title_screen_1l(
        preparatory::Title::title_1_bord_1,
        preparatory::Title::title_1_bord_2,
        preparatory::Title::title_1_text
    );

    preparatory::Title::title_screen_1p(
        preparatory::Title::title_1_bord_1,
        preparatory::Title::title_1_bord_2,
        preparatory::Title::title_1_text
    );

    // The creator boxes
    preparatory::Title::title_screen_2l(
        preparatory::Title::title_2_border,
        preparatory::Title::title_2_text
    );

    preparatory::Title::title_screen_2p(
        preparatory::Title::title_2_border,
        preparatory::Title::title_2_text
    );

    // The Current Settings
    // TODO: make the current settings actual settings
    preparatory::Title::title_screen_3l(
        preparatory::Title::title_3_subtitle,
        preparatory::Title::title_3_border,
        preparatory::Title::title_3_text
    );

    preparatory::Title::title_screen_3p(
        preparatory::Title::title_3_subtitle,
        preparatory::Title::title_3_border,
        preparatory::Title::title_3_text
    );

    // The switching option
    preparatory::Title::title_screen_4l(
        preparatory::Title::title_4_subtitle,
        preparatory::Title::title_4_border,
        preparatory::Title::title_4_text
    );

    preparatory::Title::title_screen_4p(
        preparatory::Title::title_4_subtitle,
        preparatory::Title::title_4_border,
        preparatory::Title::title_4_text
    );

    // Move on to next part of screen
	refresh();
	getch();
}

// ==> Loaders

void preparatory::Title::title_screen_1l(
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

    // Border 1
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

    // Border 2
    // Top side
    for (int i = 4; i <= 75; ++i) {
        title_1_bord_2.push_back(Output_con("═", 1, i, Output_con::Coloration::Violet));
    }
    // Left side
    for (int i = 1; i <= 5; ++i) {
        title_1_bord_2.push_back(Output_con("*", i, 77, Output_con::Coloration::Violet));
    }
    // Bottom side
    for (int i = 75; i >= 4; --i) {
        title_1_bord_2.push_back(Output_con("═", 5, i, Output_con::Coloration::Violet));
    }
    // Left side
    for (int i = 5; i >= 1; --i) {
        title_1_bord_2.push_back(Output_con("*", i, 2, Output_con::Coloration::Violet));
    }
    
    // Title Itself
    // M
    preparatory::priv::scanner(title_1_text, {"╭", "│", "╵"}, 2, 8, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 9, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 10, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"┬", "│", "╵"}, 2, 11, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 12, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 13, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"╮", "│", "╵"}, 2, 14, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {" ", " ", " "}, 2, 15, Output_con::Coloration::Yellow);
    // A
    preparatory::priv::scanner(title_1_text, {"╭", "├", "╵"}, 2, 16, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", "─", " "}, 2, 17, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", "─", " "}, 2, 18, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", "─", " "}, 2, 19, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", "─", " "}, 2, 20, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"╮", "┤", "╵"}, 2, 21, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {" ", " ", " "}, 2, 22, Output_con::Coloration::Yellow);
    // S
    preparatory::priv::scanner(title_1_text, {"╭", "╰", "╶"}, 2, 23, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", "─", "─"}, 2, 24, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", "─", "─"}, 2, 25, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", "─", "─"}, 2, 26, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"╴", "╮", "╯"}, 2, 27, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {" ", " ", " "}, 2, 28, Output_con::Coloration::Yellow);
    // T
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 29, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 30, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"┬", "│", "╵"}, 2, 31, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 32, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 33, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {" ", " ", " "}, 2, 34, Output_con::Coloration::Yellow);
    // E
    preparatory::priv::scanner(title_1_text, {"┌", "├", "└"}, 2, 35, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", "─", "─"}, 2, 36, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", "─", "─"}, 2, 37, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", "─", "─"}, 2, 38, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"╴", "╴", "╴"}, 2, 39, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {" ", " ", " "}, 2, 40, Output_con::Coloration::Yellow);
    // R
    preparatory::priv::scanner(title_1_text, {"┌", "│", "╵"}, 2, 41, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", "─", " "}, 2, 42, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", "─", " "}, 2, 43, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", "┬", "╰"}, 2, 44, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"╮", "╯", "─"}, 2, 45, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {" ", " ", " "}, 2, 46, Output_con::Coloration::Yellow);
    // M
    preparatory::priv::scanner(title_1_text, {"╭", "│", "╵"}, 2, 47, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 48, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 49, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"┬", "│", "╵"}, 2, 50, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 51, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", " ", " "}, 2, 52, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"╮", "│", "╵"}, 2, 53, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {" ", " ", " "}, 2, 54, Output_con::Coloration::Yellow);
    // I
    preparatory::priv::scanner(title_1_text, {"╶", " ", "╶"}, 2, 55, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", " ", "─"}, 2, 56, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"┬", "│", "┴"}, 2, 57, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", " ", "─"}, 2, 58, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"╴", " ", "╴"}, 2, 59, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {" ", " ", " "}, 2, 60, Output_con::Coloration::Yellow);
    // N
    preparatory::priv::scanner(title_1_text, {"╭",  "│", "╵"}, 2, 61, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"\\", " ", " "}, 2, 62, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {" ", "\\", " "}, 2, 63, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {" ", " ", "\\"}, 2, 64, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"╷",  "│", "╯"}, 2, 65, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {" ",  " ", " "}, 2, 66, Output_con::Coloration::Yellow);
    // D
    preparatory::priv::scanner(title_1_text, {"┌", "│", "└"}, 2, 67, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", " ", "─"}, 2, 68, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", " ", "─"}, 2, 69, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"─", " ", "─"}, 2, 70, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(title_1_text, {"╮", "│", "╯"}, 2, 71, Output_con::Coloration::Yellow);
}

void preparatory::Title::title_screen_2l(
    std::vector<Output_con>& title_2_border,
    std::vector<Output_con>& title_2_text
) {
    // Top side, border
    for (int i = 0; i <= 19; ++i) {
        title_2_border.push_back(Output_con("═", 8, (39 + i), 30, false, Output_con::Coloration::Blue));
        title_2_border.push_back(Output_con("═", 8, (39 - i), 30, true, Output_con::Coloration::Blue));
    }
    // Top corners, border
    title_2_border.push_back(Output_con("╔", 8, 19, 30, false, Output_con::Coloration::Blue));
    title_2_border.push_back(Output_con("╗", 8, 59, 30, true, Output_con::Coloration::Blue));
    // Sides, border
    // Will try a 60 millisecond delay– will that work better?
    for (int i = 0; i <= 3; ++i) {
        title_2_border.push_back(Output_con("║", (9 + i), 19, 60, false, Output_con::Coloration::Blue));
        title_2_border.push_back(Output_con("║", (9 + i), 59, 60, true, Output_con::Coloration::Blue));
    }
    // Bottom corners, border
    title_2_border.push_back(Output_con("╚", 13, 19, 30, false, Output_con::Coloration::Blue));
    title_2_border.push_back(Output_con("╝", 13, 59, 30, true, Output_con::Coloration::Blue));
    // Bottom side, border
    for (int i = 19; i >= 0; --i) {
        title_2_border.push_back(Output_con("═", 13, (39 + i), 30, false, Output_con::Coloration::Blue));
        title_2_border.push_back(Output_con("═", 13, (39 - i), 30, true, Output_con::Coloration::Blue));
    }

    // Text
    preparatory::priv::center_lr(title_2_text, "By:", 9, 120, Output_con::Coloration::Orange);
    preparatory::priv::center_lr(title_2_text, "<=|   Rex Alphonse Reventar  |=>", 10, 120, Output_con::Coloration::Orange);
    preparatory::priv::center_lr(title_2_text, "And:", 11, 120, Output_con::Coloration::Orange);
    preparatory::priv::center_lr(title_2_text, "<=|      Brent Cristobal     |=>", 12, 120, Output_con::Coloration::Orange);
}

void preparatory::Title::title_screen_3l (
    std::vector<Output_con>& title_3_subtitle,
    std::vector<Output_con>& title_3_border,
    std::vector<Output_con>& title_3_text
) {
    // The subtitle, "current settings"
    preparatory::priv::center_lr(title_3_subtitle, "Current Settings:", 15, 120);

    // The borders, in 2 opposite sweeping fashions
    for (int i = 0; i <= 29; ++i) {
        title_3_border.push_back(Output_con("~", 16, (25+i), 15, false));
        title_3_border.push_back(Output_con("~", 19, (54-i), 15, true));
    }

    // The ROYGBIV Part
    preparatory::priv::center_lr(title_3_text, "No Repeats, Randomized", 17, 500);
    title_3_text.push_back(Output_con("R", 18, 34, Output_con::Coloration::Red));
    title_3_text.push_back(Output_con(" ", 18, 35));
    title_3_text.push_back(Output_con("O", 18, 36, Output_con::Coloration::Orange));
    title_3_text.push_back(Output_con(" ", 18, 37));
    title_3_text.push_back(Output_con("Y", 18, 38, Output_con::Coloration::Yellow));
    title_3_text.push_back(Output_con(" ", 18, 39));
    title_3_text.push_back(Output_con("G", 18, 40, Output_con::Coloration::Green));
    title_3_text.push_back(Output_con(" ", 18, 41));
    title_3_text.push_back(Output_con("B", 18, 42, Output_con::Coloration::Blue));
    title_3_text.push_back(Output_con(" ", 18, 43));
    title_3_text.push_back(Output_con("V", 18, 44, Output_con::Coloration::Violet));
}

void preparatory::Title::title_screen_4l(
    std::vector<Output_con>& title_4_subtitle,
    std::vector<Output_con>& title_4_border,
    std::vector<Output_con>& title_4_text
) {
    // The subtitle
    preparatory::priv::center_lr(
        title_4_subtitle, 
        "Press any arrow key, then enter, to make a selection.", 
        20, 
        120,
        Output_con::Coloration::Green
    );

    // The first column
    preparatory::priv::scanner(title_4_border, {"┈", "┊", "┈"}, 21, 11, Output_con::Coloration::Red);
    // The next 2 rows
    for (int i = 0; i <= 17; ++i) {
        title_4_border.push_back(Output_con("┈", 21, (12+i), 30, false, Output_con::Coloration::Red));
        title_4_border.push_back(Output_con("┈", 23, (12+i), 30, true, Output_con::Coloration::Red));
    }
    // the next column
    preparatory::priv::scanner(title_4_border, {"┈", "┊", "┈"}, 21, 29, Output_con::Coloration::Red);
    // The next rows
    for (int i = 0; i <= 17; ++i) {
        title_4_border.push_back(Output_con("┈", 21, (30+i), 30, false, Output_con::Coloration::Red));
        title_4_border.push_back(Output_con("┈", 23, (30+i), 30, true, Output_con::Coloration::Red));
    }
    // the next column
    preparatory::priv::scanner(title_4_border, {"┈", "┊", "┈"}, 21, 47, Output_con::Coloration::Red);
    // The next rows
    for (int i = 0; i <= 17; ++i) {
        title_4_border.push_back(Output_con("┈", 21, (48+i), 30, false, Output_con::Coloration::Red));
        title_4_border.push_back(Output_con("┈", 23, (48+i), 30, true, Output_con::Coloration::Red));
    }
    // the last column
    preparatory::priv::scanner(title_4_border, {"┈", "┊", "┈"}, 21, 66, Output_con::Coloration::Red);

    // The words
    preparatory::priv::passer_lr(title_4_text, "Settings: ", 22, 15, Output_con::Coloration::Green);
    preparatory::priv::passer_lr(title_4_text, "Help: ", 22, 33, Output_con::Coloration::Green);
    preparatory::priv::passer_lr(title_4_text, "Play! ", 22, 51, 60, Output_con::Coloration::Green);
}

// ==> Printing Functions

void preparatory::Title::title_screen_1p(
    const std::vector<Output_con>& title_1_bord_1, 
    const std::vector<Output_con>& title_1_bord_2, 
    const std::vector<Output_con>& title_1_text
) {
    preparatory::priv::printcon(title_1_bord_1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    preparatory::priv::printcon(title_1_bord_2);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    preparatory::priv::printcon(title_1_text);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void preparatory::Title::title_screen_2p (
    const std::vector<Output_con>& title_2_border,
    const std::vector<Output_con>& title_2_text
) {
    preparatory::priv::printcon(title_2_border);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    preparatory::priv::printcon(title_2_text);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void preparatory::Title::title_screen_3p (
    const std::vector<Output_con>& title_3_subtitle,
    const std::vector<Output_con>& title_3_border,
    const std::vector<Output_con>& title_3_text
) {
    preparatory::priv::printcon(title_3_subtitle);

    preparatory::priv::printcon(title_3_border);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    preparatory::priv::printcon(title_3_text);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void preparatory::Title::title_screen_4p(
    const std::vector<Output_con>& title_4_subtitle,
    const std::vector<Output_con>& title_4_border,
    const std::vector<Output_con>& title_4_text
) {
    preparatory::priv::printcon(title_4_subtitle);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    preparatory::priv::printcon(title_4_border);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    preparatory::priv::printcon(title_4_text);
}

// ==> Auxiliary Functions

void const preparatory::priv::printcon(const std::vector<Output_con>& outputvec) {
    for (Output_con outputc : outputvec) {
        // Move to the necessary location
        move(outputc.y_dim, outputc.x_dim);
        
        init_pair(outputc.pair_num, static_cast<int>(outputc.given_color), 0);
        attron(COLOR_PAIR(outputc.pair_num));
        printw(outputc.output_char.c_str());
        attroff(COLOR_PAIR(outputc.pair_num));

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

void preparatory::priv::scanner(
    std::vector <Output_con>& granvec, 
    std::vector <std::string> vecstr, 
    int y_dimu, 
    int x_dimu, 
    Output_con::Coloration col
) {
    for (int i = 0; i < vecstr.size(); ++i) {
        if (i != (vecstr.size()-1)) {
            granvec.push_back(Output_con(vecstr[i], (y_dimu + i), x_dimu, round(30.0/vecstr.size()), false, col));
        } else if (i == (vecstr.size()-1)) {
            granvec.push_back(Output_con(vecstr[i], (y_dimu + i), x_dimu, round(30.0/vecstr.size()), true, col));
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

void preparatory::priv::center_lr(
    std::vector <Output_con>& granvec, 
    std::string outstr, 
    int y_dimu, 
    int lastwait, 
    Output_con::Coloration col
) {
    int len = outstr.length();
    // Distance from side
    int dis = 39 - static_cast<int>(floor(len/2.0));
    for (int i = 0; i < len; ++i) {
        std::string s(1, outstr[i]);
        granvec.push_back(Output_con(s, y_dimu, (dis + i), col));
        if (i == len-1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(lastwait));
            return;
        }
    }
}

void preparatory::priv::passer_lr(
    std::vector <Output_con>& granvec, 
    std::string outstr, 
    int y_dimu, 
    int x_dimu, 
    int lastwait
) {
    for (int i = 0; i < outstr.length(); ++i) {
        std::string s(1, outstr[i]);
        granvec.push_back(Output_con(s, y_dimu, (x_dimu + i)));
        if (i == (outstr.length() - 1)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(lastwait));
            return;
        }
    }
}

void preparatory::priv::passer_lr(
    std::vector <Output_con>& granvec, 
    std::string outstr, 
    int y_dimu, 
    int x_dimu, 
    Output_con::Coloration col
) {
    for (int i = 0; i < outstr.length(); ++i) {
        std::string s(1, outstr[i]);
        granvec.push_back(Output_con(s, y_dimu, (x_dimu + i), col));
        
        if (i == (outstr.length() - 1)) {
            return;
        }
        
    }
}

void preparatory::priv::passer_lr(
    std::vector <Output_con>& granvec, 
    std::string outstr, 
    int y_dimu, 
    int x_dimu, 
    int lastwait,
    Output_con::Coloration col
) {
    for (int i = 0; i < outstr.length(); ++i) {
        std::string s(1, outstr[i]);
        granvec.push_back(Output_con(s, y_dimu, (x_dimu + i), col));
        if (i == (outstr.length() - 1)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(lastwait));
            return;
        }
    }
}