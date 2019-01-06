/**
 *這題題目沒講字元的範圍，本來以為只有小寫，看測試才知道各種ascii符號也都可以
 *這題用hashtable紀錄當前字串有哪些數字
 *offset代表當前字串的頭，i代表當前字串的尾，len代表當前字串長度
 *隨著i向後檢查，只分兩種情況：
 *1.若s[i]不在當前字串中，則更新table及len
 *2.若s[i]已在當前字串中，則offset往後推到不跟s[i]重複為止，並將中途路過的s[offset]從table中拿掉
 *
 *另外更新maxLen只在兩個地方
 *1.發現s[i]重複的時候，在不重複的情境中，len必然越來越大，毋須多花成本去檢查
 *2.return之前，因為離開while時的最後一筆字串沒有人檢查過
 */

int lengthOfLongestSubstring(char* s) {
    int table[256] = {0};
    int len = 0, maxLen = 0;
    int i = 0, offset = 0;
    
    while(s[i]){
        if(table[s[i]] == 0){
            table[s[i]] = 1;
            ++len;
        }else{
            if(len > maxLen){
                maxLen = len;
            }
            
            while(s[offset] != s[i]){
                table[s[offset++]] = 0;
                --len;
            }
            ++offset;
        }
        ++i;
    }
    
    if(len > maxLen){
        return len;
    }    
    return maxLen;
}
