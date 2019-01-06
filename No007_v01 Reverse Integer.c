/**
 *覺得寫得有點醜
 *大致上要小心一些事情
 *1.reverse的時候溢位
 *2.二補數int的負數最小值的絕對值比正數最大值來的大1，而且該值反轉會溢位，個人直接視為特例處理
 *beat 99.93% 如果有查到0.07%的人是怎麼寫得再來更新
 */

int reverse(int x) {
    int flag = 0, sum = 0;
    int gap = INT_MAX / 10;
    
    if(x < 0){
        if(x == 0x80000000){
            return 0;
        }
        flag = 1;
        x = -x;
    }
    
    while(x){
        if(sum > gap){
            return 0;
        }
        
        sum = 10 * sum + (x % 10);
        x /= 10;
    }
    
    if(flag){
        return -sum;
    }
    return sum;
}
