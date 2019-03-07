/**
 * 給兩個二進位數字(用字串表達)
 * 回傳相加後的二進位結果(也用字串表達)
 */
 
/**
 * version1, 4ms, beats 53%
 * 沒什麼特殊的解法
 * 就照著進位規則做
 * 注意最後的字串是否多一個1就好
 */

char* addBinary(char* a, char* b) {
    int n1 = 0, n2 = 0, one = 0, tmp, i;
    char* res;
    
    while(a[n1++]);
    while(b[n2++]);
    
    if(n1 > n2){
        res = (char*)malloc(sizeof(char) * (n1 + 1));
        i = n1;
    }else{
        res = (char*)malloc(sizeof(char) * (n2 + 1));
        i = n2;
    }
    res[i--] = 0;
    n1 -= 2;
    n2 -= 2;
    
    while(n1 >= 0 && n2 >= 0){
        tmp = a[n1] + b[n2] + one;
        //printf("%d\n", tmp);
        if(tmp == 96){
            one = 0;
            res[i--] = '0';
        }else if(tmp == 97){
            one = 0;
            res[i--] = '1';
        }else if(tmp == 98){
            one = 1;
            res[i--] = '0';
        }else{
            one = 1;
            res[i--] = '1';
        }
        --n1;
        --n2;
    }
    
    while(n1 >= 0){
        tmp = a[n1] + one;
        if(tmp == 48){
            res[i--] = '0';
            one = 0;
        }else if(tmp == 49){
            res[i--] = '1';
            one = 0;
        }else{
            res[i--] = '0';
        }
        --n1;
    }
    while(n2 >= 0){
        tmp = b[n2] + one;
        if(tmp == 48){
            res[i--] = '0';
            one = 0;
        }else if(tmp == 49){
            res[i--] = '1';
            one = 0;
        }else{
            res[i--] = '0';
        }
        --n2;
    }
    if(one){
        res[0] = '1';
        return res;
    }
    return res + 1;
}
