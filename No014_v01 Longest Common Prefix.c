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
