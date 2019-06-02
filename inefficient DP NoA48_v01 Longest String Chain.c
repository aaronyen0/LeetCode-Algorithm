/**
 * 給一個字串集
 * 從中挑出一個有序集合
 * 該集合要滿足word1 is a predecessor of word2
 * 意思就是word1當中插入一個字元就可以等同word2
 * 找出所有可行有序集合的最長解
 */


/**
 * version1, 28ms, beats 86%
 * 1. 依照word的長度排序重排
 * 2. 定義dp[i]為，到字串i為止最長的predecessor集合
 * 做法等同於最長遞增子陣列
 */

int CheckPredecessor(char* word1, char* word2);

int longestStrChain(char ** words, int wordsSize){
    int k, q;
    int res = 1;
    int counting[17] = {0};
    int offset[17] = {0}; //重排wrods[i]用的，需要知道該擺在哪個位置
    int* dp = (int*)malloc(wordsSize * sizeof(int));
    char** sortWords = (char**)malloc(wordsSize * sizeof(char*)); //存放排序好的字串集
    int* wordLen = (int*)malloc(wordsSize * sizeof(int)); //存放美個字串的長度
    
    //counting sort
    for(int i = 0; i < wordsSize; ++i){
        wordLen[i] = strlen(words[i]);
        counting[wordLen[i]]++;
    }
    for(int i = 2; i < 17; ++i){
        offset[i] = offset[i - 1] + counting[i - 1];
    }
    
    for(int i = 0; i < wordsSize; ++i){
        sortWords[offset[wordLen[i]]++] = words[i];
    }
    
    k = 1;
    q = 0;
    while(k < 17){
        for(int i = 0; i < counting[k]; ++q, ++i){
            wordLen[q] = k;
        }
        ++k;
    }

    //類似最長遞增子陣列
    for(int i = 0; i < wordsSize; ++i){
        dp[i] = 1;
        for(int j = 0; j <= i; ++j){
            if(wordLen[j] + 1 != wordLen[i] || CheckPredecessor(sortWords[j], sortWords[i]) == -1){
                continue;
            }
            if(dp[j] >= dp[i]){
                dp[i] = dp[j] + 1;
            }
        }
    }
    
    for(int i = 0; i < wordsSize; ++i){
        if(dp[i] > res){
            res = dp[i];
        }
    }
    
    return res;
}

int CheckPredecessor(char* word1, char* word2){
    int l = 0, r = 0, diff = 0;
    while(*word1){
        if(*word1 != *word2){
            word2++;
            if(++diff > 1){
                return -1;
            }
            continue;
        }
        word1++;
        word2++;
    }
    return 1;
}
