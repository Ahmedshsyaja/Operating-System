
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

const int no_of_processes = 5;
const int no_of_resources = 3;

void print_state(bool finish[], int work[], int allocation[][no_of_resources], int need[][no_of_resources])
{
    cout << "Process\t\tMaximum\t\tAllocated\tNeed\t\tFinish\n";
    cout << "\t\tR1 R2 R3\tR1 R2 R3\tR1 R2 R3\n";
    for (int i = 0; i < no_of_processes; i++)
    {
        cout << "P" << i << "\t\t";
        for (int j = 0; j < no_of_resources; j++)
        {
            cout << need[i][j] + allocation[i][j] << " ";
        }
        cout << "\t\t";
        for (int j = 0; j < no_of_resources; j++)
        {
            cout << allocation[i][j] << " ";
        }
        cout << "\t\t";
        for (int j = 0; j < no_of_resources; j++)
        {
            cout << need[i][j] << " ";
        }
        cout << "\t\t" << (finish[i] ? "Finish" : "Not finish") << endl;
    }
    cout << "Available resources: " << work[0] << " " << work[1] << " " << work[2] << endl;
}

bool is_safe_state(bool finish[], int work[], int allocation[][no_of_resources], int need[][no_of_resources], int &next_process)
{
    bool found = false;
    for (int i = next_process; i < no_of_processes; i = (i + 1) % no_of_processes)
    {
        bool possible = true;
        for (int j = 0; j < no_of_resources; j++)
        {
            if (need[i][j] > work[j])
            {
                possible = false;
                break;
            }
        }
        if (possible && !finish[i])
        {
            found = true;
            next_process = (i + 1) % no_of_processes;
            for (int j = 0; j < no_of_resources; j++)
            {
                work[j] += allocation[i][j];
            }
            finish[i] = true;
            break;
        }
    }
    return found;
}
int main()
{
    int max_demand[no_of_processes][no_of_resources] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int allocation[no_of_processes][no_of_resources] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    int work[no_of_resources] = { 3, 3, 2 };
    int need[no_of_processes][no_of_resources];
    bool finish[no_of_processes] = { false };
    int next_process = 0;

    // Calculate the need matrix
    for (int i = 0; i < no_of_processes; i++)
    {
        for (int j = 0; j < no_of_resources; j++)
        {
            need[i][j] = max_demand[i][j] - allocation[i][j];
        }
    }

    // Run the Banker's Algorithm
    cout << "Initial state:\n";
    print_state(finish, work, allocation, need);
    cout << endl;
    cout << "Sequence of processes:\n";
    int count = 0;
    while (count < no_of_processes)
    {
        int process_id;
        bool safe = is_safe_state(finish, work, allocation, need, next_process);
        if (safe)
        {
            process_id = (next_process + no_of_processes - 1) % no_of_processes;
            cout << "P" << process_id << " -> ";
            count++;
        }
        else
        {
            cout << "Unsafe state: no process can proceed\n";
            break;
        }
    }
    cout << "End\n";

    return 0;
}
 
