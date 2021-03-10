#include "ncurses.h"
#include "letssee.h"
#include <thread>
#include <chrono>

// The structure that will contain the outputted things.
struct Output_con {
    std::string output_char;
    int x_dim;
    int y_dim;
    int wait_time; // in milliseconds
    bool return_now; // Will I return?
    char state_mod; // a modifier to make it bold or colored or something.

    // Constructor for Output_con given string and x,y dim
    Output_con(std::string str, int x1, int y1) :
        output_char(str), 
        x_dim(x1), 
        y_dim(y1), 
        wait_time(15), 
        return_now(true),
        state_mod(char(32)) { }
    // Constructor for Output_con given all except mod
    Output_con(std::string str, int x1, int y1, int wait, bool return_n) :
        output_char(str),
        x_dim(x1),
        y_dim(y1),
        wait_time(wait),
        return_now(return_n),
        state_mod(char(32)) {}
    // Constructor for Output_con given all
    Output_con(std::string str, int x1, int y1, int wait, bool return_n, char mod) :
        output_char(str),
        x_dim(x1),
        y_dim(y1),
        wait_time(wait),
        return_now(return_n),
        state_mod(mod) {}
};

// The namespace that will contain all of the preparatory functions.
namespace preparatory {
    // The general, overarching preparatory function.
    void startup();

    class Title {
        public:
            // Constructor.
            Title();

            // Prints the title screen and accept the inputs given to it.
            void title_screen();

            // Prints the title itself.
            void title_screen_1(
                std::vector<Output_con>& title_1_bord_1, 
                std::vector<Output_con>& title_1_bord_2, 
                std::vector<Output_con>& title_1_text
            );

            // Prints the creators.
            void title_screen_2();

            // Prints the current settings.
            void title_screen_3();

            // Prints the menu.
            void title_screen_4();
        private:
            // The vector that will contain the borders and text of the title.
            std::vector<Output_con> title_1_bord_1;
            std::vector<Output_con> title_1_bord_2;
            std::vector<Output_con> title_1_text;

            // The vectors that will contain the creators.
            std::vector<Output_con> title_2_bord_1;
            std::vector<Output_con> title_2_text;

            // The vectors that will contain the current settings.
            std::vector<Output_con> title_3_subtitle;
            std::vector<Output_con> title_3_border;
            std::vector<Output_con> title_3_text;

            // The vectors that will set up the menu.
            std::vector<Output_con> title_4_subtitle;
            std::vector<Output_con> title_4_border;
            std::vector<Output_con> title_4_text;
    };

    // Prints the help screen and accepts the inputs given to it.
    void help_screen();

    int terminal_x = -1, terminal_y = -1;
}


void preparatory::startup() {
    // before NCURSES is called
    std::cout << "This file has been designed with the library \u001b[1mNCURSES\u001b[0m in mind." << std::endl;
    std::cout << "You will also require an \u001b[1m80-pixel width terminal or wider.\u001b[0m" << std::endl;
    std::cout << "The program will call an error if you are at neither." << std::endl;
    keep_window_open_cont();

    //call NCURSES
    initscr();

    // confirm that the screen is, in fact, at least 80 pixels wide
    getmaxyx(stdscr, preparatory::terminal_y, preparatory::terminal_x);
    // call error if not
    if (preparatory::terminal_x < 80) {
        error("Your screen is not wide enough to play this game.");
    }

    // prepare the game title
    preparatory::Title Game_Title;
    Game_Title.preparatory::Title::title_screen();

    endwin();
}

void preparatory::Title::title_screen() {
	//printw("Hello World !!!");
    // wait for 1 second before beginning the run
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // The title itself
    preparatory::Title::title_screen_1(
        preparatory::Title::title_1_bord_1,
        preparatory::Title::title_1_bord_2,
        preparatory::Title::title_1_text
    );

    // Move on to next part of screen
    printw("\n");
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

}