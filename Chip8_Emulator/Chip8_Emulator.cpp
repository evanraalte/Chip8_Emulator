// Chip8_Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"
#include "Chip8.h"
constexpr auto KEY_EXIT = 27; // ESC

void get_input(function<void(int)> cb) {
    while (true) {
        char input;
        //cin >> input;
        input = _getch();
        int num = (int)input;
        if (num == KEY_EXIT)
            return;
        cb(num);
        //this_thread::sleep_for(chrono::milliseconds(10));
    }
}


int main()
{
    Chip8 c8 = Chip8();

    c8.load_file("IBM.ch8");
    c8.run();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
