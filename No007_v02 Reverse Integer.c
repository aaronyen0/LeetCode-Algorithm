//多數人的寫法，不過怎麼跑都無法8ms
int reverse(int x) {
    long int sum = 0;

    while(x){
        sum = sum * 10 + x % 10;
        x /= 10;
    }
    
    if(sum < INT_MIN || sum >INT_MAX){
        return 0;
    }
    return sum;
}

/**
 *看一下別人寫的才發現負數取餘數的規則，例如 -99 % 10 = -4
 *所以省略了一些正負數的判斷式
 *但也因此gap判斷式多了一個條件，這樣看來未必划算
 *
 *另外多數人sum的型態是long int，因此不怕溢位，在return前檢查一次就行了
 *前一版我其實也有想過這件事情
 *但曾經在某一題發現到leetcodc的64bit數字運算的耗時很高，所以構思上盡量避免使用它
 */

int reverse(int x) {
    int sum = 0;
    int gap1 = INT_MAX / 10;
    int gap2 = INT_MIN / 10;
    
    while(x){
        if(sum > gap1 || sum < gap2){
            return 0;
        }
        
        sum = 10 * sum + (x % 10);
        x /= 10;
    }
    
    return sum;
}

/**
 *覺得寫得有點醜
 *大致上要小心一些事情
 *1.reverse的時候溢位
 *2.二補數int的範圍[-2^31, 2^31 - 1]，最小值直接取正就溢位了，剛好該值反轉也會溢位，總之個人直接視為特例處理
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
