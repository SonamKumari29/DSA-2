#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class TaskManager {
private:
    // int index = 0;
    struct Task {
        int id;
        int time;
        int priority;
    };
    vector<Task> tasks; // Stores all tasks
    unordered_map<int, int> taskIndex; // Maps task_id to its index in the vector

    // Custom comparator for sorting by priority and then time
    static bool compareTasks(const Task &a, const Task &b) {
        if (a.priority == b.priority)
            return a.time < b.time;
        return a.priority > b.priority;
    }

public:
    void addTask(int id, int time, int priority) {
        Task newTask;
        newTask.id = id;
        newTask.priority = priority;
        newTask.time = time;

        tasks.push_back(newTask);
        int n = tasks.size();

        taskIndex[id] = n-1;
    }

    int getHighestPriorityTask() {
        int highest = 0;

        for (int i = 1; i < tasks.size(); i++) {
            if(compareTasks(tasks[i], tasks[highest])) {
                highest = i;
            }
        }

        return tasks[highest].id;
    }

    void removeTask(int id) {
        
        int index = taskIndex[id];
        tasks.erase(tasks.begin() + index);

        for (int i = 0; i < tasks.size(); i++) {
            int id = tasks[i].id;
            taskIndex[id] = i;
        }
        taskIndex.erase(tasks.size() - 1);
        
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