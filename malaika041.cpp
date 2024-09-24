#include <iostream>
#include <string>
Using namespace std;
struct Task {
    int id;
    string description;
    int priority;
    Task* next;
    Task(int taskId, const string& desc, int prio)
        : id(taskId), description(desc), priority(prio), next(nullptr) {}
};

class TaskManager {
private:
    Task* head;

public:
    TaskManager() : head(nullptr) {}

    // Add a new task in the correct position based on priority

    void addTask(int id, const string& description, int priority) {
        Task* newTask = new Task(id, description, priority);
        if (!head || head->priority < priority) {
            newTask->next = head;
            head = newTask;
        } else {
            Task* current = head;
            while (current->next && current->next->priority >= priority) {
                current = current->next;
            }
            newTask->next = current->next;
            current->next = newTask;
        }
        cout << "Task added: " << description << " with ID: " << id << "\n";
    }

    // Remove the task with the highest priority

    void removeHighestPriorityTask() {
        if (!head) {
            cout << "No tasks to remove.\n";
            return;
        }
        Task* temp = head;
        head = head->next;
        delete temp;
        cout << "Removed highest priority task.\n";
    }
    // Remove a specific task by ID

    void removeTaskById(int id) {
        if (!head) {
            cout << "No tasks to remove.\n";
            return;
        }
        if (head->id == id) {
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "Removed task with ID: " << id << "\n";
            return;
        }
        Task* current = head;
        while (current->next && current->next->id != id) {
            current = current->next;
        }
        if (current->next) {
            Task* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "Removed task with ID: " << id << "\n";
        } else {
            cout << "Task with ID: " << id << " not found.\n";
        } }

    // View all tasks

    void viewTasks() const {
        if (!head) {
            cout << "No tasks available.\n";
            return;
        }
        Task* current = head;
        while (current) {
            cout << "ID: " << current->id << ", Description: " << current->description << ",Priority:" << current->priority  << "\n";
            current = current->next;
        }
    }
    ~TaskManager() {
        while (head) {
            removeHighestPriorityTask();
        }
    }
};
void displayMenu() {
    cout << "\n--- Task Manager Menu ---\n";
    cout << "1. Add a new task\n";
    cout << "2. View all tasks\n";
    cout << "3. Remove the highest priority task\n";
    cout << "4. Remove a task by ID\n";
    cout << "5. Exit\n";
}

int main() {
    TaskManager manager;
    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, priority;
                string description;
                cout << "Enter task ID: ";
                cin >> id;
                cin.ignore(); // Clear newline from input buffer
                cout << "Enter task description: ";
                getline(cin, description);
                cout << "Enter task priority: ";
                cin >> priority;
                manager.addTask(id, description, priority);
                break;
            }
            case 2:
                manager.viewTasks();
                break;
            case 3:
                manager.removeHighestPriorityTask();
                break;
            case 4: {
                int id;
                cout << "Enter task ID to remove: ";
                cin >> id;
                manager.removeTaskById(id);
                break;
            }
            case 5:
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
    return 0;

 // This line will never be reached due to the infinite loop above
}