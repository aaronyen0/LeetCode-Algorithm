/**
 * 找到平方根並取整
 */
 
/** version3, 4ms, beats 100%, memory 100%
 * 同樣也是覺得y已經逼近真值
 * 縱使不逐步檢查，也應該要要善用這個優勢
 * 我將v1版本bisection中的上或下界包在y+-100內，可以accepted所有測資
 * 不過嘗試其他更小的區間時發現都會有錯誤
 * 便將牛頓法由疊代一次改為疊代兩次
 * 果然有效區間變窄許多
 * 當然這只是好玩測試的結果
 * 區間取法太特規，沒有version1版本一般化
 */
float FastInvSqrt(float number){
    float y;
    unsigned int x = *(unsigned int*)(&number);
    x  = 0x5f3759df - (x >> 1);
    
    y = *(float*)(&x);
    y = y * (1.5 - 0.5 * number * y * y); //多疊代一次
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
        return SqrtBisection(y - 32, y, x); //區間可以取得更小
    }else if(y * y == x){
        return y;
    }else{
        return SqrtBisection(y, y + 32, x);
    }
}

/** version1, 4ms, beats 100%, memory 100%
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


/**version2, 16ms, beats 48%
 * 會有這個版本主要是想嘗試一件事情
 * 理想上，y已經很靠近真值sqrt(x)
 * 可是如果加到bisection中的話
 * 豈不是又從邊界開始搜尋
 * 所以我嘗試直接在附近找答案
 * 總之結果看起來並沒有比較好
 */
int mySqrt(int x){
    if(x == 0 || x == 1){
        return x;
    }
    float y = (1.0 / FastInvSqrt(x));
    unsigned int z = (unsigned int)y;
    if(z * z == x){
        return z;
    }else if(z * z > x){
        --z;
        while(z * z > x){
            --z;
        }
        return z;
    }else{
        ++z;
        while(z * z < x){
            ++z;
        }
        if(z * z == x){
            return z;
        }
        return --z;
    }
}
