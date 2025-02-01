#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>

using namespace std;

struct Route {
    int destination, time, start_hour, end_hour, penalty;
};

struct State {
    int stop, time, transfers, penalty;
    bool operator>(const State& other) const {
        return time > other.time;
    }
};

vector<vector<Route>> graph;

int findShortestRoute(int n, int start, int destination, int max_transfers, int current_hour) {
    priority_queue<State, vector<State>, greater<State>> pq;
    vector<vector<int>> min_time(n, vector<int>(max_transfers + 1, numeric_limits<int>::max()));
    vector<vector<int>> min_penalty(n, vector<int>(max_transfers + 1, numeric_limits<int>::max()));
    
    pq.push({start, 0, 0, 0});
    min_time[start][0] = 0;
    min_penalty[start][0] = 0;
    
    while (!pq.empty()) {
        State state = pq.top(); pq.pop();
        int stop = state.stop, time = state.time, transfers = state.transfers, penalty = state.penalty;
        
        if (stop == destination) return time;
        
        if (transfers > max_transfers) continue;
        
        for (const auto& route : graph[stop]) {
            if (current_hour >= route.start_hour && current_hour <= route.end_hour) {
                int new_time = time + route.time;
                int new_penalty = penalty + route.penalty;
                
                if (new_time < min_time[route.destination][transfers + 1]) {
                    min_time[route.destination][transfers + 1] = new_time;
                    min_penalty[route.destination][transfers + 1] = new_penalty;
                    pq.push({route.destination, new_time, transfers + 1, new_penalty});
                }
            }
        }
    }
    return -1;
}

int main() {
    int n, m;
    cin >> n >> m;
    graph.resize(n);
    
    for (int i = 0; i < m; i++) {
        int start, end, time, start_hour, end_hour, penalty;
        cin >> start >> end >> time >> start_hour >> end_hour >> penalty;
        graph[start].push_back({end, time, start_hour, end_hour, penalty});
        graph[end].push_back({start, time, start_hour, end_hour, penalty});
    }
    
    int start, destination, max_transfers, current_hour;
    cin >> start >> destination >> max_transfers >> current_hour;
    
    int result = findShortestRoute(n, start, destination, max_transfers, current_hour);
    cout << result << endl;
    
    return 0;
}
