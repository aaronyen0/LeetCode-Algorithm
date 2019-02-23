"""
version1, 48ms, 89%
python語法好不熟悉，看著C的版本寫還bug一堆
"""

class Solution(object):
    def solveNQueens(self, n):
        buffSize = 2 * n - 1
        buffShift = n - 1

        res = []
        stack = [-1] * n
        colHt = [0] * n
        lSlopeHt = [0] * buffSize
        rSlopeHt = [0] * buffSize

        row = 0
        while row > -1:
            j = stack[row]
            if j != -1:
                ResetIJ(row , j, colHt, lSlopeHt, rSlopeHt, buffShift)

            j += 1
            while j < n and CheckHt(row , j, colHt, lSlopeHt, rSlopeHt, buffShift):
                j += 1

            if j == n:
                stack[row] = -1
                row -= 1
            elif row == buffShift:
                stack[row] = j
                board = []
                for i in range(n):
                    str = '.'*(stack[i]) + 'Q' + '.'*(n - stack[i] - 1)
                    board.append(str)

                res.append(board)
                stack[row] = -1
                row -= 1
            else:
                SetIJ(row , j, colHt, lSlopeHt, rSlopeHt, buffShift)
                stack[row] = j
                row += 1
        return res
    

def CheckHt(i , j, colHt, lSlopeHt, rSlopeHt, rShift):
    if colHt[j] == 1:
        return True
    if lSlopeHt[i + j] == 1:
        return True
    if rSlopeHt[j - i + rShift] == 1:
        return True
    return False


def SetIJ(i , j, colHt, lSlopeHt, rSlopeHt, rShift):
    colHt[j] = 1
    lSlopeHt[i + j] = 1
    rSlopeHt[j - i + rShift] = 1


def ResetIJ(i , j, colHt, lSlopeHt, rSlopeHt, rShift):
    colHt[j] = 0
    lSlopeHt[i + j] = 0
    rSlopeHt[j - i + rShift] = 0
