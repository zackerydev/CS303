#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Binary_Tree.h"
#include <algorithm>
#include "Code_Sort.h"
#include <map>
#include "String_Tokenizer.h"

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
        string output = "";
        for (int i = 0; i < input.length(); i++)
        {
            output.append(encode_map[input[i]]);
            output.append(" ");
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
    Binary_Tree<char> morse_tree;
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



