/**
 * 將數字換成羅馬數字
 * 麻煩的點在於4和9的規則較為特別
 */


/**
 * version1, beat100%
 * 若是直接取用下列的陣列寫法更簡單，不過有點過度取巧，於是寫了一個較通用的版本
 * int value[]    = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
 * char* romain[] = {"M", "CM", ...}
 *
 * 這版本做法為比對剩餘數字大小一直往右塞羅馬數字，而且沒有使用除法
 * 當發現塞了4個同樣的羅馬數字時
 * 判定遇到的數字到底是4還是9
 * 復歸元素陣列的idx到preOffset，重新將文字蓋掉成羅馬數字的4或9
 * 如：VIIII 覆寫為 IX
 * 如：IIII  覆寫為 IV
 */
char* intToRoman(int num) {
    int value[7]  = {1000, 500, 100 , 50 , 10 , 5  , 1  };
    char roman[7] = {'M' , 'D', 'C' , 'L', 'X', 'V', 'I'};
    char *res = (char*)malloc(20 * sizeof(char));
    int offset = 0, preOffset = 0, cnt = 0;
    for(int i = 0; i < 7;){
        if(num >= value[i]){
            res[offset++] = roman[i];
            num -= value[i];
            
            ++cnt;
        }else{
	    //進下一輪之前判別4,9並覆寫
            if(cnt == 4){
                if(offset == 4 || res[offset - 5] != roman[i - 1]){//判別為4
                    res[preOffset++] = roman[i];
                    res[preOffset++] = roman[i - 1];
                }else{//其餘判別為9
                    res[preOffset - 1] = roman[i];
                    res[preOffset++] = roman[i - 2];
                }
                offset = preOffset;
            }
            ++i;
            preOffset = offset;
            cnt = 0;
        }
    }
    res[offset] = 0;
    return res;    
}
