//又是一個DP問題
//同樣沒有想出來

//看大家的做法基本上都差不多
//將前一筆的maxProduct和minProduct，各自乘上nums[i]後和nums[i]比大小決定最新的max及min

/*
簡易歸納法：
定義max[i]為從index從k(<= i)開始乘到包含nums[i]的最大乘積，min[i]同理

max[0] = nums[0]確實是包含nums[0]的當前最大值
min[0] = nums[0]確實是包含nums[0]的當前最小值

假設包含nums[i-1]乘積中，我們都有max[i - 1]及min[i - 1]
對任意新加入的nums[i] (nums[i]可正可負也可以是0)
max[i]勢必為 MAX3(max[i - 1] * nums[i], min[i - 1] * nums[i], nums[i])
min[i]勢必為 MIN3(max[i - 1] * nums[i], min[i - 1] * nums[i], nums[i])
*/

int maxProduct(int* nums, int numsSize) {
    int max = nums[0], min = nums[0], res = nums[0];
    int tmp1, tmp2;
    for(int i = 1; i < numsSize; ++i){
        tmp1 = nums[i] * max;
        tmp2 = nums[i] * min;
        
        //更新當前的max和min
        if(tmp1 > tmp2 && tmp1 > nums[i]){
            max = tmp1;
            if(tmp2 > nums[i]){
                min = nums[i];
            }else{
                min = tmp2;
            }
        }else if(tmp2 > nums[i]){
            max = tmp2;
            if(tmp1 > nums[i]){
                min = nums[i];
            }else{
                min = tmp1;
            }
        }else{
            max = nums[i];
            if(tmp1 > tmp2){
                min = tmp2;
            }else{
                min = tmp1;
            }
        }
        
        if(max > res){
            res = max;
        }
    }
    
    return res;
}
