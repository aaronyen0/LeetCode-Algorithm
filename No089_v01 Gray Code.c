/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* grayCode(int n, int* returnSize) {
	int *res;
	if(n < 1){
		res = (int*)malloc(sizeof(int));
        res[0] = 0;
        *returnSize = 1;
        return res;
	}else{
        
    }
    const int totalLen = 2 << (n - 1);
	int offset = 2;
    //int firstBit = 1; //後來發現firstBit根本和offset同步
    
    res = (int*)malloc(sizeof(int) * totalLen);
	res[0] = 0;
    res[1] = 1;

	while(offset < totalLen){		
		//firstBit <<= 1;
		for(int i = 0; i < offset; ++i){
			//res[offset + i] = (res[offset -i - 1] | firstBit);
            res[offset + i] = (res[offset -i - 1] | offset);
		}
		offset <<= 1;
	}
    *returnSize = totalLen;
    return res;
}
