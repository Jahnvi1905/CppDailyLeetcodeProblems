
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        
        set<int> available;
        
        for (int i = 0; i < k; i++) {
            available.insert(i);
        }
        
        // {finishing time, server ID}
        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > busy;
        
        vector<int> count(k, 0);
        
        for (int i = 0; i < arrival.size(); i++) {
            
            // Free all servers whose requests are completed
            while (!busy.empty() && busy.top().first <= arrival[i]) {
                available.insert(busy.top().second);
                busy.pop();
            }
            
            // No server available
            if (available.empty()) {
                continue;
            }
            
            int target = i % k;
            
            // Find first available server >= target
            auto it = available.lower_bound(target);
            
            // Wrap around if necessary
            if (it == available.end()) {
                it = available.begin();
            }
            
            int server = *it;
            
            // Assign request
            available.erase(it);
            
            count[server]++;
            
            // Mark server busy
            busy.push({
                (long long)arrival[i] + load[i],
                server
            });
        }
        
        // Find maximum requests handled
        int maxi = *max_element(count.begin(), count.end());
        
        vector<int> ans;
        
        for (int i = 0; i < k; i++) {
            if (count[i] == maxi) {
                ans.push_back(i);
            }
        }
        
        return ans;
    }
};
