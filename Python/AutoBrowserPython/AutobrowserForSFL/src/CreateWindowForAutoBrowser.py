import tkinter as tk
from tkinter import *


def CreateMyWindow():
    # declare the window

    window = Tk()
    # set window title
    window.title("AUTO SFL FARMING made by ALLEN TUMBAGAHAN")
    # set window width and height
    window.configure(width=500, height=300)
    # set window background color
    window.configure(bg='lightgray')
    f1 = tk.Frame()
    chk1 = tk.Checkbutton(f1, text="a", height=50, width=50)
    f1.pack()
    chk1.pack()
    window.mainloop()



