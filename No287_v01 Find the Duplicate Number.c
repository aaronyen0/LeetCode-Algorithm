//這題的題目有設計過，而且保證數字是正的
//所以就是把原始的陣列當hashTable用而已，轉成負號代表已經記錄過一次

int Abs(int x){
    if(x < 0){
        return -x;
    }
    return x;
}

int findDuplicate(int* nums, int numsSize) {
    int tmp;
    for(int i = 0; i < numsSize; ++i){
        tmp = Abs(nums[i]);
        if(nums[tmp] < 0){
            return tmp;
        }else{
            nums[tmp] = -nums[tmp];
        }
    }
    return -1;
}
