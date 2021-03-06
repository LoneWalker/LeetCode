# [1727. Largest Submatrix With Rearrangements (Medium)](https://leetcode.com/problems/largest-submatrix-with-rearrangements/)

<p>You are given a binary matrix <code>matrix</code> of size <code>m x n</code>, and you are allowed to rearrange the <strong>columns</strong> of the <code>matrix</code> in any order.</p>

<p>Return <em>the area of the largest submatrix within </em><code>matrix</code><em> where <strong>every</strong> element of the submatrix is </em><code>1</code><em> after reordering the columns optimally.</em></p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<p><strong><img alt="" src="https://assets.leetcode.com/uploads/2020/12/29/screenshot-2020-12-30-at-40536-pm.png" style="width: 300px; height: 144px;"></strong></p>

<pre><strong>Input:</strong> matrix = [[0,0,1],[1,1,1],[1,0,1]]
<strong>Output:</strong> 4
<strong>Explanation:</strong> You can rearrange the columns as shown above.
The largest submatrix of 1s, in bold, has an area of 4.
</pre>

<p><strong>Example 2:</strong></p>

<p><img alt="" src="https://assets.leetcode.com/uploads/2020/12/29/screenshot-2020-12-30-at-40852-pm.png" style="width: 500px; height: 62px;"></p>

<pre><strong>Input:</strong> matrix = [[1,0,1,0,1]]
<strong>Output:</strong> 3
<strong>Explanation:</strong> You can rearrange the columns as shown above.
The largest submatrix of 1s, in bold, has an area of 3.
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> matrix = [[1,1,0],[1,0,1]]
<strong>Output:</strong> 2
<strong>Explanation:</strong> Notice that you must rearrange entire columns, and there is no way to make a submatrix of 1s larger than an area of 2.</pre>

<p><strong>Example 4:</strong></p>

<pre><strong>Input:</strong> matrix = [[0,0],[0,0]]
<strong>Output:</strong> 0
<strong>Explanation:</strong> As there are no 1s, no submatrix of 1s can be formed and the area is 0.</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>m == matrix.length</code></li>
	<li><code>n == matrix[i].length</code></li>
	<li><code>1 &lt;= m * n &lt;= 10<sup>5</sup></code></li>
	<li><code>matrix[i][j]</code> is <code>0</code> or <code>1</code>.</li>
</ul>

**Related Topics**:  
[Greedy](https://leetcode.com/tag/greedy/), [Sort](https://leetcode.com/tag/sort/)

**Similar Questions**:
* [Max Area of Island (Medium)](https://leetcode.com/problems/max-area-of-island/)

## Solution 1.

Start from a single row, the max area we can get is the number of `1`s.

Now consider adding a second row, there might be columns with height 2, 1 or 0. If we can the count of these columns, we can get the corresponding area.

For example, assume there are 3 columns with height 2, 4 columns with height 1, 1 column with height 0, then we have:
* matrix with height `2` and width `3`. So area is `6`
* matrix with height `1` and width `(3 + 1)`. So area is `4`.j

So we can keep a `vector<int> h` where `h[j]`, when visiting the `i`-th row, is the number of `1`s from `A[i][j]` upwards, i.e. the height from `A[i][j]` upwards.

And for each row, after updating `h`, we count sort the heights and calculate the corresponding areas.

## Time complexity

For each row:
* updating `h` takes `O(N)` time.
* udpating `m` takes `O(NlogN)` time.
* calculating the areas takes `O(U)` time where `U <= N` is the number of distinct heights.

So overall the time complexity is `O(MNlogN)`.

```cpp
// OJ: https://leetcode.com/problems/largest-submatrix-with-rearrangements/
// Author: github.com/lzl124631x
// Time: O(MNlogN)
// Space: O(N)
class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& A) {
        int M = A.size(), N = A[0].size(), ans = 0;
        vector<int> h(N);
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                h[j] = A[i][j] == 0 ? 0 : (h[j] + 1);
            }
            map<int, int> m;
            for (int n : h) m[n]++;
            int w = 0;
            for (auto it = m.rbegin(); it != m.rend(); ++it) {
                w += it->second;
                ans = max(ans, w * it->first);
            }
        }
        return ans;
    }
};
```