/**
 * GrayCode是一串非負整數數列
 * 用binary的角度來看
 * 相鄰的數字間只差1個bit
 */

/* 一種GrayCode範例
 Number      Gray
0b00000   0b00000
0b00001   0b00001
0b00010   0b00011
0b00011   0b00010
0b00100   0b00110
0b00101   0b00111
0b00110   0b00101
0b00111   0b00100
0b01000   0b01100
0b01001   0b01101
0b01010   0b01111
0b01011   0b01110
0b01100   0b01010
0b01101   0b01011
0b01110   0b01001
0b01111   0b01000
*/

/**
 * version2, 4ms
 * 上述範例中可以觀察出一個現象
 * 若Number那某數字的bit_(i) != bit_(i+1)
 * 則對應GrayCode的bit_(i) = 1
 * 反之則是0
 * 因此可以透過 i ^ (i >> 1) 抓出兩個相鄰bit不同的位置
 */

int* grayCode(int n, int* returnSize){
    int *res, len;
    len = (1 << n);
    res = (int*)malloc(sizeof(int) * len);
    for(int i = 0; i < len; ++i){
        res[i] = i ^ (i >> 1);
    }
    
    *returnSize = len;
    return res;
}


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
