//很糟糕的寫法 共費時232ms

//寫法的初衷在只想掃一次grid
//當我們從上到下，從左到右掃過一次陣列時
//將數字1的地方改為label，label的規則為先延續上面否則延續左邊，若上和左都沒有，則是新的label，並將counter[label]++
//但是在移動過程中，會發現某些不同label其實是連通的
//因此有一個connect[][]矩陣，紀錄label跟label之間是否連通
//最後逐一掃過connect矩陣，取得連通label的和，這邊我是用一個queue去紀錄當前連通的label
//另外還要tested[]去排除已經計算過的label
//總之耗費龐大的運算和buffer
//雖然確實只掃過一次grid，可是計算繁複，且最終掃connect時也有一個O(labelNum^2)的迴圈


//簡單參考普遍寫法，只需要一個跟圖一樣大的陣列，用以紀錄是否掃過某些地區
//若遇到元素是1且沒有掃過的點，則從該位置往外外搜尋直到每個連通的1都被加入到為止
//這個方法最差的情況就是整張圖掃過兩次(1.逐點判定、2.數字1搜尋)

int maxAreaOfIsland(int** grid, int gridRowSize, int gridColSize) {
    int offset = 1, sum, maxArea = 0;
    int counter[1251] = {0};
    int connect[1251][1251] = {0};
    int tested[1251] = {0};
    
    int queue[1250];
    int front = 0, rear = 0;
    
    for(int i = 0; i < gridRowSize; ++i){
        for(int j = 0; j < gridColSize; ++j){
            if(grid[i][j] == 1){
                if((i == 0 || grid[i - 1][j] == 0) && (j == 0 || grid[i][j - 1] == 0)){
                    grid[i][j] = offset++;
                }else if(i > 0 && grid[i - 1][j] > 0){
                    grid[i][j] = grid[i - 1][j];
                    if(j > 0 && grid[i][j - 1] > 0){
                        connect[grid[i][j - 1]][grid[i - 1][j]] = 1;
                        connect[grid[i - 1][j]][grid[i][j - 1]] = 1;
                    }
                }else if(j > 0 && grid[i][j - 1] > 0){
                    grid[i][j] = grid[i][j - 1];
                }
                counter[grid[i][j]]++;
            }
        }
    }
    
    
    for(int i = 1; i < offset; ++i){
        if(tested[i] == 1){
            continue;
        }
        
        sum = 0;
        queue[rear++] = i;
        while(front < rear){
            tested[queue[front]] = 1;
            sum += counter[queue[front]];
            for(int j = 1; j < offset; ++j){
                if(connect[queue[front]][j] == 1 && tested[j] == 0){
                    tested[j] = 1;
                    queue[rear++] = j;
                }
            }
            front++;
        }
        if(sum > maxArea){
            maxArea = sum;
        }
        
    }
    
    return maxArea;
}
