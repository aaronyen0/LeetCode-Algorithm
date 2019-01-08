/**
 *Your are given an array of positive integers nums.
 *Count and print the number of (contiguous) subarrays where the product of all the elements in the subarray is less than k.
 */

//發現自己構思題目容有一個盲點，很少會逆著想問題
//真的要謹記在心

//連續寫了三個版本，這個版本是參考別人寫的
//解法重點在i和offset的關係，和我自己設想的方式有點像，每次i只進一格，讓offset往後追
//很多需要判斷式的地方就輕易被解決了!!
//offset和i代表著當前集合的最左邊和最右邊index
//若這個集合的乘積<k
//代表從i開始往「左邊」共有(i-offset+1)個「新集合」可以滿足答案(注意每個集合都包含第i個數字)
int numSubarrayProductLessThanK(int* nums, int numsSize, int k) {
    int count = 0, crt = nums[0], offset = 0;
    if(crt < k){
        ++count;
    }
    
    for(int i = 1; i < numsSize; ++i){
        crt *= nums[i];
        while(crt >=k && offset < i){
            crt /= nums[offset++];
        }
        if(crt < k){
            count += (i - offset + 1);
        }
    }
    
    return count;
}

//我的構想，i一口氣前進到極限(crt >= k)，然後每次offset只進一格
//計算時從offset出發加到i
//若offset==i，基本上代表第i個數字就已經超過k，因此跳到下一格
//速度比上面略慢一些，判斷式比較多且又算兩次crt * nums[i]
//有嘗試將內層while條件優化，發現bug特別多放棄了
int numSubarrayProductLessThanK2(int* nums, int numsSize, int k) {
    int count = 0, crt = 1, offset = 0, i = 0;
    while(offset < numsSize){
        while(i < numsSize && crt * nums[i] < k){
            crt *= nums[i++];
        }
        
        if(crt < k){
            count += i - offset;
        }
        
        if(offset == i){
            ++i;
            crt = 1;
            offset = i;
        }else{
            crt /= nums[offset++];    
        }
    }
    return count;
}



/*
//Time Limit Exceeded
int numSubarrayProductLessThanK(int* nums, int numsSize, int k) {
    int count = 0, N = numsSize - 1, tmp;
    int passNum;
    int* buffer = (int*)malloc(sizeof(int) * numsSize);
    
    for(int i = 0; i < numsSize; ++i){
        if(nums[i] >= k){
            buffer[i] = k;
        }else{
            buffer[i] = nums[i];
            ++count;
        }
    }
    
    for(int i = 1; i < numsSize; ++i, --N){
        passNum = 0;
        for(int j = 0; j < N; ++j){
            if(buffer[j] >= k || nums[j + i] >= k){
                buffer[j] = k;
            }else{
                tmp = buffer[j] * nums[j + i];
                if(tmp >=k || tmp < 0){
                    buffer[j] = k;
                }else{
                    buffer[j] = tmp;
                    count++;
                    ++passNum;
                }
            }
        }
        if(!passNum){
            return count;
        }
    }
    return count;
}

//Memory Limit Exceeded
/*
int numSubarrayProductLessThanK(int* nums, int numsSize, int k) {
    int count = 0, N = numsSize - 1, tmp;
    int** buffer = (int**)malloc(sizeof(int*) * numsSize);
    for(int i = 0; i < numsSize; ++i){
        buffer[i] = (int*)malloc(sizeof(int) * numsSize);
    }
    
    for(int i = 0; i < numsSize; ++i){
        if(nums[i] >= k){
            buffer[0][i] = k;
        }else{
            buffer[0][i] = nums[i];
            ++count;
        }
    }
    
    for(int i = 1; i < numsSize; ++i, --N){
        for(int j = 0; j < N; ++j){
            if(buffer[i - 1][j] >= k || buffer[0][j + i] >= k){
                buffer[i][j] = k;
            }else{
                tmp = buffer[i - 1][j] * buffer[0][j + i];
                if(tmp >=k || tmp < 0){
                    buffer[i][j] = k;
                }else{
                    buffer[i][j] = tmp;
                    count++;
                }
            }
        }
    }
    return count;
}
