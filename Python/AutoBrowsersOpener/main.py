import time
import undetected_chromedriver as uc
import threading
from selenium.webdriver.common.by import By
import os

BrowserHandles = []
print("Browser list ( 1 - 3 ) : ")
userInput = input()
if userInput == "1":
    browsers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 17, 18, 19, 20, 21, 23, 24, 28, 29, 30, 31, 32, 33, 35, 36, 37, 38, 39, 40]
elif userInput == "2":
    browsers = [16, 18, 19, 20, 21, 22, 23, 26, 27, 28, 29]  # All active
elif userInput == "3":
    browsers = [10, 12, 15]
C = "500, 500"
Alias1 = ['Profile 34',
          'Profile 2',
          'Profile 6',
          'Profile 8',
          'Profile 10',
          'Profile 12',
          'Profile 9',
          'Profile 13',
          'Profile 14',
          'Profile 16',
          'Profile 17',
          'Profile 20',
          'Profile 19',
          'Profile 21',
          'Profile 22',
          'Profile 25',
          'Profile 26',
          'Profile 27',
          'Profile 28',
          'Profile 31',
          'Profile 33',
          'Profile 36',
          'Profile 37',
          'Profile 38',
          'Profile 39',
          'Profile 40',
          'Profile 41',
          'Profile 42',
          'Profile 43',
          'Profile 45',
          'Profile 46',
          'STUPID GAMER',
          'Profile 5',
          '03',
          'Profile 47',
          'Profile 48',
          'Profile 50',
          'Profile 51',
          'Profile 52',
          'Profile 53']
E = "C:\\Users\\allen\AppData\\Local\\Google\\Chrome\\User Data"
D = "https://sunflower-land.com/play/"
F = 100
OnetimeKill = 0
M = 'chrome-extension://nkbihfbeogaeaoehlefnkodbefgpgknn/popup.html#'
password = 'Tumbagahan0'
ShakeURL = 'chrome-extension://nkbihfbeogaeaoehlefnkodbefgpgknn/notification.html'


def SetupChrome(WINDOW_SIZE, UserDataDirectory, ProfileNum, index):
    op = uc.ChromeOptions()
    # add arg to load session CODE BELOW: (WORKING BUT OPEN URL NOT WORKING)
    # prefs = {'exit_type': 'none'}
    # op.add_experimental_option("prefs", {'profile': prefs})
    op.add_argument("--window-size=%s" % WINDOW_SIZE)
    # op.add_argument(f"--user-data-dir={UserDataDirectory}")
    # op.user_data_dir = UserDataDirectory
    op.add_argument('--disable-tracking')
    op.add_argument("--no-sandbox");  # Bypass OS security model
    op.add_argument(f"--profile-directory={ProfileNum}")
    # create new chrome tab with load chrome profile dir
    BrowserHandles.append(uc.Chrome(options=op, version_main=113, user_data_dir=UserDataDirectory, executable_path='C:\Program Files\Google\Chrome\Application\chrome.exe'))
    BrowserHandles[index].get(D)
    print(BrowserHandles[index], "test")
    time.sleep(999999)


def LaunchSFL(url, Scale):
    print(BrowserHandles[0].window_handles, "test3")
    if len(BrowserHandles) != 0:
        print(len(BrowserHandles[0].window_handles))
        for x in range(len(BrowserHandles[0].window_handles)):
            print(x)
            print(BrowserHandles[0].window_handles[x])
            BrowserHandles[0].switch_to.window(BrowserHandles[0].window_handles[x])
            print(x, "test2")
            BrowserHandles[0].get(url)
            BrowserHandles[0].execute_script(f"document.body.style.zoom='{Scale}%'")
            time.sleep(0.3)
            try:
                BrowserHandles[0].execute_script(
                    "document.getElementsByClassName('bg-brown-200 w-full p-1 text-xs object-contain justify-center items-center hover:bg-brown-300 cursor-pointer flex disabled:opacity-50  mb-2 py-2 text-sm relative')[0].click()")
            except:
                print('element not fount')
            print(BrowserHandles, "handles")
            time.sleep(0.5)
    else:
        print("no chrome driver use setup before launch")


def SetupMetamask(url, Scale):
    print(BrowserHandles[0].window_handles, "test3")
    if len(BrowserHandles) != 0:
        print(len(BrowserHandles[0].window_handles))
        for x in range(len(BrowserHandles[0].window_handles)):
            print(x)
            print(BrowserHandles[0].window_handles[x])
            BrowserHandles[0].switch_to.window(BrowserHandles[0].window_handles[x])
            print(x, "test2")
            BrowserHandles[0].get(url)
            BrowserHandles[0].execute_script(f"document.body.style.zoom='{Scale}%'")
            time.sleep(0.4)
            try:
                elem1 = BrowserHandles[0].find_element(By.ID, "password")
                elem1.send_keys(password)
                BrowserHandles[0].execute_script(
                    "document.getElementsByClassName('button btn--rounded btn-default')[0].click()")
            except:
                print('element not fount')
            print(BrowserHandles, "handles")
            time.sleep(0.2)
    else:
        print("no chrome driver use setup before launch")


def MetamaskHandshake():
    print(BrowserHandles[0].window_handles, "test3")
    if len(BrowserHandles) != 0:
        print(len(BrowserHandles[0].window_handles))
        for x in range(len(BrowserHandles[0].window_handles)):
            BrowserHandles[0].switch_to.window(BrowserHandles[0].window_handles[x])
            BrowserHandles[0].execute_script(" function addJavascript(jsname,pos) { var th = document.getElementsByTagName(pos)[0]; var s = document.createElement('script'); s.setAttribute('type','text/javascript'); s.setAttribute('src',jsname); th.appendChild(s); return true; }; addJavascript('https://allentumbagahan.github.io/MYSFLBOTTINGv3/BotV2/BotScriptV2.js','body');")
            if BrowserHandles[0].current_url == ShakeURL:
                try:
                    BrowserHandles[0].execute_script(
                        "document.getElementsByClassName('button btn--rounded btn-primary btn--large request-signature__footer__sign-button')[0].click()")
                except:
                    print('element not found')
            else:
                print(BrowserHandles[0].current_url)
            time.sleep(0.2)
    else:
        print("no chrome driver use setup before launch")


def Run():
    os.system("taskkill /im chrome.exe /f")

    def createDrive():
        for x in browsers:
            task0 = threading.Thread(target=SetupChrome, args=(C, E, Alias1[x - 1], x - 1))
            task0.start()
            # task1.start()
            print(x)
            time.sleep(30)
        time.sleep(10)

    task01 = threading.Thread(target=createDrive)
    task01.start()
    task01.join()
    print(BrowserHandles)
    print(BrowserHandles[0].window_handles, "win")
    task2 = threading.Thread(target=SetupMetamask, args=(M, F))
    task2.start()
    task2.join()
    task3 = threading.Thread(target=LaunchSFL, args=(D, F))
    task3.start()
    task3.join()
    task4 = threading.Thread(target=MetamaskHandshake)
    task4.start()
    task4.join()


Run()
