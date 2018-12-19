//0 <= 1 >= 2 <= 3 >= 4 <= 5 >= 6 ....

class Solution {
public:
    void wiggleSort(vector<int> &nums) {
        if (nums.size() <= 1) return;
        for (int i = 1; i < nums.size(); ++i) {
            //奇數位子不滿足代表 大 > 小 > 當前數字，swap(當前數字, 小)可以保持前面不等式滿足
            //偶數位子不滿足代表 小 < 大 < 當前數字，swap(當前數字, 大)可以保持前面不等式滿足
            if ((i % 2 == 1 && nums[i] < nums[i - 1]) || (i % 2 == 0 && nums[i] > nums[i - 1])) {
                swap(nums[i], nums[i - 1]);
            }
        }
    }
};
