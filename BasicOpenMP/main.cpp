#include <iostream>
#include <omp.h>
using namespace std;
bool isPrime(int x){
    if (x<=1) return 0;
    for (int i=2;i*i<=x;i++){
        if (x%i==0) return 0;
    }
    return 1;
}
int main() {
    int n;
    int a[100005];
    int sum = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= n; i++) {
        if (isPrime(a[i])) sum += a[i];
    }
    cout << sum;
    return 0;
}
