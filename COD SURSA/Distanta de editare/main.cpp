#include <iostream>
#include <vector>
#include <string>
using namespace std;

class EditDistance {
public:
    // Calculeaza distanta de editare dintre doua siruri
    int compute(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Initializare baza
        for (int i = 0; i <= n; i++) dp[i][0] = i;
        for (int j = 0; j <= m; j++) dp[0][j] = j;

        // Calculare DP
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1]; // Nu facem nicio operatiune
                } else {
                    dp[i][j] = 1 + min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])); // Corectare
                }
            }
        }

        return dp[n][m];
    }
};

int main() {
    string s1, s2;
    cin >> s1 >> s2;

    EditDistance ed;
    cout << "Distanta de editare: " << ed.compute(s1, s2) << "\n";

    return 0;
}
