/**
 * 不用乘除或是餘數計算除法
 */
 

/**
 * versio2, 16ms, beats 29%
 * 把table砍掉了，速度沒上升，不過減少了記憶體使用
 * 構思方向應該沒有問題，主要慢在64bit的運算
 * 不用64bit的話，會有一些例外處理(跟int範圍相關)
 * 若能列出所有例外，就能把INT64的運算改回INT32
 * 應該能進一步提速
 */ 
int divide(int dividend, int divisor) {    
    int sign = 0;
    long long int cnt = 0, tmpCnt = 1;
    long long int lDividend, lDivisor, tmpDivisor;
    
    if((dividend ^ divisor) < 0){
        sign = 1;
    }
    
    if(dividend < 0){
        lDividend = -(long long int)dividend;
    }else{
        lDividend = dividend;
    }
    
    if(divisor < 0){
        lDivisor = -(long long int)divisor;
    }else{
        lDivisor = divisor;
    }
    
    tmpDivisor = lDivisor;
    while(lDividend >= tmpDivisor){
        tmpCnt <<= 1;
        tmpDivisor <<= 1;
    }
    tmpDivisor >>= 1;
    tmpCnt >>= 1;
    
    while(tmpDivisor >= lDivisor){
        if(lDividend >=  tmpDivisor){
            cnt += tmpCnt;
            lDividend -= tmpDivisor;
        }
        tmpDivisor >>= 1;
        tmpCnt >>= 1;
    }
    
    if(sign){
        return -cnt;
    }
    if(cnt > INT_MAX){
        return INT_MAX;
    }
    return cnt;
}

/**
 * version1, 16ms, beats 29%
 * 不能乘除所以基本上能取代的運算就是shift
 * 建立表格tabe[i] = divisor * (2 ^ i)
 * 從大至小依序掃過表格便能加總除數
 */
int divide(int dividend, int divisor) {    
    int sign = 0, flag = 32;
    long long int cnt = 0;
    long long int lDividend, lDivisor;
    long long int table[33];
    long long int counter[33];
    
    if((dividend ^ divisor) < 0){
        sign = 1;
    }
    
    if(dividend < 0){
        lDividend = -(long long int)dividend;
    }else{
        lDividend = dividend;
    }
    
    if(divisor < 0){
        lDivisor = -(long long int)divisor;
    }else{
        lDivisor = divisor;
    }
    
    table[0] = lDivisor;
    counter[0] = 1;
    for(int i = 1; i < 33; ++i){
        table[i] = table[i - 1] << 1;
        counter[i] = counter[i - 1] << 1;
        
        if(table[i] > INT_MAX){
            flag = i;
            break;
        }
    }
    
    for(int i = flag; i >= 0; --i){
        if(lDividend >= table[i]){
            lDividend -= table[i];
            cnt += counter[i];
        }
    }
    if(sign){
        return -cnt;
    }
    if(cnt > INT_MAX){
        return INT_MAX;
    }
    return cnt;
}
