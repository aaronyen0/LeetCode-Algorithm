/**
 * 找到平方根並取整
 */
 

/** version1, beats 100%, memory 100%
 * 採用快速反平方根取sqrt近似值
 * 再用bisection method找到整數
 * y在程式中是近似解，y^2可能大於x，也可能小於x
 * 前者我單純用0當作bisection的'下界'
 * 後者需要找一個bisection的'上界'
 * 46340是最大signed int的平方根取整
 * 在題目引數x型態為signed int下，46340是最大可能解
 */
 
float FastInvSqrt(float number){
    float y;
    unsigned int x = *(unsigned int*)(&number);
    x  = 0x5f3759df - (x >> 1);
    y = *(float*)(&x);
    return y * (1.5 - 0.5 * number * y * y);
}

unsigned int SqrtBisection(unsigned int l, unsigned int r, unsigned int target){
    unsigned int mid = (r + l) >> 1;
    while(mid != l){
        if(mid * mid > target){
            r = mid;
        }else{
            l = mid;
        }
        mid = (r + l) >> 1;
    }
    return mid;
}

int mySqrt(int x){
    if(x == 0 || x == 1){
        return x;
    }
    unsigned int y = (1.0 / FastInvSqrt(x)); //近似解
    if(y * y > x){
        return SqrtBisection(0, y, x);
    }else if(y * y == x){
        return y;
    }else{
        return SqrtBisection(y, 46340, x);
    }
}
