//重要!!因為這題須付費，無法線上撰寫，本程式碼是直接複製LeetCode官方解說的程式碼
//單純個人學習用，沒有任何商業用途

/**
 * [題目]
 * 有一顆球在迷宮內某個點，終點在迷宮內另一個點
 * 球可以滾動，但是必須要碰到牆壁才能停下來
 * 請問是否有可能讓球剛好停在？
 */

/**
 * 比其Maze II這題單純的多，完全就是老鼠走迷宮的問題
 * 這題若遇到曾經走過的路，就可以放心捨棄不用再去走它
 * Maze II不能直接捨棄，要先判斷這輪走到這邊是否比前輪更有效益，沒有的話才能捨棄，否則要蓋掉並接著走
 */
 
public class Solution {
    public boolean hasPath(int[][] maze, int[] start, int[] destination) {
        //初始化visited陣列，用來判別某格是否走過
        //我是沒寫過java，要判別這件事情應該改maze的數字就好了吧？
        boolean[][] visited = new boolean[maze.length][maze[0].length];
        return dfs(maze, start, destination, visited);
    }
    public boolean dfs(int[][] maze, int[] start, int[] destination, boolean[][] visited) {
        //若這格走過，則可以退出
        if (visited[start[0]][start[1]])
            return false;
            
        //若這格是終點，也可以退出
        if (start[0] == destination[0] && start[1] == destination[1])
            return true;
            
        //否則將這格改為true
        visited[start[0]][start[1]] = true;
        
        //這邊事先朝某個方向加1，如果不這樣寫，可以想想看判斷式是否會變的比較複雜
        int r = start[1] + 1, l = start[1] - 1, u = start[0] - 1, d = start[0] + 1;
        
        //朝右走到底
        while (r < maze[0].length && maze[start[0]][r] == 0) // right
            r++;
        if (dfs(maze, new int[] {start[0], r - 1}, destination, visited))
            return true;
            
        //朝左走到底
        while (l >= 0 && maze[start[0]][l] == 0) //left
            l--;
        if (dfs(maze, new int[] {start[0], l + 1}, destination, visited))
            return true;
            
        //朝上走到底
        while (u >= 0 && maze[u][start[1]] == 0) //up
            u--;
        if (dfs(maze, new int[] {u + 1, start[1]}, destination, visited))
            return true;
            
        //朝下走到底
        while (d < maze.length && maze[d][start[1]] == 0) //down
            d++;
        if (dfs(maze, new int[] {d - 1, start[1]}, destination, visited))
            return true;
        
        return false;
    }
}
