/**
 * 給兩個陣列values[i]及labels[i]
 * 代表物品i的label及對應的value
 * 令num_wanted代表要選取物品的上限
 * use_limit為每一種label可被選的上限
 * 計算可選集合中，最大的value_sum為多少
 */


/**
 * version2, 16s, beats 100%
 * 1.根據label分群
 * 2.對每種label都挑前use_limit個數的值
 * 3.將所有被挑出來的值再做一次排序，並取前num_wanted個
 */

void QuickSort3(int *data, int left, int right);
void Swap(int* a, int* b);
void ResetOffset(int* count, int* offset1, int* offset2, int len);

int largestValsFromLabels(int* values, int valuesSize, int* labels, int labelsSize, int num_wanted, int use_limit){
    int sum = 0;
    if(use_limit >= num_wanted){
        QuickSort3(values, 0, valuesSize - 1);
        for(int i = 0; i < num_wanted; ++i){
            sum += values[i];
        }
        return sum;
    }
    
    int sortedValues[20000];
    int labelCount[20001] = {0};
    int labelOffset1[20001];
    int labelOffset2[20001];
    int labelNum, maxLabelNum = 0, cnt, offset, tmpOffset;
    
    for(int i = 0; i < valuesSize; ++i){
        labelNum = labels[i];
        labelCount[labelNum]++;
        if(labelNum > maxLabelNum){
            maxLabelNum = labelNum;
        }
    }
    maxLabelNum++;    
    ResetOffset(labelCount, labelOffset1, labelOffset2, maxLabelNum);
    
    for(int i = 0; i < valuesSize; ++i){
        sortedValues[labelOffset1[labels[i]]++] = values[i];
    }
    
    for(int i = 0; i < maxLabelNum; ++i){
        offset = labelOffset2[i];
        QuickSort3(sortedValues, offset, offset + labelCount[i] - 1);
    }
    
    offset = 0;
    for(int i = 0; i < maxLabelNum; ++i){
        cnt = labelCount[i];
        tmpOffset = labelOffset2[i];
        if(cnt > use_limit){
            cnt = use_limit;
        }
        for(int j = 0; j < cnt; ++j){
            sortedValues[offset++] = sortedValues[tmpOffset + j];
        }
    }
    
    QuickSort3(sortedValues, 0, offset - 1);
    for(int i = 0; i < offset && i < num_wanted; ++i){
        sum += sortedValues[i];
    }
    
    return sum;
}

void ResetOffset(int* count, int* offset1, int* offset2, int len){
    int crt = 0;
    for(int i = 0; i < len; ++i){
        offset1[i] = crt;
        offset2[i] = crt;
        crt += count[i];
    }
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
            if (data[i] < pivot){
                break;
            }
            ++i;
        }

        while (j > left){
            if (data[j] >= pivot){
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
