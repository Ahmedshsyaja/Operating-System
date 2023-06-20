
#include <iostream>
using namespace std;

int main() {
    int memBlocks[] = {300, 600, 350, 200, 750, 125};
    int numBlocks = 6;

    int processes[] = {115, 500, 358, 200, 375};
    int numProcesses = 5;

    int allocation[numProcesses];

    int i = 0;
    while (i < numProcesses) {
        allocation[i] = -1;
        int j = 0;
        while (j < numBlocks) {
            if (memBlocks[j] >= processes[i]) {
                allocation[i] = j;
                memBlocks[j] -= processes[i];
                break;
            }
            j++;
        }
        i++;
    }

    cout << "Process No.\tProcess Size\tPartition No.\n";
    i = 0;
    while (i < numProcesses) {
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

