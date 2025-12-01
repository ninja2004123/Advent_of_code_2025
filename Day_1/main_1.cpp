#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile;
    inputFile.open("input");

    int password = 0;

    int currentNumber = 50;
    string rotation;
    while (inputFile >> rotation) {
        string steps = rotation.substr(1, rotation.size() - 1);
        if (rotation[0] == 'L') {
            currentNumber = (currentNumber - stoi(steps)) % 100;
        } else if (rotation[0] == 'R') {
            currentNumber = (currentNumber + stoi(steps)) % 100;
        }

        if (currentNumber == 0)
            password++;
    }

    cout << password << endl;

    return 0;
}