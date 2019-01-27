/**
 * 檢查二元樹是否合理
 */
 
/**
 * version1, 4ms, 100%
 * 隨著樹往下長，node->val的範圍會被限縮
 * 若不滿足範圍，或是範圍異常則false
 * 有個小麻煩就是INT_MIN及INT_MAX連續出現時
 * 所以才特別檢查node->val == min，主要目的在抓出node->val == INT_MIN
 * 代表往下一層的左子樹範圍有異常，且32bit的整數(node->val - 1)因為溢位無法發現這件事情
 * 往右也是類似
 * 感覺判斷式或許能寫得更漂亮一點，有空再來改
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool Check(struct TreeNode* node, int min, int max){
    if(max < min){
        return false;
    }
    if(node->val >= min && node->val <= max){
        if(node->left){
            if(node->val == min || !Check(node->left, min, node->val - 1)){
                return false;
            }
        }
        if(node->right){
            if(node->val == max || !Check(node->right, node->val + 1, max)){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool isValidBST(struct TreeNode* root) {
    if(!root){
        return true;
    }
    return Check(root, INT_MIN, INT_MAX);
}
