char* reverseWords(char* s) {
    int offset = 0;
    int i = 0;
    while(s[i]){
        if(s[i] == ' '){
            StrInverse(&s[offset], &s[i - 1]);
            offset = i + 1;
        }
        ++i;
    }
    if(offset < i){
        StrInverse(&s[offset], &s[i - 1]);
    }
    return s;
}

void StrInverse(char* left, char* right){
    char tmp;
    while(left < right){
        tmp = *left;
        *left = *right;
        *right = tmp;
        ++left;
        --right;
    }
}
