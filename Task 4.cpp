#include <iostream>
using namespace std;

void restrictedHanoi(int n, char source, char destination, char auxiliary, int& moveCount) {
    if (n == 1) {
        cout << "Move disk 1 from " << source << " to " << destination << endl;
        moveCount++;
        return;
    }

    restrictedHanoi(n - 1, source, auxiliary, destination, moveCount);

    cout << "Move disk " << n << " from " << source << " to " << destination << endl;
    moveCount++;

    restrictedHanoi(n - 1, auxiliary, destination, source, moveCount);
}

int main() {
    int n;
    cout << "Enter the number of disks: ";
    cin >> n;
    int moveCount = 0;

    restrictedHanoi(n, 'A', 'C', 'B', moveCount);

    cout << "Total moves: " << moveCount << endl;
    return 0;
}
