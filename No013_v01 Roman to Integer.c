/**
 * 羅馬數字換成整數
 * 麻煩點一樣是4或9的規則
 */


/**
 * version1, beats 100%
 * 構思一樣是往下加不回頭
 * 但是每次加之前要檢查當前文字代表的數字，是否比前一輪的數字大
 * 較大代表遇到4或9的情況
 * 將前一輪的值倒扣並加上這個數字
 */
int romanToInt(char* s) {
    int table[26], i = 0, preNum = 0, crtNum, sum = 0;
    table['I' - 'A'] = 1;
    table['V' - 'A'] = 5;
    table['X' - 'A'] = 10;
    table['L' - 'A'] = 50;
    table['C' - 'A'] = 100;
    table['D' - 'A'] = 500;
    table['M' - 'A'] = 1000;
    
    while(s[i]){
        crtNum = table[s[i] - 'A'];
        if(crtNum > preNum){
            sum -= 2 * preNum;
        }
        sum += crtNum;
        
        preNum = crtNum;
        ++i;
    }
    return sum;
}
