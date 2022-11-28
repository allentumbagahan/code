import time
from SRC import MoreFunctions
import threading

A = "C:\\Users\\allen\AppData\\Local\\Google\\Chrome\\User Data"
B = 1
C = "200,350"
D = "https://sunflower-land.com/play/"
E = 'chrome-extension://nkbihfbeogaeaoehlefnkodbefgpgknn/popup.html'
p = "Tumbagahan0"
F = 50

MoreFunctions.SetupChrome(C, A, B)
MoreFunctions.launchURL(E, F)
MoreFunctions.ConnectMetamask(p)
time.sleep(3)
MoreFunctions.launchURL(D, F)
time.sleep(6)
MoreFunctions.SignIn()
task1 = threading.Thread(target=MoreFunctions.SignInMetamask)
task1.start()
print("done")
time.sleep(99999)