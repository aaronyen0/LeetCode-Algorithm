/*
// Definition for a Node.
public class Node {
    public int val;
    public IList<Node> children;

    public Node(){}
    public Node(int _val,IList<Node> _children) {
        val = _val;
        children = _children;
}
*/
/*
public class Solution {
    public int MaxDepth(Node root) 
    {
        int tmp, maxDepth = 0;
        if (root == null)
        {
            return 0;
        }
        foreach(Node n in root.children)
        {
            tmp = MaxDepth(n);
            if(tmp > maxDepth){
                maxDepth = tmp;
            }
        }
        return maxDepth + 1;
    }
}
*/

public class Solution {
    private int depth;
    
    public int MaxDepth(Node root) 
    {
        depth = 0;
        if (root == null)
        {
            return 0;
        }
        Traversal(root, 1);
        return depth;
    }
    
    private void Traversal(Node node, int level)
    {      
        if (node.children.Count == 0 && level > depth)
        {
            depth = level;
        }
        else
        {
            //int nLevel = level + 1;
            foreach(Node n in node.children)
            {
                Traversal(n, level + 1);
            }
        }
    }
}
