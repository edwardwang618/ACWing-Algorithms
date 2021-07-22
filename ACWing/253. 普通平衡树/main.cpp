#include <iostream>
#include <cstring>
using namespace std;

const int N = 100010, INF = 1e8;
int n;
struct Node {
    int l, r;
    int key, val;
    int cnt, size;
} tr[N];
int root, idx;

void pushup(int p) {
    tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + tr[p].cnt;
}

void zig(int &p) {
    int q = tr[p].l;
    tr[p].l = tr[q].r, tr[q].r = p, p = q;
    pushup(tr[p].r), pushup(p);
}

void zag(int &p) {
    int q = tr[p].r;
    tr[p].r = tr[q].l, tr[q].l = p, p = q;
    pushup(tr[p].l), pushup(p);
}

int get_node(int key) {
    tr[++idx].key = key;
    tr[idx].val = rand();
    tr[idx].cnt = tr[idx].size = 1;
    return idx;
}

void insert(int &p, int key) {
    if (!p) p = get_node(key);
    else if (tr[p].key > key) {
        insert(tr[p].l, key);
        if (tr[tr[p].l].val > tr[p].val) zig(p);
    } else if (tr[p].key < key) {
        insert(tr[p].r, key);
        if (tr[tr[p].r].val > tr[p].val) zag(p);
    } else tr[p].cnt++;

    pushup(p);
}

void remove(int &p, int key) {
    if (!p) return;
    if (tr[p].key > key) remove(tr[p].l, key);
    else if (tr[p].key < key) remove(tr[p].r, key);
    else {
        if (tr[p].cnt > 1) tr[p].cnt--;
        else if (tr[p].l || tr[p].r) {
            if (!tr[p].r || (!tr[p].l && tr[tr[p].l].val > tr[tr[p].r].val)) {
                zig(p);
                remove(tr[p].r, key);
            } else {
                zag(p);
                remove(tr[p].l, key);
            }
        } else p = 0;
    }

    pushup(p);
}

int get_rank_by_key(int p, int key) {
    if (!p) return 0;
    if (tr[p].key > key) return get_rank_by_key(tr[p].l, key);
    else if (tr[p].key < key) return tr[tr[p].l].size + tr[p].cnt + get_rank_by_key(tr[p].r, key);
    else return tr[tr[p].l].size + 1;
}

int get_key_by_rank(int p, int rank) {
    if (!p) return INF;
    if (tr[tr[p].l].size >= rank) return get_key_by_rank(tr[p].l, rank);
    else if (tr[tr[p].l].size + tr[p].cnt < rank) return get_key_by_rank(tr[p].r, rank - tr[tr[p].l].size - tr[p].cnt);
    else return tr[p].key;
}

int get_prev(int p, int key) {
    if (!p) return -INF;
    if (tr[p].key >= key) return get_prev(tr[p].l, key);
    return max(tr[p].key, get_prev(tr[p].r, key));
}

int get_next(int p, int key) {
    if (!p) return INF;
    if (tr[p].key <= key) return get_next(tr[p].r, key);
    return min(tr[p].key, get_next(tr[p].l, key));
}

int main() {
    scanf("%d", &n);
    while (n--) {
        int opt, x;
        scanf("%d%d", &opt, &x);
        if (opt == 1) insert(root, x);
        else if (opt == 2) remove(root, x);
        else if (opt == 3) printf("%d\n", get_rank_by_key(root, x));
        else if (opt == 4) printf("%d\n", get_key_by_rank(root, x));
        else if (opt == 5) printf("%d\n", get_prev(root, x));
        else if (opt == 6) printf("%d\n", get_next(root, x));
    }

    return 0;
}