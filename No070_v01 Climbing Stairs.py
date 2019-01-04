  def climbStairs(self, n):
      """
      :type n: int
      :rtype: int
      """
      tmp = 1
      res = 1
      for i in range(1,n):
          res += tmp
          tmp = res - tmp
      return res
