i = input()
B = [i]  # change this as array


def main(p2):
    import time
    from SRC import MoreFunctions
    import threading
    A = "C:\\Users\\allen\AppData\\Local\\Google\\Chrome\\User Data"
    G = 29  # max umber of profile
    print(f'Enter Profile: 1 to {G}')
    C = "200,350"
    D = "https://sunflower-land.com/play/"
    E = 'chrome-extension://nkbihfbeogaeaoehlefnkodbefgpgknn/popup.html'
    p = "Tumbagahan0"
    F = 50
    Alias1 = ['34', '2', '6', '8', '10', '12', '9', '13', '14', '16', '17', '20', '19', '21', '22', '25', '26', '27',
              '28',
              '31', '33', '36', '37', '38', '39', '40', '41', '42', '43']
    a = True
    while a:
        if B != 0:
            b = int(p2)
            a = False
            MoreFunctions.SetupChrome(C, A, Alias1[b - 1], b)
            task0 = threading.Thread(target=MoreFunctions.launchURL, args=(E, F))
            task1 = threading.Thread(target=MoreFunctions.ConnectMetamask, args=(p,))
            task0.start()
            task0.join()
            task1.start()
            task1.join()
            print("next")
            MoreFunctions.launchURL(D, F)
            time.sleep(2)
            MoreFunctions.SignIn()
            task2 = threading.Thread(target=MoreFunctions.SignInMetamask)
            task2b = threading.Thread(target=MoreFunctions.ConnectingSFL)
            task3 = threading.Thread(target=MoreFunctions.GetSFLData)
            task4 = threading.Thread(target=MoreFunctions.GetSFLData2)
            task5 = threading.Thread(target=MoreFunctions.InputLog)
            task6 = threading.Thread(target=MoreFunctions.GetSFLData3)
            task7 = threading.Thread(target=MoreFunctions.update)
            crazycursor = threading.Thread(target=MoreFunctions.CrazyCursorTaskThreading)
            # task8 = threading.Thread(target=MoreFunctions.OpenShop)
            task2.start()
            task2b.start()
            time.sleep(2)
            task7.start()
            task3.start()
            task4.start()
            crazycursor.start()
            task5.start()
            task6.start()
            # task8.start()
            OT = 1
            while True:
                Rest = MoreFunctions.restart()
                if Rest:
                    if len(B) > 0:
                        if OT == 1:
                            print(B)
                            OT -= 1
                            MoreFunctions.StartAgain()
                            main(B.pop())
                time.sleep(1)


main(B.pop())
