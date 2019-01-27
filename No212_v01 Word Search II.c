/**
 * 給一個board
 * 以及一些字串 words[][]
 * 查看每個str = wrods[i]
 * 是否能在board中查的到
 */

/**
 * version1, 1724ms, beats 100%
 * 絕對不是我寫得太快
 * 而是用C太麻煩沒人要寫
 * 這版本做法：
 * 1.建立一個map用來記錄該字串曾經走過的座標
 * 2.對每個字元，都已hashtable儲存有該字元的所有座標，例如 table[0] = table['a' - 'a'] = {Point1, point2, ...}
 * 3.先排除重複字串strcmp，我是透過交換的方式將步重複字串換到前面來
 * 
 * 現階段可優化的地方有幾個部分
 * 1.將字串集中重複的部分排除，可以改用hashtable
 * 2.或許可以將剩餘的字串集排序例如 aaaa, aaaaa, aaaab，通用的子字串可以一起查找，這代表Check的方法要修改
 */

char* CopyStr(char* str){
    if(str == NULL){
        return NULL;
    }
    int n = 0;
    while(str[n++] != 0);
    char* buff = malloc(sizeof(int) * n);
    memcpy(buff, str, n);
    return buff;
}

typedef struct{
    int x;
    int y;
} Point;

//就是老鼠走迷宮，因為map要給很多人用，退出前要將map還原 map[x][y] = 0
bool Check(char* str, int x, int y, char** board, char** map, Point* mapSize){
    bool res = false;
    if(str[0] != board[x][y]){
        return false;
    }
    if(str[0] == board[x][y] && str[1] == 0){
        return true;
    }
    
    map[x][y] = 1;
    if(x > 0 && map[x - 1][y] == 0){
        res = Check(&str[1], x - 1, y, board, map, mapSize);
    }
    
    if(res == false && y > 0 && map[x][y - 1] == 0){
        res = Check(&str[1], x, y - 1, board, map, mapSize);
    }
    
    if(res == false && x < mapSize->x - 1 && map[x + 1][y] == 0){
        res = Check(&str[1], x + 1, y, board, map, mapSize);
    }
    
    if(res == false && y < mapSize->y - 1 && map[x][y + 1] == 0){
        res = Check(&str[1], x, y + 1, board, map, mapSize);
    }
    
    map[x][y] = 0;
    return res;
}



char** findWords(char** board, int boardRowSize, int boardColSize, char** words, int wordsSize, int* returnSize) {
    char** res = (char**)malloc(sizeof(char*) * wordsSize);
    bool check;
    char c, *str, *tmp;
    int idx, resCnt = 0, n;
    
    Point mapSize;
    mapSize.x = boardRowSize;
    mapSize.y = boardColSize;
    char** map = (char**)malloc(sizeof(char*) * boardRowSize);
    for(int i = 0; i < boardRowSize; ++i){
        map[i] = (char*)calloc(boardColSize, sizeof(char));
    }
    
    //建立 字元vs.座標的hashtable
    int tableCnt[26] = {0};
    Point *table[26];
    n = boardRowSize * boardColSize;
    for(int i = 0; i < 26; ++i){
        table[i] = (Point*)malloc(sizeof(Point) * n);
    }    
    
    for(int x = 0; x < boardRowSize; ++x){
        for(int y = 0; y < boardColSize; ++y){
            idx = board[x][y] - 'a'; 
            table[idx][tableCnt[idx]].x = x;
            table[idx][tableCnt[idx]++].y = y;
        }    
    }
    /**
     * 將重複字串換到後面，並更新wordsSize
     * 另外要極小心一點，原本想說將後面的字串往前貼就好，並沒有交換
     * 代表words[j] 跟 words[wordsSize - 1] 有同樣的記憶體位置
     * 導致函式return後，外部釋放words記憶體時重複指向同一個地方，導致error
     * 因為一直到return前都沒出錯，這個bug大概找了1小時
     */
    for(int i = 0; i < wordsSize - 1; ++i){
        for(int j = i + 1; j < wordsSize;){
            if(strcmp(words[i], words[j]) == 0){
                tmp = words[j];
                words[j] = words[wordsSize - 1];
                words[wordsSize - 1] = tmp;
                wordsSize--;
            }else{
                ++j;
            }
            
        }
    }
    //printf("pass strcmp, wordsSize = %d\n", wordsSize);
    
    //對每個str，都去檢查是否能從board中搜索到一致的字串，若有的話則更新至res，這邊是有重配記憶體，或許可以不用
    for(int i = 0; i < wordsSize; ++i){
        str = words[i];
        idx = str[0] - 'a';
        for(int j = 0; j < tableCnt[idx]; ++j){
            check = Check(str, table[idx][j].x, table[idx][j].y, board, map , &mapSize);
            if(check == true){
                res[resCnt++] = CopyStr(words[i]);
                //printf("ans[%2d] = %s\n", resCnt , res[resCnt - 1]);
                break;
            }
        }
    }
    

    /*
    for(int i = 0; i < boardRowSize; ++i){
        free(map[i]);
    }
    free(map);

    for(int i = 0; i < 26; ++i){
        free(table[i]);
    }
    */
    
    *returnSize = resCnt;
    return res;
}
