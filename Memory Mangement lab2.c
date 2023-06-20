

#include <iostream>
using namespace std;

int main() {
    int memory_blocks[] = {300, 600, 350, 200, 750, 125};
    int num_blocks = 6;

    int processes[] = {115, 500, 358, 200, 375};
    int num_processes = 5;

    int allocation[num_processes];

    int i = 0;
    while (i < num_processes) {
        allocation[i] = -1;
        int best_index = -1;

        int j = 0;
        while (j < num_blocks) {
            if (memory_blocks[j] >= processes[i]) {
                if (best_index == -1) {
                    best_index = j;
                } else {
                    if (memory_blocks[j] < memory_blocks[best_index]) {
                        best_index = j;
                    }
                }
            }
            j++;
        }

        if (best_index != -1) {
            allocation[i] = best_index;
            memory_blocks[best_index] -= processes[i];
        }
        i++;
    }

    cout << "Process No.\tProcess Size\tPartition No.\n";
    i = 0;
    while (i < num_processes) {
        cout << i+1 << "\t\t" << processes[i] << "\t\t";
        if (allocation[i] != -1) {
            cout << allocation[i]+1;
        } else {
            cout << "Not Allocated";
        }
        cout << endl;
        i++;
    }

    return 0;
}

