#include <vector>
#include <deque>
using namespace std;

class Solution {
public:
  vector<int> maxInWindows(vector<int>& nums, int k) {
    vector<int> res;
    deque<int> dq;
    for (int i = 0; i < nums.size(); i++) {
      if (dq.size() && dq.front() <= i - k) dq.pop_front();
      while (dq.size() && nums[dq.back()] <= nums[i]) dq.pop_back();
      dq.push_back(i);
      if (i >= k - 1) res.push_back(nums[dq.front()]);
    }

    return res;
  }
};