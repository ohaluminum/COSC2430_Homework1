#include <iostream>
#include <fstream>

#include "ArgumentManager.h"
using namespace std;

//Write a function to decode the matrix
void spiralMatrixDecode(char** arr, int top, int bottom, int left, int right, string& decodedMatrix)
{
    //1.Top row: moving left -> right
    if ((left > right) || (top > bottom))
    {
        return;
    }

    for (int i = left; i <= right; i++)
    {
        decodedMatrix += arr[top][i];
    }
    
    //We have traversed the whole first row
    //Move down to the next row
    top++;
       
    //2.Right column: moving top -> bottom
    if ((left > right) || (top > bottom))
    {
        return;
    }

    for (int i = top; i <= bottom; i++)
    {
        decodedMatrix += arr[i][right];
    }

    //We have traversed the whole last column
    //Move left to the previous column.
    right--;

    //3.Bottom row: moving right -> left
    if ((left > right) || (top > bottom))
    {
        return;
    }

    for (int i = right; i >= left; i--)
    {
        decodedMatrix += arr[bottom][i];
    }

    //We have traversed the whole last row
    //Move up to the previous row
    bottom--;
        
    //4.Left column: moving bottom -> up
    if ((left > right) || (top > bottom))
    {
        return;
    }

    for (int i = bottom; i >= top; i--)
    {
        decodedMatrix += arr[i][left];
    }

    //We have traversed the whole first col
    //Move right to the next column
    left++;

    //Recursion: calling function itself
    spiralMatrixDecode(arr, top, bottom, left, right, decodedMatrix);
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
    string input = "input13.txt";
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

    string line;
    string label;
    string row_str;
    string col_str;
    int row = 0;
    int col = 0;

    //Define matrix parameters
    int top;
    int bottom;
    int left;
    int right;
    string decodedMatrix;

    //Declare a pointer array to store string-pointer
    string** matrixList = new string*[numOfMatrix];
    for (int i = 0; i < numOfMatrix; i++)
    {
        matrixList[i] = new string[2];
    }

    //Store all the matrix information to the array
    for (int i = 0; i < numOfMatrix; i++)
    {
        //Read matrix label
        inFS >> line;
        label = line;
        matrixList[i][0] = label;

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

        //Define matrix parameters
        top = 0;
        bottom = row - 1;
        left = 0;
        right = col - 1;
        decodedMatrix = "";

        //Call function to decode metrix to string    
        spiralMatrixDecode(matrix, top, bottom, left, right, decodedMatrix);
        matrixList[i][1] = decodedMatrix;

        //Delete pointer
        for (int i = 0; i < row; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;

        matrix = nullptr;
    }
    
    //Close input file
    inFS.close();

    //It works! 
    for (int i = 0; i < numOfMatrix; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << matrixList[i][j] << endl;
        }
    }
    return 0;
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
