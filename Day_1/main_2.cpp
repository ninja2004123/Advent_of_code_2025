#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int main() {
    ifstream inputFile;
    inputFile.open("input");

    int password = 0;

    int currentNumber = 50;
    string rotation;
    while (inputFile >> rotation) {
        int steps = stoi(rotation.substr(1, rotation.size() - 1));

        while (steps--) {
            if (rotation[0] == 'L')
                currentNumber--; 
            else if (rotation[0] == 'R')
                currentNumber++;

            currentNumber %= 100;
            if (currentNumber == 0)
                password++;
        }
    }

    cout << password << endl;

    return 0;
}