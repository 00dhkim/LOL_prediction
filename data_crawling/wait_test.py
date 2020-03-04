from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
driver = webdriver.Chrome("chromedriver.exe")
driver.get("https://www.op.gg/summoner/userName=hide+on+bush")

warp = driver.find_element_by_class_name("GameItemWrap")
warp.find_element_by_id("right_match").click()
#driver.implicitly_wait(10)
try:
    element = WebDriverWait(driver, 10).until(
        EC.presence_of_element_located((By.ID, "right_match_team")))
    print("waited")
finally:
    warp.find_element_by_id("right_match_team").click()
