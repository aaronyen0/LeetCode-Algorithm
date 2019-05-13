/**
 * 給三個點
 * 判斷這三個點是否呈現迴力鏢狀
 * 其實就是判斷三個點不能貢獻
 */


/**
 * version2, 0ms, beats 100%
 * 一樣是算出兩個向量
 * 檢查向量是否共線
 * 但是有些判斷式其實是多餘的
 * 省略到最後判斷式只有一個
 * 因此也不用buffer住向量的值
 * 另外判斷式用不等於才能達到100%
 * 個人覺得只是剛好測試傾向於這樣寫速度比較快而已
 */

bool isBoomerang(int** points, int pointsSize, int* pointsColSize){
    if((points[1][0] - points[0][0]) * (points[2][1] - points[0][1]) != 
       (points[1][1] - points[0][1]) * (points[2][0] - points[0][0])){
        return true;
    }
    
    return false;
}


/**
 * version1, 4ms, beats 90%
 * 算出兩個向量
 * 檢查向量是否共線
 */

bool isBoomerang(int** points, int pointsSize, int* pointsColSize){
    int v1_x, v1_y, v2_x, v2_y;
    v1_x = points[1][0] - points[0][0];
    v1_y = points[1][1] - points[0][1];
    
    v2_x = points[2][0] - points[0][0];
    v2_y = points[2][1] - points[0][1];
    if((v1_x == 0 && v1_y == 0) || (v2_x == 0 && v2_y == 0)){
        return false;
    }
    
    if(v1_y * v2_x == v1_x * v2_y){
        return false;
    }
    
    return true;
}
