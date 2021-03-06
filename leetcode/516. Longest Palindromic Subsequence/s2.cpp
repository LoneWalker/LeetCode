// OJ: https://leetcode.com/problems/longest-palindromic-subsequence
// Author: github.com/lzl124631x
// Time: O(N^2)
// Space: O(N)
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int N = s.size();
        vector<int> dp(N + 1);
        for (int i = N - 1; i >= 0; --i) {
            int prev = 0;
            for (int j = i; j <= N - 1; ++j) {
                int cur = dp[j];
                if (i == j) dp[j] = 1;
                else if (s[i] == s[j]) dp[j] = 2 + prev;
                else dp[j] = max(dp[j], dp[j - 1]);
                prev = cur;
            }
        }
        return dp[N - 1];
    }
};