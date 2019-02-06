/**
 * 判斷字串needle是否為haystack的子字串
 * 是的話回傳子字串的位置
 * 不是回傳-1
 */

/**
 * version1, 4ms, beats 43%
 * 暴力解沒什麼好說的
 * 我知道有專門找subarray的優化方法
 * 應該是記錄重複的部分
 * 讓檢查的人能快速跳過
 * 之後再來研究
 */
 
int strStr(char* haystack, char* needle) {
    int nLen, hLen, j;
    for(nLen = 0; needle[nLen] != 0; ++nLen);
    if(nLen == 0){
        return 0;
    }
    
    for(hLen = 0; haystack[hLen] != 0; ++hLen);
    hLen -= nLen - 1;
    for(int i = 0; i < hLen; ++i){
        for(j = 0; j < nLen; ++j){
            if(haystack[j] != needle[j]){
                break;
            }
        }
        if(j == nLen){
            return i;
        }
        ++haystack;

    }
    return -1;
}
