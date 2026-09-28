#include <bits/stdc++.h>
#include <pthread.h>
#include <chrono>

#define N_THREAD 8

using namespace std;

// ============================================================
// STRUCT
// ============================================================

struct ThreadData {
    int id;
    int start;
    int end;
    long long count;   // Số perfect number thread tìm được
};

// ============================================================
// KIỂM TRA SỐ HOÀN HẢO
// ============================================================

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

// ============================================================
// SINGLE THREAD
// ============================================================

long long findPerfectSingle(int n) {

    long long count = 0;

    for (int i = 1; i <= n; i++) {

        if (checkPerfectNum(i)) {
            count++;
        }
    }

    return count;
}

// ============================================================
// PTHREAD
// ============================================================

void* findPerfectParallel(void* arg) {

    ThreadData* data = (ThreadData*)arg;

    data->count = 0;

    for (int i = data->start; i <= data->end; i++) {

        if (checkPerfectNum(i)) {
            data->count++;
        }
    }

    pthread_exit(NULL);
}

// ============================================================
// MAIN
// ============================================================

int main() {

    int n;

    cout << "Nhap n: ";
    cin >> n;

    cout << "\n========================================\n";
    cout << "   TIM SO HOAN HAO\n";
    cout << "========================================\n";

    cout << "n = " << n << endl;
    cout << "So thread = " << N_THREAD << endl;

    // ========================================================
    // 1. SINGLE THREAD
    // ========================================================

    cout << "\n[1] CHAY DON LUONG\n";

    auto single_start =
        chrono::high_resolution_clock::now();

    long long single_count =
        findPerfectSingle(n);

    auto single_end =
        chrono::high_resolution_clock::now();

    chrono::duration<double> single_time =
        single_end - single_start;

    cout << "So perfect number: "
         << single_count << endl;

    cout << "Thoi gian: "
         << single_time.count()
         << " giay\n";


    // ========================================================
    // 2. MULTI THREAD
    // ========================================================

    cout << "\n[2] CHAY DA LUONG\n";

    pthread_t thread_handles[N_THREAD];

    ThreadData thread_data[N_THREAD];

    // Chia cong viec
    for (int i = 0; i < N_THREAD; i++) {

        thread_data[i].id = i;

        thread_data[i].start =
            i * n / N_THREAD + 1;

        thread_data[i].end =
            (i + 1) * n / N_THREAD;

        thread_data[i].count = 0;
    }

    auto parallel_start =
        chrono::high_resolution_clock::now();

    // Tao thread
    for (int i = 0; i < N_THREAD; i++) {

        pthread_create(
            &thread_handles[i],
            NULL,
            findPerfectParallel,
            (void*)&thread_data[i]
        );
    }

    // Cho tat ca thread hoan thanh
    for (int i = 0; i < N_THREAD; i++) {

        pthread_join(
            thread_handles[i],
            NULL
        );
    }

    auto parallel_end =
        chrono::high_resolution_clock::now();

    chrono::duration<double> parallel_time =
        parallel_end - parallel_start;


    // ========================================================
    // TONG HOP KET QUA
    // ========================================================

    long long parallel_count = 0;

    for (int i = 0; i < N_THREAD; i++) {
        parallel_count += thread_data[i].count;
    }

    cout << "So perfect number: "
         << parallel_count << endl;

    cout << "Thoi gian: "
         << parallel_time.count()
         << " giay\n";


    // ========================================================
    // 3. SO SANH
    // ========================================================

    cout << "\n========================================\n";
    cout << "             SO SANH\n";
    cout << "========================================\n";

    cout << fixed << setprecision(6);

    cout << "Don luong : "
         << single_time.count()
         << " giay\n";

    cout << "Da luong  : "
         << parallel_time.count()
         << " giay\n";

    double difference =
        single_time.count() - parallel_time.count();

    cout << "Chenh lech: "
         << difference
         << " giay\n";

    if (parallel_time.count() > 0) {

        double speedup =
            single_time.count() /
            parallel_time.count();

        cout << "Speedup   : "
             << speedup
             << "x\n";
    }

    // Kiem tra ket qua
    cout << "\nKiem tra ket qua: ";

    if (single_count == parallel_count) {
        cout << "KHOP\n";
    }
    else {
        cout << "SAI - KHONG KHOP\n";
    }

    return 0;
}
