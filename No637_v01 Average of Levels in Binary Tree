/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
double* averageOfLevels(struct TreeNode* root, int* returnSize) {
    long long int sum[1024] = {0};
    int count[1024] = {0};
    int maxLevel = 0;
    Traversal(root, 1, &maxLevel, sum, count);
    
    double* average = (double*)malloc(sizeof(double) * maxLevel);
    for(int i = 0; i < maxLevel; ++i){
        if(count[i]){
            average[i] = (double)sum[i] / count[i];
        }else{
            average[i] = 0;
        }
    }
    *returnSize = maxLevel;
    return average;
}

void Traversal(struct TreeNode* node, int level, int* maxLevel, long long int* sum, int* count){
    (*sum) += node->val;
    (*count)++;
    
    if(level > *maxLevel){
        *maxLevel = level;
    }
    
    ++sum;
    ++count;
    
    if(node->left){
        Traversal(node->left, level + 1, maxLevel, sum, count);
    }
    if(node->right){
        Traversal(node->right, level + 1, maxLevel, sum, count);
    }
}
