#include <iostream>
#include <cstring>
using namespace std;

const int N = 100010;
int n, m;
int w[N];
struct Node {
    int l, r;
    long sum, add;
} tr[4 * N];

void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void pushdown(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.add) {
        left.add += root.add, left.sum += (long) (left.r - left.l + 1) * root.add;
        right.add += root.add, right.sum += (long) (right.r - right.l + 1) * root.add;
        root.add = 0;
    }
}

void build(int u, int l, int r) {
    if (l == r) tr[u] = {l, r, w[l], 0};
    else {
        tr[u] = {l, r};
        int mid = l + (r - l >> 1);
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int l, int r, int d) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].sum += (long) (tr[u].r - tr[u].l + 1) * d;
        tr[u].add += d;
    } else {
        pushdown(u);
        int mid = tr[u].l + (tr[u].r - tr[u].l >> 1);
        if (l <= mid) modify(u << 1, l, r, d);
        if (r > mid) modify(u << 1 | 1, l, r, d);
        pushup(u);
    }
}

long query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;

    pushdown(u);
    int mid = tr[u].l + (tr[u].r - tr[u].l >> 1);
    long sum = 0;
    if (l <= mid) sum += query(u << 1, l, r);
    if (r > mid) sum += query(u << 1 | 1, l, r);
    return sum;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);

    build(1, 1, n);
    while (m--) {
        char op[2];
        int l, r, d;
        scanf("%s%d%d", op, &l, &r);
        if (op[0] == 'C') {
            cin >> d;
            modify(1, l, r, d);
        } else printf("%ld\n", query(1, l, r));
    }
    
    return 0;
}