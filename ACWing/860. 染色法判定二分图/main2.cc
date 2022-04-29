#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int N = 1e5 + 10, M = 2 * N;
int n, m;
int h[N], e[M], ne[M], idx;
int p[N];

void add(int a, int b) {
  e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int find(int x) {
  if (x != p[x]) p[x] = find(p[x]);
  return p[x];
}

int main() {
  scanf("%d%d", &n, &m);
  memset(h, -1, sizeof h);
  while (m--) {
    int a, b;
    scanf("%d%d", &a, &b);
    add(a, b), add(b, a);
  }
  
  for (int i = 1; i <= n; i++) p[i] = i;
  
  bool res = true;
  for (int u = 1; u <= n; u++) {
    int t, pu = find(u);
    for (int j = h[u]; ~j; j = ne[j]) {
      int v = e[j], pv = find(v);
      if (pu == pv) {
        res = false;
        break;
      }
      if (j == h[u]) t = find(v);
      else p[pv] = t;
    }
  }
  
  if (res) puts("Yes");
  else puts("No");
  return 0;
}