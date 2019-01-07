/**
 *O(n^2) beat 77%，個人寫法檢查對稱由中心往兩邊擴張
 *有兩種對稱方式
 *1.長度為奇數的對稱，中心點為一個數字
 *2.長度為偶數的對稱，中心點為兩個數字
 */

char* longestPalindrome(char* s) {
    int i, j, k, size, maxLen = 0, tmpLen, maxOffset;
    char* res;
    
    //1.抓出字串全長
    for(size = 0; s[size] != 0; ++size);
    res = malloc(sizeof(char) * (size + 1));
    res[0] = 0;
    
    if(!size){
        return res;
    }
    
    //2.逐一更新中心點，往兩側檢查對稱
    for(int i = 0; i < size; ++i){
        
        //case1
        j = i - 1;
        k = i + 1;
        while(j >= 0 && k < size && s[j] == s[k]){
            --j;
            ++k;
        }
        tmpLen = 2 * (i - j) - 1;
        if(tmpLen > maxLen){
            maxLen = tmpLen;
            maxOffset = j + 1;
        }
        
        //case2
        j = i;
        k = i + 1;        
        while(j >= 0 && k < size && s[j] == s[k]){
            --j;
            ++k;
        }
        tmpLen = 2 * (i - j);
        if(tmpLen > maxLen){
            maxLen = tmpLen;
            maxOffset = j + 1;
        }
    }
    
    //3.最後再將最長的對稱子字串貼到res中
    memcpy(res, &s[maxOffset], maxLen);
    res[maxLen] = 0;
    return res;
}
