/**
 * 將陣列中不是val的數字擺到陣列前面
 * 並回傳不是val的數字有幾個
 * 限制要in-place
 */
 
/**
 * verions1, 0ms, beats 100%
 * 想法類似quicksort
 * i從左開始慢慢找val，j從右開始慢慢找不是val的值
 * 若兩邊都有找到，就把j對應的數字蓋到i那格
 */

int removeElement(int* nums, int numsSize, int val) {
    if(!numsSize){
        return 0;
    }
    int i = 0, j = numsSize - 1;
    while(i <= j){
        while(i < j && nums[i] != val){
            ++i;
        }
        while(i < j && nums[j] == val){
            --j;
        }
        if(i >= j){
            if(nums[i] == val){
                return i;
            }
            return i + 1;
        }
        nums[i] = nums[j--];
        
    }
    return i + 1;
}
