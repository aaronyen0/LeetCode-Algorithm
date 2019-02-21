/**
 * 給一個句子
 * 找出最後一個字的長度
 * 字不包含空白字元 ' '
 * 另外句子可以有很多空白字元 "abc  defg   "
 */

/**
 * version3, 4ms, 23%
 * 改成用倒退找最後一個出現的字
 * 可是C沒有辦法事先知道字串長度
 * 所以要一個個數，也沒比較快
 * 本來寫得稍微複雜，後來參考別人的改寫一些小地方
 * 這個寫法的精隨在 else if(cnt)，可以省略很多判斷
 */
 
int lengthOfLastWord(char* s) {
    int idx = 0, cnt = 0;
    while(s[idx++]);
    idx -= 2;
    
    while(idx >= 0){
        if(s[idx--] != ' '){
            ++cnt;
        }else if(cnt){
            return cnt;
        }
    }
    return cnt;
}

/**
 * version2, 4ms, 23%
 * 紀錄 (idx - offset) 改成紀錄 (cnt++) 而已
 * 另外參考ver3寫法，稍微修改了判斷式
 * 要一直++，可能反而沒ver1快
 */

int lengthOfLastWord(char* s) {
    int lastCnt = 0, crtCnt = 0;
    for(int i = 0; s[i] != 0; ++i){
        if(s[i] != ' '){
            ++crtCnt;
        }else if(crtCnt){
            lastCnt = crtCnt;   
            crtCnt = 0;
        }
    }
    if(crtCnt){
        return crtCnt;
    }
    return lastCnt;
}

/**
 * version1, 4ms, 23%
 * 直覺的寫法
 */

int lengthOfLastWord(char* s) {
    int offset = 0, idx = 0, lastWord = 0;
    while(s[idx]){
        //printf("idx = %d\n", idx);
        if(s[idx] == ' '){
            if(idx > offset){
                lastWord = idx - offset;    
            }
            offset = idx + 1;
        }
        ++idx;
    }
    if(idx > offset){
        return idx - offset;    
    }
    return lastWord;
}
