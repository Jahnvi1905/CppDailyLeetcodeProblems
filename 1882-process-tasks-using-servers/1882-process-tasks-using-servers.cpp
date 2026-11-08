
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();

        // {weight, index}
        priority_queue<pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>> available;

        // {freeTime, weight, index}
        priority_queue<tuple<long long, int, int>,
            vector<tuple<long long, int, int>>,
            greater<tuple<long long, int, int>>> busy;

        for (int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        vector<int> ans(m);
        long long currentTime = 0;

        for (int i = 0; i < m; i++) {

            currentTime = max(currentTime, (long long)i);

            // Release all servers that are free
            while (!busy.empty() &&
                   get<0>(busy.top()) <= currentTime) {

                auto [time, weight, index] = busy.top();
                busy.pop();

                available.push({weight, index});
            }

            // If no server is available, jump to earliest release time
            if (available.empty()) {
                currentTime = get<0>(busy.top());

                while (!busy.empty() &&
                       get<0>(busy.top()) <= currentTime) {

                    auto [time, weight, index] = busy.top();
                    busy.pop();

                    available.push({weight, index});
                }
            }

            // Select server with minimum weight, then index
            auto [weight, index] = available.top();
            available.pop();

            ans[i] = index;

            // Server becomes free after processing this task
            busy.push({
                currentTime + tasks[i],
                weight,
                index
            });
        }

        return ans;
    }
};
