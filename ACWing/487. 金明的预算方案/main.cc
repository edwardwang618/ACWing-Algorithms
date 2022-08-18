#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> PII;

const int N = 70, M = 32010;

int n, m;
PII master[N];
vector<PII> servant[N];
int f[M];

int main() {
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        int v, w, q;
        cin >> v >> w >> q;
        // q是0的话，当前物品是主件
        if (!q) master[i] = {v, v * w};
        // 否则是附件，价格是v，收益是v * w
        else servant[q].push_back({v, v * w});
    }

    for (int i = 1; i <= n; i++) 
        for (int j = m; j >= 0; j--) {
            auto &sv = servant[i];
            for (int k = 0; k < 1 << sv.size(); k++) {
                int v = master[i].first, w = master[i].second;
                for (int u = 0; u < sv.size(); u++)
                    if (k >> u & 1) {
                        v += sv[u].first;
                        w += sv[u].second;
                    }
                    
                if (j >= v) f[j] = max(f[j], f[j - v] + w);
            }
        }

    cout << f[m] << endl;

    return 0;
}