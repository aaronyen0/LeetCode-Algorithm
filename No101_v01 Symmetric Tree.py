# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

"""version 1, 40ms, 99.51%
給兩個list，分別代表左右子樹
以對稱的方式不斷更新兩邊的list
用的方法基本上是LevelOrder
"""
def compare_tree_recursive(left_lt, right_lt):
    if len(left_lt) == 0:
        return True
    else:
        lnode = left_lt.pop(0)
        rnode = right_lt.pop(0)
        
        if lnode.val != rnode.val:
            return False
        else:
            if lnode.left != None and rnode.right != None:
                left_lt.append(lnode.left)
                right_lt.append(rnode.right)
            elif lnode.left != None or rnode.right != None:
                return False
            
            if lnode.right != None and rnode.left != None:
                left_lt.append(lnode.right)
                right_lt.append(rnode.left)
            elif lnode.right != None or rnode.left != None:
                return False
                
    return compare_tree_recursive(left_lt, right_lt)

class Solution:
    def isSymmetric(self, root: TreeNode) -> bool:
        if root == None:
            return True
        return compare_tree_recursive([root], [root])


"""version 1, 40ms, 99.51%
方法同上，改成不用遞迴而已
"""

def isSymIterative(root):
    lt = [root, root]
    
    while len(lt) > 0:
        lnode = lt.pop(0)
        rnode = lt.pop(0)        

        if lnode.val != rnode.val:
            return False
        else:
            if lnode.left != None and rnode.right != None:
                lt.append(lnode.left)
                lt.append(rnode.right)
            elif lnode.left != None or rnode.right != None:
                return False
            
            if lnode.right != None and rnode.left != None:
                lt.append(lnode.right)
                lt.append(rnode.left)
            elif lnode.right != None or rnode.left != None:
                return False
        
    return True


class Solution:
    def isSymmetric(self, root: TreeNode) -> bool:
        if root == None:
            return True
        return isSymIterative(root)
