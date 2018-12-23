int maxProduct(char** words, int wordsSize) {
    int* table = (int*)calloc(wordsSize, sizeof(int));
    int* counter = (int*)calloc(wordsSize, sizeof(int));
    int map[26], one = 1, maxNum = 0, tmp;
    char* str;
    
    //table[i]代表第i個數字中，用到了哪一些字元，若該字串有某字元，其對應的位置(char - 'a')bit值為1
    //為了方便把bit拉為1，因此先製造一個map，例如map['c' - 'a'] = b,100
    for(int i = 0; i < 26; ++i){
        map[i] = one;
        one <<= 1;
    }
    
    //將每個字串的每個字元做紀錄到table上，並一邊紀錄該字串長度
    for(int i = 0; i < wordsSize; ++i){
        str = words[i];
        while(*str){
            table[i] |= map[(*str) - 'a'];
            ++str;
            counter[i]++;
        }
    }
    
    //任兩兩比較
    for(int i = 0; i < wordsSize; ++i){
        for(int j = i + 1; j < wordsSize; ++j){
            if((table[i] & table[j]) == 0){
                tmp = counter[i] * counter[j];
                if(tmp > maxNum){
                    maxNum = tmp;
                }
            }
        }
    }
    return maxNum;
}
