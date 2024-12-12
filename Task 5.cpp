#include <iostream>
#include <vector>
using namespace std;

void alternatingDisks(int n, vector<char>& disks) {
    int moves = 0;


    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n - 1 - i; j++) {
            if (disks[j] == 'L' && disks[j + 1] == 'D') {
                swap(disks[j], disks[j + 1]);
                moves++;
            }
        }
    }

    cout << "Final arrangement of disks: ";
    for (char disk : disks) {
        cout << disk << " ";
    }
    cout << endl;

    cout << "Total moves: " << moves << endl;
}

int main() {
    int n;
    cout << "Enter the number of disks of each color: ";
    cin >> n;

    vector<char> disks(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        if (i % 2 == 0) {
            disks[i] = 'D'; 
        }
        else {
            disks[i] = 'L'; 
        }
    }

    alternatingDisks(n, disks);

    return 0;
}
