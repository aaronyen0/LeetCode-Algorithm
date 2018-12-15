//若是想進一步加速，又不在意空間的話
//一種可行的方法是擴張hashTable size，變成int hashTable[27 + 'a']
//資料可以直接儲存在hashTable[order[i]]，這樣就不用每次查找前都減'a'了

bool isAlienSorted(char** words, int wordsSize, char* order) {
    int hashTable[26], n = wordsSize - 1;
    for(int i = 0; i < 26; ++i){
        hashTable[order[i] - 'a'] = i;
    }
    
    if(n < 1){
        return true;
    }
    char *str0, *str1;
    
    for(int i = 0; i < n; ++i){
        str0 = words[i];
        str1 = words[i + 1];
        while(1){
            if(*str0 == 0){
                break;
            }else if(*str1 == 0){
                return false;
            }else if(hashTable[*str0 - 'a'] < hashTable[*str1 - 'a']){
                break;
            }else if(hashTable[*str0 - 'a'] > hashTable[*str1 - 'a']){
                return false;
            }
            ++str0;
            ++str1;
        }
    }
    return true;
}

/*
bool isAlienSorted(char** words, int wordsSize, char* order) {
    int hashTable[26], n = wordsSize - 1, flag;
    for(int i = 0; i < 26; ++i){
        hashTable[order[i] - 'a'] = i;
    }
    
    if(n < 1){
        return true;
    }
    char *str0, *str1;
    
    for(int i = 0; i < n; ++i){
        flag = 0;
        str0 = words[i];
        str1 = words[i + 1];
        while(*str0 && *str1){
            if(hashTable[*str0 - 'a'] < hashTable[*str1 - 'a']){
                flag = 1;
                break;
            }else if(hashTable[*str0 - 'a'] > hashTable[*str1 - 'a']){
                return false;
            }else{
                ++str0;
                ++str1;
            }
        }
        //根據if有2種到這個位置的方式
        //1.str0 < str1
        //2.str0或str1其中一個結束了(else)
        //其中case2需要做額外判斷是否是str1比str0早結束所以多判斷flag
        //後來想想有點多餘，變成上面那個版本
        if(flag == 0 && *str0){
            return false;
        }
    }
    
    return true;
}
*/
