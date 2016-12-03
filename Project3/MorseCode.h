#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Code_Sort.h"
#include <map>
#include "String_Tokenizer.h"
#include "Morse_Tree.h"

using namespace std;



class MorseCode
{
public:
    MorseCode() {}
    ~MorseCode() {}

    MorseCode(string _file_name) : file_name(_file_name)
    {
        fstream file;
        file.open(file_name);
        while (!file.eof())
        {
            string line;
            getline(file, line);
            commands.push_back(line);
        }
        sort(commands.begin(), commands.end(), code_sort);
        BTNode<char>* root = new BTNode<char>('\0');
        morse_tree.setRoot(root);
        Create_Tree(commands);
    }

    string Encode(string input)
    {
         // This allows us to check to make sure the iterator returns a valid spot on the map, if its not the end the item will be in the map.
         // We decided to not raise an error and just continue, notifying the user that we have encountered a certain invalid character and 
         // are moving on.
        string output = "";
        for (int i = 0; i < input.length(); i++)
        {
            map<char,string>::const_iterator iter = encode_map.find(input[i]);
            if (iter != encode_map.end())
            {
                output.append(encode_map.find(input[i])->second);
                output.append(" ");
            }
            else
            {
                cout << "Unable to convert " << input[i] << " to a morse code value...skipping character" << endl;
            }
        }
        return output;
    }

    string Decode(string input)
    {
        string output = "";
        String_Tokenizer st(input);
        while (st.has_more_tokens())
        {
            output += (morse_tree.find_morse_wrapper(st.next_token()));
        }
        return output;
    }

    


private:
    string file_name;
    vector<string> commands;
    Morse_Tree morse_tree;
    Code_Sort code_sort;
    map<char, string> encode_map;
    String_Sort string_sort;


    void Create_Tree(vector<string> commands)
    {       
        for (int i = 0; i < commands.size(); i++)
        {
            char letter = commands[i][0];
            string code = commands[i].substr(1);
            
            encode_map[letter] = code;
            morse_tree.insert_morse_wrapper(code, letter);
        }
    }
};



