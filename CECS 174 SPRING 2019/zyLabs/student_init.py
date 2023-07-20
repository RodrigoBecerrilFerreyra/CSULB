class Student:
    def __init__(self, name, score = 0, numquiz = 0):
        self.name = name
        self.tot_score = score
        self.numquiz = numquiz

    def getName(self):
        return self.name
    def addQuiz(self, score):
        self.tot_score += score
        self.numquiz += 1
    def getTotalScore(self):
        return self.tot_score
    def getAverageScore(self):
        return self.tot_score/self.numquiz

def main():
    st1 = Student('Jim Black')
    print(st1.getName())
    st1.addQuiz(10)
    st1.addQuiz(20)
    print(st1.getTotalScore())
    print(st1.getAverageScore())

main()
