import undetected_chromedriver as uc
from selenium.webdriver.common.by import By
from selenium.common.exceptions import NoSuchElementException
import time
from src import CreateWindowForAutoBrowser
import os

# Variables
os.system("taskkill /im chrome.exe /f")
time.sleep(2)
MetamaskNotifUrl = "chrome-extension://nkbihfbeogaeaoehlefnkodbefgpgknn/notification.html#unlock"
SunflowerLandUrl = 'https://sunflower-land.com/play/'
SunflowerLandFarmUrl = 'farm'
CreateWindowForAutoBrowser.CreateMyWindow()
UserDataDirectory = "C:\\Users\\allen\AppData\\Local\\Google\\Chrome\\User Data"
ProfileNum = 10
WINDOW_SIZE = "200,350"
MyHandles = []


def ConnectMetaMask(password):
    # change window handle
    WaitForMetaMaskWindow = True
    while WaitForMetaMaskWindow:
        if len(browser.window_handles) > 1:
            WaitForMetaMaskWindow = False
            MetamaskWin = browser.window_handles[1]
            browser.switch_to.window(MetamaskWin)
            time.sleep(2)
            # enter metamask password
            elem1 = browser.find_element(By.ID, "password")
            elem1.send_keys(password)
            print('password input done')
            # enter confirm password
            elem2 = browser.find_element(By.TAG_NAME, 'button')
            elem2.click()
            browser.switch_to.window(browser.window_handles[0])
            # check sign in
            time.sleep(3)
            signIn = check_exists_by_element("xpath", "/html/body/div[2]/div/div/div[2]/div/span[1]")
            print(signIn, 'signIn')
            if signIn:
                tryVar = True
                while tryVar:
                    if len(browser.window_handles) > 1:
                        tryVar = False
                        print(browser.window_handles, "check handles")
                    else:
                        # exit signIn if sign window didn't appear
                        currentURL = SetCurrentURLwithoutHPTTPS()
                        if SunflowerLandFarmUrl in currentURL:
                            tryVar = False


def StartSunflowerLAnd():
    if len(browser.window_handles) > 0:
        browser.execute_script("window.open('{}');".format(SunflowerLandUrl))


def waitUntil(condition, output, timeout):  # defines function

    wU = True
    while wU:
        print(condition)
        if condition:  # checks the condition
            output
            wU = False
        else:
            print('not exists')
        time.sleep(timeout)  # waits for preformance (in seconds)


def waitUntilCurrentUrlContains(s1, timeout):  # defines function

    w = True
    while w:
        currentURL = SetCurrentURLwithoutHPTTPS()
        print(currentURL)
        if s1 in currentURL:  # checks the condition
            print('current url contains', SunflowerLandFarmUrl)
            w = False
            GetFarmFieldData()
        else:
            print('not exists')
            T2 = threading.Thread(target=SignInMetamask())
            T2.start()
        time.sleep(timeout)  # waits for preformance (in seconds)


def GetFarmFieldData():
    browser.switch_to.window(browser.window_handles[0])
    print('ckecking balance')
    # get sfl balance
    varA: bool = True
    ElemBal = check_exists_by_element("xpath", "/html/body/div/div/div/div[3]/div[2]/span")
    while varA:
        if ElemBal:
            if check_exists_by_element("css", "body > div.fade.modal.show > div > div > div > div > span"):
                time.sleep(1)
                print("loading")
            else:
                time.sleep(5)
                varA = False
                print(browser.page_source)
                bal = browser.find_element(By.TAG_NAME, 'small')
                print("balance: ", bal.text)
                print(bal.text == "")
                print(browser.page_source)
                while bal.text == "":
                    bal = browser.find_element(By.TAG_NAME, 'small')
                    print(bal.text)
                    print("balance: ", bal.text)
        else:
            ElemBal = check_exists_by_element("xpath", "/html/body/div/div/div/div[3]/div[2]/span")


def check_exists_by_element(typeElement, xpath):
    if typeElement == "xpath":
        try:
            browser.find_element(By.XPATH, xpath)
        except NoSuchElementException:
            return False
        return True
    if typeElement == "text":
        try:
            browser.find_element(By.LINK_TEXT, xpath)
        except NoSuchElementException:
            return False
        return True
    if typeElement == "tag":
        try:
            browser.find_element(By.TAG_NAME, xpath)
        except NoSuchElementException:
            return False
        return True
    if typeElement == "class":
        try:
            browser.find_element(By.CLASS_NAME, xpath)
        except NoSuchElementException:
            return False
        return True
    if typeElement == "css":
        try:
            browser.find_element(By.CSS_SELECTOR, xpath)
        except NoSuchElementException:
            return False
        return True


def SignInMetamask():
    while not check_exists_by_element("text", "Accept the signature request in your browser wallet to login."):
        while check_exists_by_element("text", "Accept the signature request in your browser wallet to login."):
            MetamaskWin = browser.window_handles[1]
            browser.switch_to.window(MetamaskWin)
            SignInButton = check_exists_by_element("xpath", "/html/body/div[1]/div/div[2]/div/div[3]/button[2]")
            print(SignInButton, 'check signIn button if exists')
            if SignInButton:
                time.sleep(1)
                ElemSignInButton = browser.find_element(By.XPATH, "/html/body/div[1]/div/div[2]/div/div[3]/button[2]")
                ElemSignInButton.click()
                print("signed")
        else:
            print("sigIn button not exits")
            time.sleep(2)


def SetCurrentURLwithoutHPTTPS():
    browser.switch_to.window(browser.window_handles[0])
    c = browser.current_url.replace("https://", "")
    return c


def waitforuntil_DELAY(condition):
    wU = True
    while wU:
        print(condition)
        if condition:  # checks the condition
            wU = False  # exit this function if meet the condition


class HANDLE:
    def __init__(self, handleID):
        self.handleID = handleID


# open new chrome tab with new session CODE BELOW: (WORKING)
op = uc.ChromeOptions()
# add arg to load session CODE BELOW: (WORKING BUT OPEN URL NOT WORKING)
prefs = {'exit_type': 'none'}
op.add_experimental_option("prefs", {'profile': prefs})
op.add_argument("--window-size=%s" % WINDOW_SIZE)
op.add_argument(f"--user-data-dir={UserDataDirectory}")
op.add_argument(f"--profile-directory=Profile {ProfileNum}")
# create new chrome tab with load chrome profile dir
browser = uc.Chrome(options=op)
print(browser)
browser.get(SunflowerLandUrl)
print(MyHandles)
browser.execute_script("console.log(`Hello from Python`)")  # send from chrome console
browser.execute_script("document.body.style.zoom='50%'")  # zoom out by 50%
print(browser.window_handles, 'handles')
# print(browser.page_source)
# setup metamask and sunflowerland
# check and click connect metamask button
time.sleep(2)
while check_exists_by_element("xpath", "/html/body/div[2]/div/div/div[2]/div/div/button[1]"):
    elem = browser.find_element(By.XPATH, "/html/body/div[2]/div/div/div[2]/div/div/button[1]").click()
    time.sleep(3)
    ConnectMetaMask('Tumbagahan0')
    waitUntilCurrentUrlContains(SunflowerLandFarmUrl, 20)
    print("DONE")
    # print(elem)
    # clear browser data before closing
    time.sleep(1000)
else:
    waitUntilCurrentUrlContains(SunflowerLandFarmUrl, 20)
    print("DONE")
    # print(elem)
    # clear browser data before closing
    time.sleep(1000)
