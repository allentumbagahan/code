import undetected_chromedriver as uc
from selenium.webdriver.common.by import By
from selenium.common.exceptions import NoSuchElementException
import time
import os

Handles = []
browser = ""


def SetupChrome(WINDOW_SIZE, UserDataDirectory, ProfileNum):
    # open new chrome tab with new session CODE BELOW: (WORKING)
    os.system("taskkill /im chrome.exe /f")
    op = uc.ChromeOptions()
    op.add_argument("--window-size=%s" % WINDOW_SIZE)
    op.add_argument(f"--user-data-dir={UserDataDirectory}")
    op.add_argument(f"--profile-directory=Profile {ProfileNum}")
    # create new chrome tab with load chrome profile dir
    global browser
    browser = uc.Chrome(options=op)
    # send from chrome console browser.execute_script("console.log(`Hello from Python`)")
    # zoom out by 50% browser.execute_script("document.body.style.zoom='50%'")


def launchURL(url, Scale):
    print(url, "url")
    if browser != "":
        print(browser)
        browser.get(url)
        browser.execute_script(f"document.body.style.zoom='{Scale}%'")
        print(len(browser.window_handles), "handles")
    else:
        print("no chrome driver use setup before launch")


def ConnectMetamask(password):
    while not Check_exists_by_element("id", "password", False, ""):
        # do not remove this prints
        print(Check_exists_by_element("id", "password", False, password))
        print(Check_exists_by_element("css", "#app-content > div > div.main-container-wrapper > div > div > button", True, ""), "ConnectMetamask")
        time.sleep(1)




def Check_exists_by_element(typeElement, xpath, click, Skeys):
    if typeElement == "xpath":
        try:
            a = browser.find_element(By.XPATH, xpath)
            if click:
                a.click()
            if Skeys != '':
                a.send_keys(Skeys)
        except NoSuchElementException:
            return False
        return True
    if typeElement == "text":
        try:
            a = browser.find_element(By.LINK_TEXT, xpath)
            if click:
                a.click()
            if Skeys != '':
                a.send_keys(Skeys)
        except NoSuchElementException:
            return False
        return True
    if typeElement == "tag":
        try:
            a = browser.find_element(By.TAG_NAME, xpath)
            if click:
                a.click()
            if Skeys != '':
                a.send_keys(Skeys)
        except NoSuchElementException:
            return False
        return True
    if typeElement == "class":
        try:
            a = browser.find_element(By.CLASS_NAME, xpath)
            if click:
                a.click()
            if Skeys != '':
                a.send_keys(Skeys)
        except NoSuchElementException:
            return False
        return True
    if typeElement == "css":
        try:
            a = browser.find_element(By.CSS_SELECTOR, xpath)
            if click:
                if a:
                    a.click()
            if Skeys != '':
                a.send_keys(Skeys)
        except NoSuchElementException:
            return False
        return True
    if typeElement == "id":
        try:
            a = browser.find_element(By.ID, xpath)
            if click:
                a.click()
            if Skeys != '':
                a.send_keys(Skeys)
        except NoSuchElementException:
            return False
        return True


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
    while not Check_exists_by_element("css",
                                      "#app-content > div > div.main-container-wrapper > div > div.request-signature__footer > button.button.btn--rounded.btn-primary.btn--large.request-signature__footer__sign-button",
                                      True, ""):
        while not Check_exists_by_element("css",
                                          "#app-content > div > div.main-container-wrapper > div > div.request-signature__footer > button.button.btn--rounded.btn-primary.btn--large.request-signature__footer__sign-button",
                                          True, ""):
            print(Check_exists_by_element("css",
                                          "#app-content > div > div.main-container-wrapper > div > div.request-signature__footer > button.button.btn--rounded.btn-primary.btn--large.request-signature__footer__sign-button",
                                          True, ""), "SignInMetamask")
            time.sleep(2)
