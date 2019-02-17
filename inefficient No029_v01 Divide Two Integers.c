/**
 * 不用乘除或是餘數計算除法
 */
 
 
 
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
