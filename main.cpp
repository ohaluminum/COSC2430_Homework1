#include <iostream>
#include <fstream>
#include <sstream>

#include "ArgumentManager.h"
using namespace std;

//Write a function to decode the matrix
//Reference: https://www.educative.io/edpresso/spiral-matrix-algorithm
string spiralMatrixDecode(int row, int col, char** arr)
{
    //Defining the boundaries of the matrix.
    int top = 0;
    int bottom = row - 1;
    int left = 0;
    int right = col - 1;
    string decodedMatrix = "";

    //Defining the direction in which the array is to be traversed.
    //1: left -> right
    //2: top -> bottom
    //3: right -> left
    //4: bottom -> top

    //Initial the direction: left -> right
    int dir = 1;

    while (top <= bottom && left <= right)
    {
        //Moving left -> right
        if (dir == 1)
        {
            for (int i = left; i <= right; i++)
            {
                decodedMatrix += arr[top][i];
            }

            //We have traversed the whole first row 
            //Move down to the next row
            top++;
            dir = 2;
        }

        //Moving top -> bottom
        else if (dir == 2)
        {
            for (int i = top; i <= bottom; i++)
            {
                decodedMatrix += arr[i][right];
            }

            //We have traversed the whole last column
            //Move left to the previous column.
            right--;
            dir = 3;
        }

        //Moving right -> left
        else if (dir == 3)
        {
            for (int i = right; i >= left; i--)
            {
                decodedMatrix += arr[bottom][i];
            }

            //We have traversed the whole last row
            //Move up to the previous row
            bottom--;
            dir = 4;
        }

        //Moving bottom -> up
        else if (dir == 4)
        {
            for (int i = bottom; i >= top; i--)
            {
                decodedMatrix += arr[i][left];
            }

            //We have traversed the whole first col
            //Move right to the next column
            left++;
            dir = 1;
        }
    }
    return decodedMatrix;
}

int readNumOfMatrix(ifstream& inFS)
{
    int counter = 0;
    int size = 0;
    string size_str;
    string tempLine;

    while (getline(inFS, tempLine))
    {
        getline(inFS, size_str, ',');
        size = stoi(size_str);
        getline(inFS, tempLine);

        for (int i = 0; i < size; i++)
        {
            getline(inFS, tempLine);
        }
        counter++;
    }
    return counter;
}


int main(int argc, char* argv[])
{
    ArgumentManager am(argc, argv);

    //Get the filename of argument name "input" and "output"
    //string input = am.get("input");
    //string output = am.get("output");

    //Test
    string input = "input.txt";
    string output = "output11.txt";

    ifstream inFS;
    ofstream outFS;

    inFS.open(input);
    outFS.open(output);

    //Check if the input file is open
    if (!inFS.is_open())
    {
        cout << "Could not open input file." << endl;
        return 1;
    }

    //Read number of matrix in the file
    int numOfMatrix = readNumOfMatrix(inFS);

    //Close input file (in order to re-open and read again)
    inFS.close();

    //Reopen the input file
    inFS.open(input);

    //Check if the input file is open
    if (!inFS.is_open())
    {
        cout << "Could not open input file." << endl;
        return 1;
    }

    cout << numOfMatrix;

    istringstream inSS;
    string line;
    string label;
    string row_str;
    string col_str;
    int row = 0;
    int col = 0;
    string delimiter;
    string eachChar;

    while (getline(inFS, line))
    {
        //Read matrix label 
        label = line;

        //Read matrix dimension
        //Function: getline(istream& iuputStream, string& str, char delimiter)
        getline(inFS, row_str, ',');
        getline(inFS, col_str);

        row = stoi(row_str);
        col = stoi(col_str);
        
        if ((row < 0) || (row > 9) || (col < 0) || (col > 9))
        {
            cout << "The dimenstion of matrix is not bigger than 9 * 9." << endl;
            return 1;
        }

        //Create the 2D dynamic array to store metrix
        char** matrix = new char*[row];
        for (int i = 0; i < row; i++)
        {
            matrix[i] = new char[col];
        }

        //Read metrix from file
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {                     
                inFS >> matrix[i][j];
            }
        }

        string decodedMatrix;

        //Call function to decode metrix to string    
        decodedMatrix = spiralMatrixDecode(row, col, matrix);
        cout << decodedMatrix;

        






    }



        


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
