#-*- coding:utf-8 -*-
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

driver = webdriver.Chrome("chromedriver.exe")

userName = "adidasu"
#userName = "Hide+on+bush"
driver.get("https://www.op.gg/summoner/userName=%s"%userName)

def CommaRemover(x):
    return int(x.replace(',',''))
CR = CommaRemover

def getTeamPoint(item): # 값이 0인 경우 생략됨. 팀의 대표값을 찾기 위한 함수
    text = item.text.split('\n')
    if(len(text) == 13): # non-zero
        return text[0], CR(text[6]), CR(text[7])
    elif(len(text) == 3): # 무작위 총력전
        return text[0], 0, 0
    else:
        ret_val = text[0]
        text = text[1:]
        sumnum = 0
        i = 0
        while(True):
            sumnum += CR(text[i])
            i += 1
            if(sumnum == CR(text[i])):
                break
        return ret_val, CR(text[i]), CR(text[i+1])


if __name__ == '__main__':
    print_log = []

    # TODO: disabled인 버튼은 누르지 않게 하기
    for i in range(30):
        driver.implicitly_wait(10)

        try:
            while(driver.find_element_by_class_name("GameMoreButton").\
           find_element_by_tag_name('a').\
           get_attribute("disabled") != None):
                print("None", i)
            driver.find_element_by_class_name("GameMoreButton").click()
            print('click', i)
        except:
            print('ERROR', i)
        finally:
            pass

    warps = driver.find_elements_by_class_name("GameItemWrap")
    
    print_log.append("********** REPORT **********")
    print_log.append('userName: '+userName)
    print_log.append("Data length: %d"%len(warps))
    print_log.append('  **** format ****')
    print_log.append('gameType')
    print_log.append("챔피언 처치")
    print_log.append("골드 획득량")
    print_log.append("챔피언에게 가한 피해량")
    print_log.append("와드 설치")
    print_log.append("받은 피해량")
    print_log.append("CS")
    print_log.append("="*40)

    print('program init finish')
    print('len:', len(warps))

    for warp in warps:
        print('\n',warps.index(warp), sep='', end=' ')
        print_log.append("[%d]"%warps.index(warp))
        print_log.append(warp.find_element_by_class_name("GameType").text)

        if(warp.find_element_by_class_name("GameResult").text == "다시하기"):
            print_log.append('** 다시하기 **')
            print_log.append("="*20)
            continue

        try:
            element = WebDriverWait(warp, 10).until(
                EC.presence_of_element_located((By.ID, "right_match")))
        finally:
            warp.find_element_by_id("right_match").click()
            print('RM',end=' ')
        
        try:
            element = WebDriverWait(warp, 10).until(
                EC.presence_of_element_located((By.ID, "right_match_team")))
        finally:
            warp.find_element_by_id("right_match_team").click()
            print('RMT',end=' ')

        try:
            element = WebDriverWait(warp, 10).until(
                EC.presence_of_element_located((By.CLASS_NAME, "MatchAnalysisListItem")))
        finally:
            for item in warp.find_elements_by_class_name("MatchAnalysisListItem"):
                TeamPoint = getTeamPoint(item)
                print_log.append("%s %s"%(TeamPoint[1], TeamPoint[2]))
            print('point',end='')

        print_log.append("="*20)

    print('\n\n')

    f = open("GameData.txt", 'w')
    for x in print_log:
        f.write(x)
        f.write('\n')
        #print(x)
    f.close()


