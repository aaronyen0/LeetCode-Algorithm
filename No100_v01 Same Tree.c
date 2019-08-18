/**
 * 比較兩棵樹是否完全一致
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


/**
 * 兩棵樹同步的往下遞迴
 * 若任何一個node發現不同步的地方
 * 則回傳false
 * 若平安走到葉子節點，則回傳true
 */

/**
 * version1, 0ms, 100%
 * 1. if() 和 else if() 在檢查當前node是否平衡:
 *     - 如果一致為NULL回傳true
 *     - 如果一邊NULL一邊不是則回傳false
 * 2. 進else代表兩邊node都非空
 *     - 檢查是否數值一致
 *     - 一致的話回傳兩側子樹是否一致
 */

bool isSameTree(struct TreeNode* p, struct TreeNode* q){
    bool resLeft, resRight;
    if(p == NULL){
        if(q == NULL){
            return true;
        }else{
            return false;
        }
    }else if(q == NULL){
        return false;
    }else{
        if(p->val == q->val){
            resLeft = isSameTree(p->left, q->left);
            resRight = isSameTree(p->right, q->right);
            return resLeft & resRight; //兩側子樹的回傳值
        }else{
            return false;
        }
    }
}

