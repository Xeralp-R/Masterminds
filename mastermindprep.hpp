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
    // Will contain attribute information
    enum class Attribute{
        Naught = 0,
        Reversed
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
    // a modifier to give an attribute
    Attribute given_attr;
    // the color's pair number
    int pair_num;

    // Constructor for Output_con given string and x,y dim
    Output_con(std::string str, int y1, int x1) :
        output_char(str), 
        x_dim(x1), 
        y_dim(y1), 
        wait_time(30), 
        return_now(true),
        given_color(Coloration::Naught),
        given_attr(Attribute::Naught) { 
            pair_num = 1;
        }
    // Constructor for Output_con given all except mod
    Output_con(std::string str, int y1, int x1, int wait, bool return_n) :
        output_char(str),
        x_dim(x1),
        y_dim(y1),
        wait_time(wait),
        return_now(return_n),
        given_color(Coloration::Naught),
        given_attr(Attribute::Naught) { 
            pair_num = 1;
        }
    // Constructor for Output_con given all
    Output_con(std::string str, int y1, int x1, int wait, bool return_n, Coloration mod) :
        output_char(str),
        x_dim(x1),
        y_dim(y1),
        wait_time(wait),
        return_now(return_n),
        given_color(mod),
        given_attr(Attribute::Naught){
            pair_num = color_table(mod);
        }
    // Constructor for Output_con given all
    Output_con(std::string str, int y1, int x1, int wait, bool return_n, Coloration mod, Attribute attr) :
        output_char(str),
        x_dim(x1),
        y_dim(y1),
        wait_time(wait),
        return_now(return_n),
        given_color(mod),
        given_attr(attr){
            pair_num = color_table(mod);
        }
    // Constructor given just a color
    Output_con(std::string str, int y1, int x1, Coloration mod) :
        output_char(str),
        x_dim(x1),
        y_dim(y1),
        wait_time(30),
        return_now(true),
        given_color(mod),
        given_attr(Attribute::Naught) {
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

// The vector that will contain all of the valid inputs.
std::vector<std::string> valid_tokens = {"R", "O", "Y", "G", "B", "V"};

// The namespace that will contain all of the preparatory functions.
namespace preparatory {
    // The first preparatory function, before starting ncurses.
    void antecedent();

    // begin ncurses
    void begin_ncurses();

    // end ncurses
    void end_ncurses();

    // The general, overarching preparatory function.
    void startup();
    
    class Title {
        public:
            // Constructor.
            //Title();

            // The enum class that will state which of the title states is correct.
            enum class Title_state {
                Settings,
                Help,
                Play
            };

            // Load the input screen
            void title_screen_load();

            // Prints the title screen and accept the inputs given to it.
            preparatory::Title::Title_state title_screen_print();

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
                std::vector<Output_con>& title_4_border
            );

            // Prints the menu.
            void title_screen_4p(
                const std::vector<Output_con>& title_4_subtitle,
                const std::vector<Output_con>& title_4_border
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

            // print out the title state
            void choice_printer(Title::Title_state given_choice, std::vector<Output_con>& granvec);
    };

    class Help {
        public:
            // Constructor?
            // Help();

            // The enum class that will contain the choice of help
            enum class Help_state {
                // The first page of the explainer
                Explain_1,
                // The second page of the explainer
                Explain_2,
                // Explain how to play this implementation
                Refresh,
                // Back to the help screen
                Help_screen,
                // Back to the title screen
                Title_screen
            };

            // Load the help screen unpon instantiating
            void help_screen_load();

            // the interface for the player when interacting with the help screen
            void help_screen_inter();

            // a "destructor"– clear out all the variables
            void help_screen_clear();
        private:
            // loads the title portion
            void help_screen_1l(
                std::vector<Output_con>& help_1_border,
                std::vector<Output_con>& help_1_text
            );

            // load the menu border
            void help_screen_2l(
                std::vector<Output_con>& help_2_border
            );

            // loads the explain bit
            void help_screen_34l(
                std::vector<Output_con>& help_3_mtext,
                std::vector<Output_con>& help_4_mtext,
                std::vector<Output_con>& help_34_border
            );

            // loads the refresher
            void help_screen_5l(
                std::vector<Output_con>& help_5_mtext,
                std::vector<Output_con>& help_5_border
            );

            // prints the title portion in its own window
            void help_screen_1p(
                const std::vector<Output_con>& help_1_border,
                const std::vector<Output_con>& help_1_text,
                WINDOW * given_win
            );

            // print the menu border
            void help_screen_2p(
                const std::vector<Output_con>& help_2_border,
                WINDOW * given_win
            );

            // prints the explain part 1
            void help_screen_3p(
                const std::vector<Output_con>& help_3_mtext,
                const std::vector<Output_con>& help_34_border,
                WINDOW * given_win
            );

            // prints the explain part 2
            void help_screen_4p(
                const std::vector<Output_con>& help_4_mtext,
                const std::vector<Output_con>& help_34_border,
                WINDOW * given_win
            );

            // prints the refreshervoid 
            void help_screen_5p(
                const std::vector<Output_con>& help_5_mtext,
                const std::vector<Output_con>& help_5_border,
                WINDOW * given_win
            );

            // govern the input of entries into the first explain screen
            // return the passed enum class
            Help_state help_screen_explain_1(
                WINDOW * given_win
            );

            // govern the input of entries into the second explain screen
            // return whether the user decided to go out or not
            bool help_screen_explain_2(
                WINDOW * given_win
            );

            // govern the input of entry into the refresher screen
            // upon returning, go back to running the help screen
            void help_screen_refresher(
                WINDOW * given_win
            );

            // vectors that will containt the title stuff
            std::vector<Output_con> help_1_border {};
            std::vector<Output_con> help_1_text {};

            // vectors that will contain the main menu
            std::vector<Output_con> help_2_border {};
            std::vector<Output_con> help_2_text {};

            // vectors that will contain the explain part 1
            std::vector<Output_con> help_3_mtext {};
            std::vector<Output_con> help_34_border {}; // for both 3 and 4
            std::vector<Output_con> help_3_stext {};

            // vectors that will contain the explain part 2
            std::vector<Output_con> help_4_mtext {};
            std::vector<Output_con> help_4_stext {};

            // vectors that will contain the refresher
            std::vector<Output_con> help_5_mtext {};
            std::vector<Output_con> help_5_border {};
            std::vector<Output_con> help_5_stext {};

            // print out the title state
            void main_choice_printer(
                Help::Help_state given_choice, 
                std::vector<Output_con>& granvec,
                WINDOW * given_win
            );

            // load and print out the state of the 1st explain screen
            void help_choice_printer_1(
                Help::Help_state given_choice,
                std::vector<Output_con>& granvec,
                WINDOW * given_win
            );

            // load and print out the state of the second explain screen
            void help_choice_printer_2(
                Help::Help_state given_choice,
                std::vector<Output_con>& granvec,
                WINDOW * given_win
            );
    };

    // All of the private data that needs to be kept away from mastermind.
    // Primarily helper functions and other such things.
    namespace priv {
        int terminal_x = -1, terminal_y = -1;

        // The required termwidth.
        static const int termwidth = 80;

        // Output the outputcons correctly
        void const printcon (const std::vector<Output_con>& outputvec);

        // Output the outputcons to a window
        void const wprintcon (WINDOW * given_win, const std::vector<Output_con>& outputvec);

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
        
        // Center text, and provide color, atribute, will_return, and many more!
        // No last wait, though– I don't think there's a need for it.
        void center_lr(
            std::vector <Output_con>& granvec, 
            std::string outstr, 
            int y_dimu, 
            Output_con::Coloration col,
            Output_con::Attribute attri,
            bool will_return
        );

        // Pass a string, horizontal, and it's positions.
        // For documentation processes.
        void passer_lr(
            std::vector <Output_con>& granvec, 
            std::string outstr, 
            int y_dimu, 
            int x_dimu, 
            int lastwait
        );

        // Pass a string, horizontal, its positions, and the prefered color, and more.
        void passer_lr(
            std::vector <Output_con>& granvec,
            std::string outstr, 
            int y_dimu, 
            int x_dimu, 
            Output_con::Coloration col,
            Output_con::Attribute attri,
            bool will_return
        );

        // Load in the valid tokens with the correct colors
        void valid_color_loader(
            std::vector <Output_con>& granvec,
            const std::vector<std::string>& valid_tokens,
            int y_dimu
        );
    }

    // * load in the alphabet in large 3-pixel height letters
    namespace alpha {
        void letter_a(
            std::vector<Output_con>& granvec,
            int y_dimu,
            int x_dimu,
            Output_con::Coloration col
        );

        void letter_d(
            std::vector<Output_con>& granvec,
            int y_dimu,
            int x_dimu,
            Output_con::Coloration col
        );

        void letter_e(
            std::vector<Output_con>& granvec,
            int y_dimu,
            int x_dimu,
            Output_con::Coloration col
        );

        void letter_h(
            std::vector<Output_con>& granvec,
            int y_dimu,
            int x_dimu,
            Output_con::Coloration col
        );

        void letter_i(
            std::vector<Output_con>& granvec,
            int y_dimu,
            int x_dimu,
            Output_con::Coloration col
        );

        void letter_l(
            std::vector<Output_con>& granvec,
            int y_dimu,
            int x_dimu,
            Output_con::Coloration col
        );


        void letter_m(
            std::vector<Output_con>& granvec,
            int y_dimu,
            int x_dimu,
            Output_con::Coloration col
        );

        void letter_n(
            std::vector<Output_con>& granvec,
            int y_dimu,
            int x_dimu,
            Output_con::Coloration col
        );

        void letter_p(
            std::vector<Output_con>& granvec,
            int y_dimu,
            int x_dimu,
            Output_con::Coloration col
        );

        void letter_r(
            std::vector<Output_con>& granvec,
            int y_dimu,
            int x_dimu,
            Output_con::Coloration col
        );

        void letter_s(
            std::vector<Output_con>& granvec,
            int y_dimu,
            int x_dimu,
            Output_con::Coloration col
        );

        void letter_t(
            std::vector<Output_con>& granvec,
            int y_dimu,
            int x_dimu,
            Output_con::Coloration col
        );
    };
}

// ==> Grand Definitions

void preparatory::antecedent() {
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
}

void preparatory::begin_ncurses () {
    // call NCURSES
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
    
    // Start colors
    start_color();

    // Make screen white on black
    wbkgd(stdscr, COLOR_PAIR(1));

    // get all characters
    cbreak();

    // ensure that the escape characters don't get printed
    noecho();

    // let's get our arrow keys
    keypad(stdscr, true);
}

void preparatory::end_ncurses () {
    refresh();
    curs_set(1);
    getch();
    endwin();
}

void preparatory::startup() {
    // prepare the game title
    preparatory::Title Game_Title;

    // load the title creen
    Game_Title.preparatory::Title::title_screen_load();
    // print the title screen
    preparatory::Title::Title_state titular_state = Game_Title.preparatory::Title::title_screen_print();

    bool game_passant = false;

    while (!game_passant) {
        if (titular_state == preparatory::Title::Title_state::Help) {
            // prepare the help screen
            preparatory::Help Game_Help;

            // load the help screen
            Game_Help.preparatory::Help::help_screen_load();

            // interface with the help screen
            Game_Help.preparatory::Help::help_screen_inter();

            // destroy all variables in preparation for another run
            Game_Help.preparatory::Help::help_screen_clear();
        } else if (titular_state == preparatory::Title::Title_state::Settings) {
            // The settings screen
        } else if (titular_state == preparatory::Title::Title_state::Play) {
            game_passant = true;
            return;
            //break;
        }
        if (game_passant == false) {
            // clear the standard screen
            wclear(stdscr);
            // print the title screen again
            titular_state = Game_Title.preparatory::Title::title_screen_print();
        }
    }
}

// ==> Title Functions

void preparatory::Title::title_screen_load() {
    // The title itself
    preparatory::Title::title_screen_1l(
        preparatory::Title::title_1_bord_1,
        preparatory::Title::title_1_bord_2,
        preparatory::Title::title_1_text
    );

    // The creator boxes
    preparatory::Title::title_screen_2l(
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

    // The switching option
    preparatory::Title::title_screen_4l(
        preparatory::Title::title_4_subtitle,
        preparatory::Title::title_4_border
    );
}

preparatory::Title::Title_state preparatory::Title::title_screen_print() {

    curs_set(0);
    
    // The title itself
    preparatory::Title::title_screen_1p(
        preparatory::Title::title_1_bord_1,
        preparatory::Title::title_1_bord_2,
        preparatory::Title::title_1_text
    );

    // The creator boxes
    preparatory::Title::title_screen_2p(
        preparatory::Title::title_2_border,
        preparatory::Title::title_2_text
    );

    // The Current Settings
    preparatory::Title::title_screen_3p(
        preparatory::Title::title_3_subtitle,
        preparatory::Title::title_3_border,
        preparatory::Title::title_3_text
    );

    // The switching option
    preparatory::Title::title_screen_4p(
        preparatory::Title::title_4_subtitle,
        preparatory::Title::title_4_border
    );

    // state the default choice
    preparatory::Title::Title_state given_choice = preparatory::Title::Title_state::Play;

    // print out title_state the first time, with default choice
    preparatory::Title::choice_printer(given_choice, preparatory::Title::title_4_text);

    // int that will contain the input? I have no clue, but that's how it works, I guess.
    int given_switcher = 0;

    // bool that will state whether to get out of the loop and go to another screen
    bool got_in = false;

    while(!got_in) {
        // get the person's choice
        given_switcher = getch();

        switch(given_switcher) {
            // if the user entered left
            case KEY_LEFT:
                // switch each value to the one on the left
                if (given_choice == preparatory::Title::Title_state::Play) {
                    given_choice = preparatory::Title::Title_state::Help;
                } else if (given_choice == preparatory::Title::Title_state::Help) {
                    given_choice = preparatory::Title::Title_state::Settings;
                } else if (given_choice == preparatory::Title::Title_state::Settings) {
                    given_choice = preparatory::Title::Title_state::Play;
                }
                // make out the change
                preparatory::Title::choice_printer(given_choice, preparatory::Title::title_4_text);
                break;
            case KEY_RIGHT:
                // switch each value to the one on the right
                if (given_choice == preparatory::Title::Title_state::Play) {
                    given_choice = preparatory::Title::Title_state::Settings;
                } else if (given_choice == preparatory::Title::Title_state::Help) {
                    given_choice = preparatory::Title::Title_state::Play;
                } else if (given_choice == preparatory::Title::Title_state::Settings) {
                    given_choice = preparatory::Title::Title_state::Help;
                }
                // make out the change
                preparatory::Title::choice_printer(given_choice, preparatory::Title::title_4_text);
                break;
            case 10: // char(10) is the return, or endl
                got_in = true;
                break;
        }
    }

    return given_choice;

    // Move on to next part of screen
	//refresh();
	//getch();
    //curs_set(1);
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
    preparatory::alpha::letter_m(title_1_text, 2, 8, Output_con::Coloration::Yellow);
    // A
    preparatory::alpha::letter_a(title_1_text, 2, 16, Output_con::Coloration::Yellow);
    // S
    preparatory::alpha::letter_s(title_1_text, 2, 23, Output_con::Coloration::Yellow);
    // T
    preparatory::alpha::letter_t(title_1_text, 2, 29, Output_con::Coloration::Yellow);
    // E
    preparatory::alpha::letter_e(title_1_text, 2, 35, Output_con::Coloration::Yellow);
    // R
    preparatory::alpha::letter_r(title_1_text, 2, 41, Output_con::Coloration::Yellow);
    // M
    preparatory::alpha::letter_m(title_1_text, 2, 47, Output_con::Coloration::Yellow);
    // I
    preparatory::alpha::letter_i(title_1_text, 2, 55, Output_con::Coloration::Yellow);
    // N
    preparatory::alpha::letter_n(title_1_text, 2, 61, Output_con::Coloration::Yellow);
    // D
    preparatory::alpha::letter_d(title_1_text, 2, 67, Output_con::Coloration::Yellow);
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
    preparatory::priv::valid_color_loader(title_3_text, valid_tokens, 18);
}

void preparatory::Title::title_screen_4l(
    std::vector<Output_con>& title_4_subtitle,
    std::vector<Output_con>& title_4_border
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
    /*
    // The words
    preparatory::priv::passer_lr(title_4_text, "Settings: ", 22, 15, Output_con::Coloration::Green);
    preparatory::priv::passer_lr(title_4_text, "Help: ", 22, 33, Output_con::Coloration::Green);
    preparatory::priv::passer_lr(title_4_text, "Play! ", 22, 51, 60, Output_con::Coloration::Green);
    */
}

// ==> Title Printing Functions

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
    const std::vector<Output_con>& title_4_border
) {
    preparatory::priv::printcon(title_4_subtitle);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    preparatory::priv::printcon(title_4_border);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    /*
    preparatory::priv::printcon(title_4_text);
    */
}

void preparatory::Title::choice_printer(
    Title::Title_state given_choice,
    std::vector<Output_con>& granvec
) {
    if (given_choice == preparatory::Title::Title_state::Settings) {
        preparatory::priv::passer_lr(
            granvec,
            "Settings:",
            22,
            16,
            Output_con::Coloration::Green,
            Output_con::Attribute::Reversed,
            false
        );
        preparatory::priv::passer_lr(
            granvec,
            "Help:",
            22,
            36,
            Output_con::Coloration::Green,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::passer_lr(
            granvec,
            "Game!",
            22,
            54,
            Output_con::Coloration::Green,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::printcon(granvec);
        granvec.clear();
    } else if (given_choice == preparatory::Title::Title_state::Help) {
        preparatory::priv::passer_lr(
            granvec,
            "Settings:",
            22,
            16,
            Output_con::Coloration::Green,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::passer_lr(
            granvec,
            "Help:",
            22,
            36,
            Output_con::Coloration::Green,
            Output_con::Attribute::Reversed,
            false
        );
        preparatory::priv::passer_lr(
            granvec,
            "Game!",
            22,
            54,
            Output_con::Coloration::Green,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::printcon(granvec);
        granvec.clear();
    } else if (given_choice == preparatory::Title::Title_state::Play) {
        preparatory::priv::passer_lr(
            granvec,
            "Settings:",
            22,
            16,
            Output_con::Coloration::Green,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::passer_lr(
            granvec,
            "Help:",
            22,
            36,
            Output_con::Coloration::Green,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::passer_lr(
            granvec,
            "Game!",
            22,
            54,
            Output_con::Coloration::Green,
            Output_con::Attribute::Reversed,
            false
        );
        preparatory::priv::printcon(granvec);
        granvec.clear();
    }
}

// ==> Help Functions

void preparatory::Help::help_screen_load() {
    // load the top of the help screen:
    help_screen_1l(help_1_border, help_1_text);

    // load the subtitles and choices and stuff
    help_screen_2l(help_2_border);

    // load the explain pages
    help_screen_34l(
        help_3_mtext,
        help_4_mtext,
        help_34_border
    );

    // load the refresher page
    help_screen_5l(
        help_5_mtext,
        help_5_border
    );
}

void preparatory::Help::help_screen_inter() {
    // clear the rest of the screen
    wclear(stdscr);

    // create the window for the top
    //! Possible location for bugs!
    WINDOW * Help_Titular;
    Help_Titular = newwin(7, 80, 0, 0);

    WINDOW * Help_Primary;
    Help_Primary = newwin(17, 80, 7, 0);

    // get our arrow keys for help primary?
    keypad(Help_Primary, true);

    // Make screen white on black
    // wbkgd(stdscr, COLOR_PAIR(1));

    // bool that will declare whether we go back to main
    bool reenter_main = false;

    // place outside because this will only load once
    help_screen_1p(
        preparatory::Help::help_1_border, 
        preparatory::Help::help_1_text, 
        Help_Titular
    );

    // the governing while loop
    while (!reenter_main) {

        // print out the help screen
        help_screen_2p(
            preparatory::Help::help_2_border,
            Help_Primary
        );

        // prepare the default game state
        preparatory::Help::Help_state given_help_state_1 = preparatory::Help::Help_state::Explain_1;

        // print out the choice
        main_choice_printer(given_help_state_1, help_2_text, Help_Primary);

        // int that will contain the input?
        int given_help_switcher_1 = 0;

        // bool that will state whether to get out of the loop and go to another screen
        bool help_got_in_1 = false;

        while (!help_got_in_1) {    
            given_help_switcher_1 = wgetch(Help_Primary);

            switch(given_help_switcher_1) {
                case KEY_UP:
                    if (given_help_state_1 == preparatory::Help::Help_state::Explain_1) {
                        given_help_state_1 = preparatory::Help::Help_state::Title_screen;
                    } else if (given_help_state_1 == preparatory::Help::Help_state::Title_screen) {
                        given_help_state_1 = preparatory::Help::Help_state::Refresh;
                    } else if (given_help_state_1 == preparatory::Help::Help_state::Refresh) {
                        given_help_state_1 = preparatory::Help::Help_state::Explain_1;
                    }

                    // print the change
                    main_choice_printer(given_help_state_1, help_2_text, Help_Primary);
                    break;
                case KEY_DOWN:
                    if (given_help_state_1 == preparatory::Help::Help_state::Explain_1) {
                        given_help_state_1 = preparatory::Help::Help_state::Refresh;
                    } else if (given_help_state_1 == preparatory::Help::Help_state::Refresh) {
                        given_help_state_1 = preparatory::Help::Help_state::Title_screen;
                    } else if (given_help_state_1 == preparatory::Help::Help_state::Title_screen) {
                        given_help_state_1 = preparatory::Help::Help_state::Explain_1;
                    }

                    // print the change
                    main_choice_printer(given_help_state_1, help_2_text, Help_Primary);
                    break;
                case 10: // char(10) is the return, or endl
                    help_got_in_1 = true;
                    break;
            }
        }

        // act on the choice given
        if (given_help_state_1 == preparatory::Help::Help_state::Explain_1) {
            bool am_i_out_yet = false;
            while (!am_i_out_yet) {
                preparatory::Help::Help_state explain_state = 
                preparatory::Help::help_screen_explain_1(Help_Primary);
                if (explain_state == preparatory::Help::Help_state::Explain_2) {
                    am_i_out_yet = preparatory::Help::help_screen_explain_2(Help_Primary);
                } else if (explain_state == preparatory::Help::Help_state::Help_screen) {
                    am_i_out_yet = true;
                }
            }
        } else if (given_help_state_1 == preparatory::Help::Help_state::Refresh) {
            preparatory::Help::help_screen_refresher(Help_Primary);
        } else if (given_help_state_1 == preparatory::Help::Help_state::Title_screen) {
            reenter_main = true;
        }
    }

    //curs_set(1);

    //wgetch(Help_Primary);

    //curs_set(0);

    delwin(Help_Titular);
    delwin(Help_Primary);
}

void preparatory::Help::help_screen_clear() {
    // clear top title, to be fixed
    preparatory::Help::help_1_border.clear();
    preparatory::Help::help_1_text.clear();
    preparatory::Help::help_2_border.clear();
    preparatory::Help::help_2_text.clear();
    preparatory::Help::help_34_border.clear();
    preparatory::Help::help_3_mtext.clear();
    preparatory::Help::help_3_stext.clear();
    preparatory::Help::help_4_mtext.clear();
    preparatory::Help::help_4_stext.clear();
    preparatory::Help::help_5_border.clear();
    preparatory::Help::help_5_mtext.clear();
    preparatory::Help::help_5_stext.clear();
}

// ==> Help Sub-functions

// govern the input of entries into the first explain screen
// return the passed enum class
preparatory::Help::Help_state preparatory::Help::help_screen_explain_1(
    WINDOW * given_win
) {
    // clear the window
    //wclear(given_win);

    // output the text
    help_screen_3p(help_3_mtext, help_34_border, given_win);

    // prepare te default game state
    preparatory::Help::Help_state given_help_state_2 = preparatory::Help::Help_state::Explain_2;

    //print that out
    help_choice_printer_1(given_help_state_2, help_3_stext, given_win);

    // get the character
    int given_help_switcher_2 = 0;

    // whether the person has made a choice yet
    bool help_got_in_2 = false;

    while (!help_got_in_2) {
        given_help_switcher_2 = wgetch(given_win);

        switch(given_help_switcher_2) {
            case KEY_RIGHT: // apparently, it has the same effect whether you go key right or key left!
            case KEY_LEFT:  // makes my job easier.
                if (given_help_state_2 == preparatory::Help::Help_state::Explain_2) {
                    given_help_state_2 = preparatory::Help::Help_state::Help_screen;
                } else if (given_help_state_2 == preparatory::Help::Help_state::Help_screen) {
                    given_help_state_2 = preparatory::Help::Help_state::Explain_2;
                }

                help_choice_printer_1(given_help_state_2, help_3_stext, given_win);
                break;
            case 10:
                help_got_in_2 = true;
                break;
        }
    }

    return given_help_state_2;
}

// govern the input of entries into the second explain screen
// return whether the user decided to go out or not
bool preparatory::Help::help_screen_explain_2(
    WINDOW * given_win
) {
    help_screen_4p(help_4_mtext, help_34_border, given_win);

    // prepare the defualt state of choices
    // back to the help screen
    preparatory::Help::Help_state given_help_state_3 = preparatory::Help::Help_state::Help_screen;

    // print out that first state
    preparatory::Help::help_choice_printer_2(given_help_state_3, help_4_stext, given_win);

    // initialize the char
    int given_help_switcher_3 = 0;

    // initialize the bool to get out
    bool help_got_in_3 = false;

    while (!help_got_in_3) {
        given_help_switcher_3 = wgetch(given_win);

        switch(given_help_switcher_3) {
            case KEY_RIGHT:
            case KEY_LEFT:
                if (given_help_state_3 == preparatory::Help::Help_state::Help_screen) {
                    given_help_state_3 = preparatory::Help::Help_state::Explain_1;
                } else if (given_help_state_3 == preparatory::Help::Help_state::Explain_1) {
                    given_help_state_3 = preparatory::Help::Help_state::Help_screen;
                }

                help_choice_printer_2(given_help_state_3, help_4_stext, given_win);
                break;
            case 10:
                help_got_in_3 = true;
                break;
        }
    }

    if (given_help_state_3 == preparatory::Help::Help_state::Help_screen) {
        return true;
    } else if (given_help_state_3 == preparatory::Help::Help_state::Explain_1) {
        return false;
    } else {
        return true;
    }
} // you may see this cuase an error– that's expected

// govern the input of entry into the refresher screen
// upon returning, go back to running the help screen
void preparatory::Help::help_screen_refresher(
    WINDOW * given_win
) {
    help_screen_5p(help_5_mtext, help_5_border, given_win);

    // rpint out the single choice
    preparatory::priv::passer_lr(
        help_5_stext,
        "Back to Help",
        15, 34,
        Output_con::Coloration::Yellow,
        Output_con::Attribute::Reversed,
        false
    );

    preparatory::priv::wprintcon(given_win, help_5_stext);

    // get the player input
    int given_help_switcher_4 = 0;

    // while the ainput is not yet a return
    while (given_help_switcher_4 != 10){
        // continue getting characters
        given_help_switcher_4 = wgetch(given_win);
    }
    
    // end
    return;
}

// ==> Help Loader Functions

void preparatory::Help::help_screen_1l (
    std::vector<Output_con>& help_1_border,
    std::vector<Output_con>& help_1_text
) {
    // load the border
    // left side of outer, right side inner
    help_1_border.push_back(Output_con("┃", 3, 0, 60, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("*", 3, 77, 60, true, Output_con::Coloration::Naught));
    help_1_border.push_back(Output_con("┃", 2, 0, 30, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("┃", 4, 0, 30, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("*", 2, 77, 30, false, Output_con::Coloration::Naught));
    help_1_border.push_back(Output_con("*", 4, 77, 30, true, Output_con::Coloration::Naught));
    help_1_border.push_back(Output_con("┃", 1, 0, 30, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("┃", 5, 0, 30, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("*", 1, 77, 30, false, Output_con::Coloration::Naught));
    help_1_border.push_back(Output_con("*", 5, 77, 30, true, Output_con::Coloration::Naught));
    help_1_border.push_back(Output_con("┏", 0, 0, 60, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("┗", 6, 0, 60, true, Output_con::Coloration::Red));
    // the tops and bottoms
    help_1_border.push_back(Output_con("━", 0, 1, 30, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("━", 6, 1, 30, true, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("━", 0, 2, 30, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("━", 6, 2, 30, true, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("━", 0, 3, 30, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("━", 6, 3, 30, true, Output_con::Coloration::Red));
    for (int i = 0; i <= 71; ++i) {
        help_1_border.push_back(Output_con("━", 0, (4+i), 15, false, Output_con::Coloration::Red));
        help_1_border.push_back(Output_con("━", 6, (4+i), 15, false, Output_con::Coloration::Red));
        help_1_border.push_back(Output_con("═", 1, (75-i), 15, false, Output_con::Coloration::Naught));
        help_1_border.push_back(Output_con("═", 5, (75-i), 15, true, Output_con::Coloration::Naught));
    }
    help_1_border.push_back(Output_con("━", 0, 76, 30, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("━", 6, 76, 30, true, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("━", 0, 77, 30, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("━", 6, 77, 30, true, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("━", 0, 78, 30, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("━", 6, 78, 30, true, Output_con::Coloration::Red));
    // right side of outer, left side of inner
    help_1_border.push_back(Output_con("┓", 0, 79, 60, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("┛", 6, 79, 60, true, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("┃", 1, 79, 30, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("┃", 5, 79, 30, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("*", 1, 2, 30, false, Output_con::Coloration::Naught));
    help_1_border.push_back(Output_con("*", 5, 2, 30, true, Output_con::Coloration::Naught));
    help_1_border.push_back(Output_con("┃", 2, 79, 30, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("┃", 4, 79, 30, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("*", 2, 2, 30, false, Output_con::Coloration::Naught));
    help_1_border.push_back(Output_con("*", 4, 2, 30, true, Output_con::Coloration::Naught));
    help_1_border.push_back(Output_con("┃", 3, 79, 60, false, Output_con::Coloration::Red));
    help_1_border.push_back(Output_con("*", 3, 2, 60, true, Output_con::Coloration::Naught));

    // Load the text
    // H
    preparatory::alpha::letter_h(help_1_text, 2, 28, Output_con::Coloration::Red);
    // E
    preparatory::alpha::letter_e(help_1_text, 2, 35, Output_con::Coloration::Red);
    // L
    preparatory::alpha::letter_l(help_1_text, 2, 41, Output_con::Coloration::Red);
    // P
    preparatory::alpha::letter_p(help_1_text, 2, 47, Output_con::Coloration::Red);
}

void preparatory::Help::help_screen_2l(
    std::vector<Output_con>& help_2_border
) {
    // load the subtitle
    preparatory::priv::center_lr(
        help_2_border, 
        "What do you need help about?", 
        1, 
        60, 
        Output_con::Coloration::Orange
    );
    preparatory::priv::center_lr(
        help_2_border, 
        "Press the arrow key, then enter, to make a selection.", 
        2, 
        60, 
        Output_con::Coloration::Orange
    );
    // load the border
    help_2_border.push_back(Output_con("╔", 4, 19, 30, false, Output_con::Coloration::Violet));
    help_2_border.push_back(Output_con("╝", 12, 58, 30, true, Output_con::Coloration::Violet));
    for (int i = 0; i <= 37; ++i) {
        help_2_border.push_back(Output_con("═", 4, (20+i), 30, false, Output_con::Coloration::Violet));
        help_2_border.push_back(Output_con("═", 12, (57-i), 30, true, Output_con::Coloration::Violet));
    }
    help_2_border.push_back(Output_con("╗", 4, 58, 30, false, Output_con::Coloration::Violet));
    help_2_border.push_back(Output_con("╚", 12, 19, 30, true, Output_con::Coloration::Violet));
}

void preparatory::Help::help_screen_34l(
    std::vector<Output_con>& help_3_mtext,
    std::vector<Output_con>& help_4_mtext,
    std::vector<Output_con>& help_34_border
) {
    // the actual text itself of the first explain screen
    preparatory::priv::center_lr(
        help_3_mtext, 
        "What is Mastermind?", 
        1, 60,
        Output_con::Coloration::Naught
    );
    preparatory::priv::center_lr(
        help_3_mtext, 
        "\"Mastermind is a code-breaking game,\"", 
        3, 60, 
        Output_con::Coloration::Orange
    );
    preparatory::priv::center_lr(
        help_3_mtext, 
        "\"made for 2 players.\"", 
        4, 60, 
        Output_con::Coloration::Orange
    );
    preparatory::priv::center_lr(
        help_3_mtext, 
        "* This implementation only requires 1, however.", 
        5, 60, 
        Output_con::Coloration::Blue
    );
    preparatory::priv::center_lr(
        help_3_mtext, 
        "The computer generates 3 colors,", 
        7, 60, 
        Output_con::Coloration::Yellow
    );
    preparatory::priv::center_lr(
        help_3_mtext, 
        "of the 6 possible options:", 
        8, 60, 
        Output_con::Coloration::Naught
    );
    preparatory::priv::center_lr(
        help_3_mtext, 
        "Red, Orange, Yellow, Green, Blue, and Violet.", 
        9, 60, 
        Output_con::Coloration::Naught
    );
    preparatory::priv::center_lr(
        help_3_mtext, 
        "Depending on your settings, this code can be made", 
        11, 60, 
        Output_con::Coloration::Naught
    );
    preparatory::priv::center_lr(
        help_3_mtext, 
        "either to repeat values or not to do so.", 
        12, 60, 
        Output_con::Coloration::Naught
    );

    // the second explain screen
    preparatory::priv::center_lr(
        help_4_mtext, 
        "What is Mastermind?", 
        1, 60,
        Output_con::Coloration::Naught
    );
    preparatory::priv::center_lr(
        help_4_mtext, 
        "You will then have 7 opportunities to guess", 
        3, 60, 
        Output_con::Coloration::Naught
    );
    preparatory::priv::center_lr(
        help_4_mtext, 
        "what the correct code is.", 
        4, 60, 
        Output_con::Coloration::Naught
    );
    preparatory::priv::center_lr(
        help_4_mtext, 
        "You will then be given a score, with 3 sorted values,", 
        6, 60, 
        Output_con::Coloration::Naught
    );
    preparatory::priv::center_lr(
        help_4_mtext, 
        "with each value ranging from 2 to 0:", 
        7, 60, 
        Output_con::Coloration::Naught
    );
    preparatory::priv::center_lr(
        help_4_mtext, 
        "2 means you have a color and position correct,", 
        8, 60, 
        Output_con::Coloration::Orange
    );
    preparatory::priv::center_lr(
        help_4_mtext, 
        "1 means you have a color correct, but in the incorrect position,", 
        9, 60, 
        Output_con::Coloration::Orange
    );
    preparatory::priv::center_lr(
        help_4_mtext, 
        "and 0 means you do not have the correct color nor position.", 
        10, 60, 
        Output_con::Coloration::Orange
    );
    preparatory::priv::center_lr(
        help_4_mtext, 
        "The game ends when you guess the correct code or you run out of turns.", 
        12, 60, 
        Output_con::Coloration::Orange
    );

    // the border
    preparatory::priv::scanner(
        help_34_border,
        {"╒", "│", "╘"},
        14, 20,
        Output_con::Coloration::Blue
    );
    for (int i = 0; i <= 17; ++i) {
        preparatory::priv::scanner(
            help_34_border,
            {"═", " ", "═"},
            14, (21 + i),
            Output_con::Coloration::Blue
        );
    }
    preparatory::priv::scanner(
        help_34_border,
        {"╤", "│", "╧"},
        14, 39,
        Output_con::Coloration::Blue
    );
    for (int i = 0; i <= 17; ++i) {
        preparatory::priv::scanner(
            help_34_border,
            {"═", " ", "═"},
            14, (40 + i),
            Output_con::Coloration::Blue
        );
    }
    preparatory::priv::scanner(
        help_34_border,
        {"╕", "│", "╛"},
        14, 58,
        Output_con::Coloration::Blue
    );
}

void preparatory::Help::help_screen_5l(
    std::vector<Output_con>& help_5_mtext,
    std::vector<Output_con>& help_5_border
) {
    // the text itself
    preparatory::priv::center_lr(
        help_5_mtext, 
        "How do I play this version?", 
        1, 60,
        Output_con::Coloration::Naught
    );
    preparatory::priv::center_lr(
        help_5_mtext, 
        "You will be requested to enter a code of 3 characters,", 
        3, 60,
        Output_con::Coloration::Orange
    );
    preparatory::priv::center_lr(
        help_5_mtext, 
        "out of the 6 possible.", 
        4, 60,
        Output_con::Coloration::Naught
    );
    preparatory::priv::center_lr(
        help_5_mtext, 
        "The characters we will draw from are:", 
        5, 60,
        Output_con::Coloration::Naught
    );
    preparatory::priv::valid_color_loader(
        help_5_mtext,
        valid_tokens,
        7
    );
    preparatory::priv::center_lr(
        help_5_mtext, 
        "You may be able to change these in the settings,", 
        9, 60,
        Output_con::Coloration::Naught
    );
    preparatory::priv::center_lr(
        help_5_mtext, 
        "depending on your version.", 
        10, 60,
        Output_con::Coloration::Naught
    );
    preparatory::priv::center_lr(
        help_5_mtext, 
        "After inputting, the board will print out with your feedback.", 
        12, 60,
        Output_con::Coloration::Naught
    );

    // the border
     preparatory::priv::scanner(
        help_5_border,
        {"╒", "│", "╘"},
        14, 30,
        Output_con::Coloration::Blue
    );
    for (int i = 0; i <= 17; ++i) {
        preparatory::priv::scanner(
            help_5_border,
            {"═", " ", "═"},
            14, (31 + i),
            Output_con::Coloration::Blue
        );
    }
    preparatory::priv::scanner(
        help_5_border,
        {"╕", "│", "╛"},
        14, 49,
        Output_con::Coloration::Blue
    );
}

// ==> Help Printer Functions

void preparatory::Help::help_screen_1p(
    const std::vector<Output_con>& help_1_border,
    const std::vector<Output_con>& help_1_text,
    WINDOW * given_win
){
    preparatory::priv::wprintcon(given_win, help_1_border);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    preparatory::priv::wprintcon(given_win, help_1_text);
}

void preparatory::Help::help_screen_2p(
    const std::vector<Output_con>& help_2_border,
    WINDOW * given_win
) {
    wclear(given_win);

    preparatory::priv::wprintcon(given_win, help_2_border);
}

void preparatory::Help::help_screen_3p(
    const std::vector<Output_con>& help_3_mtext,
    const std::vector<Output_con>& help_34_border,
    WINDOW * given_win
) {
    wclear(given_win);

    preparatory::priv::wprintcon(given_win, help_3_mtext);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    preparatory::priv::wprintcon(given_win, help_34_border);
}

void preparatory::Help::help_screen_4p(
    const std::vector<Output_con>& help_4_mtext,
    const std::vector<Output_con>& help_34_border,
    WINDOW * given_win
) {
    wclear(given_win);

    preparatory::priv::wprintcon(given_win, help_4_mtext);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    preparatory::priv::wprintcon(given_win, help_34_border);
}

void preparatory::Help::help_screen_5p(
    const std::vector<Output_con>& help_5_mtext,
    const std::vector<Output_con>& help_5_border,
    WINDOW * given_win
) {
    wclear(given_win);

    preparatory::priv::wprintcon(given_win, help_5_mtext);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    preparatory::priv::wprintcon(given_win, help_5_border);
}

void preparatory::Help::main_choice_printer(
    Help::Help_state given_choice, 
    std::vector<Output_con>& granvec,
    WINDOW * given_win
) {
    if (given_choice == preparatory::Help::Help_state::Explain_1) {
        preparatory::priv::center_lr(
            granvec,
            "<         What is Mastermind?          >",
            6,
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Reversed,
            false
        );
        preparatory::priv::center_lr(
            granvec,
            "<     How do I play this version?      >",
            8,
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::center_lr(
            granvec,
            "<                 Home                 >",
            10,
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::wprintcon(given_win, granvec);
        granvec.clear();
    } else if (given_choice == preparatory::Help::Help_state::Refresh) {
        preparatory::priv::center_lr(
            granvec,
            "<         What is Mastermind?          >",
            6,
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::center_lr(
            granvec,
            "<     How do I play this version?      >",
            8,
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Reversed,
            false
        );
        preparatory::priv::center_lr(
            granvec,
            "<                 Home                 >",
            10,
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::wprintcon(given_win, granvec);
        granvec.clear();
    } else if (given_choice == preparatory::Help::Help_state::Title_screen) {
        preparatory::priv::center_lr(
            granvec,
            "<         What is Mastermind?          >",
            6,
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::center_lr(
            granvec,
            "<     How do I play this version?      >",
            8,
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::center_lr(
            granvec,
            "<                 Home                 >",
            10,
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Reversed,
            false
        );
        preparatory::priv::wprintcon(given_win, granvec);
        granvec.clear();
    } else {
        error ("Absurd implementation of home screen choice");
    }
}

// load and print out the state of the 1st explain screen
void preparatory::Help::help_choice_printer_1(
    Help::Help_state given_choice,
    std::vector<Output_con>& granvec,
    WINDOW * given_win
) {
    if (given_choice == preparatory::Help::Help_state::Explain_2) {
        preparatory::priv::passer_lr(
            granvec,
            "Back to Help",
            15, 24, // 22?
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::passer_lr(
            granvec,
            "Next",
            15, 48, // 46?
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Reversed,
            false
        );
        preparatory::priv::wprintcon(given_win, granvec);
        granvec.clear();
    } else if (given_choice == preparatory::Help::Help_state::Help_screen) {
        preparatory::priv::passer_lr(
            granvec,
            "Back to Help",
            15, 24, // cor 24
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Reversed,
            false
        );
        preparatory::priv::passer_lr(
            granvec,
            "Next",
            15, 48, // cor 48
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::wprintcon(given_win, granvec);
        granvec.clear();
    } else {
        error("Absurd implementation of help screen choices");
    }
}

// load and print out the state of the second explain screen
void preparatory::Help::help_choice_printer_2(
    Help::Help_state given_choice,
    std::vector<Output_con>& granvec,
    WINDOW * given_win
) {
    if (given_choice == preparatory::Help::Help_state::Help_screen) {
        preparatory::priv::passer_lr(
            granvec,
            "Previous",
            15, 26, // 24?
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::passer_lr(
            granvec,
            "Back to Help",
            15, 43, // 45?
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Reversed,
            false
        );
        preparatory::priv::wprintcon(given_win, granvec);
        granvec.clear();
    } else if (given_choice == preparatory::Help::Help_state::Explain_1) {
        preparatory::priv::passer_lr(
            granvec,
            "Previous",
            15, 26, // 24?
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Reversed,
            false
        );
        preparatory::priv::passer_lr(
            granvec,
            "Back to Help",
            15, 43, // 45?
            Output_con::Coloration::Yellow,
            Output_con::Attribute::Naught,
            false
        );
        preparatory::priv::wprintcon(given_win, granvec);
        granvec.clear();
    } else {
        error("Absurd implementation of 2nd explain screen");
        EXIT_FAILURE;
    }
}

// ==> Auxiliary Functions

void const preparatory::priv::printcon(const std::vector<Output_con>& outputvec) {
    for (Output_con outputc : outputvec) {
        // Move to the necessary location
        move(outputc.y_dim, outputc.x_dim);
        
        init_pair(outputc.pair_num, static_cast<int>(outputc.given_color), 0);

        if (outputc.given_attr == Output_con::Attribute::Naught) {
            attron(COLOR_PAIR(outputc.pair_num));
            printw(outputc.output_char.c_str());
            attroff(COLOR_PAIR(outputc.pair_num));
        } else if (outputc.given_attr == Output_con::Attribute::Reversed) {
            attron(COLOR_PAIR(outputc.pair_num) | A_REVERSE);
            printw(outputc.output_char.c_str());
            attroff(COLOR_PAIR(outputc.pair_num) | A_REVERSE);
        }

        // If we need to return, return
        if (outputc.return_now == true) {
            refresh();
        }

        // Wait for the given time in milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(outputc.wait_time));
    }
}

void const preparatory::priv::wprintcon (WINDOW* given_win, const std::vector<Output_con>& outputvec) {
    for (Output_con outputc : outputvec) {
        // Move to the necessary location
        wmove(given_win, outputc.y_dim, outputc.x_dim);
        
        init_pair(outputc.pair_num, static_cast<int>(outputc.given_color), 0);

        if (outputc.given_attr == Output_con::Attribute::Naught) {
            wattron(given_win, COLOR_PAIR(outputc.pair_num));
            wprintw(given_win, outputc.output_char.c_str());
            wattroff(given_win, COLOR_PAIR(outputc.pair_num));
        } else if (outputc.given_attr == Output_con::Attribute::Reversed) {
            wattron(given_win, COLOR_PAIR(outputc.pair_num) | A_REVERSE);
            wprintw(given_win, outputc.output_char.c_str());
            wattroff(given_win, COLOR_PAIR(outputc.pair_num) | A_REVERSE);
        }

        // If we need to return, return
        if (outputc.return_now == true) {
            wrefresh(given_win);
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

void preparatory::priv::center_lr(
    std::vector <Output_con>& granvec, 
    std::string outstr, 
    int y_dimu, 
    Output_con::Coloration col,
    Output_con::Attribute attri,
    bool will_return
) {
    int len = outstr.length();
    // Distance from side
    int dis = 39 - static_cast<int>(floor(len/2.0));
    for (int i = 0; i < len; ++i) {
        std::string s(1, outstr[i]);
        if ((i == len-1) && (will_return == false)) {
            granvec.push_back(Output_con(s, y_dimu, (dis + i), 0, true, col, attri));
            return;
        } else if (will_return == false) {
            granvec.push_back(Output_con(s, y_dimu, (dis + i), 0, false, col, attri));
        } else if (will_return == true) {
            granvec.push_back(Output_con(s, y_dimu, (dis + i), 30, true, col, attri));
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
    Output_con::Coloration col,
    Output_con::Attribute attri,
    bool will_return
) {
    if (will_return == true) {
        for (int i = 0; i < outstr.length(); ++i) {
            std::string s(1, outstr[i]);
            granvec.push_back(Output_con(s, y_dimu, (x_dimu + i), 30, true, col, attri));
            if (i == (outstr.length() - 1)) {
                return;
            }
        }
    } else if (will_return == false){
        for (int i = 0; i < outstr.length(); ++i) {
            std::string s(1, outstr[i]);
            if (i == (outstr.length() - 1)) {
                granvec.push_back(Output_con(s, y_dimu, (x_dimu + i), 0, true, col, attri));
                return;
            }
            granvec.push_back(Output_con(s, y_dimu, (x_dimu + i), 0, false, col, attri));
        }
    }
}

void preparatory::priv::valid_color_loader(
    std::vector <Output_con>& granvec,
    const std::vector<std::string>& valid_tokens,
    int y_dimu
) {
    granvec.push_back(Output_con(valid_tokens[0], y_dimu, 34, Output_con::Coloration::Red));
    granvec.push_back(Output_con(" ", 18, 35));
    granvec.push_back(Output_con(valid_tokens[1], y_dimu, 36, Output_con::Coloration::Orange));
    granvec.push_back(Output_con(" ", 18, 37));
    granvec.push_back(Output_con(valid_tokens[2], y_dimu, 38, Output_con::Coloration::Yellow));
    granvec.push_back(Output_con(" ", 18, 39));
    granvec.push_back(Output_con(valid_tokens[3], y_dimu, 40, Output_con::Coloration::Green));
    granvec.push_back(Output_con(" ", 18, 41));
    granvec.push_back(Output_con(valid_tokens[4], y_dimu, 42, Output_con::Coloration::Blue));
    granvec.push_back(Output_con(" ", 18, 43));
    granvec.push_back(Output_con(valid_tokens[5], y_dimu, 44, Output_con::Coloration::Violet));
}

// letter generators

void preparatory::alpha::letter_a(
    std::vector<Output_con>& granvec,
    int y_dimu,
    int x_dimu,
    Output_con::Coloration col
) {
    preparatory::priv::scanner(granvec, {"╭", "├", "╵"}, y_dimu, x_dimu, Output_con::Coloration::Yellow);
    preparatory::priv::scanner(granvec, {"─", "─", " "}, y_dimu, (x_dimu+1), Output_con::Coloration::Yellow);
    preparatory::priv::scanner(granvec, {"─", "─", " "}, y_dimu, (x_dimu+2), Output_con::Coloration::Yellow);
    preparatory::priv::scanner(granvec, {"─", "─", " "}, y_dimu, (x_dimu+3), Output_con::Coloration::Yellow);
    preparatory::priv::scanner(granvec, {"─", "─", " "}, y_dimu, (x_dimu+4), Output_con::Coloration::Yellow);
    preparatory::priv::scanner(granvec, {"╮", "┤", "╵"}, y_dimu, (x_dimu+5), Output_con::Coloration::Yellow);
    preparatory::priv::scanner(granvec, {" ", " ", " "}, y_dimu, (x_dimu+6), Output_con::Coloration::Yellow);
}

void preparatory::alpha::letter_d(
    std::vector<Output_con>& granvec,
    int y_dimu,
    int x_dimu,
    Output_con::Coloration col
) {
    preparatory::priv::scanner(granvec, {"┌", "│", "└"}, y_dimu, (x_dimu), col);
    preparatory::priv::scanner(granvec, {"─", " ", "─"}, y_dimu, (x_dimu+1), col);
    preparatory::priv::scanner(granvec, {"─", " ", "─"}, y_dimu, (x_dimu+2), col);
    preparatory::priv::scanner(granvec, {"─", " ", "─"}, y_dimu, (x_dimu+3), col);
    preparatory::priv::scanner(granvec, {"╮", "│", "╯"}, y_dimu, (x_dimu+4), col);
    preparatory::priv::scanner(granvec, {" ", " ", " "}, y_dimu, (x_dimu+5), col);
}

void preparatory::alpha::letter_e(
    std::vector<Output_con>& granvec,
    int y_dimu,
    int x_dimu,
    Output_con::Coloration col
) {
    preparatory::priv::scanner(granvec, {"┌", "├", "└"}, y_dimu, (x_dimu), col);
    preparatory::priv::scanner(granvec, {"─", "─", "─"}, y_dimu, (x_dimu+1), col);
    preparatory::priv::scanner(granvec, {"─", "─", "─"}, y_dimu, (x_dimu+2), col);
    preparatory::priv::scanner(granvec, {"─", "─", "─"}, y_dimu, (x_dimu+3), col);
    preparatory::priv::scanner(granvec, {"╴", "╴", "╴"}, y_dimu, (x_dimu+4), col);
    preparatory::priv::scanner(granvec, {" ", " ", " "}, y_dimu, (x_dimu+5), col);
}

void preparatory::alpha::letter_h(
    std::vector<Output_con>& granvec,
    int y_dimu,
    int x_dimu,
    Output_con::Coloration col
) {
    preparatory::priv::scanner(granvec, {"╷", "├", "╵"}, y_dimu, (x_dimu), col);
    preparatory::priv::scanner(granvec, {" ", "─", " "}, y_dimu, (x_dimu+1), col);
    preparatory::priv::scanner(granvec, {" ", "─", " "}, y_dimu, (x_dimu+2), col);
    preparatory::priv::scanner(granvec, {" ", "─", " "}, y_dimu, (x_dimu+3), col);
    preparatory::priv::scanner(granvec, {" ", "─", " "}, y_dimu, (x_dimu+4), col);
    preparatory::priv::scanner(granvec, {"╷", "┤", "╵"}, y_dimu, (x_dimu+5), col);
    preparatory::priv::scanner(granvec, {" ", " ", " "}, y_dimu, (x_dimu+6), col);
}

void preparatory::alpha::letter_i(
    std::vector<Output_con>& granvec,
    int y_dimu,
    int x_dimu,
    Output_con::Coloration col
) {
    preparatory::priv::scanner(granvec, {"╶", " ", "╶"}, y_dimu, (x_dimu), col);
    preparatory::priv::scanner(granvec, {"─", " ", "─"}, y_dimu, (x_dimu+1), col);
    preparatory::priv::scanner(granvec, {"┬", "│", "┴"}, y_dimu, (x_dimu+2), col);
    preparatory::priv::scanner(granvec, {"─", " ", "─"}, y_dimu, (x_dimu+3), col);
    preparatory::priv::scanner(granvec, {"╴", " ", "╴"}, y_dimu, (x_dimu+4), col);
    preparatory::priv::scanner(granvec, {" ", " ", " "}, y_dimu, (x_dimu+5), col);
}

void preparatory::alpha::letter_l(
    std::vector<Output_con>& granvec,
    int y_dimu,
    int x_dimu,
    Output_con::Coloration col
) {
    preparatory::priv::scanner(granvec, {"╷", "│", "└"}, y_dimu, (x_dimu), col);
    preparatory::priv::scanner(granvec, {" ", " ", "─"}, y_dimu, (x_dimu+1), col);
    preparatory::priv::scanner(granvec, {" ", " ", "─"}, y_dimu, (x_dimu+2), col);
    preparatory::priv::scanner(granvec, {" ", " ", "─"}, y_dimu, (x_dimu+3), col);
    preparatory::priv::scanner(granvec, {" ", " ", "╴"}, y_dimu, (x_dimu+4), col);
    preparatory::priv::scanner(granvec, {" ", " ", " "}, y_dimu, (x_dimu+5), col);
}

void preparatory::alpha::letter_m(
    std::vector<Output_con>& granvec,
    int y_dimu,
    int x_dimu,
    Output_con::Coloration col
) {
    preparatory::priv::scanner(granvec, {"╭", "│", "╵"}, y_dimu, (x_dimu), col);
    preparatory::priv::scanner(granvec, {"─", " ", " "}, y_dimu, (x_dimu+1), col);
    preparatory::priv::scanner(granvec, {"─", " ", " "}, y_dimu, (x_dimu+2), col);
    preparatory::priv::scanner(granvec, {"┬", "│", "╵"}, y_dimu, (x_dimu+3), col);
    preparatory::priv::scanner(granvec, {"─", " ", " "}, y_dimu, (x_dimu+4), col);
    preparatory::priv::scanner(granvec, {"─", " ", " "}, y_dimu, (x_dimu+5), col);
    preparatory::priv::scanner(granvec, {"╮", "│", "╵"}, y_dimu, (x_dimu+6), col);
    preparatory::priv::scanner(granvec, {" ", " ", " "}, y_dimu, (x_dimu+7), col);
}

void preparatory::alpha::letter_n(
    std::vector<Output_con>& granvec,
    int y_dimu,
    int x_dimu,
    Output_con::Coloration col
) {
    preparatory::priv::scanner(granvec, {"╭",  "│", "╵"}, y_dimu, (x_dimu), col);
    preparatory::priv::scanner(granvec, {"\\", " ", " "}, y_dimu, (x_dimu+1), col);
    preparatory::priv::scanner(granvec, {" ", "\\", " "}, y_dimu, (x_dimu+2), col);
    preparatory::priv::scanner(granvec, {" ", " ", "\\"}, y_dimu, (x_dimu+3), col);
    preparatory::priv::scanner(granvec, {"╷",  "│", "╯"}, y_dimu, (x_dimu+4), col);
    preparatory::priv::scanner(granvec, {" ",  " ", " "}, y_dimu, (x_dimu+5), col);
}

void preparatory::alpha::letter_p(
    std::vector<Output_con>& granvec,
    int y_dimu,
    int x_dimu,
    Output_con::Coloration col
) {
    preparatory::priv::scanner(granvec, {"┌", "│", "╵"}, y_dimu, (x_dimu), col);
    preparatory::priv::scanner(granvec, {"─", "─", " "}, y_dimu, (x_dimu+1), col);
    preparatory::priv::scanner(granvec, {"─", "─", " "}, y_dimu, (x_dimu+2), col);
    preparatory::priv::scanner(granvec, {"─", "─", " "}, y_dimu, (x_dimu+3), col);
    preparatory::priv::scanner(granvec, {"╮", "╯", " "}, y_dimu, (x_dimu+4), col);
    preparatory::priv::scanner(granvec, {" ", " ", " "}, y_dimu, (x_dimu+5), col);
}

void preparatory::alpha::letter_r(
    std::vector<Output_con>& granvec,
    int y_dimu,
    int x_dimu,
    Output_con::Coloration col
) {
    preparatory::priv::scanner(granvec, {"┌", "│", "╵"}, y_dimu, (x_dimu), col);
    preparatory::priv::scanner(granvec, {"─", "─", " "}, y_dimu, (x_dimu+1), col);
    preparatory::priv::scanner(granvec, {"─", "─", " "}, y_dimu, (x_dimu+2), col);
    preparatory::priv::scanner(granvec, {"─", "┬", "╰"}, y_dimu, (x_dimu+3), col);
    preparatory::priv::scanner(granvec, {"╮", "╯", "─"}, y_dimu, (x_dimu+4), col);
    preparatory::priv::scanner(granvec, {" ", " ", " "}, y_dimu, (x_dimu+5), col);
}

void preparatory::alpha::letter_s(
    std::vector<Output_con>& granvec,
    int y_dimu,
    int x_dimu,
    Output_con::Coloration col
) {
    preparatory::priv::scanner(granvec, {"╭", "╰", "╶"}, y_dimu, (x_dimu), col);
    preparatory::priv::scanner(granvec, {"─", "─", "─"}, y_dimu, (x_dimu+1), col);
    preparatory::priv::scanner(granvec, {"─", "─", "─"}, y_dimu, (x_dimu+2), col);
    preparatory::priv::scanner(granvec, {"─", "─", "─"}, y_dimu, (x_dimu+3), col);
    preparatory::priv::scanner(granvec, {"╴", "╮", "╯"}, y_dimu, (x_dimu+4), col);
    preparatory::priv::scanner(granvec, {" ", " ", " "}, y_dimu, (x_dimu+5), col);
}

void preparatory::alpha::letter_t(
    std::vector<Output_con>& granvec,
    int y_dimu,
    int x_dimu,
    Output_con::Coloration col
) {
    preparatory::priv::scanner(granvec, {"─", " ", " "}, y_dimu, (x_dimu), col);
    preparatory::priv::scanner(granvec, {"─", " ", " "}, y_dimu, (x_dimu+1), col);
    preparatory::priv::scanner(granvec, {"┬", "│", "╵"}, y_dimu, (x_dimu+2), col);
    preparatory::priv::scanner(granvec, {"─", " ", " "}, y_dimu, (x_dimu+3), col);
    preparatory::priv::scanner(granvec, {"─", " ", " "}, y_dimu, (x_dimu+4), col);
    preparatory::priv::scanner(granvec, {" ", " ", " "}, y_dimu, (x_dimu+5), col);
}