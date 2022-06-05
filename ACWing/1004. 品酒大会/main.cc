#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
using PLL = pair<long, long>;

const int N = 3e5 + 10;
const long INF = 2e18;
int n, m;
char s[N];
int sa[N], rk[N], y[N], c[N], he[N];
int w[N], p[N], sz[N];
long max1[N], max2[N], min1[N], min2[N];
vector<int> hs[N];
PLL res[N];

void get_sa() {
  for (int i = 1; i <= n; i++) c[rk[i] = s[i]]++;
  for (int i = 2; i <= m; i++) c[i] += c[i - 1];
  for (int i = n; i; i--) sa[c[rk[i]]--] = i;

  for (int k = 1; k < n; k <<= 1) {
    int num = 0;
    for (int i = n - k + 1; i <= n; i++) y[++num] = i;
    for (int i = 1; i <= n; i++) if (sa[i] > k) y[++num] = sa[i] - k;
    for (int i = 1; i <= m; i++) c[i] = 0;
    for (int i = 1; i <= n; i++) c[rk[i]]++;
    for (int i = 2; i <= m; i++) c[i] += c[i - 1];
    for (int i = n; i; i--) sa[c[rk[y[i]]]--] = y[i];
    swap(rk, y);
    rk[sa[1]] = num = 1;
    for (int i = 2; i <= n; i++)
      rk[sa[i]] = y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] ? num : ++num;
    if (num == n) break;
    m = num;
  }
}

void get_height() {
  for (int i = 1, k = 0; i <= n; i++) {
    if (rk[i] == 1) continue;
    if (k) k--;
    int j = sa[rk[i] - 1];
    while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
    he[rk[i]] = k;
  }
}

int find(int x) {
  if (p[x] != x) p[x] = find(p[x]);
  return p[x];
}

long get(int x) {
  return x * (x - 1l) / 2;
}

PLL cal(int r) {
  static long cnt = 0, maxv = -INF;
  for (auto x : hs[r]) {
    int a = find(x - 1), b = find(x);
    cnt -= get(sz[a]) + get(sz[b]);
    p[a] = b;
    sz[b] += sz[a];
    cnt += get(sz[b]);
    if (max1[a] >= max1[b]) {
      max2[b] = max(max1[b], max2[a]);
      max1[b] = max1[a];
    } else if (max1[a] > max2[b]) max2[b] = max1[a];
    if (min1[a] <= min1[b]) {
      min2[b] = min(min1[b], min2[a]);
      min1[b] = min1[a];
    } else if (min1[a] < min2[b]) min2[b] = min1[a];

    maxv = max(maxv, max(max1[b] * max2[b], min1[b] * min2[b]));
  }

  if (maxv == -INF) return {cnt, 0};
  else return {cnt, maxv};
}

int main() {
  scanf("%d", &n), m = 'z';
  scanf("%s", s + 1);
  for (int i = 1; i <= n; i++) scanf("%d", &w[i]);

  get_sa();
  get_height();
  for (int i = 2; i <= n; i++) hs[he[i]].push_back(i);

  for (int i = 1; i <= n; i++) {
    p[i] = i;
    sz[i] = 1;
    max1[i] = min1[i] = w[sa[i]];
    max2[i] = -INF, min2[i] = INF;
  }

  for (int i = n - 1; i >= 0; i--) res[i] = cal(i);
  for (int i = 0; i < n; i++) printf("%ld %ld\n", res[i].first, res[i].second);
}