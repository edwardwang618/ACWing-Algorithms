#include <iostream>
using namespace std;

const int N = 500010;
int n, m;
int w[N];
struct Node {
    int l, r;
    int sum, lmax, rmax, tmax;
} tr[4 * N];

void pushup(Node &root, Node &l, Node &r) {
    root.sum = l.sum + r.sum;
    root.lmax = max(l.lmax, l.sum + r.lmax);
    root.rmax = max(r.rmax, r.sum + l.rmax);
    root.tmax = max(max(l.tmax, r.tmax), l.rmax + r.lmax);
}

void pushup(int u) {
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void build(int u, int l, int r) {
    if (l == r) tr[u] = {l, r, w[l], w[l], w[l], w[l]};
    else {
        tr[u] = {l, r};
        int m = l + (r - l >> 1);
        build(u << 1, l, m), build(u << 1 | 1, m + 1, r);
        pushup(u);
    }
}

int modify(int u, int x, int v) {
    if (tr[u].l == x && tr[u].r == x) tr[u] = {x, x, v, v, v, v};
    else {
        int m = tr[u].l + (tr[u].r - tr[u].l >> 1);
        if (x <= m) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);

        pushup(u);
    }
}

Node query(int u, int l, int r) {
    if (l <= tr[u].l && tr[u].r <= r) return tr[u];
    
    int m = tr[u].l + (tr[u].r - tr[u].l >> 1);
    if (r <= m) return query(u << 1, l, r);
    else if (l > m) return query(u << 1 | 1, l, r);
    else {
        Node left = query(u << 1, l, r), right = query(u << 1 | 1, l, r);
        Node res;
        pushup(res, left, right);
        return res;
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];
    build(1, 1, n);

    while (m--) {
        int k, x, y;
        cin >> k >> x >> y;
        if (k == 1) {
            if (x > y) swap(x, y);
            cout << query(1, x, y).tmax << endl;
        } else modify(1, x, y);
    }
    
    return 0;
}