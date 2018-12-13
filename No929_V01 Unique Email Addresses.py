class Solution:
    def numUniqueEmails(self, emails):
        setNum = 0
        
        for mail in emails:
            flag = 0
            local, domain = mail.split("@")
            if '+' in local:
                local = local[0:local.index('+')]
            local = "".join(local.split(".")) + '@' + domain
            
            if local not in emails[0:setNum]:
                emails[setNum] = local
                setNum += 1

        return setNum
        

""" 
class Solution:
    def numUniqueEmails(self, emails):
        mySet = set()
        for mail in emails:
            n = len(mail)
            tmpMail = ""
            offset = 0
            plusFlag = 0
            for i in range(n):
                if mail[i] == '@':
                    if plusFlag == 0:
                        mySet.add(tmpMail + mail[offset:n])
                        #tmpMail += mail(offset, n)
                    else:
                        mySet.add(tmpMail + mail[i:n])
                        #tmpMail += mail(i, n)
                    break
                elif plusFlag == 0:
                    if mail[i] == '.':
                        tmpMail += mail[offset:i]
                        offset = i + 1
                    elif mail[i] == '+':
                        tmpMail += mail[offset:i]
                        plusFlag = 1
        return len(mySet)
""" 
