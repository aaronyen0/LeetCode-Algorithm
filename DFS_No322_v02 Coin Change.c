void quicksort3(int *data, int left, int right);
void swap(int* a, int* b);

//速度超慢 time limit exceeded
void DFS(int *coins, int i, int remain, int cnt, int *minCnt) {
	//printf("coins[%d] = %d, remain = %d, cnt = %d\n", i, coins[i], remain, cnt);
	int num;
	if (remain == 0) {
		if (cnt < *minCnt) {
			*minCnt = cnt;
		}
		return;
	}
	
	if (i < 0 || cnt + 2 > *minCnt) {
		return;
	}
	
	for (int j = remain / coins[i]; j >= 0; --j) {
		DFS(coins, i - 1, remain - j * coins[i], cnt + j, minCnt);
	}
}

//快很多 4ms beat 100%
void DFS2(int *coins, int i, int remain, int cnt, int *minCnt) {
	//printf("coins[%d] = %d, remain = %d, cnt = %d\n", i, coins[i], remain, cnt);
	if (remain == 0) {
		if (cnt < *minCnt) {
			*minCnt = cnt;
		}
		return;
	}
	
	if (i < 0) {
		return;
	}
	
	for (int j = remain / coins[i]; j >= 0; --j) {
		//為何只是把判斷式移到這邊時間卻能差這麼多?
		//當然call function需要複製引數，需要額外配記憶體...等，確實時間上有差
		//但從order的角度來看，總覺得不至於會差到超時
		if (cnt + j + 1 > *minCnt) {
			break;
		}
		DFS2(coins, i - 1, remain - j * coins[i], cnt + j, minCnt);
	}
}

int coinChange(int* coins, int coinsSize, int amount) {
	if (amount == 0) {
		return 0;
	}

	int k, res = INT_MAX;

	quicksort3(coins, 0, coinsSize - 1);

	for (k = 0; coins[k] <= amount, k < coinsSize; ++k);
	--k;

	DFS2(coins, k, amount, 0, &res);
	if (res != INT_MAX) {
		return res;
	}
	return -1;
}

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void quicksort3(int *data, int left, int right)
{
    if (left >= right) { 
        return; 
    }
    int pivot = data[left];
    int i = left + 1;
    int j = right;

    while (1){
        while (i <= right){
            if (data[i] >= pivot){
                break;
            }
            ++i;
        }

        while (j > left){
            if (data[j] < pivot){
                break;
            }
            --j;
        }

        if (i > j) { 
            break; 
        }
        swap(&data[i], &data[j]);
    }

    swap(&data[left], &data[j]);

    quicksort3(data, left, j - 1);
    quicksort3(data, j + 1, right);
}
