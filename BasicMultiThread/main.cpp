#include <bits/stdc++.h>
using namespace std;

const int n_threads = 8;
const int max_n = 1000;

struct ThreadData {
    int start;
    int end;
    int id;
    int result;
};

void* calcSum (void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data -> result;
    for (int i=data->start; i<=data->end; i++) {
        data -> result +=i;
    }
    return 0;
}
int main() {
    pthread_t threads[n_threads];
    ThreadData data[n_threads];
    int chunk = max_n / n_threads;
    for (int i=0; i<n_threads;i++){
        data[i].id = i + 1;
        data[i].start = i*chunk+1;
        data[i].end = (i == n_threads - 1) ? max_n : (i + 1) * chunk;
        pthread_create(&threads[i], NULL, calcSum, (void*)&data[i]);
    }

    for (int i=0; i<n_threads;i++)
        pthread_join(threads[i], NULL);
    long long total_sum = 0;
    for (int i=0;i<n_threads; i++)
        total_sum += data[i].result;
    cout << total_sum;
    return 0;
}
