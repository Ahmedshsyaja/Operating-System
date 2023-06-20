
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
        int worst_index = -1;
        int j = 0;
        while (j < num_blocks) {
            if (memory_blocks[j] >= processes[i]) {
                if (worst_index == -1 || memory_blocks[j] > memory_blocks[worst_index])
                    worst_index = j;
            }
            j++;
        }
        if (worst_index != -1) {
            allocation[i] = worst_index;
            memory_blocks[worst_index] -= processes[i];
        }
        i++;
    }

    cout << "Process No.\tProcess Size\tPartition No.\n";
    int k = 0;
    while (k < num_processes) {
        cout << k+1 << "\t\t" << processes[k] << "\t\t";
        if (allocation[k] != -1)
            cout << allocation[k]+1;
        else
            cout << "Not Allocated";
        cout << endl;
        k++;
    }

    return 0;
}