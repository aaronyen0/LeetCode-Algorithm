/**
 *參考別人寫法
 *核心思想跟我的不太一樣
 *1.先找到跟s[i]重複的字元
 *2.再從重複的字元之外開始往兩側掃
 *這樣就沒有所謂的兩個case，大家都是同一個case
 *另外string長度的計算方法也有改善，顯得更通用(而且對前一版本也適用)
 *但是依舊只有 beat 89%
 */

char* longestPalindrome(char* s) {
    int i, j, k, size, maxLen = 0, tmpLen, maxOffset;
    char* res;
    
    for(size = 0; s[size] != 0; ++size);
    res = malloc(sizeof(char) * (size + 1));

    for(int i = 0; i < size; ++i){
        //找到跟s[i]重複的字元
        k = i;
        while(k < size && s[i] == s[k]){
            ++k;
        }        
        j = i - 1;
        
        //從重複的字元之外開始往兩側掃
        while(j >= 0 && k < size && s[j] == s[k]){
            --j;
            ++k;
        }
        tmpLen = k - j - 1;
        if(tmpLen > maxLen){
            maxLen = tmpLen;
            maxOffset = j + 1;
        }
    }
    
    memcpy(res, &s[maxOffset], maxLen);
    res[maxLen] = 0;
    return res;
}


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
