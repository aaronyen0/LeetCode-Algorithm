/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

/*
個人覺得這樣寫有點矯枉過正，純粹為了提高效率而寫的，好壞見仁見智：
好處：每個Fizz和Buzz都指到同一塊記憶體，所以省空間，加上出現頻率高，少去很多配置記憶體和複製字串的時間，所以整體效能也快
壞處：外部若是照雙重指標的一般釋放法，會遇到bug，外部釋放記憶體時需要作一些額外判斷

另外自己塞數字的字串是否能進一步優化，可以再研究
不過一般來說應該會比標準函式sprintf快
*/
char** fizzBuzz(int n, int* returnSize) {
    int numSize = 1, cmpNum = 10, x;
    char* tmp;
    
    char* Fizz = (char*)malloc(sizeof(char) * 5);    
    char* Buzz = (char*)malloc(sizeof(char) * 5);
    char* FizzBuzz = (char*)malloc(sizeof(char) * 9);
    char** res = (char**)malloc(sizeof(char*) * n);
    
    memcpy(Fizz, "Fizz", 5);
    memcpy(Buzz, "Buzz", 5);
    memcpy(FizzBuzz, "FizzBuzz", 9);
    
    for(int i = 1; i <= n; ++i){
        if(i % 15 == 0){
            res[i - 1] = FizzBuzz;
        }else if(i % 3 == 0){
            res[i - 1] = Fizz;
        }else if(i % 5 == 0){
            res[i - 1] = Buzz;
            if(i == cmpNum){
                cmpNum *= 10;
                ++numSize;
            }
        }else{
            x = i;
            tmp = (char*)malloc(sizeof(char) * (numSize + 1));
            tmp[numSize] = 0;
            
            for(int j = numSize - 1; j >= 0; --j){
                tmp[j] = (x % 10) + '0';
                x /= 10;
            }
            res[i - 1] = tmp;
        }
    }
    *returnSize = n;
    return res;
}


//一般作法，易讀性高，缺點是記憶體配置寫死了，小心會溢位
/*
char** fizzBuzz(int n, int* returnSize) {
    char** res = (char**)malloc(sizeof(char*) * n);
    for(int i = 0; i < n; ++i){
        res[i] = (char*)malloc(sizeof(char) * 10);
    }
    
    for(int i = 1; i <= n; ++i){
        if(i % 15 == 0){
            memcpy(res[i - 1], "FizzBuzz", 9);
        }else if(i % 3 == 0){
            memcpy(res[i - 1], "Fizz", 5);
        }else if(i % 5 == 0){
            memcpy(res[i - 1], "Buzz", 5);
        }else{
            sprintf(res[i - 1], "%d", i);
        }
    }
    *returnSize = n;
    return res;
}
*/
