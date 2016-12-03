#pragma once
#ifndef MORSE_TREE
#define MORSE_TREE
#include "Binary_Tree.h"
#include <iostream>
#include <string>

using namespace std;
 
class Morse_Tree : public Binary_Tree<char>
{
public:

    Morse_Tree() : Binary_Tree() {};

    bool insert_morse(BTNode<char>*& local_root, std::string code, char letter)
    {
        std::string next_command = code.substr(0, 1);

        if (local_root == NULL)
        {
            local_root = new BTNode<char>(letter);
            return true;
        }
        else if (next_command == ".")
            insert_morse(local_root->left, code.substr(1), letter);
        else if (next_command == "_")
            insert_morse(local_root->right, code.substr(1), letter);
        else
        {
            cerr << "ERROR INSERTING, INVALID INPUT STRING" << endl;
            return false;
        }
    }

    void find_morse(BTNode<char>*& local_root, std::string code, std::string& output)
    {
        if (code.length() == 1)
        {
            if (code[0] == '.')
            {
                output += (local_root->left->data);
                return;
            }
            else if (code[0] == '_')
            {
                output += (local_root->right->data);
                return;
            }
        }
        else if (code[0] == '.')
        {
            find_morse(local_root->left, code.substr(1), output);
        }
        else if (code[0] == '_')
        {
            find_morse(local_root->right, code.substr(1), output);
        }
    }

    std::string find_morse_wrapper(std::string code)
    {
        string output;
        find_morse(root, code, output);
        return output;
    }


    bool insert_morse_wrapper(std::string code, char letter)
    {
        return insert_morse(root, code, letter);
    }
};








#endif