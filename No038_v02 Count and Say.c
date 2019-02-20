/**
 * 1 >> 1個1 >> 11
 * 11 >> 2個1 >> 21
 * 21 >> 1個2 1個1 >> 1211
 * 1211 >> 1個1 1個2 2個1 >> 111221
 * ...回傳第n個字串
 */

/*
 * version2, 4ms, 33%
 * 其實跟第一版一樣，只是變成指標版本，leetcode自從加入memory用量判斷後，似乎連計時也變慢了
 * 看大家的寫法都差不多
 * ps. 4463 為 n = 30 的buffer長度
 */

char* countAndSay(int n) {    
    char* buf1 = (char*)malloc(sizeof(char) * 4463);
    char* buf2 = (char*)malloc(sizeof(char) * 4463);
    char* swap, *pre, *crt;
    char crtNum;
    int cnt, len;
    
    pre = buf1;
    crt = buf2;
    
    pre[0] = '1';
    pre[1] = 0;
    for(int i = 2; i <= n; ++i){
        len = 0;
        cnt = 0;
        crtNum = pre[0];
        do{
            if(crtNum == *pre){
                ++cnt;
            }else{
                *crt++ = cnt + '0';
                *crt++ = crtNum;
                cnt = 1;
                crtNum = *pre;
            }
        }while(*++pre);
        *crt++ = cnt + '0';
        *crt++ = crtNum;
        *crt = 0;

        swap = buf1;
        buf1 = buf2;
        buf2 = swap;
        pre = buf1;
        crt = buf2;
    }
    return pre;
}

/*
 * version1, 4ms, 33%
 * 沒什麼特別的，就是照規則做
 * 除了buffer異常的大
 */

char* countAndSay(int n) {    
    char* crt = (char*)malloc(sizeof(char) * 8192);
    char* pre = (char*)malloc(sizeof(char) * 8192);
    char* swap;
    char tmp;
    pre[0] = '1';
    pre[1] = 0;
    
    int offset, cnt;
    for(int i = 2; i <= n; ++i){
        //printf("pre = %s\n", pre);
        offset = 0;
        cnt = 1;
        tmp = pre[0];
        for(int j = 1; pre[j] != 0; ++j){
            //printf("tmp = %c, pre[%d] = %c\n", tmp, j, pre[j]);
            if(pre[j] != tmp){
                crt[offset++] = cnt + '0';
                crt[offset++] = tmp;
                tmp = pre[j];
                cnt = 1;
            }else{
                ++cnt;
            }
        }
        crt[offset++] = cnt + '0';
        crt[offset++] = tmp;
        crt[offset] = 0;
        
        swap = crt;
        crt = pre;
        pre = swap;
        
    }
    return pre;
}
