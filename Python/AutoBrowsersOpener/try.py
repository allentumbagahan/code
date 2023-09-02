import time

import undetected_chromedriver as uc
E = "C:\\Users\\allen\AppData\\Local\\Google\\Chrome\\User Data"
e = "C:\\Users\\allen\\AppData\\Local\\Google\\Chrome\\User Data\\Profile 1"
ProfileNum = 6
chrome_options = uc.ChromeOptions()
chrome_options.add_argument(f'--user-data-dir={E}')
chrome_options.add_argument(f"--profile-directory=Profile {ProfileNum}")
driver = uc.Chrome(options=chrome_options, use_subprocess=True)
print(driver)
driver.get('https://www.youtube.com/watch?v=5oxxi0d7AQI')
print("hello")
time.sleep(10000)