/**
 * 給一個以排序的陣列及一個target
 * 回傳target再陣列中的位置
 * 若找不到則回傳要插入在哪個位置
 */

/**
 * version2, 4ms, 21%
 * 小心binary search的while(l <= r)裡面有包含等於
 * 怎麼交都是4ms，不過看不出來跟0ms程式差在哪，應該只是誤差而已
 */

int searchInsert(int* nums, int numsSize, int target) {
    int l = 0, r = --numsSize, mid;
	
    while(l <= r){
        mid = (l + r) >> 1;
        
        if(target > nums[mid]){
            l = ++mid;
        }else if(target < nums[mid]){
            r = --mid;
        }else{
            return mid;
        }
    }
    return l;
}

/**
 * version1, 4ms, 21%
 * 就是binary search
 * 只有21%，不知道是哪裡浪費了時間
 */

int searchInsert(int* nums, int numsSize, int target) {
    int l = 0, r = numsSize - 1, mid;
    
    while(l < r){
        mid = (l + r) >> 1;
        if(target == nums[mid]){
            return mid;
        }else if(target < nums[mid]){
            r = mid - 1;
        }else{
            l = mid + 1;
        }
    }
    if(target <= nums[l]){
        return l;
    }else{
        return l + 1;
    }
}
