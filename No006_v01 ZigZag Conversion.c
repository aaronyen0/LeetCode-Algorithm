/**
 * 給一個原始字串s, 及分割列數numRow
 * 將字串依照分割的列數以Z字型重排
 * 再將重排的後的字串，依照每一列出現的順序，複寫到新的字串上
 * ex: s = "abcdefghijklmnopq", rowNum = 4
 * row0 = "a   g   m"
 * row1 = "b  fh  ln"
 * row2 = "c e i k o q"
 * row3 = "d   j   p"
 * Z字形是從上而下開始看
 * newStr = "agmbfhlnceikoqdjp"
 * 從row0開始依序將字元填入新字串中
 */

/** 
 * version1, 100%
 * 雖然說是寫Z字形，也可以說是做很多三角形
 * 可以發現寫一組三角形需要消耗 (rowNum - 1) * 2個字元
 * 一個三角形的第一列和最後一列會消耗一個字元，其餘列會消耗兩個字元
 * 寫法基本上就是等差的加入新的字元
 * 只要小心消耗兩字元的等差條件就好
 *
 * ps. rowNum = 1並不滿足一個三角形消耗(rowNum - 1)*2的公式，因此需要特殊處理
 */

char* convert(char* s, int numRows) {
    char* res;
    int j, q, idx;
    int len = 0, delta;
    int halfGroup = numRows - 1, group = halfGroup << 1;
    
    while(s[len++]);
    res = (char*)malloc(sizeof(char) * len);
    res[--len] = 0;
    if(numRows == 1){
        memcpy(res, s, len);
        return res;
    }
    
    idx = 0;
    
    //i = 0
    for(j = 0; j < len; j += group){
        res[idx++] = s[j];
    }
    
    // i = 1 ~ halfRow
    delta = group;
    for(int i = 1; i < halfGroup; ++i){
        delta -= 2;
        for(j = i, q = i + delta; q < len; j += group, q += group){
            res[idx++] = s[j];
            res[idx++] = s[q];
        } 
        if(j < len){
            res[idx++] = s[j];
        }
    }
    
    // i = halfRow
    for(j = halfGroup; j < len; j += group){
        res[idx++] = s[j];
    }
    
    return res;
}
