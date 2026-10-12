#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void printOptimalParens(vector<vector<int>>& split, int i, int j) {
    if (i == j) {
        cout << "A" << i;
        return;
    }
    cout << "(";
    printOptimalParens(split, i, split[i][j]);
    printOptimalParens(split, split[i][j] + 1, j);
    cout << ")";
}

int matrixChainOrder(vector<int>& p, int n) {   // n = number of matrices
    // dp[i][j] = min cost to multiply matrices i..j
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> split(n + 1, vector<int>(n + 1, 0));

    // L = chain length (length 1 chains cost 0 — already initialized)
    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;

            // try every split point k
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j]
                         + p[i - 1] * p[k] * p[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;   // remember best split
                }
            }
        }
    }

    cout << "Optimal parenthesization: ";
    printOptimalParens(split, 1, n);
    cout << endl;

    return dp[1][n];
}

int main() {
    
    vector<int> p = {10, 30, 5 , 60};
    int n = p.size() - 1;   // number of matrices

    cout << "Minimum scalar multiplications: "
         << matrixChainOrder(p, n) << endl;

    return 0;
}
