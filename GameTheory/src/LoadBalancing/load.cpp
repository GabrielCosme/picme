#include <stdio.h>
#include <queue>
#include <algorithm>

using namespace std;

class machine{
    public:
        int load = 0;
        priority_queue<int, vector<int>, greater<int>> tasks;
};

bool comp(machine a, machine b){
    return a.load < b.load;
}

void printqueue(priority_queue<int, vector<int>, greater<int>> q){
    while (!q.empty()){
        printf(" %d", q.top());
        q.pop();
    }
}

int main(){
    int i, j = 1, m, aux = 0;

    printf("Number of machines: ");
    scanf("%d", &m);

    machine machines[m];

    printf("Weight of the task: ");
    scanf("%d", &i);

    while (i != 0){
        printf("Machine where it will start: ");
        scanf("%d", &j);
        machines[j].tasks.push(i);
        machines[j].load += i;
        printf("Weight of the task: ");
        scanf("%d", &i);
    }

    puts(" i | load | tasks");

    while (true){
        puts("---|------|---------------------------");
        sort(machines, machines+m, comp);
        for (j = 0; j < m; j++){
            printf("%02d | %04d |", j, machines[j].load);
            printqueue(machines[j].tasks);
            puts("");
        }
        for (i = m - 1; i > 0; i--){
            if (machines[0].load < machines[i].load - machines[i].tasks.top()){
                aux = machines[i].tasks.top();
                machines[0].load += aux;
                machines[i].load -= aux;
                machines[i].tasks.pop();
                machines[0].tasks.push(aux);
                printf("---|------| moved %d from %d to 0\n", aux, i);
                break;
            }
        }
        if (i == 0) break;
    }

    return 0;
}