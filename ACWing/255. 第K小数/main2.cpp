#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 1e5 + 10;
int n, m;
int a[N];
vector<int> nums;
struct Node {
    int l, r;
    int cnt;
} tr[(N << 2) + N * 17];
int root[N], idx;

int find(int x) {
    return lower_bound(nums.begin(), nums.end(), x) - nums.begin();
}

int build(int l, int r) {
    int p = ++idx;
    if (l == r) return p;
    int mid = l + (r - l >> 1);
    tr[p].l = build(l, mid), tr[p].r = build(mid + 1, r);
    return p;
}

int insert(int p, int l, int r, int x) {
    int q = ++idx;
    int res = q;
    while (l < r) {
        tr[q] = tr[p];
        tr[q].cnt++;
        int mid = l + (r - l >> 1);
        if (x <= mid) {
            tr[q].l = ++idx;
            q = tr[q].l, p = tr[p].l;
            r = mid;
        } else {
            tr[q].r = ++idx;
            q = tr[q].r, p = tr[p].r;
            l = mid + 1;
        }
    }

    tr[q].cnt++;
    return res;
}

int query(int q, int p, int l, int r, int k) {
    if (l == r) return l;
    int cnt = tr[tr[q].l].cnt - tr[tr[p].l].cnt;
    int mid = l + (r - l >> 1);
    if (k <= cnt) return query(tr[q].l, tr[p].l, l, mid, k);
    else return query(tr[q].r, tr[p].r, mid + 1, r, k - cnt);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        nums.push_back(a[i]);
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    root[0] = build(0, nums.size() - 1);
    for (int i = 1; i <= n; i++)
        root[i] = insert(root[i - 1], 0, nums.size() - 1, find(a[i]));

    while (m--) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", nums[query(root[r], root[l - 1], 0, nums.size() - 1, k)]);
    }

    return 0;
}