#include <iostream>
using namespace std;

int main() {
    int x, y;
    cin >> x >> y;
    int sum = 0;
    if (x > y) swap(x, y);
    for (int i = x + 1; i < y; i++) if (i % 2) sum += i;
    cout << sum << endl;
    return 0;
}