/**
 * 給定三個不重複的整數 x < y < z
 * 我們可以將最大的z，或最小的x移動到某個整數k
 * 但是k必須要滿足，x < k < z，並形成另一組數字 x1 < y1 < z1
 * 試問最多移動幾次以及最少移動幾次
 * 數列便不能再動彈
 */

/** version1, beats 100%, 4ms
 * Note: The returned array must be malloced, assume caller calls free().
 */
 
/**
 * 其中最多的移動次數：
 * 將x'逐步'移動到y-1，將z'逐步'移動到y+1，>>> (y - x - 1) + (z - y - 1)
 * 最小的移動次數：
 * 有幾種可能：
 * 1. y - x == 2 或 z - y == 2，這時只要把另一側的數字放到中間就夠了
 * 2. 單邊或是雙邊原本就貼在一起
 * 3. 假設數字比此都離很遠頂多就是移動2次
 * 程式開始先排序，之後便按照上述邏輯判斷移動次數
 */
int* numMovesStones(int a, int b, int c, int* returnSize){
    int* res = (int*)malloc(sizeof(int) * 2);
    int maxLeft, maxRight, min = 0, tmp;
    if(b < a){
        tmp = a;
        a = b;
        b = tmp;
    }
    if(c < a){
        tmp = a;
        a = c;
        c = tmp;
    }
    if(c < b){
        tmp = b;
        b = c;
        c = tmp;
    }
    maxLeft = b - a;
    maxRight = c - b;
    
    if(maxLeft == 2 || maxRight == 2){
        min = 1;
    }else{
        if(maxLeft > 1){
            ++min;
        }
        if(maxRight > 1){
            ++min;
        }
    }
    
    res[0] = min;
    res[1] = maxRight + maxLeft - 2;
    *returnSize = 2;
    return res;
}
