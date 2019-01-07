/**
 *題目規則有點多，可以是任意字串
 *1.數字從第一個「非空白」的字元開始計算
 *2.第一個非空白字元有可能是'+'或'-'
 *3.數字部分沒什麼好說的，在數字之後的任意字串都可以不理他
 *4.若第一個非空白字串非+-或是數字則回傳0
 *5.若數字超出Int32範圍[-2^32, 2^32 - 1]，則回傳INT_MIN或INT_MAX
 */

int myAtoi(char* str) {
    int i = 0, negativeFlag = 0;
    long int sum = 0;
    
    //1.略過空白
    while(str[i] == ' '){
        ++i;
    }
    
    //2.判斷首個非空白字元是否是+-號
    if(str[i] == '-'){
        negativeFlag = 1;
        ++i;
    }else if(str[i] == '+'){
        ++i;
    }
    
    //3.計算數字順便檢查有無溢位
    while(str[i] >= '0' && str[i] <= '9'){
        if(negativeFlag){
            sum = sum * 10 - (str[i] - '0');
            if(sum < INT_MIN){
                return INT_MIN;
            }
        }else{
            sum = sum * 10 + (str[i] - '0');
            if(sum > INT_MAX){
                return INT_MAX;
            }
        }
        ++i;
    }
    
    return sum;
}
