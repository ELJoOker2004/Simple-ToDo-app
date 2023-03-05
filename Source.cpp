#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Task struct to hold the task description and status
struct Task {
    string description;
    bool done;
};

// Function to add a task to the list and save it to a file
void addTask(vector<Task>& tasks, const string& filename) {
    // Prompt user for task description
    cout << "Enter task description: ";
    string description;
    getline(cin, description);

    // Create new task and add it to the list
    Task newTask = { description, false };
    tasks.push_back(newTask);

    // Save tasks to file
    ofstream outFile(filename);
    for (const auto& task : tasks) {
        outFile << task.description << ',' << task.done << endl;
    }
}
void deleteTask(vector<Task>& tasks, const string& filename) {
    int taskNum;
    cout << "Enter number of task to delete: ";
    cin >> taskNum;
    cin.ignore(); // Ignore newline character
    if (taskNum < 1 || taskNum > tasks.size()) {
        cout << "Invalid number. Please try again." << endl;
    }
    else {
        tasks.erase(tasks.begin() + taskNum - 1);
        cout << "Task deleted successfully!" << endl;

        // Save tasks to file
        ofstream outFile(filename);
        for (const auto& task : tasks) {
            outFile << task.description << ',' << task.done << endl;
        }
    }
}


// Function to load tasks from a file into the list
void loadTasks(vector<Task>& tasks, const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            size_t pos = line.find(',');
            if (pos != string::npos) {
                string description = line.substr(0, pos);
                bool done = stoi(line.substr(pos + 1));
                tasks.push_back({ description, done });
            }
        }
        inFile.close();
    }
}

// Function to print the list of tasks
void printTasks(const vector<Task>& tasks) {
    cout << "Task List:\n";
    for (size_t i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". ";
        if (tasks[i].done) {
            cout << "[x] ";
        }
        else {
            cout << "[ ] ";
        }
        cout << tasks[i].description << endl;
    }
}

// Main function
int main() {
    const string filename = "tasks.txt";
    vector<Task> tasks;

    // Load tasks from file
    loadTasks(tasks, filename);

    // Main loop
    bool done = false;
    while (!done) {
        cout << "Enter command (add, list, done, delete, quit): ";
        string command;
        getline(cin, command);

        if (command == "add") {
            addTask(tasks, filename);
        }
        else if (command == "list") {
            printTasks(tasks);
        }
        else if (command == "done") {
            cout << "Enter task number: ";
            int taskNum;
            cin >> taskNum;
            cin.ignore(); // Ignore newline character
            if (taskNum > 0 && taskNum <= static_cast<int>(tasks.size())) {
                tasks[taskNum - 1].done = true;
                // Save tasks to file
                ofstream outFile(filename);
                for (const auto& task : tasks) {
                    outFile << task.description << ',' << task.done << endl;
                }
            }
            else {
                cout << "Invalid task number.\n";
            }
        }
        else if (command == "delete") {
            int taskNum;
            cout << "Enter number of task to delete: ";
            cin >> taskNum;
            cin.ignore(); // Ignore newline character
            if (taskNum < 1 || taskNum > tasks.size()) {
                cout << "Invalid number. Please try again." << endl;
            }
            else {
                tasks.erase(tasks.begin() + taskNum - 1);
                // Save tasks to file
                ofstream outFile(filename);
                for (const auto& task : tasks) {
                    outFile << task.description << ',' << task.done << endl;
                }
                cout << "Task deleted successfully!" << endl;
            }
        }

        else if (command == "quit") {
            done = true;
        }
        else {
            cout << "Invalid command.\n";
        }
    }

    return 0;
}
