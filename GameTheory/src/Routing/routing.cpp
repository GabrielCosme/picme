#include <bits/stdc++.h>

#define MAXV 50

using namespace std;

double dist[MAXV];

bool comp(int a, int b){
    return dist[a] > dist[b];
}

int main(){
    int i, aux, e, x, y, players, v;
    vector <int> todo;
    map <pair<int,int>, int> occupancy;
    bool finished = true;
    double price;

    printf("Number of vertices: ");
    scanf("%d", &v);
    printf("Number of edges: ");
    scanf("%d", &e);
    printf("Number of players: ");
    scanf("%d", &players);

    double cost[players] = {0};
    pair <int, int> route[players];
    vector <pair <int, int>> graph[v];
    int parent[players][v];
    memset(parent, -1, players * v * sizeof(int));

    for (i = 0; i < e; i++){
        printf("edge %d: ", i + 1);
        scanf("%d %d %d", &x, &y, &aux);
        graph[y].push_back({x, aux});
    }

    for (i = 0; i < players; i++){
        printf("start and end point of player %d: ", i + 1);
        scanf("%d %d", &x, &y);
        route[i] = {y, x};
    }

    for (int p = 0; p < players or !finished; p++){
        if (p == players){
            p = 0;
            finished = true;
            puts("------------------------");
        }
        x = route[p].first;
        y = route[p].second;

        for (i = y; parent[p][i] != -1;){
            occupancy[{parent[p][i], i}]--;
            i = parent[p][i];
        }

        for (i = 0; i < v; i++){
            dist[i] = LONG_LONG_MAX;
            todo.push_back(i);
        }
        dist[x] = 0;
        make_heap(todo.begin(), todo.end(), comp);

        while(!todo.empty()){
            aux = todo.front();
            pop_heap(todo.begin(), todo.end(), comp);
            todo.pop_back();
            if (dist[aux] == LONG_LONG_MAX) break;

            for (auto j: graph[aux]){
                i = j.first;
                price = (((double)j.second)/(occupancy[{aux, i}]+1)) + dist[aux];

                if(price < dist[i]){
                    dist[i] = price;
                    parent[p][i] = aux;
                    make_heap(todo.begin(), todo.end(), comp);
                }
            }
        }

        if (cost[p] != dist[y]){
            finished = false;
            cost[p] = dist[y];
        }

        printf("%d - %.4lf |", p, cost[p]);
        for (i = y; parent[p][i] != -1;){
            printf(" %d", i);
            occupancy[{parent[p][i], i}]++;
            i = parent[p][i];
        }
        printf(" %d\n", i);
    }

    return 0;
}