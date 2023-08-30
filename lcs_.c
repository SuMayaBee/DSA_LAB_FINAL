#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

int dp[MAX_LEN][MAX_LEN];
char lcs[MAX_LEN];

int LCS(char* X, char* Y, int m, int n) {
    if (m == 0 || n == 0) {
        return 0;
    }
    if (dp[m][n] != -1) {
        return dp[m][n];
    }
    if (X[m-1] == Y[n-1]) {
        dp[m][n] = 1 + LCS(X, Y, m-1, n-1);
        lcs[dp[m][n]-1] = X[m-1];
    } else {
        int len1 = LCS(X, Y, m-1, n);
        int len2 = LCS(X, Y, m, n-1);
        dp[m][n] = (len1 > len2) ? len1 : len2;
    }
    return dp[m][n];
}

int main() {
    char X[MAX_LEN], Y[MAX_LEN];
    printf("Enter first string: ");
    scanf("%s", X);
    printf("Enter second string: ");
    scanf("%s", Y);
    int m = strlen(X);
    int n = strlen(Y);
    memset(dp, -1, sizeof(dp));
    int len = LCS(X, Y, m, n);
    printf("LCS of these two strings is: %d\n", len);
    printf("LCS string is: %s\n", lcs);
    return 0;
}