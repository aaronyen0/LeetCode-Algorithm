int Min2(int a, int b){
    if(a < b){
        return a;
    }
    return b;
}

int minimumTotal(int** triangle, int triangleRowSize, int *triangleColSizes) {
    for(int i = triangleRowSize - 2; i >=0; --i){
        for(int j = 0; j < i + 1; ++j){
            triangle[i][j] +=  Min2(triangle[i + 1][j], triangle[i + 1][j + 1]);
        }
    }
    return triangle[0][0];
}
