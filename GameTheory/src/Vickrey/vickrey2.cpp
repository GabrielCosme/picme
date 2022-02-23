#include <bits/stdc++.h>

#define MAXV 50

using namespace std;

int distx[MAXV], disty[MAXV];

bool compx(int a, int b){
    return distx[a] > distx[b];
}

bool compy(int a, int b){
    return disty[a] > disty[b];
}

bool compq(pair <int, pair <int, int>> a, pair <int, pair <int, int>> b){
    return a.first > b.first;
}

int cost(vector <pair <int, int>> graph, int v){
    for (auto i: graph){
        if (i.first == v) return i.second;
    }
    return 0;
}

int find(vector <pair <int, pair <int, int>>> q, pair <int, int> e){
    for (int i = 0; i < q.size(); i++){
        if (q[i].second == e){
            return i;
        }
    }
    return -1;
}

int block(int path[], int parent[], int i){
    if (path[i] == -1) return block(path, parent, parent[i]);
    return path[i];
}

int main(){
    int v, e, i, x, y, aux, price, k, w, sum = 0;

    printf("Number of vertices: ");
    scanf("%d", &v);
    printf("Number of edges: ");
    scanf("%d", &e);

    int parentx[v], parenty[v], path[v];
    memset(path, -1, v*sizeof(int));

    vector <pair <int, int>> left[v], right[v];
    vector <int> todo;
    vector <pair <int, pair <int, int>>> Q;

    for (i = 0; i < e; i++){
        printf("edge %d: ", i + 1);
        scanf("%d %d %d", &x, &y, &aux);
        left[x].push_back({y, aux});
        right[y].push_back({x, aux});
    }

    printf("Start and end vertice: ");
    scanf("%d %d", &x, &y);

    for (i = 0; i < v; i++){
        distx[i] = INT_MAX;
    }

    memset(parentx, -1, v*sizeof(int));
    todo.push_back(x);
    distx[x] = 0;
    make_heap(todo.begin(), todo.end(), compx);

    while(!todo.empty()){
        aux = todo.front();
        pop_heap(todo.begin(), todo.end(), compx);
        todo.pop_back();
        if (parentx[aux] >= 0) continue;
        parentx[aux] = -parentx[aux] - 1;

        for (auto j: left[aux]){
            i = j.first;
            price = j.second + distx[aux];

            if(price < distx[i]){
                distx[i] = price;
                parentx[i] = -aux - 1;
                todo.push_back(i);
                push_heap(todo.begin(), todo.end(), compx);
            }
        }
    }
    
    for (i = 0; i < v; i++){
        disty[i] = INT_MAX;
    }

    memset(parenty, -1, v*sizeof(int));
    todo.push_back(y);
    disty[y] = 0;
    make_heap(todo.begin(), todo.end(), compy);

    while(!todo.empty()){
        aux = todo.front();
        pop_heap(todo.begin(), todo.end(), compy);
        todo.pop_back();
        if (parenty[aux] >= 0) continue;
        parenty[aux] = -parenty[aux] - 1;

        for (auto j: right[aux]){
            i = j.first;
            price = j.second + disty[aux];

            if(price < disty[i]){
                disty[i] = price;
                parenty[i] = -aux - 1;
                todo.push_back(i);
                push_heap(todo.begin(), todo.end(), compy);
            }
        }
    }

    i = 0;
    for (int j = x; j != y; j = parenty[j]){
        path[j] = i;
        i++;
    }
    path[y] = i;
    k = i + 1;

    for (i = 0; i < v; i++){
        path[i] = block(path, parentx, i);
    }

    vector <pair <int, int>> L[k], R[k];
    int p[k];

    i = 0;
    for (int j = x; j != y; j = parenty[j]){
        p[i] = j;
        i++;
    }
    p[i] = y;

    for (i = 0; i < v; i++){
        for (auto j: left[i]){
            if (parenty[i] != j.first and path[i] < path[j.first]){
                L[path[i]].push_back({i, j.first});
                R[path[j.first]].push_back({i, j.first});
            }
        }
    }
    
    for (i = 0; i < k-1; i++){
        for (auto j: L[i]){
            w = distx[j.first] + cost(left[j.first], j.second) + disty[j.second];
            Q.push_back({w, j});
        }
        for (auto j: R[i]){
            if ((aux = find(Q, j)) >= 0)
                Q.erase(Q.begin()+aux);
        }
        make_heap(Q.begin(), Q.end(), compq);
        p[i] = Q.front().first - distx[y] + cost(left[p[i]], p[i+1]);
    }

    printf(" edge | pay\n");

    i = 0;
    for (int j = x; j != y; j = parenty[j]){
        printf(" %02d-%02d: %02d\n", j, parenty[j], p[i]);
        sum += p[i];
        i++;
    }
    printf("Total cost: %d\n", sum);

    return 0;
}