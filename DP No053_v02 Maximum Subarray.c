//DP真的需要多訓練
//這題寫概念是不斷儲存包含arr[i]的最大總和
//若往右邊移動的過程arr[i]就已經比crt + arr[i]來的大，當前包含arr[i]的最大和就是arr[i]
//若crt + arr[i] < arr[i]，則包含arr[i]的當前最大和就是相加

int maxSubArray(int* nums, int numsSize) {
    int crt = nums[0], maxNum = nums[0];
    for(int i = 1; i < numsSize; ++i){
        if(crt + nums[i] > nums[i]){
            nums[i] += crt;
        }
        crt = nums[i];
        
        if(nums[i] > maxNum){
            maxNum = nums[i];
        }
    }
    return maxNum;
}
