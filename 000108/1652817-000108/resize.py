import os
import cv2

files = os.listdir()
for file in files:
    if ".png" in file:
        img = cv2.imread(file)
        img = cv2.resize(img, (960, 515))
        cv2.imwrite(r"D:\Courses\Fall 2018\shenjian-network\000108/" + file, img)