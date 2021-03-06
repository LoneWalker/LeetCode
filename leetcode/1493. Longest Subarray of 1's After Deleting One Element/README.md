# [1493. Longest Subarray of 1's After Deleting One Element (Medium)](https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/)

<p>Given a binary array <code>nums</code>, you should delete one element from it.</p>

<p>Return the size of the longest non-empty subarray containing only 1's&nbsp;in the resulting array.</p>

<p>Return 0 if there is no such subarray.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> nums = [1,1,0,1]
<strong>Output:</strong> 3
<strong>Explanation: </strong>After deleting the number in position 2, [1,1,1] contains 3 numbers with value of 1's.</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> nums = [0,1,1,1,0,1,1,0,1]
<strong>Output:</strong> 5
<strong>Explanation: </strong>After deleting the number in position 4, [0,1,1,1,1,1,0,1] longest subarray with value of 1's is [1,1,1,1,1].</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> nums = [1,1,1]
<strong>Output:</strong> 2
<strong>Explanation: </strong>You must delete one element.</pre>

<p><strong>Example 4:</strong></p>

<pre><strong>Input:</strong> nums = [1,1,0,0,1,1,1,0,1]
<strong>Output:</strong> 4
</pre>

<p><strong>Example 5:</strong></p>

<pre><strong>Input:</strong> nums = [0,0,0]
<strong>Output:</strong> 0
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= nums.length &lt;= 10^5</code></li>
	<li><code>nums[i]</code>&nbsp;is either&nbsp;<code>0</code>&nbsp;or&nbsp;<code>1</code>.</li>
</ul>


**Related Topics**:  
[Array](https://leetcode.com/tag/array/)

## Solution 1.

`prev2` and `prev` are the indexes of the non-one values we've seen most recently during scanning.

```
prev2              prev            i
  0       1 1 1     0      1 1 1   0 
```

If the array only contains 1, then return `N - 1`.
Otherwise, the answer is the maximum of `i - prev2 - 2`.

```cpp
// OJ: https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(1)
class Solution {
public:
    int longestSubarray(vector<int>& A) {
        int N = A.size(), prev2 = -1, prev = -1, ans = 0;
        for (int i = 0; i <= N; ++i) {
            if (i < N && A[i] == 1) continue;
            if (i == N && prev == -1) return N - 1;
            if (prev != -1) ans = max(ans, i - prev2 - 2);
            prev2 = prev;
            prev = i;
        }
        return ans;
    }
};
```

## Solution 2. Sliding Window

Sliding window `[i, j)` with at most `2` zeros.

1. Keep extending the right edge until the window becomes invalid, i.e. more than one zero, or can't be extended any more.
1. Now `cnt` can be either `0`, `1` or `2`. The corresponding size after deleting one element is `j - i - max(cnt, 1)`.
1. Then we shrink the left edge until `cnt` becomes valid, i.e. `cnt <= 1`.
1. Back to step 1 until the window reaches the end.

```cpp
// OJ: https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(1)
class Solution {
public:
    int longestSubarray(vector<int>& A) {
        int i = 0, j = 0, N = A.size(), cnt = 0, ans = 0;
        while (j < N) {
            while (j < N && cnt <= 1) cnt += A[j++] == 0;
            ans = max(ans, j - i - max(cnt, 1));
            while (cnt > 1) cnt -= A[i++] == 0;
        }
        return ans;
    }
};
```

## Solution 3. Sliding Window

Sliding window `[i, j)` with at most `1` zero.

1. Keep extending the right edge until it reaches the end or one more extension will include 2 zeros.
2. `j - i - 1` is the corresponding answer for this window.
3. Shrink the left edge until `cnt == 0`.
4. Back to step 1 until the window reaches the end.

```cpp
// OJ: https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(1)
class Solution {
public:
    int longestSubarray(vector<int>& A) {
        int i = 0, j = 0, N = A.size(), cnt = 0, ans = 0;
        while (j < N) {
            while (j < N && cnt + (A[j] == 0) <= 1) cnt += A[j++] == 0;
            ans = max(ans, j - i - 1);
            while (cnt == 1) cnt -= A[i++] == 0;
        }
        return ans;
    }
};
```

## Solution 4. Sliding Window

Sliding window `[i, j]` with at most `1` zero.

1. Keep extending the right edge.
2. Once the `cnt > 1`, shrink the left edge.
3. The size for this window with one deletion is `j - i`.
4. Back to step 1 until it reaches the end.

This solution is simpler than the previous one because we don't need to think about when to stop the extension of the right edge.

```cpp
// OJ: https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(1)
class Solution {
public:
    int longestSubarray(vector<int>& A) {
        int i = 0, j = 0, N = A.size(), cnt = 0, ans = 0;
        for (; j < N; ++j) {
            cnt += A[j] == 0;
            while (cnt > 1) cnt -= A[i++] == 0;
            ans = max(ans, j - i);
        }
        return ans;
    }
};
```

## Solution 5. Sliding Window

Sliding window `[i - ans + 1, i]` with at most `1` zero that never shrinks.

```cpp
// OJ: https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(1)
class Solution {
public:
    int longestSubarray(vector<int>& A) {
        int N = A.size(), cnt = 0, ans = 0;
        for (int i = 0; i < N; ++i) {
            cnt += A[i] == 0;
            if (cnt > 1) cnt -= A[i - ans] == 0;
            else ++ans;
        }
        return ans - 1;
    }
};
```

Sliding window `[i, j]` with at most `1` zero taht never shrinks.

```cpp
// OJ: https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(1)
class Solution {
public:
    int longestSubarray(vector<int>& A) {
        int i = 0, j = 0, N = A.size(), cnt = 0;
        for (; j < N; ++j) {
            cnt += A[j] == 0;
            if (cnt > 1) cnt -= A[i++] == 0;
        }
        return j - i - 1;
    }
};
```