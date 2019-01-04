class Solution(object):
    def grayCode(self, n):
        """
        :type n: int
        :rtype: List[int]
        """
        if n < 1:
            return [0]
        
        offset = 2 
        totalLen = 2 << (n - 1);
        
        lst = [0] * totalLen
        lst[1] = 1
        
        while offset < totalLen:
            for i in range(offset):
                lst[offset + i] = lst[offset - i - 1] | offset
            offset <<= 1
        return lst
