#include <iostream>
#include <queue>
using namespace std;

int n;
priority_queue<int> max_heap;
priority_queue<int, vector<int>, greater<int>> min_heap;

void adjust() {
  if (min_heap.size() > max_heap.size()) {
    max_heap.push(min_heap.top());
    min_heap.pop();
  } else if (min_heap.size() + 1 < max_heap.size()) {
    min_heap.push(max_heap.top());
    max_heap.pop();
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    if (max_heap.empty() || x <= max_heap.top()) max_heap.push(x);
    else min_heap.push(x);
    adjust();
    if (i & 1) printf("%d\n", max_heap.top());
  }
}