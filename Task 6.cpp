#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;


int calculateCost(const vector<string>& words, int i, int j, int LW) {
    int totalLength = 0;

    for (int k = i; k <= j; ++k) {
        totalLength += words[k].size();
    }
    int spaces = j - i;  
    int remainingSpace = LW - totalLength - spaces;  
    if (remainingSpace < 0) {
        return INT_MAX; 
    }
    return remainingSpace * remainingSpace;  
}


void printText(const vector<string>& words, const vector<int>& breakPoint) {
    int n = words.size();
    int i = 0;
    while (i < n) {
        int j = breakPoint[i];  
        for (int k = i; k <= j; ++k) {
            cout << words[k] << " ";
        }
        cout << endl;
        i = j + 1; 
    }
}

void wordWrap(const vector<string>& words, int LW) {
    int n = words.size();

    vector<int> dp(n, INT_MAX);
    vector<int> breakPoint(n, -1);

    dp[0] = 0;  

    for (int i = 0; i < n; ++i) {
        int lineLength = 0;
        for (int j = i; j < n; ++j) {
            lineLength += words[j].size();
            if (j > i) lineLength++; 

            if (lineLength <= LW) {
                int cost = calculateCost(words, i, j, LW);
                if (i == 0) {
         
                    if (cost < dp[j]) {
                        dp[j] = cost;
                        breakPoint[j] = i;
                    }
                }
                else {
                    if (dp[i - 1] + cost < dp[j]) {
                        dp[j] = dp[i - 1] + cost;
                        breakPoint[j] = i;
                    }
                }
            }
            else {
                break;  
            }
        }
    }

 
    printText(words, breakPoint);
}

int main() {
    vector<string> words = { "Mary", "loves", "to", "sing", "and", "perform", "tapdancing" };
    int LW = 10;

    wordWrap(words, LW);

    return 0;
}
