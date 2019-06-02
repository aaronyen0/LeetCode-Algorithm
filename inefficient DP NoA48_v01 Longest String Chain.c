/**
 * 給一個字串集
 * 從中挑出一個有序集合
 * 該集合要滿足word1 is a predecessor of word2
 * 意思就是word1當中插入一個字元就可以等同word2
 * 找出所有可行有序集合的最長解
 */


/**
 * version2, 16ms, beats 95%
 * 剪枝
 * 由於我的排序是counting sort，而且過程中設計一個陣列專門用來存offset
 * 所以根本就知道長度-1的字串的起訖點
 * 可以減少很多if判斷
 */
 
int CheckPredecessor(char* word1, char* word2);

int longestStrChain(char ** words, int wordsSize){
    int k, q, tmpMax, tmpLen;
    int res = 1;
    int counting[17] = {0};
    int offset[17] = {0};
    int* dp = (int*)malloc(wordsSize * sizeof(int));
    char** sortWords = (char**)malloc(wordsSize * sizeof(char*));
    int* wordLen = (int*)malloc(wordsSize * sizeof(int));
    //int* sortLen = (int*)malloc(wordsSize * sizeof(int));
    
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
        //sortLen[offset[wordLen[i]]++] = wordLen[i];
    }
    k = 1;
    q = 0;
    while(k < 17){
        for(int i = 0; i < counting[k]; ++q, ++i){
            wordLen[q] = k;
        }
        ++k;
    }

    //類似最大子陣列寫法
    for(int i = 0; i < wordsSize; ++i){
        if(wordLen[i] == 1){
           dp[i] = 1;
            continue;
        }
        
        tmpMax = 1;
        tmpLen = wordLen[i];
        for(int j = offset[tmpLen - 2]; j < offset[tmpLen - 1]; ++j){ //剪枝
            if(CheckPredecessor(sortWords[j], sortWords[i]) == -1){
                continue;
            }
            if(dp[j] >= tmpMax){
                tmpMax = dp[j] + 1;
            }
        }
        if(tmpMax > res){
            res = tmpMax;
        }
        dp[i] = tmpMax;
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

/**
 * version1, 28ms, beats 86%
 * 1. 依照word的長度重排字串
 * 2. 定義dp[i]：為終點為字串i時最長的predecessor集合
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
