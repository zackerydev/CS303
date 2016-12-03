#include <iostream>
#include "Morse_Tree.h"
#include "MorseCode.h"
#include <string>

using namespace std;

int main()
{
    MorseCode morse_code("morse.txt");
    string encode = morse_code.Encode("ac3");
    string decode = morse_code.Decode("._ _._.");
    cout << "encode: " << encode << "\n" << "decode: " << decode << endl;

    

    return 0;
}