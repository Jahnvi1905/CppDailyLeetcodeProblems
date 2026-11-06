
class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        
        // Sort logs by time
        sort(logs.begin(), logs.end(), 
            [](const vector<int>& a, const vector<int>& b) {
                return a[1] < b[1];
            });

        // Store queries with their original indices
        vector<pair<int, int>> q;
        for (int i = 0; i < queries.size(); i++) {
            q.push_back({queries[i], i});
        }

        sort(q.begin(), q.end());

        vector<int> ans(queries.size());
        vector<int> freq(n + 1, 0);

        int left = 0, right = 0;
        int active = 0;

        for (auto [time, idx] : q) {

            int start = time - x;
            
            // Add logs within the right boundary
            while (right < logs.size() && logs[right][1] <= time) {
                int id = logs[right][0];

                if (freq[id] == 0)
                    active++;

                freq[id]++;
                right++;
            }

            // Remove logs before the left boundary
            while (left < right && logs[left][1] < start) {
                int id = logs[left][0];

                freq[id]--;

                if (freq[id] == 0)
                    active--;

                left++;
            }

            // Servers with zero requests
            ans[idx] = n - active;
        }

        return ans;
    }
};
