/**
 * 給一個用陣列呈現的數字
 * 將這個數字加上1之後回傳 (同樣以陣列表達)
 */
 
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

/**
 * version1, 4ms, beats 47%
 * 寫法有兩個要點
 * 1.一開始配的記憶體+1，若到時候用不到則將指標往後推一格回傳就好
 * 2.若數字1，在這個位置不會進位的話，代表之後都沒有進位問題，可以直接複製
 */

int* plusOne(int* digits, int digitsSize, int* returnSize) {
    int* res = (int*)malloc(sizeof(int) * (digitsSize + 1));
    int one = 1;
    int i = digitsSize - 1, j = digitsSize;
	
	//只要進入if代表持續進位，但只要進入else就跳出這個迴圈，用途在減少每次迴圈都要做的判斷運算
    while(i >= 0){
        if(one && digits[i] == 9){
            res[j] = 0;
            --i;
            --j;
        }else{
            res[j] = digits[i] + 1;
            one = 0;
            --i;
            --j;
            break;
        }
    }
	
	//若程式跑到這裡還要進位，代表digits檢查完畢且前面每個數字都進位，也就是99999...，則+1之後變成100000...
    if(one){
        res[j] = 1;
        *returnSize = digitsSize + 1;
        return res;
    }
    
	//若程式跑到這邊，則將剩餘的數字複製至res中
    while(i >= 0){
        res[j--] = digits[i--];
    }
    *returnSize = digitsSize;
    return &res[1];
}
