#include <iostream>
using namespace std;

void determineFakeCoinWeight() {
    char result1 = 'b'; // Simulated result of weighing A and B
    char result2 = 'r'; // Simulated result of weighing A or B against C

    if (result1 == 'b') {
        if (result2 == 'l') {
            cout << "The fake coin is C and it is heavier." << endl;
        }
        else if (result2 == 'r') {
            cout << "The fake coin is C and it is lighter." << endl;
        }
        else {
            cout << "Unexpected result." << endl;
        }
    }
    else if (result1 == 'l' || result1 == 'r') {
        if (result2 == result1) {
            cout << "The fake coin is A and it is " << (result1 == 'l' ? "lighter" : "heavier") << "." << endl;
        }
        else {
            cout << "The fake coin is B and it is " << (result1 == 'l' ? "heavier" : "lighter") << "." << endl;
        }
    }
    else {
        cout << "Unexpected result." << endl;
    }
}

int main() {
    determineFakeCoinWeight();
    return 0;
}
