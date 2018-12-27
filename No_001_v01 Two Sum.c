/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* twoSum(int* nums, int numsSize, int target) {
    int* res = (int*)malloc(sizeof(int) * 2);
    for(int i = 0; i < numsSize; ++i){
        for(int j = i + 1; j < numsSize; ++j){
            if(nums[i] + nums[j] == target){
                res[0] = i;
                res[1] = j;
                return res;
            }
        }    
    }
    return NULL;
}

//這是別人的寫法
//我也有一版跟這個很像，不過這個寫法顯然更精闢
//重點在這段 map[nums[i]-min] = ++i
//讓儲存的index至少從1開始，因此配記憶體時就能用calloc初始化為0
//我的寫法是 map[nums[i]-min] = i 因為i可以是0，所以配完記憶體還加一個迴圈將陣列初始化為-1
//另外明明配置記憶體一樣大，但是「我用malloc + for迴圈初始化」會遇到Memory Limit Exceeded的錯誤 (在min, max級距很大時)

int* twoSum2(int* nums, int numsSize, int target) {
    int i, max, min;
    max = min = nums[0];
    for(i = 0; i < numsSize; i++) {
        if(nums[i] > max) max = nums[i];
        if(nums[i] < min) min = nums[i];
    }
    
    int *map   = (int*)calloc((max-min+1), sizeof(int));
    int *reval = (int*)malloc(sizeof(int)*2);
    
    for(i = 0; i < numsSize; map[nums[i]-min] = ++i) {
        int lookfornum = target - nums[i];
        if(lookfornum < min || lookfornum > max) continue;
        int dis = lookfornum - min;
        if (map[dis]) {         
            reval[0] = i;
            reval[1] = map[dis] -1;
            break;
        }
    }
    
    return reval;
}
