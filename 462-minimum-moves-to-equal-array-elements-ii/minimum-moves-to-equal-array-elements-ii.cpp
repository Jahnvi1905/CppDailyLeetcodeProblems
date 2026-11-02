class Solution {
public:
    int minMoves2(vector<int>& nums) {
        // Optimize standard standard I/O operations for speed
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        
        int n = nums.size();
        
        // Find the median position using quickselect (O(n) average time complexity)
        auto median_it = nums.begin() + n / 2;
        std::nth_element(nums.begin(), median_it, nums.end());
        int median = *median_it;
        
        // Calculate total moves needed to reach the median
        int moves = 0;
        for (int num : nums) {
            moves += abs(num - median);
        }
        
        return moves;
    }
};