#include <bits/stdc++.h>
#define N_THREAD 4
using namespace std;

pthread_mutex_t print_lock;

struct Employees{
    int id;
    string name;
    int work_count;
};

void* printSay(void *arg){
    Employees* emp = (Employees*)arg;
    int id = emp -> id;
    string name = emp -> name;
    int count = emp -> work_count;

    for (int i=1;i<=count;i++){
        pthread_mutex_lock(&print_lock);
        cout << "So: " << id << " | Ten: " << name << " | CV: " << i << "/" << count << endl;
        pthread_mutex_unlock(&print_lock);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_mutex_init(&print_lock, NULL);
    pthread_t thread_handles[N_THREAD];
    Employees employees[N_THREAD];
    string names[N_THREAD] = {
        "Nguyen Minh - A",
        "Nguyen Minh - B",
        "Nguyen Minh - C",
        "Nguyen Minh - D"
    };
    for (int i=0;i<N_THREAD;i++){
        employees[i].id = i;
        employees[i].name = names[i];
        employees[i].work_count = i*2 + 1;
    }
    for (int i=0;i<N_THREAD;i++){
        pthread_create(&thread_handles[i], NULL, printSay, (void*)&employees[i]);
    }
    for (int i=0;i<N_THREAD;i++){
        pthread_join(thread_handles[i], NULL);
    }
    pthread_mutex_destroy(&print_lock);
    return 0;
}
