/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** fizzBuzz(int n, int* returnSize) {
    /*
    char* Fizz = "Fizz";
    char* Buzz = "Buzz";
    char* FB = "FizzBuzz";
    */
    char* Fizz = (char*)malloc(sizeof(char) * 5);
    memcpy(Fizz, "Fizz", 5);
    char* Buzz = (char*)malloc(sizeof(char) * 5);
    memcpy(Buzz, "Buzz", 5);
    char* FizzBuzz = (char*)malloc(sizeof(char) * 9);
    memcpy(FizzBuzz, "FizzBuzz", 9);
    
    int numSize = 1, cmpNum = 10, x;
    char* tmp;
    
    char** res = (char**)malloc(sizeof(char*) * n);
    /*
    for(int i = 0; i < n; ++i){
        res[i] = (char*)malloc(sizeof(char) * 10);
    }
    */
    
    for(int i = 1; i <= n; ++i){
        if(i % 15 == 0){
            //memcpy(res[i - 1], FB, 9);
            res[i - 1] = FizzBuzz;
        }else if(i % 3 == 0){
            //memcpy(res[i - 1], Fizz, 5);
            res[i - 1] = Fizz;
        }else if(i % 5 == 0){
            //memcpy(res[i - 1], Buzz, 5);
            res[i - 1] = Buzz;
            if(i == cmpNum){
                cmpNum *= 10;
                ++numSize;
            }
        }else{
            //sprintf(res[i - 1], "%d", i);
            x = i;
            tmp = (char*)malloc(sizeof(char) * (numSize + 1));
            tmp[numSize] = 0;
            
            for(int j = numSize - 1; j >=0; --j){
                tmp[j] = (x % 10) + '0';
                x /= 10;
            }
            res[i - 1] = tmp;
        }
    }
    *returnSize = n;
    return res;
}
