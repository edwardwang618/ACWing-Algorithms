#include <iostream>
using namespace std;

const int N = 100010;
int a[N], f[N];

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];

        f[1] = a[1];
        for (int i = 2; i <= n; i++)
            f[i] = max(f[i - 1], f[i - 2] + a[i]);

        cout << f[n] << endl;
    }

    return 0;
}