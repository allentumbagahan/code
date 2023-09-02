import time
import undetected_chromedriver as uc
from selenium.webdriver.common.by import By

UserDataDirectory = "C:\\Users\\allen\AppData\\Local\\Google\\Chrome\\User Data"
ProfileNum = 'Profile 34'
options = uc.ChromeOptions()
# prefs = {'exit_type': 'none'}
# options.add_experimental_option("prefs", {'profile': prefs})
options.add_argument('--window-size=800,600')
options.add_argument('--disable-tracking')
options.add_argument(f"--profile-directory={ProfileNum}")
driver = uc.Chrome(options=options, version_main=113, user_data_dir=UserDataDirectory, browser_executable_path='C:\Program Files\Google\Chrome\Application\chrome.exe')
driver.get('chrome-extension://nkbihfbeogaeaoehlefnkodbefgpgknn/popup.html#')
time.sleep(5)
elem1 = driver.find_element(By.ID, "password")
print("found pass element")
elem1.send_keys('Tumbagahan')
driver.execute_script(
    "document.getElementsByClassName('button btn--rounded btn-default')[0].click()")
print("found element")
time.sleep(99999)