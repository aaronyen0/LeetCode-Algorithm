//當時一直在想如何使用O(1)的記憶體，而且迴圈中不包含if的情況下寫這題
//不用if困難點在如何更新小的數字換成當前最大的
//後來突然想到了不使用tmp交換數字的方法
//概念為交換途中一直都保有能恢復兩個數字的「基底」，通常最常見的就是xor運算和+-法運算

int climbStairs(int n) {
	int tmp = 1;
	int sum = 1;
	for(int i = 2; i <= n; ++i){
		sum += tmp;
		tmp = sum - tmp;
	}
    return sum;
}

//費氏數列
//這個寫法用固定陣列並不安全，但足夠pass所有測試項目
int climbStairs(int n) {
    int step[512];
    step[0] = 1;
    step[1] = 1;
    for(int i = 2; i <= n; ++i){
        step[i] = step[i - 1] + step[i - 2];
    }
    return step[n];
}
