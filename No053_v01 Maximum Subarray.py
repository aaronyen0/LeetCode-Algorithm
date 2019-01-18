class Solution:
    def maxSubArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        size = len(nums)
        if size <= 0:
            return 0
        
        crt, res = nums[0], nums[0]
        
        for i in range(1, size):
            if crt > 0:
                crt += nums[i]
            else:
                crt = nums[i]
                
            if crt > res:
                res = crt
        return res
