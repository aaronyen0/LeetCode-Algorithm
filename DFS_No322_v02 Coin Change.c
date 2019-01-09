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

void DFS(int *coins, int i, int remain, int cnt, int *minStep) {
	//printf("coins[%d] = %d, remain = %d, cnt = %d\n", i, coins[i], remain, cnt);
	int num;
	if (remain == 0 && cnt < *minStep) {
		*minStep = cnt;
		return;
	}
	
	if (i < 0 || cnt > *minStep) {
		return;
	}
	
	for (int j = remain / coins[i]; j >= 0; --j) {
		DFS(coins, i - 1, remain - j * coins[i], cnt + j, minStep);
	}
}

void DFS2(int *coins, int i, int remain, int cnt, int *minStep) {
	//printf("coins[%d] = %d, remain = %d, cnt = %d\n", i, coins[i], remain, cnt);
	int num;
	if (remain == 0) {
		if (cnt < *minStep) {
			*minStep = cnt;
		}
		return;
	}
	
	if (i < 0 || cnt > *minStep) {
		return;
	}
	
	for (int j = remain / coins[i]; j >= 0; --j) {
		if (cnt + j + 1 > *minStep) {
			break;
		}
		DFS2(coins, i - 1, remain - j * coins[i], cnt + j, minStep);
	}
}

int coinChange(int* coins, int coinsSize, int amount) {
	if (amount == 0) {
		return 0;
	}

	int k, res, minStep = INT_MAX;

	quicksort3(coins, 0, coinsSize - 1);

	for (k = 0; coins[k] <= amount, k < coinsSize; ++k);
	--k;

	DFS2(coins, k, amount, 0, &minStep);
	if (minStep != INT_MAX) {
		return minStep;
	}
	return -1;
}
