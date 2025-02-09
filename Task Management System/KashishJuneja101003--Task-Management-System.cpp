#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class TaskManager {
private:
    struct Task {
        int id;
        int time;
        int priority;

        bool operator<(const Task &other) const {
            if (priority == other.priority)
                return time > other.time; // Earlier time comes first
            return priority < other.priority; // Higher priority comes first
        }
    };

    priority_queue<Task> pq; // Max-heap to maintain highest priority task
    unordered_map<int, Task> taskMap; // Stores tasks for quick access

public:
    void addTask(int id, int time, int priority) {
        Task newTask = {id, time, priority};
        pq.push(newTask);
        taskMap[id] = newTask;
    }

    int getHighestPriorityTask() {
        while (!pq.empty() && taskMap.find(pq.top().id) == taskMap.end()) {
            pq.pop(); // Remove invalid tasks
        }
        return pq.empty() ? -1 : pq.top().id; // Return highest priority task ID
    }

    void removeTask(int id) {
        if (taskMap.find(id) != taskMap.end()) {
            taskMap.erase(id); // Invalidate the task
        }
    }
};

int main() {
    TaskManager manager;

    int n, q;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int id, time, priority;
        cin >> id >> time >> priority;
        manager.addTask(id, time, priority);
    }

    cin >> q;
    while (q--) {
        int queryType;
        cin >> queryType;
        if (queryType == 1) {
            int id, time, priority;
            cin >> id >> time >> priority;
            manager.addTask(id, time, priority);
        } else if (queryType == 2) {
            cout << manager.getHighestPriorityTask() << endl;
        } else if (queryType == 3) {
            int id;
            cin >> id;
            manager.removeTask(id);
        }
    }

    return 0;
}
