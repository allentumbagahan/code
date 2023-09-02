import undetected_chromedriver as uc
from selenium.webdriver.common.by import By
from selenium.common.exceptions import NoSuchElementException
import time
import pyautogui
import random

ShopData = []
ShopBuyButtons = []
mRight = False
mLeft = False
mouseDown = False
mouseUp = True
Drivers = []
browser = ""
TPlotsHarvest = 22
TPlotsPlant = 22
showData2 = 0
showData3 = 0
Harvesting = False
Planting = False
global R
R = False
PN = 0
MYSEEDS = {}
NeededSeeds = 22
PrioritizeSeeds = [
    'kale', 'wheat', 'radish', 'parsnip', 'cauliflower']
PrioritizeBuySeeds = [
    'Kale Seed', 'Wheat Seed', 'Radish Seed', 'Parsnip Seed', 'Cauliflower Seed']
BoughtSeeds = []
Ready2Plant = False
data3 = []
go = False


def SetupChrome(WINDOW_SIZE, UserDataDirectory, ProfileNumAlias, ProfileNum):
    global PN
    global browser
    PN = ProfileNum
    # open new chrome tab with new session CODE BELOW: (WORKING)
    op = uc.ChromeOptions()
    op.add_argument(
        f"--user-data-dir={UserDataDirectory}")
    op.add_argument(
        f"--profile-directory=Profile {ProfileNumAlias}")
    # create new chrome tab with load chrome profile dir
    browser = uc.Chrome(options=op)


def launchURL(url, Scale):
    global browser
    print(browser)
    if browser != "":
        print(browser)
        browser.get(url)
        browser.execute_script(f"document.body.style.zoom='{Scale}%'")
        print(len(browser.window_handles), "handles")
    else:
        print("no chrome driver use setup before launch")


def ConnectMetamask(password):
    global browser
    print("Sign In Metamask...")
    click1 = False
    a = True
    while a:
        while not click1:
            if not click1:
                click1 = Check_exists_by_element("id", "password", False, password)
                time.sleep(2)
            if click1:
                print("password entered done")
                browser.execute_script(
                    "document.querySelector('#app-content > div > div.main-container-wrapper > div > div > button').click()")
                a = False
        time.sleep(2)


def Check_exists_by_element(typeElement, xpath, click, Skeys):
    if typeElement == "xpath":
        try:
            a = browser.find_element(By.XPATH, xpath)
            if a:
                if click:
                    a.click()
                if Skeys != '':
                    a.send_keys(Skeys)
        except NoSuchElementException:
            return False
        if a:
            return True
        else:
            return False
    if typeElement == "text":
        try:
            a = browser.find_element(By.LINK_TEXT, xpath)
            if a:

                if click:
                    a.click()

                if Skeys != '':
                    a.send_keys(Skeys)
        except NoSuchElementException:
            return False
        if a:
            return True
        else:
            return False
    if typeElement == "tag":
        try:
            a = browser.find_element(By.TAG_NAME, xpath)
            if a:
                if click:
                    a.click()
                if Skeys != '':
                    a.send_keys(Skeys)
        except NoSuchElementException:
            return False
        if a:
            return True
        else:
            return False
    if typeElement == "class":
        try:
            a = browser.find_element(By.CLASS_NAME, xpath)
            if a:
                if click:
                    a.click()
                if Skeys != '':
                    a.send_keys(Skeys)
        except NoSuchElementException:
            return False
        if a:
            return True
        else:
            return False
    if typeElement == "css":
        try:
            a = browser.find_element(By.CSS_SELECTOR, xpath)
            if a:
                if click:
                    a.click()
                if Skeys != '':
                    a.send_keys(Skeys)
        except NoSuchElementException:
            return False
        if a:
            return True
        else:
            return False
    if typeElement == "id":
        try:
            a = browser.find_element(By.ID, xpath)
            if a:
                if click:
                    a.click()
                if Skeys != '':
                    a.send_keys(Skeys)
        except NoSuchElementException:
            print("element not found")
            return False
        if a:
            return True
        else:
            return False


def SignIn():
    # do not remove this prints

    while not Check_exists_by_element("xpath",
                                      "/html/body/div[2]/div/div/div[2]/div/div/button[1]",
                                      False, ""):
        print(Check_exists_by_element("xpath",
                                      "/html/body/div[2]/div/div/div[2]/div/div/button[1]",
                                      True, ""), "SignIn")

    else:
        print(Check_exists_by_element("xpath",
                                      "/html/body/div[2]/div/div/div[2]/div/div/button[1]",
                                      False, ""), "SignIn")
        browser.execute_script(
            'document.querySelector("body > div.fade.modal.show > div > div > div.bg-brown-600.text-white.pb-1 > div > div > button:nth-child(2) > div > div").click()')
    time.sleep(3)


def SignInMetamask():
    a = False
    while not a:
        try:
            if len(browser.window_handles) > 0:
                browser.switch_to.window(browser.window_handles[1])
                browser.execute_script(
                    'document.querySelector("#app-content > div > div.main-container-wrapper > div > div.request-signature__footer > button.button.btn--rounded.btn-primary.btn--large.request-signature__footer__sign-button").click()')
                a = True
            else:
                a = False
        except:
            time.sleep(2)
    print(browser.window_handles)


def GetSFLData():
    browser.switch_to.window(browser.window_handles[0])
    # get filed 1 - 22 data
    a1 = False
    a = True
    while a:
        a1 = Check_exists_by_element("class", "flex-1", False, "")
        if a1:
            a = False
            try:
                even = False
                n = 1
                for b1 in browser.find_elements(By.CLASS_NAME, "flex-1"):
                    if even:
                        print(f" PLOT {n} : ")
                        print(b1.get_attribute('innerHTML').replace('&nbsp;', " "), f"IN PROFILE {PN}")
                        even = False
                        n = n + 1
                    else:
                        even = True
                print(f"TOTAL PLOT PLANTED {n - 1}")
            except:
                print("something went wrong from field 1")
        else:
            time.sleep(0.5)


def GetSFLData2():
    browser.switch_to.window(browser.window_handles[0])
    # get ready plots
    global showData2
    global TPlotsPlant
    global Ready2Plant
    c1 = False
    c = True
    data1 = []
    nn = 0
    while c:
        c1 = Check_exists_by_element("tag", "small", False, "")
        if c1:
            ca1 = browser.find_element(By.TAG_NAME, "small")
            if float(ca1.get_attribute('innerHTML')) > 0.0000:
                c = False
                try:
                    for d1 in browser.find_elements(By.TAG_NAME, "img"):
                        if d1.get_attribute('class') == 'absolute':
                            data1.append(d1)
                    for d2 in data1:
                        if d2.get_attribute(
                                'src') == 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAaCAMAAACJtiw1AAAABGdBTUEAALGOfPtRkwAAABJQTFRFAAAAcz45Picx5KZyuG9QwoVpdG2/2AAAAAZ0Uk5TAP//////enng/gAAAEtJREFUGJXljsERACEIA8WQ/lu+GAaPHtwHQ3ZAXOs90oxMCLahcggZztxGhRlbxOnogdwm0aJM4u7ICMxXUXd575rOxxj+X60Jtx/G9AIB2PftNQAAAABJRU5ErkJggg==':
                            nn += 1
                except:
                    print("something went wrong from field 1")
            else:
                time.sleep(0.5)
    if Ready2Plant:
        showData2 = 0
        TPlotsPlant = browser.execute_script(
            'Count = 0; djsfiuduhfid = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAaCAMAAACJtiw1AAAABGdBTUEAALGOfPtRkwAAABJQTFRFAAAAcz45Picx5KZyuG9QwoVpdG2/2AAAAAZ0Uk5TAP//////enng/gAAAEtJREFUGJXljsERACEIA8WQ/lu+GAaPHtwHQ3ZAXOs90oxMCLahcggZztxGhRlbxOnogdwm0aJM4u7ICMxXUXd575rOxxj+X60Jtx/G9AIB2PftNQAAAABJRU5ErkJggg=="; jdnsfndfb = document.getElementsByTagName("img"); for (let x = 0; x < jdnsfndfb.length; x++){ if (jdnsfndfb[x].getAttribute("src") == djsfiuduhfid){ Count++; }; }; return Count;')
        print('test ready to plant')
        if TPlotsPlant > 0:
            print('test picking seed')
            PickSeed()
        else:
            print("done planting")
            global R
            R = True
    TPlotsPlant = browser.execute_script(
        'Count = 0; djsfiuduhfid = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAaCAMAAACJtiw1AAAABGdBTUEAALGOfPtRkwAAABJQTFRFAAAAcz45Picx5KZyuG9QwoVpdG2/2AAAAAZ0Uk5TAP//////enng/gAAAEtJREFUGJXljsERACEIA8WQ/lu+GAaPHtwHQ3ZAXOs90oxMCLahcggZztxGhRlbxOnogdwm0aJM4u7ICMxXUXd575rOxxj+X60Jtx/G9AIB2PftNQAAAABJRU5ErkJggg=="; jdnsfndfb = document.getElementsByTagName("img"); for (let x = 0; x < jdnsfndfb.length; x++){ if (jdnsfndfb[x].getAttribute("src") == djsfiuduhfid){ Count++; }; }; return Count;')

    if showData2 == 0:
        print(f'TOTAL READY PLOT/s TO PLANT : {TPlotsPlant}')
        showData2 += 1
        print("test")


def InputLog():
    global R
    global browser
    while not R:
        i = input('command type HELP for cmd list : ')
        st0 = i == "refresh plots v1" or i == 'rp1' or i == 'plots' or i == 'planted'
        st1 = i == "countdown" or i == 'cd'
        st3 = i == "refresh plots v2" or i == 'rp2' or i == 'ready plot'
        st4 = i == "get balance" or i == 'bal' or i == 'balance'
        st5 = i == "refresh plots v3" or i == 'rp3' or i == 'h' or i == 'harvest'
        st6 = i == 'all plots' or i == 'rp' or i == 'ap'
        st7 = i == 'fp'
        st8 = i == 'fh'
        st9 = i == 'r' or i == 'restart'
        # for plot refreshing
        if st0:
            t = 2
            while t != 0:
                print(f'refreshing data...... in {t}sec')
                t = t - 1
                time.sleep(1)
            else:
                GetSFLData()
        # testing countdown
        if st1:
            c = input('Enter Value : ')
            CountDown("", c, "", "done")
        # for plot refreshing
        if st3:
            t = 2
            while t != 0:
                print(f'refreshing data...... in {t}sec')
                t = t - 1
                time.sleep(1)
            else:
                GetSFLData2()
        # get balance
        if st4:
            for x in browser.window_handles:
                browser.switch_to.window(browser.window_handles[x])
                CountDown("refreshing data balance.... ", 3, "sec/s", "done")
                ca1 = browser.find_element(By.TAG_NAME, "small")
                print('SFL BALANCE : ', ca1.get_attribute('innerHTML'))

            # for plot refreshing data ready harvest
        if st5:
            t = 2
            while t != 0:
                print(f'refreshing data...... in {t}sec')
                t = t - 1
                time.sleep(1)
            else:
                GetSFLData3()
        if st6:
            t = 2
            while t != 0:
                print(f'refreshing data...... in {t}sec')
                t = t - 1
                time.sleep(1)
            else:
                GetSFLData()
                GetSFLData2()
                GetSFLData3()
        if st7:
            t = 3
            while t != 0:
                print(f'refreshing data...... in {t}sec')
                t = t - 1
                time.sleep(1)
            else:
                FindPlotToPlant()
        if st8:
            t = 3
            while t != 0:
                print(f'refreshing data...... in {t}sec')
                t = t - 1
                time.sleep(1)
            else:
                FindPlotToHarvest()
        if st9:
            t = 2
            while t != 0:
                print(f'refreshing data...... in {t}sec')
                t = t - 1
                time.sleep(1)
            else:
                R = True
        time.sleep(1)
    else:
        exit()


def CountDown(text1, time1, text2, finishTEXT):
    t = int(time1)
    while t != 0:
        print(text1, text2)
        try:
            t = t - 1
        except:
            print("only number can be use")
        time.sleep(1)
    print(finishTEXT)


def CheckSFLCropsImageBase64(img1):
    # cauliflower base64
    a_1 = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAaBAMAAABMRsE0AAAAHlBMVEUAAADChWnot5b///+4b1A+iUgmXELkpnJjx00ZPD7nOhu4AAAAAXRSTlMAQObYZgAAAHNJREFUCNdjoCkQFITQjMrGAmCGkLGxIVhAydgYKARhGEEYysZKIIZYkJKSaiJQILVVSSkiTIBBJLUjSLUjzJFBRCw0LS00EcgQTA1LDRN0ZGB0lJw5c6IIUJuIeHl5oSPIHEdBQZAAUMjFxRFiu6AgUAAAtjgS/44RDAEAAAAASUVORK5CYII='
    # wheat base64
    a_2 = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAaBAMAAABMRsE0AAAAGFBMVEUAAAD3diL7qiDChWn/3h//+U64b1DkpnJ7WpR1AAAAAXRSTlMAQObYZgAAAGtJREFUCNeli8EJgDAQBE/TgAkpwQJCDvKP2ICxAw/SgP2Du8GHf3cfNwx78jeTZwFxZxeRsLGAuLI01Vc/zBgBJk74NXMSCDSE/Bp3HUhLUnJj7APKe5o4yy23kgRKbzURKFUKqN4hqFQhHr6jF7YkwRNkAAAAAElFTkSuQmCC'
    # radish base64
    a_3 = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAaBAMAAABMRsE0AAAAJFBMVEUAAADChWmiJjPkpnImXEK4b1A+iUhjx03kO0QZPD4+JzH2dXpYgMGVAAAAAXRSTlMAQObYZgAAAIdJREFUCNdjIBOwuDgAEZDhVl7iXp4CYqSXpZeBGWnl5WkgBsu0tLRMB5BqzimeEyD6pnhCaCYVJwUwQ6OjuwnK6NgEokUXKSlpBTIwMAaCGKICDKKCUkpKCw0DGUSFDZWUhMEMY0FBYyCDMdAYCIBqQEIgAZA2QUGQAFAoNBQoABISFAQKAABSWBv0yZXJuwAAAABJRU5ErkJggg=='
    # parsnip base64
    a_4 = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAaBAMAAABMRsE0AAAAHlBMVEUAAADChWnkpnK4b1AmXELq1Kq+Si9jx00+iUj///9xy9fYAAAAAXRSTlMAQObYZgAAAIVJREFUCNdjoBiwOLA4gBnuJe4lYIHyivZyBxCjwqOlHSzn0tHhAlbD7NFiAGZYprhNBgtMDUuNBAmxqUZODUoAMsSUIqcqJTIwMBomqQapCQswCAuCGIqGDMJCYqpBiWCGoqCgEJDBaKgEBEA1QCElJaAASJugIEgAKGRsDBQACQkKAgUAEiAXgs1l8PAAAAAASUVORK5CYII='
    # beetroot base64
    a_5 = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAaBAMAAABMRsE0AAAAJFBMVEUAAADChWm1UIj2dXrkpnJoOGy4b1AmXEJjx00+iUgZPD4+JzG8VHZ6AAAAAXRSTlMAQObYZgAAAI1JREFUCNdjoBSwlxcAEZBR0dEOREBGpUXnjObpIMbUjo5IEIN9ZeTUWQUg1VxLoxaAtSmrBhmBaCZjIFAAMZSNjY1ADFElY2OlQAYGxuwgJSXVbQIMYoJbg1SjHRMZxESkQ0M3ghmOgoIiQAZjogsQiAkwAIVcXIACDEAhQUGQAFAoLQ0oABISFAQKAABxiB+r2l/ECQAAAABJRU5ErkJggg=='
    # cabbage base64
    a_6 = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAaBAMAAABMRsE0AAAAIVBMVEUAAAC1UIjChWloOGw+iUgmXEL2dXq4b1Dot5bkpnJjx02gg3eLAAAAAXRSTlMAQObYZgAAAI5JREFUCNe1yK0OwyAYRuF3PxewLyRkciFpyNwIVVNLWkwlgwvANGhM9QypnqteL3TQe+hRJw926BDzZZsr0WeDTBQrncI88wdw7njMoX1h+PFxDM8Vg1I8MLbCKUakmIHrSGtqDZpeMcV6C+neWnuTIBtnnLEJx9R4b+UNkPdl+SagkBAVCk1TgUpCFPgDQhMb48Qjh9kAAAAASUVORK5CYII='
    # carrot base64
    a_7 = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAaBAMAAABMRsE0AAAAJFBMVEUAAADChWnkpnK4b1D+rjT3diK+Si9jx01Np2/+52E+iUgmXEK3n0dnAAAAAXRSTlMAQObYZgAAAIFJREFUCNdjoB7gaOBoADPaq5ZXgBld5eUrwAzu5VUbwAyWXasdwAzP7G1TQDTrFLcUzwAggy3Ec4prApAhFuo5JTSRgYHRMDXENUxYgEFYEMRQNGQQFhILcU0EMxQFBYWADEZDJSAAqgEKKSkBBUDaBAVBAkAhY2OgAEhIUBAoAACDzBk8QJCv6AAAAABJRU5ErkJggg=='
    # pumpkin base64
    a_8 = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAaBAMAAABMRsE0AAAAIVBMVEUAAADChWm+Si/3diJzPjm4b1D+rjQmXELkpnJjx00+iUiURrsmAAAAAXRSTlMAQObYZgAAAHpJREFUCNdjoCIoh9LsMwugjJXToUJVUIZK1XInEM1k5OKSpgBkKBuZpaklgRjKxmlJcIYRAwOjs7KxWZKJAIOok5OxsYpKIIOoiIqSkpMjkCHo4qTiIhjIwBgoCASiAgwMohIdHY2BDAxAIYgAUCg0FCgAEhIUBAoAAAU9FceBmUu6AAAAAElFTkSuQmCC'
    # potato base64
    a_9 = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAaBAMAAABMRsE0AAAAJFBMVEUAAADChWnkpnImXEK4b1C+Si8+iUhzPjljx03XdkMZPD7LYDma8ZzCAAAAAXRSTlMAQObYZgAAAINJREFUCNdjIBcYG0No5owOAwgjrcPYGMw0TrPoSAaLrcpoS4ZKJkNVZS2A6As2hdDskzQLwIzKSZrTQbRI6eyd4Y4MDIyOpdFbw0UEGEQES0NDwxUdGUSExENDC8EMRUFBISCD0VEJCIBqgEJKSkABkDZBQZAAUMjFBSgAEhIUBAoAAFBtGPOHB1xBAAAAAElFTkSuQmCC'
    # sunflowerland base64
    a_10 = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAaBAMAAABMRsE0AAAAKlBMVEUAAADChWm+Si/kpnK4b1D/+U4+iUhzPjn/3h8mXEL7qiD3diJjx03/6zZBkCPGAAAAAXRSTlMAQObYZgAAAJRJREFUCNdjwAqYlKC0aiiEpbE1dIcCSKCj61ZHE4ixY3n5ik1AhmpUeXlVqAKQEVteXgtkwERgauC64ObATD4GYqQlKR3LBNJsZ05mpoEYkmknM2dOZGBg9ExLyzQWEWAQEZw5M9PZ0JFBRNhEMhHCMHYUNAYyGB2NgQCoBiQEEmAACgkKggSAQi4uQAGQkKAgUAAAqsosXwoI3jUAAAAASUVORK5CYII='
    # kale base64
    a_11 = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAaBAMAAABMRsE0AAAAGFBMVEUAAAA+iUjChWljx00mXEK4b1DkpnIZPD7vWzZFAAAAAXRSTlMAQObYZgAAAHFJREFUCNe1yjEKhTAQBND1n+DP38BvdSH2i14gGLAPeAGL9IL3x4mewWmWeTvyaoDndtP0fborjT24JlqnM7A4nwhAavOQ1XNqm7zMmZvBw/FP+pOI9VxPFIl2p8inVCb2InGsdS8iJLMGpG0jNDIjXDNuEVbMm8UhAAAAAElFTkSuQmCC'
    SC = img1 == a_1 or img1 == a_2 or img1 == a_3 or img1 == a_4 or img1 == a_5 or img1 == a_6 or img1 == a_7 or img1 == a_8 or img1 == a_9 or img1 == a_10 or img1 == a_11
    if SC:
        a = True
    else:
        a = False
    return a


def GetSFLData3():
    browser.switch_to.window(browser.window_handles[0])
    # get ready to harvest
    global TPlotsHarvest
    global showData3
    c1 = False
    c = True
    data2 = []
    nn = 0
    while c:
        c1 = Check_exists_by_element("tag", "small", False, "")
        if c1:
            ca1 = browser.find_element(By.TAG_NAME, "small")
            if float(ca1.get_attribute('innerHTML')) > 0.0000:
                c = False
                try:
                    for d1 in browser.find_elements(By.TAG_NAME, "img"):
                        if d1.get_attribute('class') == 'absolute':
                            data2.append(d1)
                    for d2 in data2:
                        if CheckSFLCropsImageBase64(d2.get_attribute('src')):
                            nn += 1
                except:
                    print("something went wrong from field 1")
            else:
                time.sleep(0.2)
    TPlotsHarvest = nn
    if showData3 == 0:
        print(f'TOTAL READY PLOT/s HARVEST : {TPlotsHarvest}')
        showData3 += 1


def FindPlotToPlant():
    global Planting
    Planting = True
    browser.switch_to.window(browser.window_handles[0])
    # find plot ready to plant
    n = 0
    g = False
    print('FINDING PLOT READY TO PLANT :')
    for x in browser.find_elements(By.CSS_SELECTOR, "div.relative.group"):
        for e in x.find_elements(By.TAG_NAME, 'img'):
            if not g:
                if e.get_attribute(
                        'src') == 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAaCAMAAACJtiw1AAAABGdBTUEAALGOfPtRkwAAABJQTFRFAAAAcz45Picx5KZyuG9QwoVpdG2/2AAAAAZ0Uk5TAP//////enng/gAAAEtJREFUGJXljsERACEIA8WQ/lu+GAaPHtwHQ3ZAXOs90oxMCLahcggZztxGhRlbxOnogdwm0aJM4u7ICMxXUXd575rOxxj+X60Jtx/G9AIB2PftNQAAAABJRU5ErkJggg==':
                    print(f'PLOT {n}')
                    g = True
            if g:
                if e.get_attribute(
                        'src') == 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAB4AAAAeAgMAAABGXkYxAAAABGdBTUEAALGPC/xhBQAAAAxQTFRFAAAAuG9Q6tSqJitEPjZUHQAAAAF0Uk5TAEDm2GYAAABhSURBVBjTY+D/z8DAACKsVgMZfKsOMLyCMDYwvAoHMnijkBl/gAzmXxsYrh4AMhhMCxAMexDNwA/m0g3ALX0FttdqAxID7C+gU+HeuQVhAN0M9k5oAYMphHGAgR/sr/8MAKPEKneqHAQSAAAAAElFTkSuQmCC':
                    # click element here
                    ClickPlot(f'PLOT {n}', 'planting')
                    g = False
        n += 1
    Planting = False
    GetSFLData2()
    # next


def ClickPlot(p, action):
    # add here picking seed
    t = 0.1
    browser.execute_script("d = []")
    browser.execute_script('a = document.getElementsByTagName("img")')
    browser.execute_script(
        'for (let i = 0; i < a.length; i+=2) { if (a[i].src == "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAB4AAAAeAgMAAABGXkYxAAAABGdBTUEAALGPC/xhBQAAAAxQTFRFAAAAuG9Q6tSqJitEPjZUHQAAAAF0Uk5TAEDm2GYAAABhSURBVBjTY+D/z8DAACKsVgMZfKsOMLyCMDYwvAoHMnijkBl/gAzmXxsYrh4AMhhMCxAMexDNwA/m0g3ALX0FttdqAxID7C+gU+HeuQVhAN0M9k5oAYMphHGAgR/sr/8MAKPEKneqHAQSAAAAAElFTkSuQmCC") { console.log(a[i].src); d.push(a[i]); }}')
    b = p.replace("PLOT ", "")
    a = b.replace(" ", "")
    CountDown(f"{action} at ...... plot : {a}", t, "", "done")
    try:
        browser.execute_script(f"d[{a}].click()")
    except:
        print('error planting')


def ConnectingSFL():
    browser.switch_to.window(browser.window_handles[0])
    global R
    while not R:
        if Check_exists_by_element("css", "span.text-shadow.loading", False, ""):
            try:
                e = browser.find_element(By.CSS_SELECTOR, "span.text-shadow.loading")
                print(e.get_attribute('innerHTML'))
                time.sleep(3)
            except:
                print('something went error')
        time.sleep(1)
    else:
        exit()


def FindPlotToHarvest():
    global Harvesting
    Harvesting = True
    # find plot ready to plant
    n = 0
    print('FINDING PLOT READY TO HARVEST :')
    for x1 in browser.find_elements(By.CSS_SELECTOR, "div.relative.group"):
        for e in x1.find_elements(By.TAG_NAME, 'img'):
            if e.get_attribute('class') == 'absolute':
                if CheckSFLCropsImageBase64(e.get_attribute('src')):
                    CountDown('harvesting...', 0.1, f'PLOT {n}', 'done')
                    ClickPlot(f'PLOT {n}', 'harvesting')

        n += 1
    Harvesting = False


def PickSeed():
    try:
        browser.execute_script(
            "a = document.getElementsByTagName('img')")
        browser.execute_script(
            'for ( x = 0; x < a.length; x++ ){ if (a[x].src == "https://sunflower-land.com/play/assets/round_button.cae0e1ef.png"){ a[x].click() }}')
        browser.execute_script(
            'ZXC = []; b1zz = document.getElementsByClassName("flex flex-col pl-2"); b1x = b1zz[0].getElementsByTagName("span"); for ( x = 0; x < b1x.length; x++ ){ if (b1x[x].getAttribute("class") == " text-white text-xxs"){ ZXC.push(b1x[x])}}; ZXC[(ZXC.length) - 1].click();')
        browser.execute_script(
            'SBHJGGUSGDUISGD = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAsAAAALAgMAAADUwp+1AAAABGdBTUEAALGPC/xhBQAAAAxQTFRFAAAAi5u0GBQl////mo6iugAAAAF0Uk5TAEDm2GYAAAA1SURBVAjXY9BiWsCwv/sHw/z3Nxim/49gUPuXwMD9v4FB//4Dhv3hPxjmpt5gmNoZwQBUBwCl3RKJRykUxQAAAABJRU5ErkJggg==";HDJSFJ = document.getElementsByTagName("img");for (x = 0; x < HDJSFJ.length; x++){if (HDJSFJ[x].getAttribute("src") == SBHJGGUSGDUISGD){HDJSFJ[x].click();};}')
        FindPlotToPlant()
    except:
        print("something went wrong with picking seed")


def update():
    OneTime = True
    global R
    while True:
        print("update")
        while not R:
            print("restart false update")
            global TPlotsHarvest
            global TPlotsPlant
            if len(browser.window_handles) > 1:
                try:
                    browser.switch_to.window(browser.window_handles[1])
                except:
                    print('no second handles')
            else:
                browser.switch_to.window(browser.window_handles[0])
            print("GetSFLData2")
            GetSFLData2()
            print("GetSFLData3")
            GetSFLData3()
            print("opening shop")
            if TPlotsHarvest != 0:
                if not Harvesting:
                    FindPlotToHarvest()
            else:
                if TPlotsPlant == 0:
                    GetSFLData()
                    print('restarting...')
                    R = True
                    restart()
                else:
                    if OneTime:
                        OneTime = False
                        OpenShop()
                    else:
                        print(OneTime, "OneTime")
        time.sleep(2)


def restart():
    global R
    return R


def OpenShop():
    c1 = Check_exists_by_element("tag", "small", False, "")
    if c1:
        ca1 = browser.find_element(By.TAG_NAME, "small")
        if float(ca1.get_attribute('innerHTML')) > 0.0000:
            try:
                browser.execute_script(
                    'document.querySelector("#shop > img").click()')
            except:
                print("something went wrong ")
                time.sleep(1)
            else:
                CountDown('Getting Seeds Stock ', 2, ".....", "Getting Seeds Stock Done")
                # GetSeedStock()
                SellSeeds()


def CrazyCursorForSFL():
    global Harvesting
    global Planting
    global mRight
    global mLeft
    global mouseDown
    global mouseUp
    while Harvesting or Planting:
        positonOfBrowser = browser.get_window_position(windowHandle='current')
        bnph = browser.execute_script('return window.outerHeight;')
        bnpw = browser.execute_script('return window.outerWidth;')
        centerWindowY = (positonOfBrowser['y'] + (bnph / 2))
        centerWindowX = (positonOfBrowser['x'] + (bnpw / 2))
        # start
        # setup window size and location
        # move mouse to the center of current browser window
        if mouseUp:
            pyautogui.mouseDown(centerWindowX, centerWindowY + 50, "left")
            mouseDown = True
            mouseUp = False
        currentMouseX, currentMouseY = pyautogui.position()
        if mRight or not mLeft:
            pyautogui.moveTo(centerWindowX + 200, centerWindowY - random.randint(-300, 300), 0.1)
            mRight = False
            mLeft = True
        if mLeft:
            pyautogui.moveTo(centerWindowX - 200, centerWindowY + random.randint(-300, 300), 0.1)
            mRight = True
            mLeft = False
        # End
    else:
        if mouseDown:
            currentMouseX, currentMouseY = pyautogui.position()
            pyautogui.mouseUp(currentMouseX, currentMouseX, "left")
            mouseDown = False
            mouseUp = True
            print(Harvesting)


def CrazyCursorTaskThreading():
    while True:
        CrazyCursorForSFL()


def GetSeedStock():
    global MYSEEDS
    browser.execute_script(
        'jidhfhbd1 = document.getElementsByClassName("text-sm"); for (let x = 0; x < jidhfhbd1.length; x++){ if (jidhfhbd[x].innerText == "Buy"){ dsfhnuawei = jidhfhbd1[x]; dsfhnuawei.click(); }; };')
    MYSEEDS = browser.execute_script(
        'Seedname = ["sunflower", "potato", "pumpkin", "carrot", "cabbage", "beetroot", "cauliflower", "parsnip", "radish", "wheat", "kale"]; class Seed{constructor(name, stock){this.stock = stock;this.name = name;}};Seeds = [];el1 = document.getElementsByClassName("w-full sm:w-3/5 h-fit h-fit overflow-y-auto scrollable overflow-x-hidden p-1 mt-1 sm:mt-0 sm:mr-1 flex flex-wrap");relatives = el1[0].querySelectorAll(".relative");for (let x = 0; x != 11; x++){y = relatives[(x*2)].getElementsByTagName("span")[0];if (typeof(y) != "undefined"){Seeds.push(new Seed(Seedname[x], y.innerHTML))};}; return Seeds')
    print(MYSEEDS, "MYSEEDS STOCK")
    GetShopStockData()


def StartAgain():
    global R
    global ShopData
    global showData2
    global showData3
    global TPlotsPlant
    global TPlotsHarvest
    global ShopBuyButtons
    global Ready2Plant
    R = False
    showData2 = 0
    showData3 = 0
    TPlotsHarvest = 22
    TPlotsPlant = 22
    ShopData = []
    ShopBuyButtons = []
    Ready2Plant = False


def GetShopStockData():
    global ShopData
    global ShopBuyButtons
    global TPlotsPlant
    global NeededSeeds
    global PrioritizeBuySeeds
    global MYSEEDS
    global Ready2Plant
    NeededSeeds = TPlotsPlant
    print(NeededSeeds)
    global BoughtSeeds
    # set Needed seed base on (Total ready plots - Seeds on Inventory(priority))
    print(MYSEEDS[0], "my seeddata 0")
    for x in range(len(MYSEEDS)):
        a = MYSEEDS[x]
        print(a)
        print(a.get("name"))
        if NeededSeeds != 0:
            if a.get("name") in PrioritizeSeeds:
                NeededSeeds = NeededSeeds - int(a.get("stock"))
    if NeededSeeds < 0:
        NeededSeeds = 0
    for x in range(11):
        num = 0
        y = 10 - x
        browser.execute_script(f'X = {y};')
        browser.execute_script(
            'data = {}; ShopStock = "0 in stock"; ShopStockNumber = 0; el1 = document.getElementsByClassName("w-full sm:w-3/5 h-fit h-fit overflow-y-auto scrollable overflow-x-hidden p-1 mt-1 sm:mt-0 sm:mr-1 flex flex-wrap"); relatives = el1[0].querySelectorAll(".relative"); y2 = relatives[(X*2)].getElementsByTagName("div")[0]; y2.click(); el1a = document.getElementsByClassName("bg-blue-600 border text-xxs px-2 py-1 rounded-md w-auto -mt-2 mb-1"); if (typeof(el1a[0]) != "undefined"){ ShopStock = el1a[0].innerText}; el1b = document.getElementsByClassName("text-center"); for (let x = 0; x < el1b.length; x++){ a = el1b[x].innerText; if(a.includes("Seed")){ el1bz = el1b[x];}}; if (typeof(el1bz) != "undefined"){ ShopName = el1bz.innerText; }; ShopStockNumber = ShopStock.replace(" in stock", ""); data = { "name": ShopName, "stock": ShopStockNumber };')
        dataNow = browser.execute_script('return data;')
        ShopData.append(browser.execute_script('return data;'))
        ShopBuyButtons.append(browser.execute_script('return y2;'))
        print(NeededSeeds)
        time.sleep(1)
        # Buy Seeds
        for o in range(NeededSeeds):
            # print(int(dataNow.get('stock')))
            if dataNow.get('name') in PrioritizeBuySeeds:
                if int(dataNow.get('stock')) != 0:
                    browser.execute_script(
                        'el2b = document.getElementsByClassName("bg-brown-200 w-full p-1 text-white text-shadow text-sm object-contain justify-center items-center hover:bg-brown-300 cursor-pointer flex disabled:opacity-50  text-xs mt-1");')
                    btn1 = browser.execute_script('return el2b[0].innerText;')
                    if btn1 == 'Buy 1':
                        browser.execute_script('el2b[0].click();')
                        num += 1
                        NeededSeeds -= 1
        if num != 0:
            BoughtSeeds.append({
                "name": dataNow.get('name'),
                "quantity": num})
    print(BoughtSeeds)
    if NeededSeeds == 0:
        print("planting time")
        Ready2Plant = True
        PickSeed()
    else:
        print("time to synchronize")
    print(ShopData)
    # print(ShopData[0].get('name')) - the way to get data from shop data


def SellSeeds():
    global data3
    global go
    go = False
    browser.execute_script(
        'jidhfhbd = document.getElementsByClassName("text-sm"); for (let x = 0; x < jidhfhbd.length; x++){ if (jidhfhbd[x].innerText == "Sell"){ dsfhnuawei = jidhfhbd[x]; dsfhnuawei.click(); }; };')
    for x in range(11):
        go = False
        browser.execute_script(
            f'X1 = {x};')
        browser.execute_script(
            'FGH = document.getElementsByClassName("absolute flex justify-center items-center w-full h-full");FGH[(((FGH.length) - 11)+X1)].click();')
        browser.execute_script(
            'a = document.getElementsByClassName("bg-brown-200 w-full p-1 text-white text-shadow text-sm object-contain justify-center items-center hover:bg-brown-300 cursor-pointer flex disabled:opacity-50  text-xs mt-1 mr-1 sm:mr-0 flex-1");')
        while not browser.execute_script('try_a = a[0].disabled; return try_a'):
            print("btn1")
            browser.execute_script(
                'a[0].click();')
            time.sleep(0.3)
        else:
            go = True
        time.sleep(0.3)
    while True:
        if go:
            go = False
            time.sleep(3)
            GetSeedStock()
