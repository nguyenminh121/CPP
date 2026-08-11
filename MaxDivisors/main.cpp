#include <bits/stdc++.h>
using namespace std;

const int n_threads = 8;
const int last_n = 100000;

struct ThreadData {
    int start;
    int last;
    int id;
    int n_divi;
    int pos;
};

int get_divisours(int x) {
    int cnt = 0;
    for (int i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            if (i * i == x) cnt++;
            else cnt += 2;
        }
    }
    return cnt;
}

void* count_divisours(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->n_divi = -1;
    data->pos = -1;
    for (int i = data->start; i <= data->last; i++) {
        int divs = get_divisours(i);
        if (divs > data->n_divi) {
            data->n_divi = divs;
            data->pos = i;
        }
    }
    return NULL;
}

int main() {
    pthread_t threads[n_threads];
    ThreadData data[n_threads];
    int chunk_size = last_n / n_threads;
    for (int i = 0; i < n_threads; i++){
        data[i].id = i + 1;
        data[i].start = i * chunk_size + 1;
        data[i].last = (i == n_threads - 1) ? last_n : (i + 1) * chunk_size;

        pthread_create(&threads[i], NULL, count_divisours, (void*)&data[i]);
    }
    for (int i = 0; i < n_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    int max_divi = -1;
    int best_pos = -1;
    for (int i = 0; i < n_threads; i++) {
        if (data[i].n_divi > max_divi) {
            max_divi = data[i].n_divi;
            best_pos = data[i].pos;
        }
    }
    cout << "So co nhieu uoc nhat tu 1 den " << last_n << " la: "
         << best_pos << " voi " << max_divi << " uoc." << endl;
    return 0;
}
