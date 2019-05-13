/**
 * 給一個傳統的二元樹(小的往左丟、大的往右丟)
 * 裡面的數都沒有任何重複
 * 將每個節點的數字重新計算，計算規則如下：
 * 節點的新數字，為舊的樹中，所以有大於等於自己的數字總和(也就是包含自己)
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
 * version1, beats 100%
 * 基本思想就是最大的數字要最早處理
 * 然後往次大的數字移動，並buffer住截至目前為止的總和
 * 我的寫法依舊是很暴力的傳指標進每個節點
 * 確實每次這樣寫都很快
 * 但也可能因為常這樣寫
 * 讓我在設計遞迴還有DP問題都變得很不拿手(因為不會切割子問題)
 */
  
struct TreeNode* bstToGst(struct TreeNode* root){
    int iniVal = 0;
    treeTraversal(root, &iniVal);
    return root;
}

void treeTraversal(struct TreeNode* node, int* tmp){
    if(node->right){
        treeTraversal(node->right, tmp);
    }
    (*tmp) += node->val;
    node->val = *tmp;
    if(node->left){
        treeTraversal(node->left, tmp);
    }
}
