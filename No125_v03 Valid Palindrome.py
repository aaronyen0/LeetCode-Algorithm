class Solution:
    """ version3, 44ms, 99%
    正規表示式(regular expression)
    根據使用心得，python有現成函式就要用
    多半都比自己刻快多了
    """
    def isPalindrome3(self, s: str) -> bool:
        import re
        s1 = re.sub('[^A-Za-z0-9]+', '', s).lower()
        if s1[::-1] == s1:
            return True
        else:
            return False
            
    """version2, 76ms, 26%
    嘗試傳統C語言的做法
    效能實在不能跟用現成函式比
    """
    def isPalindrome2(self, s: str) -> bool:
        i = 0
        j = len(s) - 1
        
        while True:
            while i < j and s[i].isalnum() == False:
                i += 1
            while i < j and s[j].isalnum() == False:
                j -= 1
                
            if i < j:
                if s[i].lower() == s[j].lower():
                    i += 1
                    j -= 1   
                else:
                    return False
            else:
                return True
    
    
    """version1, 64ms, 62%
    這寫法基本上是看別人的，因為我不知道python判斷英數字的語法有什麼
    str.isalnum()可以判定字串是否都是英文數字
    但是我們其實是要保留英文數字，只好逐字判斷
    另外lt[::-1]是將list逆著排
    python真的有很多有意思的寫法
    """
    def isPalindrome1(self, s: str) -> bool:
        lt = []
        for c in s:
            if c.isalnum():
                lt.append(c.lower())
        return lt == lt[::-1]
    
