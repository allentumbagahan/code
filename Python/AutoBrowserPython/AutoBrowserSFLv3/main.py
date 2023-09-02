import time
import undetected_chromedriver as uc
from selenium.webdriver.common.by import By
from selenium.common.exceptions import NoSuchElementException
import threading
from SRC import MoreFunctions
b = 10
UserDataDirectory = "C:\\Users\\allen\AppData\\Local\\Google\\Chrome\\User Data"
WINDOW_SIZE = "50,200"
Alias1 = ['34', '2', '6', '8', '10', '12', '9', '13', '14', '16', '17', '20', '19', '21', '22', '25', '26', '27',
          '28',
          '31', '33', '36', '37', '38', '39', '40', '41', '42', '43']
loadProfile = Alias1[b - 1]

op = uc.ChromeOptions()
op.add_argument(
    "--window-size=%s" % WINDOW_SIZE)
op.add_argument(f"--user-data-dir={UserDataDirectory}")
op.add_argument(f"--profile-directory=Profile {loadProfile}")
print(loadProfile)

