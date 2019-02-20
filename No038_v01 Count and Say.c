/**
 * 1 >> 1個1 >> 11
 * 11 >> 2個1 >> 21
 * 21 >> 1個2 1個1 >> 1211
 * 1211 >> 1個1 1個2 2個1 >> 111221
 * ...回傳第n個字串
 */

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
