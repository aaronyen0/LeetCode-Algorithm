class Solution:
    def sortArrayByParityII(self, A):
        n = len(A)
        i = 0
        j = 1
        while 1:
            while i < n and A[i] & 1 == 0:
                i += 2

            while j < n and A[j] & 1 == 1:
                j += 2

            if i >= n or j >= n:
                break

            A[i], A[j] = A[j], A[i]
            i += 2
            j += 2
        return A
