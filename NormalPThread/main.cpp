#include <bits/stdc++.h>
#include <pthread.h>

#define N_THREAD 8

using namespace std;

pthread_mutex_t print_lock;

struct ThreadData {
    int id;
    int start;
    int end;
};

bool checkPerfectNum(int x) {
    if (x < 6)
        return false;
    int sum = 1;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            sum += i;
            if (i * i != x)
                sum += x / i;
        }
    }
    return sum == x;
}
void* findPerfect(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int id = data->id;
    int start = data->start;
    int end = data->end;
    for (int i = start; i <= end; i++) {
        if (checkPerfectNum(i)) {
            pthread_mutex_lock(&print_lock);
            cout << "Thread " << id
                 << " | Number: " << i
                 << " | This number is perfect"
                 << endl;
            pthread_mutex_unlock(&print_lock);
        }
    }

    pthread_exit(NULL);
}
int main() {
    pthread_mutex_init(&print_lock, NULL);
    pthread_t thread_handles[N_THREAD];
    int n = 1000000;
    ///cin >> n;
    ThreadData thread_data[N_THREAD];
    for (int i = 0; i < N_THREAD; i++) {
        thread_data[i].id = i;
        thread_data[i].start =
            i * n / N_THREAD + 1;
        thread_data[i].end =
            (i + 1) * n / N_THREAD;
    }
    for (int i = 0; i < N_THREAD; i++) {
        int rc = pthread_create(
            &thread_handles[i],
            NULL,
            findPerfect,
            (void*)&thread_data[i]
        );
        if (rc != 0) {
            cerr << "Loi khi tao thread "
                 << i
                 << ", ma loi: "
                 << rc
                 << endl;

            return -1;
        }
    }
    for (int i = 0; i < N_THREAD; i++) {

        pthread_join(
            thread_handles[i],
            NULL
        );
    }
    pthread_mutex_destroy(&print_lock);
    return 0;
}
