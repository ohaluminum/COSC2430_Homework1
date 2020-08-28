#include <iostream>
#include <fstream>
#include <sstream>

#include "ArgumentManager.h"
using namespace std;

//write a function!!
//To read number of matrix

int main(int argc, char* argv[])
{
    ArgumentManager am(argc, argv);

    //Get the filename of argument name "input" and "output"
    //string input = am.get("input");
    //string output = am.get("output");

    //Test
    string input = "input.txt";
    string output = "output11.txt";

    ifstream inFS(input);
    ofstream outFS(output);

    //Check if the input file is open
    if (!inFS.is_open())
    {
        cout << "Could not open input file." << endl;
        return 1;
    }

    istringstream inSS;
    string line;
    string label;
    string row_str;
    string col_str;
    int row = 0;
    int col = 0;
    string delimiter;

    while (getline(inFS, line))
    {
        //Read matrix label 
        label = line;

        //Read matrix dimension
        getline(inFS, line);
        inSS.clear();
        inSS.str(line);

        //Function: getline(istream& iuputStream, string& str, char delimiter)
        //getline(inFS, row_str, ',');

        getline(inSS, row_str, ',');
        getline(inSS, col_str, ',');

        row = stoi(row_str);
        col = stoi(col_str);

        if ((row < 0) || (row > 9) || (col < 0) || (col > 9))
        {
            cout << "The dimenstion of matrix is not bigger than 9 * 9." << endl;
            return 1;
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {


            }
        }



    }


    cout << row << col;

        


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
