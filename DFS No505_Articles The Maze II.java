//重要!!因為這題須付費，無法線上撰寫，本程式碼是直接複製LeetCode官方解說的程式碼
//單純個人學習用，沒有任何商業用途

/**
 * 有一顆球在迷宮內某個點，終點在迷宮內另一個點
 * 球可以滾動，但是必須要碰到牆壁才能停下來
 * 請問走到終點「的最短路徑」為？
 * 若沒有最短路徑則回傳-1
 */

/**
 * 滾球的程式碼類似老鼠走迷宮，但是有幾個麻煩處
 * 1.朝一個方向滾動必須滾到底
 * 2.本題需要紀錄最短路徑
 *
 * 官方解的DFS版本大致上有幾個步驟
 * 1.建立另一個distance map專門用來記錄到達該點的最短路徑，因此將這個map的所有點初始化為INT_NAX
 * 2.從某個點出發，朝上下左右的其中一方移動，並紀錄走到底的步數
 * 3.走到底之後，若 該點紀錄的步數 > 當前走到這裡的步數，則更新該點最短步數並回到2
 * 4.若 該點紀錄的步數 <= 當前走到這裡的步數，無須再多判斷，退回前一點朝另一個方向走

public class Solution {
    public int shortestDistance(int[][] maze, int[] start, int[] dest) {
        int[][] distance = new int[maze.length][maze[0].length];
        //初始化陣列
        for (int[] row: distance)
            Arrays.fill(row, Integer.MAX_VALUE);
        
        //初始化起點並開始移動
        distance[start[0]][start[1]] = 0;
        dfs(maze, start, distance);
        
        //若所有路徑都走完，終點依舊是INT_MAX，代表沒能走到終點
        return distance[dest[0]][dest[1]] == Integer.MAX_VALUE ? -1 : distance[dest[0]][dest[1]];
    }

    public void dfs(int[][] maze, int[] start, int[][] distance) {
        int[][] dirs={{0,1}, {0,-1}, {-1,0}, {1,0}};
        
        //依序朝四個方向前進
        for (int[] dir: dirs) {
            int x = start[0] + dir[0];
            int y = start[1] + dir[1];
            
            //從選擇的方向走到底，迴圈出來後，count則是該方向走到底經歷的步數
            int count = 0;
            while (x >= 0 && y >= 0 && x < maze.length && y < maze[0].length && maze[x][y] == 0) {
                x += dir[0];
                y += dir[1];
                count++;
            }
            
            //若步數 < 已紀錄，更新該格的步數，並進入下一層遞迴中
            if (distance[start[0]][start[1]] + count < distance[x - dir[0]][y - dir[1]]) {
                distance[x - dir[0]][y - dir[1]] = distance[start[0]][start[1]] + count;
                dfs(maze, new int[]{x - dir[0],y - dir[1]}, distance);
            }
        }
    }
}
