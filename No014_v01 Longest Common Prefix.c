//有些題目會要求重配記憶體，但發現這題不用，所以蓋掉原本的陣列即可
char* longestCommonPrefix(char** strs, int strsSize) {
    if(strsSize == 0){
        return "";
    }
    int len, j;
    
    for(len = 0; strs[0][len] != 0; ++len);

       
    for(int i = 1; i < strsSize; ++i){
        for(j = 0; j < len && strs[i][j] != 0 && strs[0][j] == strs[i][j]; ++j);
        len = j;
        if(!len){
            break;
        }
    }
        
    strs[0][len] = 0;
    return strs[0];
}


char* longestCommonPrefix(char** strs, int strsSize) {
    if(strsSize == 0){
        return "";
    }
    int len, j;
    char* res;
    
    for(len = 0; strs[0][len] != 0; ++len);
    
    res = (char*)malloc(sizeof(char) * (len + 1));
    memcpy(res, strs[0], len + 1);
       
    for(int i = 1; i < strsSize; ++i){
        for(j = 0; j < len && strs[i][j] != 0 && res[j] == strs[i][j]; ++j);
        len = j;
        if(!len){
            break;
        }
    }
    
    res[len] = 0;
    return res;
}
