import pyautogui


def testClasses():
    data = []

    class Student:
        def __init__(self, name):
            self.name = name

        def myname(self):
            print(self.name)

    s1 = Student("allen")
    s2 = Student("julie")
    data.append(s1)
    data.append(s2)

    for x in data:
        x.myname()


def moveMouse():
    # pyautogui.moveTo(200, 300, 1)


moveMouse()
