'''
blue = [110, 50, 50] to [130,255,255]

'''
import numpy as np
import cv2

#import serial
import time

#ser = serial.Serial('/dev/ttyACM0',19200)

#Function for converting co ordinates to 3 digit strings
def check(x,y,h,w):
    if(x>=290 and x <= 310 and y>=267 and y<=287 and h >= 274 and h<=294 and w>= 147 and w<=167):
        return "1"
    return "0"
def process(x,y):
	x = str(x)
	y = str(y)
	temp = ""
	t = 3 - len(x)
	while(t>0):
		temp+= '0'
		t -= 1
	temp += x + "z"
	t = 3 - len(y)
	while(t>0):
		temp+='0'
		t -= 1
	temp += y
	
	return temp + "z"
	
	
#A code for color detection in Autonomous Garbage Collector

colors = {} 						# a collection of range of HSV values for given range of colors. 
colors["blue"] = [[110,50,50],[130,255,255]] 				#for each color the lower and upper bound is the range of HSV values for detection of the color	
colors["yellow"] = [[20,80,80],[40,255,255]]				
colors["greeen"] = [[33,80,40],[102,255,255]]
colors["all"] = [[20,50,40],[130,255,255]]

#f = open("output.txt","w")         #For writing into a file . Un comment this and also the line where *** is there        

cap = cv2.VideoCapture(1)
center_x = 0
center_y = 0
while(True):
	_,im = cap.read()
	hsv_img = cv2.cvtColor(im, cv2.COLOR_BGR2HSV)
	COLOR_MIN = np.array(colors["yellow"][0],np.uint8)
	COLOR_MAX = np.array(colors["yellow"][1],np.uint8)
	frame_threshed = cv2.inRange(hsv_img, COLOR_MIN, COLOR_MAX)
	imgray = frame_threshed
	ret,thresh = cv2.threshold(frame_threshed,127,255,0)
	contours, hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
# Find the index of the largest contour
	areas = [cv2.contourArea(c) for c in contours]
	if(areas!=[]):	
		max_index = np.argmax(areas)
		cnt=contours[max_index]
		x,y,w,h = cv2.boundingRect(cnt)
		cv2.rectangle(im,(x,y),(x+w,y+h),(0,255,0),2)
	        center_x = (x+(w/2))
                center_y = (y+(h/2))
                print process(center_x, center_y) + " "+ str(h) + " " + str(w)
                print check(center_x,center_y,h,w)
                #ser.write(check(center_x,center_y,h,w)) 
                time.sleep(0.5)               
		#f.write(process(center_x,center_y))          #              ***
                cv2.imshow("Show",im)
	cv2.waitKey(10)
cv2.destroyAllWindows()
