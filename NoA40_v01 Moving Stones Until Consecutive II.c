void Swap(int* a, int* b);
void QuickSort3(int* arr, int left, int right); 
int FindMinClipNum(int* arr, int len);

int* numMovesStonesII(int* stones, int stonesSize, int* returnSize){
    int minVal, maxVal;
    int lSpace1, rSpace1;
    int rIdx, lIdx;
    int* res = (int*)malloc(sizeof(int) * 2);
    *returnSize = 2;
    
    QuickSort3(stones, 0, stonesSize - 1);
    minVal = stones[0];
    maxVal = stones[stonesSize - 1];
    if(minVal + stonesSize == maxVal + 1){
        res[0] = 0;
        res[1] = 0;
        return res;
    }
    
    //最大
    lSpace1 = stones[1] - stones[0] - 1;
    rSpace1 = stones[stonesSize - 1] - stones[stonesSize - 2] - 1;
    if(lSpace1 < rSpace1){
        res[1] = maxVal - minVal + 1 - stonesSize - lSpace1; // 左邊往內縮
    }else{
        res[1] = maxVal - minVal + 1 - stonesSize - rSpace1; // 右邊往內縮
    }
    
    //最小
    res[0] = FindMinClipNum(stones, stonesSize);
    
    return res;
}

int FindMinClipNum(int* arr, int len){
    int rNum, minClipNum = INT_MAX;
    int crtRightIdx = 0;
    int clipNum;

    for(int i = 0; i < len - 1; ++i){
        rNum = arr[i] + len - 1;
        while(crtRightIdx < len && arr[crtRightIdx] <= rNum){
            crtRightIdx++;
        }

        clipNum = len - crtRightIdx + i;
        if(clipNum == 1 && arr[crtRightIdx - 1] != rNum){
            clipNum = 2;
        }

        //printf("%d, %d, %d\n", i, crtRightIdx, clipNum);
        if(clipNum < minClipNum){
            minClipNum = clipNum;
        }
    }	
    return minClipNum;
}


void Swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void QuickSort3(int *data, int left, int right)
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
        Swap(&data[i], &data[j]);
    }

    Swap(&data[left], &data[j]);

    QuickSort3(data, left, j - 1);
    QuickSort3(data, j + 1, right);
}
